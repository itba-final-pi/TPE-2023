#include "../headers/CityStations.h"
#include "../headers/BikeStation.h"

#include <stdio.h>
#include <stdlib.h>

#define BLOCK_STATION 1000

#define ERROR 1

#define LINE_SIZE 255
#define DELIM ";"

typedef enum {ID = 0, NAME, LATITUDE, LONGITUDE} Fields;


static int _loadStations(CityStations city, const char * stations_path);
static void _processTrips(CityStations city, const char * trips_path);
static void _orderStationsByTrips(new);

List add(List list, BikeStation station){
    Node * new = malloc(sizeof(Node));
    new->station = station;
    new->next = list;
    return new;
}

typedef struct node{
    BikeStation station;
    struct node * next;
}Node;

typedef Node * List;

typedef struct CityStationsCDT{
    BikeStation * stations;
    size_t trips_by_day[7];
    // TODO: add list of stations sorted by alphabetical order
    List stations_by_name;
    // TODO: add vec of stations sorted by number of trips
    List stations_by_trips; // ? Not Sure
    size_t stations_length;
    size_t stations_count;
}CityStationsCDT;

CityStations newCityStations(const char * stations_path,const char * trips_path){
    CityStations new = calloc(1, sizeof(CityStationsCDT));
    if(_loadStations(new, stations_path) == ERROR){
        freeCityStations(new);
        return NULL;
    }
    _processTrips(new, trips_path);
    _orderStationsByTrips(new);
    return new;
}

static int _loadStations(CityStations city, const char * stations_path){
    // TODO
    // - open stations file and load the stations in a vector of BikeStation
    // - sort a list by alphabetical order

    FILE *fp;
    char LINE[LINE_SIZE];

    fp = fopen(stations_path, "r");
    if (fp == NULL)
        return ERROR;
    city->stations = calloc(BLOCK_STATION, sizeof(BikeStation));

    if(city->stations == NULL)
        return ERROR;
    char * field;

    while (fgets(LINE, LINE_SIZE, (FILE *)fp) != NULL)
    {
        field = strtok(LINE, DELIM);
        unsigned field_index;
        int id = atoi(field);
        char * name = strtok(NULL, DELIM);
        BikeStation new = newBikeStation(id, name);
        
        for(field_index = LATITUDE; field = strtok(NULL, DELIM); field_index++)
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
        if(id >= city->stations_length)
        {
            city->stations = recalloc(city->stations, city->stations_count, (id+1) * sizeof(BikeStation));
            if(city->stations == NULL)
                return ERROR;
            city->stations_length = id+1;
        }
        city->stations[id] = new;

    }

}

static void _processTrips(CityStations city, const char * trips_path){
    // TODO
    //  - saves the amount of trips per station and the first one made
    //  - saves the amount of trips per day
}

static void _orderStationsByTrips(new){
    // TODO:
    //  - sort the stations list by number of trips
}