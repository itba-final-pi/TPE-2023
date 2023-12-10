#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "CityStations.h"
#include "FileHandler.h"
#include "constants.h"


#ifdef MON
static const int fields_trips[NUMBER_OF_FIELDS_TRIPS] = {START_DATE, START_STATION_ID, END_DATE, END_STATION_ID, IS_MEMBER};
#define IS_MEMBER(field) (field[0] == '1')

#elif defined(NYC)
static const int fields_trips[NUMBER_OF_FIELDS_TRIPS] = {START_DATE, START_STATION_ID, END_DATE, END_STATION_ID, RIDEABLE_TYPE, IS_MEMBER};
#define IS_MEMBER(field) (field[0] == 'm')

#else
#error "No city was specified on build target"
#endif


void processTrips(CityStations city_stations, char * file_name){
		FileHandler file = newFileHandler(file_name);
		if (file == NULL || errno != 0) {
			freeFileHandler(file);
			return;
		}

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

