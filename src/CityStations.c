#include "CityStations.h"
#include "BikeStation.h"

// HELPERS
#include "recalloc.h"
#include "FileHandler.h"
#include "constants.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>

#ifdef MON
static const int fields_station[NUMBER_OF_FIELDS_S] = {ID, NAME, LATITUDE, LONGITUDE};
static const int fields_trips[NUMBER_OF_FIELDS_T] = {START_DATE, START_STATION_ID, END_DATE, END_STATION_ID, IS_MEMBER};
#elif defined(NYC)
static const int fields_station[NUMBER_OF_FIELDS_S] = {NAME, LATITUDE, LONGITUDE, ID};
static const int fields_trips[NUMBER_OF_FIELDS_T] = {START_DATE, START_STATION_ID, END_DATE, END_STATION_ID, RIDEABLE_TYPE, IS_MEMBER};
#else
#error "No city was specified on build target"
#endif

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
    size_t started_trips_by_day[7];
    size_t ended_trips_by_day[7];
    List stations_by_name;
    BikeStation *stations_by_trips;
    size_t stations_max_length;
    size_t stations_count;
} CityStationsCDT;

// static void orderStationsByTrips(CityStations new);

static List addRecursive(List list, BikeStation station);
/**
 * adds a station to the city
 * 
 * @param city CityStations TAD
 * @param station station to add
 * @note the station isn't copied, the TAD will keep a reference to it
 * @return 0 if the station was added, 1 if an error ocurred
 */
static int addStation(CityStations city, BikeStation station);

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

    BikeStation new = newBikeStation(id, name);

    if (new == NULL)
        return ERROR;

    setLatitude(new, latitude);
    setLongitude(new, longitude);

    if (addStation(city, new) == ERROR)
        return ERROR;

    return 0;
}

static List addRecursive(List list, BikeStation station)
{
    if (list == NULL || compareStationsByName(list->station, station) < 0)
    {
        List new = malloc(sizeof(Node));
        new->station = station;
        new->next = list;
        return new;
    }
    list->next = addRecursive(list->next, station);
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
        if (city->stations == NULL)
            return ERROR;
        city->stations_max_length = id + BLOCK_STATION;
    }

    city->stations[id] = station;

    city->stations_by_name = addRecursive(city->stations_by_name, station);
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
    free(city);
}

int processTrip(CityStations city, const char *trip_info)
{
    // TODO
    // - open trips file and count for each station and day of the week the trips made
    // - save the first trip made for each station
    //

    // TODO
    //  - saves the amount of trips per station and the first one made
    //  	- checks if both the starting and returning stations are in stations
    //  	- if not, it ignores them
    //  	- checks if the trip starts and ends at the same station
    //  	- if it does, it's not considered when checking for the oldest trip
    //  - saves the amount of trips per day
    //  	- increments the position by one in the coresponding day

    if (city == NULL)
        return ERROR;

    if (trip_info == NULL)
        return ERROR;

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
            start_date[20] = '\0';
#endif
            break;
        case START_STATION_ID:
            start_station_id = strtoul(field, NULL, 10);
            break;
        case END_DATE:
            end_date = field;
#ifdef NYC
            end_date[20] = '\0';
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

//  void orderStationsByTrips(CityStations new)
// {
//     // TODO:
//     //  - sort the stations list by number of trips
// }

void incrementStartedTripsByDate(CityStations city, char date[DATE_LEN])
{
    struct tm date_time = {0};
    if (strptime(date, "%Y-%m-%d", &date_time) == NULL) // %H:%M:%S
        printf("Error incrementing ended trips by date\n");

    city->started_trips_by_day[date_time.tm_wday]++;
}

void incrementEndedTripsByDate(CityStations city, char date[DATE_LEN])
{
    struct tm date_time = {0};

    if (strptime(date, "%Y-%m-%d", &date_time) == NULL) // %H:%M:%S
        printf("Error incrementing ended trips by date\n");
    city->ended_trips_by_day[date_time.tm_wday]++;
}
