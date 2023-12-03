#include "../headers/CityStations.h"
#include "../headers/BikeStation.h"

// HELPERS
#include "../headers/recalloc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: evaluate reallocating in blocks
#define BLOCK_STATION 600

#define ERROR 1

#define LINE_SIZE 255
#define DELIM ";"

typedef enum
{
    ID = 0,
    NAME,
    LATITUDE,
    LONGITUDE
} Fields;

typedef struct node
{
    BikeStation station;
    struct node *next;
} Node;

typedef Node *List;

typedef struct CityStationsCDT
{
    BikeStation *stations;
    size_t trips_by_day[7];
    // TODO: add list of stations sorted by alphabetical order
    List stations_by_name;
    // TODO: add vec of stations sorted by number of trips
    List stations_by_trips; // ? Not Sure
    size_t stations_length;
    size_t stations_count;
} CityStationsCDT;

static int _loadStations(CityStations city, const char *stations_path);
// static void _processTrips(CityStations city, const char * trips_path);
// static void _orderStationsByTrips(CityStations new);

static List _add(List list, BikeStation station);

CityStations newCityStations(const char *stations_path, const char *trips_path)
{
    printf("Loading stations...\n");
    printf("Stations path: %s\n", stations_path);
    printf("Trips path: %s\n", trips_path);
    CityStations new = calloc(1, sizeof(CityStationsCDT));
    if (_loadStations(new, stations_path) == ERROR)
    {
        freeCityStations(new);
        return NULL;
    }
    // _processTrips(new, trips_path);
    // _orderStationsByTrips(new);
    return new;
}

static int _loadStations(CityStations city, const char *stations_path)
{
    // TODO
    // - open stations file and load the stations in a vector of BikeStation
    // - sort a list by alphabetical order

    FILE *fp;
    char line[LINE_SIZE];

    fp = fopen(stations_path, "r");
    if (fp == NULL)
    {
        perror("Error opening file");
        return ERROR;
    }
    city->stations = calloc(BLOCK_STATION, sizeof(BikeStation));
    printf("Stations memory address: %p\n", (void *)city->stations);
    printf("Stations memory address[0]: %p\n", (void *)city->stations[0]);


    if (city->stations == NULL)
    {
        perror("Error allocating memory");
        return ERROR;
    }

    char *field;
    while (fgets(line, LINE_SIZE, (FILE *)fp) != NULL)
    {
        field = strtok(line, DELIM);
        unsigned field_index;
        size_t id = atoi(field);

        if (id < city->stations_length && city->stations[id] != NULL)
            // freeStation(city->stations[id]);
            continue;

        char *name = strtok(NULL, DELIM);

        BikeStation new = newBikeStation(id, name);

        for (field_index = LATITUDE; (field = strtok(NULL, DELIM)); field_index++)
        {
            switch (field_index)
            {
            case LATITUDE:
                setLatitude(new, atof(field));
                break;
            case LONGITUDE:
                setLongitude(new, atof(field));
                break;
            default:
                break;
            }
        }
        city->stations_count++;
        if (id >= city->stations_length)
        {
            city->stations = recalloc(city->stations, city->stations_length * sizeof(BikeStation) , (id + 1) * sizeof(BikeStation));
            if (city->stations == NULL)
            {
                perror("Error allocating memory for stations");
                return ERROR;
            }
            city->stations_length = id + 1;
        }
        city->stations[id] = new;

        city->stations_by_name = _add(city->stations_by_name, new);
    }
    
    if (fclose(fp) == EOF)
    {
        perror("Error closing file");
        return ERROR;
    }
    return 0;
}

static List _add(List list, BikeStation station)
{   
    if (list == NULL || compareStationsByName(list->station,station) < 0) // This is a 💎
    {
        List new = malloc(sizeof(Node));
        new->station = station;
        new->next = list;
        return new;
    }
    list->next = _add(list->next, station);
    return list;
}

void freeCityStations(CityStations city)
{
    size_t i;
    for (i = 0; i < city->stations_length; i++)
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

void printStation(CityStations city, size_t station_id)
{
    BikeStation station = city->stations[station_id];
    char * name = getName(station);
    printf("Station memory address: %p\n", (void *)station);
    printf("Station ID: %lu\n", getId(station));
    printf("Station Name: %s\n", name);
    printf("Station Latitude: %f\n", getLatitude(station));
    printf("Station Longitude: %f\n", getLongitude(station));
    free(name);
}

void printMemoryAddressStations(CityStations city)
{
    size_t i;
    for (i = 0; i < city->stations_length; i++)
        // if (city->stations[i] != NULL)
            printf("Memory Address[%lu]: %p\n", i, (void *)city->stations[i]);
}

// static void _processTrips(CityStations city, const char * trips_path){
//     // TODO
//     //  - saves the amount of trips per station and the first one made
//     //  - saves the amount of trips per day
// }

// static void _orderStationsByTrips(CityStations new){
//     // TODO:
//     //  - sort the stations list by number of trips
// }

int main(void)
{
    CityStations city = newCityStations("../temp/stationsMON.csv", "../temp/bikesMON.csv");
    printStation(city, 520);
    printMemoryAddressStations(city);
    freeCityStations(city);

    return 0;
}
