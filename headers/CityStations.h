#include <stdlib.h>

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
CityStations newCityStations(const char * stations_path,const char * trips_path);

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




#endif