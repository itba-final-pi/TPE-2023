#include "CityStations.h"
#include "BikeStation.h"

// HELPERS
#include "recalloc.h"
#include "FileHandler.h"
#include "constants.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <time.h>

#ifdef MON
static const int fields_station[NUMBER_OF_FIELDS_STATIONS] = {ID, NAME, LATITUDE, LONGITUDE};
static const int fields_trips[NUMBER_OF_FIELDS_TRIPS] = {START_DATE, START_STATION_ID, END_DATE, END_STATION_ID, IS_MEMBER};
#elif defined(NYC)
static const int fields_station[NUMBER_OF_FIELDS_STATIONS] = {NAME, LATITUDE, LONGITUDE, ID};
static const int fields_trips[NUMBER_OF_FIELDS_TRIPS] = {START_DATE, START_STATION_ID, END_DATE, END_STATION_ID, RIDEABLE_TYPE, IS_MEMBER};
#else
#error "No city was specified on build target"
#endif

// Fix tm_wday values, since they start on Sunday. Recives a struct tm 
#define GET_WEEK_DAY(date) date.tm_wday - 1 > 0 ? date.tm_wday - 1 : NUMBER_OF_WEEK_DAYS - 1

// TODO: evaluate reallocating in blocks
#define BLOCK_STATION 600

#define LINE_SIZE 255
#define DELIM ";"

typedef struct node
{
    BikeStation station;
    struct node *next;
} Node;

typedef Node *List;

typedef struct CityStationsCDT
{
    BikeStation *stations;
    size_t started_trips_by_day[NUMBER_OF_WEEK_DAYS];
    size_t ended_trips_by_day[NUMBER_OF_WEEK_DAYS];
    List stations_by_name;
    List current_station_by_name;
    List stations_by_trips;
    List current_station_by_trips;
    size_t stations_max_length;
    size_t stations_count;
} CityStationsCDT;


//TODO: REFACTOR THIS(scoped functions)
typedef int (*compareStations)(BikeStation, BikeStation);

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
static void incrementStartedTripsByDate(CityStations city, char date[DATE_LEN]);

/**
 * increments the number of ended trips in the given date
 * 
 * @param city CityStations ADT
 * @return void
 */
static void incrementEndedTripsByDate(CityStations city, char date[DATE_LEN]);

CityStations newCityStations(void)
{
    CityStations new = calloc(1, sizeof(CityStationsCDT));

    if (new == NULL)
        return NULL;

    return new;
}

int loadStation(CityStations city, const char *station_info)
{
    unsigned field_index;
    size_t id;
    char *name;
    double latitude, longitude;

    char *field = strtok((char *)station_info, DELIM);
    // Iterate over the columns on the file
    for (field_index = ID; field; field_index++, field = strtok(NULL, DELIM))
    {
        switch (fields_station[field_index])
        {
        case ID:
            id = strtoul(field, NULL, 10);
            break;
        case NAME:
            name = field;
            break;
        case LATITUDE:
            latitude = atof(field);
            break;
        case LONGITUDE:
            longitude = atof(field);
            break;
        default:
            break;
        }
    }

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

    if (id >= city->stations_max_length)
    {
        city->stations = recalloc(city->stations, city->stations_max_length * sizeof(BikeStation), (id + BLOCK_STATION) * sizeof(BikeStation));
        if (city->stations == NULL || errno == ENOMEM)
                return ERROR;
        city->stations_max_length = id + BLOCK_STATION;
    }

    city->stations[id] = station;

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
    return city->stations[id];
}

void freeCityStations(CityStations city)
{
    size_t i;
    for (i = 0; i < city->stations_max_length; i++)
        if (city->stations[i] != NULL)
            freeStation(city->stations[i]);
    free(city->stations);
    List aux;
    while (city->stations_by_name != NULL)
    {
        aux = city->stations_by_name;
        city->stations_by_name = city->stations_by_name->next;
        free(aux);
    }
    while (city->stations_by_trips != NULL)
    {
        aux = city->stations_by_trips;
        city->stations_by_trips = city->stations_by_trips->next;
        free(aux);
    }
    free(city);
}

int processTrip(CityStations city, const char *trip_info)
{
    if (city == NULL || trip_info == NULL)
    {
        errno = EINVAL;
        return ERROR;
    }

    char *field;
    unsigned field_index;
    char *start_date;
    char *end_date;
    size_t start_station_id;
    size_t end_station_id;
    size_t is_member; // ! TODO: Make it work for NYC

    field = strtok((char*) trip_info, DELIM);
    for (field_index = START_DATE; field; field_index++, field = strtok(NULL, DELIM))
    {
        switch (fields_trips[field_index])
        {
        case START_DATE:
            start_date = field;
#ifdef NYC
            start_date[DATE_LEN-1] = '\0';
#endif
            break;
        case START_STATION_ID:
            start_station_id = strtoul(field, NULL, 10);
            break;
        case END_DATE:
            end_date = field;
#ifdef NYC
            end_date[DATE_LEN-1] = '\0';
#endif
            break;
        case END_STATION_ID:
            end_station_id = strtoul(field, NULL, 10);
            break;
        case IS_MEMBER:
            is_member = strtoul(field, NULL, 10);
            break;
        default:
            break;
        }
    }

    // Now that the values are saved on vars, set the structs:

    BikeStation start_station = city->stations[start_station_id];
    BikeStation end_station = city->stations[end_station_id];

    // Both stations should exist in our struct
    if (start_station && end_station)
    {
        // Checks that the trip is not circular and the date is older
        if (start_station_id != end_station_id && isOlderTrip(start_station, start_date))
        {
            setOldestTrip(start_station, end_station, start_date);
        }
        if (is_member)
        {
            incrementMemberTrips(start_station);
        }
        else
        {
            incrementCasualTrips(start_station);
        }
        incrementStartedTripsByDate(city, start_date);
        incrementEndedTripsByDate(city, end_date);
    }

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

static void incrementStartedTripsByDate(CityStations city, char date[DATE_LEN])
{
    struct tm date_time = {0};
    if (strptime(date, "%Y-%m-%d", &date_time) == NULL || errno == EINVAL) // %H:%M:%S
            return;

    city->started_trips_by_day[GET_WEEK_DAY(date_time)]++;
}

static void incrementEndedTripsByDate(CityStations city, char date[DATE_LEN])
{
    struct tm date_time = {0};
    if (strptime(date, "%Y-%m-%d", &date_time) == NULL || errno == EINVAL) // %H:%M:%S
        return;

    city->ended_trips_by_day[GET_WEEK_DAY(date_time)]++;
}

void orderStationsByTrips(CityStations city)
{
    size_t i;
    int error = OK;
    for (i = 0; i < city->stations_max_length && !error; i++)
    {
        if (city->stations[i] != NULL)
        {
            city->stations_by_trips = addRecursive(city->stations_by_trips, city->stations[i], compareStationsByTrips, SORT_DESCENDING, &error);
        }
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
    city->current_station_by_trips = city->stations_by_trips;
}

int hasNextTripsOrder(CityStations city)
{
    return city->current_station_by_trips != NULL;
}

BikeStation nextTripsOrder(CityStations city)
{
    BikeStation station = city->current_station_by_trips->station;
    city->current_station_by_trips = city->current_station_by_trips->next;
    return station;
}

