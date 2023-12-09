#ifndef __load_stations_h_
#define __load_stations_h_

#include <stdio.h>
#include "CityStations.h"

/**
 * TODO: maybe return if some error ocurres
 *
 * Load data from a .csv stations file into a CityStations ADT.
 * 
 * @param city CityStations ADT.
 * @param file_name The .csv file that has the data to load. 
 */
void loadStations(CityStations city_stations, char * file_name);

#endif

