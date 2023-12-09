#include <stdio.h>
#include <stdlib.h>

#include "CityStations.h"
#include "FileHandler.h"
#include "htmlTable.h"
#include "constants.h"

#define QUERY_1_NAME "query1"
#define QUERY_2_NAME "query2"
#define QUERY_3_NAME "query3"


void loadStations(CityStations city_stations, char * file_name){
	FileHandler file = newFileHandler(file_name);

    char * line = getNextLine(file); // ignore header line

    while( hasNextLine(file) && (line = getNextLine(file)) ) {
        loadStation(city_stations, line);
    }
	freeFileHandler(file);
}

void loadTrips(CityStations city_stations, char * file_name){
	FileHandler file = newFileHandler(file_name);

    char * line = getNextLine(file); // ignore header line

    while( hasNextLine(file) && (line = getNextLine(file)) ) {
        processTrip(city_stations, line);
    }
	freeFileHandler(file);
}



int main(int argc, char *argv[])
{
	// TODO: see if maybe it's worth to chech things like an empty csv and such


	if(argc != 3) {
		// TODO: handle error if # of args is wrong
		printf("Usage: dale panchito\n");
		return 1;
	} 

	char * stations_path = argv[1];
	char * trips_path = argv[2];

	CityStations city_stations = newCityStations();

	loadStations(city_stations, stations_path);

	printf("Stations loaded\n");

	loadTrips(city_stations, trips_path);
	
	printf("Finished loading everything\n");

	orderStationsByTrips(city_stations);

	printf("Finished ordering by trips\n");

	// Query 1  -  total de viajes por estación, orden por cantidad
	//
	// 	nombre de estación ; cantidad de viajes de miembros ; cantidad de viajes de no miembros ; total
	//
	//	guardar csv y html (primero el html, después vemos)
	//
	//	- guardar encabezados en los archivos
	//		- creando el html
	//	- generar iterador, iterar cada elemento y guardar la línea en el html
	

	htmlTable table = newTable( QUERY_1_NAME ".html", 4, "bikeStation", "memberTrips", "casualTrips", "allTrips");

	toBeginTripsOrder(city_stations);
	while(hasNextTripsOrder(city_stations)) 
	{
		BikeStation station = nextTripsOrder(city_stations);

		char * name = getName(station);
		char member_trips[SIZE_T_CHAR_LEN];
		char casual_trips[SIZE_T_CHAR_LEN];
		char all_trips[SIZE_T_CHAR_LEN];

		sprintf(member_trips, "%zu", getMemberTrips(station));
		sprintf(casual_trips, "%zu",  getCasualTrips(station));
		sprintf(all_trips, "%zu", getAllTrips(station)); 

		addHTMLRow(table, name, member_trips, casual_trips, all_trips);

		free(name);
    }
    closeHTMLTable(table);
	


	// Query 2

	// Query 3	


	freeCityStations(city_stations);

    return 0;
}
