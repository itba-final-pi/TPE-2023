#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#include "CityStations.h"
#include "FileHandler.h"
#include "htmlTable.h"
#include "csvTable.h"
#include "constants.h"
#include "loadStations.h"
#include "processTrips.h"

#define QUERY_1_OUTPUT_FILE "query1"
#define QUERY_2_OUTPUT_FILE "query2"
#define QUERY_3_OUTPUT_FILE "query3"

#define QUERY_1_COLUMNS 4
#define QUERY_2_COLUMNS 3
#define QUERY_3_COLUMNS 3

#define QUERY_1_HEADERS "bikeStation", "memberTrips", "casualTrips", "allTrips"
#define QUERY_2_HEADERS "bikeStation", "bikeEndStation", "oldestDateTime"
#define QUERY_3_HEADERS "weekDay", "startedTrips", "endedTrips"

#define QUERY_1_ERROR "ERROR: Couldn't complete Query 1"
#define QUERY_2_ERROR "ERROR: Couldn't complete Query 2"
#define QUERY_3_ERROR "ERROR: Couldn't complete Query 3"

#define HANDLE_ERROR(condition, message) if(condition) { printf("%s\n", message); return 0; }

static const char *week_day_names[NUMBER_OF_WEEK_DAYS] = {
		"Monday",
		"Tuesday",
		"Wednesday",
		"Thursday",
		"Friday",
		"Saturday",
		"Sunday"
};


int main(int argc, char *argv[])
{

		HANDLE_ERROR(argc != 3, "ERROR: Invalid arguments. Usage: ./bikeSharing<CITY> <bikes_file> <stations_file>");

		// Reset errno
		errno = 0;

		char * trips_path = argv[1];
		char * stations_path = argv[2];

		htmlTable html_table; 
		csvTable csv_table; 

		CityStations city_stations = newCityStations();
		HANDLE_ERROR(city_stations == NULL, "ERROR: Memory allocation error");

		loadStations(city_stations, stations_path);
		HANDLE_ERROR(errno != 0, "ERROR: Couldn't load stations");
		
		if (getStationsCount(city_stations) != 0)
		{
			processTrips(city_stations, trips_path);
			HANDLE_ERROR(errno != 0, "ERROR: Couldn't process trips");
		}
		
		orderStationsByTrips(city_stations);
		HANDLE_ERROR(errno != 0, "ERROR: Couldn't order stations by trips");

		// ---- QUERY 1 ----

		html_table = newTable( QUERY_1_OUTPUT_FILE ".html", QUERY_1_COLUMNS, QUERY_1_HEADERS );
		csv_table = newCsvTable( QUERY_1_OUTPUT_FILE ".csv", QUERY_1_COLUMNS, QUERY_1_HEADERS );
		HANDLE_ERROR(html_table == NULL || csv_table == NULL || errno != 0, "ERROR: Couldn't save files");

		toBeginTripsOrder(city_stations);
		HANDLE_ERROR(errno != 0, "ERROR: Couldn't start reading stations in trips order");
		while(hasNextTripsOrder(city_stations)) 
		{
				BikeStation station = nextTripsOrder(city_stations);
				HANDLE_ERROR(errno != 0, QUERY_1_ERROR);
				
				char * name = getName(station);
				char member_trips[SIZE_T_CHAR_LEN];
				char casual_trips[SIZE_T_CHAR_LEN];
				char all_trips[SIZE_T_CHAR_LEN];

				sprintf(member_trips, "%zu", getMemberTrips(station));
				sprintf(casual_trips, "%zu",  getCasualTrips(station));
				sprintf(all_trips, "%zu", getAllTrips(station)); 

				addHTMLRow(html_table, name, member_trips, casual_trips, all_trips);
				addCsvRow(csv_table, name, member_trips, casual_trips, all_trips);
				HANDLE_ERROR(errno != 0, QUERY_1_ERROR);

				free(name);
		}
		HANDLE_ERROR(errno != 0, QUERY_1_ERROR);

		closeHTMLTable(html_table);
		closeCsvTable(csv_table);
		HANDLE_ERROR(errno != 0, "ERROR: Couldn't close files");


		// ---- QUERY 2 ----

		html_table = newTable( QUERY_2_OUTPUT_FILE ".html", QUERY_2_COLUMNS, QUERY_2_HEADERS );
		csv_table = newCsvTable( QUERY_2_OUTPUT_FILE ".csv",  QUERY_2_COLUMNS, QUERY_2_HEADERS );
		HANDLE_ERROR(html_table == NULL || csv_table == NULL || errno != 0, "ERROR: Couldn't save files");

		toBeginAlphabeticOrder(city_stations);
		HANDLE_ERROR(errno != 0, "ERROR: Couldn't start reading stations in alphabetic order");
		while(hasNextAlphabeticOrder(city_stations)) 
		{
				BikeStation station = nextAlphabeticOrder(city_stations);
				BikeStation oldest_end_station = getOldestTripEndStation(station);
				HANDLE_ERROR(errno != 0, QUERY_2_ERROR);

				if(oldest_end_station == NULL) 
						// The station has no trips, so no trip is the oldest.
						continue;

				char * name = getName(station);
				char * end_station_name = getName(oldest_end_station);
				char * date = getOldestTripDate(station);
				HANDLE_ERROR(errno != 0, QUERY_2_ERROR);

				// Format the output date
				struct tm date_time;
				strptime(date, "%Y-%m-%d %H:%M:%S", &date_time);
				strftime(date, DATE_LEN, "%d/%m/%Y %H:%M", &date_time);

				addHTMLRow(html_table, name, end_station_name, date);
				addCsvRow(csv_table, name, end_station_name, date);
				HANDLE_ERROR(errno != 0, QUERY_2_ERROR);

				free(name);
				free(end_station_name);
				free(date);
		}
		HANDLE_ERROR(errno != 0, QUERY_2_ERROR);
		closeHTMLTable(html_table);
		closeCsvTable(csv_table);
		HANDLE_ERROR(errno != 0, "ERROR: Couldn't close files");


		// ---- QUERY 3 ----

		html_table = newTable( QUERY_3_OUTPUT_FILE ".html", QUERY_3_COLUMNS, QUERY_3_HEADERS );
		csv_table = newCsvTable( QUERY_3_OUTPUT_FILE ".csv", QUERY_3_COLUMNS, QUERY_3_HEADERS );
		HANDLE_ERROR(html_table == NULL || csv_table == NULL || errno != 0, "ERROR: Couldn't save files");

		WeekDays day;
		for(day=MONDAY; day < NUMBER_OF_WEEK_DAYS; day++){
				char started_trips[SIZE_T_CHAR_LEN];
				char ended_trips[SIZE_T_CHAR_LEN];

				sprintf(started_trips, "%zu", getStartedTripsByDay(city_stations, day));
				sprintf(ended_trips, "%zu",  getEndedTripsByDay(city_stations, day));

				addHTMLRow(html_table, week_day_names[day], started_trips, ended_trips);
				addCsvRow(csv_table, week_day_names[day], started_trips, ended_trips);
				HANDLE_ERROR(errno != 0, QUERY_3_ERROR);
		}
		closeHTMLTable(html_table);
		closeCsvTable(csv_table);
		HANDLE_ERROR(errno != 0, "ERROR: Couldn't close files");


		freeCityStations(city_stations);
		HANDLE_ERROR(errno != 0, "ERROR: Couldn't free resources");

		return 0;
}


