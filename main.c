#include <stdio.h>
#include <stdlib.h>

#include "CityStations.h"
#include "FileHandler.h"
#include "htmlTable.h"
#include "csvTable.h"
#include "constants.h"

#define QUERY_1_NAME "query1"
#define QUERY_2_NAME "query2"
#define QUERY_3_NAME "query3"

#define QUERY_1_HEADERS "bikeStation", "memberTrips", "casualTrips", "allTrips"

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
		printf("Error: Wrong amount of arguments provided\n");
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

	htmlTable html_table = newTable( QUERY_1_NAME ".html", 4, QUERY_1_HEADERS );
	csvTable csv_table = newCsvTable( QUERY_1_NAME ".csv", 4, QUERY_1_HEADERS );

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

		addHTMLRow(html_table, name, member_trips, casual_trips, all_trips);
		addCsvRow(csv_table, name, member_trips, casual_trips, all_trips);

		free(name);
    }
    closeHTMLTable(html_table);
    closeCsvTable(csv_table);
	
	// Query 2

	// Query 3	


	freeCityStations(city_stations);

    return 0;
}
