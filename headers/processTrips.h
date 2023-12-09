#ifndef __process_trips_h_
#define __process_trips_h_

#include <stdio.h>
#include "CityStations.h"

/**
 * TODO: maybe return if some error ocurres
 *
 * Process the data from a .csv trips file into a CityStations ADT.
 * 
 * @param city CityStations ADT.
 * @param file_name The .csv file that has the data to process. 
 */
void processTrips(CityStations city_stations, char * file_name);

#endif

