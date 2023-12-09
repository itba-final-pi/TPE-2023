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

#define QUERY_1_OUTPUT_FILE "query1"
#define QUERY_2_OUTPUT_FILE "query2"
#define QUERY_3_OUTPUT_FILE "query3"

#define QUERY_1_COLUMNS 4
#define QUERY_2_COLUMNS 3
#define QUERY_3_COLUMNS 3

#define QUERY_1_HEADERS "bikeStation", "memberTrips", "casualTrips", "allTrips"
#define QUERY_2_HEADERS "bikeStation", "bikeEndStation", "oldestDateTime"
#define QUERY_3_HEADERS "weekDay", "startedTrips", "endedTrips"



#ifdef MON
static const int fields_station[NUMBER_OF_FIELDS_STATIONS] = {ID, NAME, LATITUDE, LONGITUDE};
static const int fields_trips[NUMBER_OF_FIELDS_TRIPS] = {START_DATE, START_STATION_ID, END_DATE, END_STATION_ID, IS_MEMBER};
#define IS_MEMBER(field) (field[0] == '1')

#elif defined(NYC)
static const int fields_station[NUMBER_OF_FIELDS_STATIONS] = {NAME, LATITUDE, LONGITUDE, ID};
static const int fields_trips[NUMBER_OF_FIELDS_TRIPS] = {START_DATE, START_STATION_ID, END_DATE, END_STATION_ID, RIDEABLE_TYPE, IS_MEMBER};
#define IS_MEMBER(field) (field[0] == 'm')

#else
#error "No city was specified on build target"
#endif


static const char *week_day_names[NUMBER_OF_WEEK_DAYS] = {
		"Monday",
		"Tuesday",
		"Wednesday",
		"Thursday",
		"Friday",
		"Saturday",
		"Sunday"
};


void loadStations(CityStations city_stations, char * file_name){
		FileHandler file = newFileHandler(file_name);

		char * line = getNextLine(file); // ignore header line

		size_t id;
		char *name;
		double latitude, longitude;

		while( hasNextLine(file) && (line = getNextLine(file)) ) 
		{
				char *field = strtok((char *)line, DELIM);

				// Iterate over the columns on the file
				// fields_station has the field you are reading given it's index
				for (unsigned field_index = 0; field; field_index++, field = strtok(NULL, DELIM))
				{
						switch (fields_station[field_index])
						{
								case ID:
										id = strtoul(field, NULL, 10);
										break;
								case NAME:
										name = field;
										break;
								case LATITUDE:
										latitude = atof(field);
										break;
								case LONGITUDE:
										longitude = atof(field);
										break;
								default:
										break;
						}
				}

				loadStation(city_stations, id, name, latitude, longitude);
		}

		freeFileHandler(file);
}

void loadTrips(CityStations city_stations, char * file_name){
		FileHandler file = newFileHandler(file_name);

		char * line = getNextLine(file); // ignore header line

		char *start_date;
		char *end_date;
		size_t start_station_id;
		size_t end_station_id;
		int is_member; 

		while( hasNextLine(file) && (line = getNextLine(file)) ) {
				char *field = strtok((char*) line, DELIM);

				// Iterate over the columns on the file
				// fields_trips has the field you are reading given it's index
				for (unsigned field_index = 0; field; field_index++, field = strtok(NULL, DELIM))
				{
						switch (fields_trips[field_index])
						{
								case START_DATE:
										start_date = field;
#ifdef NYC
										start_date[DATE_LEN-1] = '\0';
#endif
										break;
								case START_STATION_ID:
										start_station_id = strtoul(field, NULL, 10);
										break;
								case END_DATE:
										end_date = field;
#ifdef NYC
										end_date[DATE_LEN-1] = '\0';
#endif
										break;
								case END_STATION_ID:
										end_station_id = strtoul(field, NULL, 10);
										break;
								case IS_MEMBER:
										is_member = IS_MEMBER(field); 
										break;
								default:
										break;
						}
				}
				processTrip(city_stations, start_date, end_date, start_station_id, end_station_id, is_member);

		}
		freeFileHandler(file);
}



int main(int argc, char *argv[])
{
		if(argc != 3) {
				// TODO: handle error if # of args is wrong
				printf("Error: Wrong amount of arguments provided\n");
				return 1;
		} 

		char * stations_path = argv[1];
		char * trips_path = argv[2];

		htmlTable html_table; 
		csvTable csv_table; 

		CityStations city_stations = newCityStations();

		loadStations(city_stations, stations_path);
		loadTrips(city_stations, trips_path);
		orderStationsByTrips(city_stations);


		// ---- QUERY 1 ----

		html_table = newTable( QUERY_1_OUTPUT_FILE ".html", QUERY_1_COLUMNS, QUERY_1_HEADERS );
		csv_table = newCsvTable( QUERY_1_OUTPUT_FILE ".csv", QUERY_1_COLUMNS, QUERY_1_HEADERS );

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


		// ---- QUERY 2 ----

		html_table = newTable( QUERY_2_OUTPUT_FILE ".html", QUERY_2_COLUMNS, QUERY_2_HEADERS );
		csv_table = newCsvTable( QUERY_2_OUTPUT_FILE ".csv",  QUERY_2_COLUMNS, QUERY_2_HEADERS );

		toBeginAlphabeticOrder(city_stations);
		while(hasNextAlphabeticOrder(city_stations)) 
		{
				BikeStation station = nextAlphabeticOrder(city_stations);
				BikeStation oldest_end_station = getOldestTripEndStation(station);

				if(oldest_end_station == NULL) 
						// The station has no trips, so no trip is the oldest.
						continue;

				char * name = getName(station);
				char * end_station_name = getName(oldest_end_station);
				char * date = getOldestTripDate(station);

				// Format the output date
				struct tm date_time;
				strptime(date, "%Y-%m-%d %H:%M:%S", &date_time);
				strftime(date, DATE_LEN, "%d/%m/%Y %H:%M:%S", &date_time);

				addHTMLRow(html_table, name, end_station_name, date);
				addCsvRow(csv_table, name, end_station_name, date);

				free(name);
				free(end_station_name);
				free(date);
		}
		closeHTMLTable(html_table);
		closeCsvTable(csv_table);


		// ---- QUERY 3 ----

		html_table = newTable( QUERY_3_OUTPUT_FILE ".html", QUERY_3_COLUMNS, QUERY_3_HEADERS );
		csv_table = newCsvTable( QUERY_3_OUTPUT_FILE ".csv", QUERY_3_COLUMNS, QUERY_3_HEADERS );

		WeekDays day;
		for(day=MONDAY; day < NUMBER_OF_WEEK_DAYS; day++){
				char started_trips[SIZE_T_CHAR_LEN];
				char ended_trips[SIZE_T_CHAR_LEN];

				sprintf(started_trips, "%zu", getStartedTripsByDay(city_stations, day));
				sprintf(ended_trips, "%zu",  getEndedTripsByDay(city_stations, day));

				addHTMLRow(html_table, week_day_names[day], started_trips, ended_trips);
				addCsvRow(csv_table, week_day_names[day], started_trips, ended_trips);
		}
		closeHTMLTable(html_table);
		closeCsvTable(csv_table);


		freeCityStations(city_stations);

		return 0;
}


