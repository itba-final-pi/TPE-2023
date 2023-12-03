#include <stdlib.h>

#ifndef _city_stations_h
#define _city_stations_h

typedef struct CityStationsCDT * CityStations;

/**
 * creates a CityStations TAD and loads the stations and processes the trips
 * 
 * @param stations_path path to the stations file
 * @param trips_path path to the trips file 
 * @return CityStations TAD
 */
CityStations newCityStations(const char * stations_path,const char * trips_path);



#endif