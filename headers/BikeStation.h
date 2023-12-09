#include <stdlib.h>
#include "constants.h"

#ifndef _bike_stations_h
#define _bike_stations_h

typedef struct BikeStationCDT * BikeStation;

/**
 * creates a new BikeStation
 * @param id the station id
 * @param name the station name
 * @param latitude the station latitude
 * @param longitude the station longitude
 * @return the new BikeStation
 */
BikeStation newBikeStation(size_t id, char * name, double latitude, double longitude);

/**
 * frees the memory allocated for the BikeStation
 * @param station the BikeStation to free
 */
void freeStation(BikeStation station);

/**
 * sets the oldest trip of the station
 * @param startStation the station where the trip started
 * @param endStation the station where the trip ended
 * @param startedAt the date when the trip started
 */
void setOldestTrip(BikeStation startStation, BikeStation endStation, char startedAt[DATE_LEN]);

/**
 * increments the number of trips made by member users of the station 
 * @param station the station to increment the trips
 */
void incrementMemberTrips(BikeStation station);

/**
 * increments the number of trips made by casual users of the station
 * @param station the station to increment the trips
 */
void incrementCasualTrips(BikeStation station);

/**
 * returns the total number of trips of the station 
 * @param station the station to get the trips
 * @return the total number of trips of the station
 */
size_t getAllTrips(BikeStation station);

/**
 * returns the number of trips made by member users of the station 
 * @param station the station to get the trips
 * @return the number of trips made by member users of the station
 */
size_t getMemberTrips(BikeStation station);

/**
 * returns the number of trips made by casual users of the station 
 * @param station the station to get the trips
 * @return the number of trips made by casual users of the station
 */
size_t getCasualTrips(BikeStation station);

/**
 * returns the name of the station
 * @param station BikeStation ADT
 * @note is a **COPY** of the name, so it must be freed
 * @return the name of the station
 */
char * getName(BikeStation station);

/**
 * returns the latitude of the station
 * @param station BikeStation ADT
 * @return the latitude of the station
 */
double getLatitude(BikeStation station);

/**
 * returns the longitude of the station
 * @param station BikeStation ADT
 * @return the longitude of the station
 */
double getLongitude(BikeStation station);

/**
 * returns the end station of the oldest trip
 * @param station BikeStation ADT
 * @return BikeStation ADT of the end station of the oldest trip
 */
BikeStation getOldestTripEndStation(BikeStation station);

/**
 * returns the date of the oldest trip
 * @param station BikeStation ADT
 * @note is a **COPY** of the date, so it must be freed
 * @return the date of the oldest trip
 */
char * getOldestTripDate(BikeStation station);

/**
 * returns the id of the station
 * @param station BikeStation ADT
 * @return the id of the station
 */
size_t getId(BikeStation station);

/**
 * compares two stations by name, alphabetically, case insensitive
 * @param a first BikeStation ADT
 * @param b second BikeStation ADT
 * @return 0 if the name of the stations are equal, positive if the name of the first station is greater, negative otherwise
 */
int compareStationsByName(BikeStation a, BikeStation b);

/**
 * compares two stations by amount of trips
 * @param a first BikeStation ADT
 * @param b second BikeStation ADT
 * @return 0 if the id of the stations are equal, positive if the id of the first station is greater, negative otherwise
 */
int compareStationsByTrips(BikeStation a, BikeStation b);

/**
 * compares the date of the oldest trip of the station with the given date
 * @param station BikeStation ADT
 * @param date date to compare
 * @return 1 if the date of the oldest trip is older than the given date, 0 otherwise
 */
int isOlderTrip(BikeStation station, char date[DATE_LEN]);

#endif
