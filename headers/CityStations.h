#include <stdlib.h>
#include "BikeStation.h"

#ifndef _city_stations_h
#define _city_stations_h

typedef struct CityStationsCDT * CityStations;

/**
 * creates a CityStations
 * 
 * @return CityStations ADT, NULL if an error ocurred
 */
CityStations newCityStations(void);

/**
 * frees the memory allocated for the CityStations ADT
 * 
 * @param city CityStations ADT
 */
void freeCityStations(CityStations city);

/**
 * returns the number of stations in the city
 * 
 * @param city CityStations ADT
 * @return number of stations in the city
 */
size_t getStationsCount(CityStations city);


// To replace addStation -- binary trees needed
/**
 * adds a station to the city
 * 
 * @param city CityStations TAD
 * @param station_info station to add
 * @return 0 if the station was added, 1 if an error ocurred
 */
int loadStation(CityStations city, const char * station_info);

/**
 * adds a trip to the city
 * 
 * @param city CityStations ADT
 * @param trip_info trip to add
 * @return 0 if the trip was added, 1 if an error ocurred
 */
int processTrip(CityStations city, const char *trip_info);

/**
 * returns the station with the given id
 * 
 * @param city CityStations ADT
 * @param id id of the station
 * @return station with the given id, NULL if it doesn't exist
 */
BikeStation getStation(CityStations city, size_t id);

/**
 * increments the number of started trips in the given date
 * 
 * @param city CityStations ADT
 * @return void
 */
void incrementStartedTripsByDate(CityStations city, char date[DATE_LEN]);

/**
 * increments the number of ended trips in the given date
 * 
 * @param city CityStations ADT
 * @return void
 */
void incrementEndedTripsByDate(CityStations city, char date[DATE_LEN]);

/**
 * returns the number of started trips in the given date
 * 
 * @param city CityStations ADT
 * @return void
 */
void orderStationsByTrips(CityStations city);

/**
* set the iterator to the first station in the city, in alphabetic order
* 
* @param city CityStations ADT
* @return void
*/
void toBeginAlphabeticOrder(CityStations city);

/**
 * checks if there is a next station in alphabetic order
 * 
 * @param city CityStations ADT
 * @return 1 if there is a next station, 0 otherwise
 */
int hasNextAlphabeticOrder(CityStations city);

/**
 * returns the next station in alphabetic order
 * 
 * @param city CityStations ADT
 * @return next station
 */
BikeStation nextAlphabeticOrder(CityStations city);


/**
 * set the iterator to the first station in the city, in increasing order of started trips
 * 
 * @param city CityStations ADT
 * @return void
 */
void toBeginTripsOrder(CityStations city);

/**
 * checks if there is a next station in increasing order of started trips
 * 
 * @param city CityStations ADT
 * @return 1 if there is a next station, 0 otherwise
 */
int hasNextTripsOrder(CityStations city);

/**
 * returns the next station in increasing order of started trips
 * 
 * @param city CityStations ADT
 * @return next station
 */
BikeStation nextTripsOrder(CityStations city);


#endif