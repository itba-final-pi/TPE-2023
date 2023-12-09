#include "CityStations.h"
#include "BikeStation.h"
#include "BinaryTree.h"

// HELPERS
#include "recalloc.h"
#include "FileHandler.h"
#include "constants.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <time.h>


// Fix tm_wday values, since they start on Sunday. Recives a struct tm 
#define GET_WEEK_DAY(date) date.tm_wday - 1 > 0 ? date.tm_wday - 1 : NUMBER_OF_WEEK_DAYS - 1

// TODO: evaluate reallocating in blocks
#define BLOCK_STATION 600


typedef struct node
{
		BikeStation station;
		struct node *next;
} Node;

typedef Node *List;

typedef struct CityStationsCDT
{
		BinaryTree stations;
		size_t started_trips_by_day[NUMBER_OF_WEEK_DAYS];
		size_t ended_trips_by_day[NUMBER_OF_WEEK_DAYS];
		List stations_by_name;
		List current_station_by_name;
		BinaryTree stations_by_trips;
		BikeStation current_station_by_trips;
		size_t stations_max_length;
		size_t stations_count;
} CityStationsCDT;


//TODO: REFACTOR THIS(scoped functions)
typedef int (*compareStations)(const BikeStation, const BikeStation);

/**
 * adds a station to the list in order
 * 
 * @param list list to add the station to
 * @param station station to add
 * @param compare function to compare the stations
 * @param order 1 for ascending order, -1 for descending order
 * @return the new list
 */
static List addRecursive(List list, BikeStation station, compareStations compare, int order, int *error);

/**
 * adds a station to the city
 * 
 * @param city CityStations TAD
 * @param station station to add
 * @note the station isn't copied, the TAD will keep a reference to it
 * @return 0 if the station was added, 1 if an error ocurred
 */
static int addStation(CityStations city, BikeStation station);

/**
 * increments the number of started trips in the given date
 * 
 * @param city CityStations ADT
 * @return void
 */
static void incrementStartedTripsByDate(CityStations city, const char date[DATE_LEN]);

/**
 * increments the number of ended trips in the given date
 * 
 * @param city CityStations ADT
 * @return void
 */
static void incrementEndedTripsByDate(CityStations city, const char date[DATE_LEN]);

CityStations newCityStations(void)
{
		CityStations new = calloc(1, sizeof(CityStationsCDT));
        new->stations = newBinaryTree();
        new->stations_by_trips = newBinaryTree();
		if (new == NULL)
				return NULL;

		return new;
}

int loadStation(CityStations city, const size_t id, const char *name, const double latitude, const double longitude)
{
		BikeStation new = newBikeStation(id, name, latitude, longitude);
		if (new == NULL)
				return ERROR;

		if (addStation(city, new) == ERROR)
				return ERROR;

		return 0;
}

static List addRecursive(List list, BikeStation station, compareStations compare, int order, int *error)
{
		if (list == NULL || (compare(list->station, station))*order < 0)
		{
				List new = malloc(sizeof(Node));
				if (new == NULL || errno == ENOMEM)
				{
						*error = ERROR;
						return list;
				}
				new->station = station;
				new->next = list;
				return new;
		}
		list->next = addRecursive(list->next, station, compare, order, error);
		return list;
}

size_t getStationsCount(CityStations city)
{
		return city->stations_count;
}

static int addStation(CityStations city, BikeStation station)
{
		size_t id = getId(station);

		insert(city->stations, id, station);
        BikeStation aux = search(city->stations, id);
        if (aux == NULL)
                printf(">>>>>>>>>ERROR<<<<<<<<<<\n");
        
        if (id > city->stations_max_length)
        {
            city->stations_max_length = id + 100;
        }

        // ! TEMPORAL
		int error = OK;
		city->stations_by_name = addRecursive(city->stations_by_name, station, compareStationsByName, SORT_ASCENDING, &error);
		if (error == ERROR)
				return ERROR;

		city->stations_count++;
		return 0;
}

BikeStation getStation(CityStations city, size_t id)
{
		if (id >= city->stations_max_length)
				return NULL;
		return search(city->stations, id);
}

void freeCityStations(CityStations city)
{
        toBeginTreeIter(city->stations);
        BikeStation station_aux;
		while((station_aux = (BikeStation) getNextTreeElem(city->stations)) != NULL)
        {
                // BikeStation station = getNextTreeElem(city->stations);
                // freeStation(station);
                freeStation(station_aux);
        }
		freeBinaryTree(city->stations);
		List aux;
		while (city->stations_by_name != NULL)
		{
				aux = city->stations_by_name;
				city->stations_by_name = city->stations_by_name->next;
				free(aux);
		}
		while (city->stations_by_trips != NULL)
		{
				// aux = city->stations_by_trips;
				// city->stations_by_trips = city->stations_by_trips->next;
				// free(aux);
                freeBinaryTree(city->stations_by_trips);
		}
		free(city);
}

int processTrip(CityStations city, const char *start_date, const char *end_date, const size_t start_station_id, const size_t end_station_id, const int is_member)
{
		// TODO: validate that dates are valid

		if (city == NULL)
		{
				errno = EINVAL;
				return ERROR;
		}

		BikeStation start_station = search(city->stations, start_station_id);
		BikeStation end_station = search(city->stations, end_station_id);

		// Both stations should exist in our struct
		if (!start_station || !end_station)
				return 0;

		// Checks that the trip is not circular and its date is older to update oldest trip
		if (start_station_id != end_station_id && isOlderTrip(start_station, start_date)) {
				setOldestTrip(start_station, end_station, start_date);
		}

		if (is_member) 
				incrementMemberTrips(start_station);
		else 
				incrementCasualTrips(start_station);

		incrementStartedTripsByDate(city, start_date);
		incrementEndedTripsByDate(city, end_date);

		return 0;
}

size_t getStartedTripsByDay(CityStations city, WeekDays day)
{
		if (0 <= day && day >= NUMBER_OF_WEEK_DAYS)
		{
				errno = EINVAL;
				return 0;
		}
		return city->started_trips_by_day[day];
}

size_t getEndedTripsByDay(CityStations city, WeekDays day)
{
		if (0 <= day && day >= NUMBER_OF_WEEK_DAYS)
		{
				errno = EINVAL;
				return 0;
		}
		return city->ended_trips_by_day[day];
}

static void incrementStartedTripsByDate(CityStations city, const char date[DATE_LEN])
{
		struct tm date_time = {0};
		if (strptime(date, "%Y-%m-%d", &date_time) == NULL || errno == EINVAL) // %H:%M:%S
				return;

		city->started_trips_by_day[GET_WEEK_DAY(date_time)]++;
}

static void incrementEndedTripsByDate(CityStations city, const char date[DATE_LEN])
{
		struct tm date_time = {0};
		if (strptime(date, "%Y-%m-%d", &date_time) == NULL || errno == EINVAL) // %H:%M:%S
				return;

		city->ended_trips_by_day[GET_WEEK_DAY(date_time)]++;
}

void orderStationsByTrips(CityStations city)
{
		// int error = OK;
		toBeginTreeIter(city->stations);
        BikeStation station;
        while ((station = (BikeStation) getNextTreeElem(city->stations)) != NULL)
        {
            // city->stations_by_trips = addRecursive(city->stations_by_trips, station, compareStationsByTrips, SORT_DESCENDING, &error);
            // if (error == ERROR)
            //         return;
            insert(city->stations_by_trips, getAllTrips(station), station);
            printf("Inserted station %zu\n", getId(station));
        }
}

void toBeginAlphabeticOrder(CityStations city)
{
		city->current_station_by_name = city->stations_by_name;
}

int hasNextAlphabeticOrder(CityStations city)
{
		return city->current_station_by_name != NULL;
}

BikeStation nextAlphabeticOrder(CityStations city)
{
		BikeStation station = city->current_station_by_name->station;
		city->current_station_by_name = city->current_station_by_name->next;
		return station;
}

void toBeginTripsOrder(CityStations city)
{
        toBeginTreeIter(city->stations_by_trips);
}

int hasNextTripsOrder(CityStations city)
{
		return hasNextTreeElem(city->stations_by_trips);
}

BikeStation nextTripsOrder(CityStations city)
{
		return getNextTreeElem(city->stations_by_trips);
}

