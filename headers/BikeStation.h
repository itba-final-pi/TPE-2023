#include <stdlib.h>

#ifndef _bike_stations_h
#define _bike_stations_h

#define DATE_LEN 20

typedef struct BikeStationCDT * BikeStation;

// Creates a new BikeStation
BikeStation newBikeStation(size_t id, char * name);

void freeStation(BikeStation station);

void setLatitude(BikeStation station, double latitude);

void setLongitude(BikeStation station, double longitude);

void setOldestTrip(BikeStation startStation, BikeStation endStation, char startedAt[DATE_LEN]);

void incrementMemberTrips(BikeStation station);

void incrementCasualTrips(BikeStation station);

size_t getAllTips(BikeStation station);

size_t getMemberTrips(BikeStation station);

size_t getCasualTrips(BikeStation station);

// Returns a **COPY** of the station name
char * getName(BikeStation station);

double getLatitude(BikeStation station);

double getLongitude(BikeStation station);

BikeStation getOldestTripEndStation(BikeStation station);

// Returns a **COPY** of the oldest trip starting date
char * getOldestTripDate(BikeStation station);

size_t getId(BikeStation station);

int compareStationsByName(BikeStation a, BikeStation b);

#endif
