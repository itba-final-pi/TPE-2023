#include <stdlib.h>
#include "BikeStation.h"

#ifndef _city_stations_h
#define _city_stations_h

typedef struct CityStationsCDT * CityStations;

/**
 * creates a CityStations TAD and loads the stations and processes the trips
 * 
 * @param stations_path path to the stations file
 * @param trips_path path to the trips file 
 * @return CityStations TAD, NULL if an error ocurred
 */
CityStations newCityStations(const char * stations_path, const char * trips_path);

/**
 * frees the memory allocated for the CityStations TAD
 * 
 * @param city CityStations TAD
 */
void freeCityStations(CityStations city);

/**
 * returns the number of stations in the city
 * 
 * @param city CityStations TAD
 * @return number of stations in the city
 */
size_t getStationsCount(CityStations city);

/**
 * adds a station to the city
 * 
 * @param city CityStations TAD
 * @param station station to add
 * @note the station isn't copied, the TAD will keep a reference to it
 * @return 0 if the station was added, 1 if an error ocurred
 */
int addStation(CityStations city, BikeStation station);

/**
 * returns the station with the given id
 * 
 * @param city CityStations TAD
 * @param id id of the station
 * @return station with the given id, NULL if it doesn't exist
 */
BikeStation getStation(CityStations city, size_t id);

void incrementStartedTripsByDate(CityStations city, char date[DATE_LEN]);

void incrementEndedTripsByDate(CityStations city, char date[DATE_LEN]);

#endif
