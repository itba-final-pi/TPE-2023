#include "../headers/CityStations.h"
#include "../headers/BikeStation.h"

#include <stdio.h>
#include <stdlib.h>

#define INITIAL_STATIONS_LEN 1000

#define BUFF_SIZE 255
#define DELIM ";"


typedef struct CityStationsCDT{
    BikeStation ** stations;
    size_t trips_by_day[7];
    // TODO: add list of stations sorted by alphabetical order
    // TODO: add vec of stations sorted by number of trips
    size_t stations_count;
}CityStationsCDT;

CityStations newCityStations(const char * stations_path,const char * trips_path){
    CityStations new = calloc(1, sizeof(CityStationsCDT));
    _loadStations(new, stations_path);
    _processTrips(new, trips_path);
    _orderStationsByTrips(new);
    return new;
}

static void _loadStations(CityStations city, const char * stations_path){
    // TODO
    // - open stations file and load the stations in a vector of BikeStation
    // - sort a list by alphabetical order
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