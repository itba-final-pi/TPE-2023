#include <stdlib.h>

#ifndef _bike_stations_h
#define _bike_stations_h

typedef struct BikeStationCDT {
    size_t id;
    char * name;
    double latitude;
    double longitude;
    size_t memberTrips;
    size_t casualTrips;
} BikeStationCDT;

typedef BikeStationCDT * BikeStation;

#endif
