#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "CityStations.h"
#include "FileHandler.h"
#include "constants.h"


#ifdef MON
static const int fields_station[NUMBER_OF_FIELDS_STATIONS] = {ID, NAME, LATITUDE, LONGITUDE};

#elif defined(NYC)
static const int fields_station[NUMBER_OF_FIELDS_STATIONS] = {NAME, LATITUDE, LONGITUDE, ID};

#else
#error "No city was specified on build target"
#endif


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

