#undef NDEBUG

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "tests.h"

#include "BikeStation.h"
#include "CityStations.h"
#include "FileHandler.h"
#include "constants.h"

int
main(void) {
    
    
    // FILE HANDLER
    CityStations new = newCityStations();
    
    FileHandler file = newFileHandler("./Datasets Alumnos SMALL/stationsMON.csv");

    char * line = getNextLine(file); // ignore header line

    // While there's a line, AND it is not empty
    while( hasNextLine(file) && (line = getNextLine(file)) ) {
        loadStation(new, line);
    }

    BikeStation station = newBikeStation(1286, "Evans / Clark");
    setLatitude(station, 45.5110837);
    setLongitude(station, -73.5679775);

    assert( getStationsCount(new) == 9 );
    assert( getStation(new, 1286) != NULL );
    assert( compareStationsByName(getStation(new, 1286), station) == 0 );
    assert( getLongitude(getStation(new, 1286)) == getLongitude(station) );
    assert( getLatitude(getStation(new, 1286)) == getLatitude(station) );

    freeFileHandler(file);
    //process trip
    file = newFileHandler("./Datasets Alumnos SMALL/bikesMON.csv");
    line = getNextLine(file); // ignore header line

    // While there's a line, AND it is not empty
    while( hasNextLine(file) && (line = getNextLine(file)) ) {
        processTrip(new, line);
    }

    freeStation(station);
    freeCityStations(new);
    freeFileHandler(file);

    return 0;
}
