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
    
    FileHandler file = newFileHandler("./temp/stationsMON.csv");

    char * line = getNextLine(file); // ignore header line

    // While there's a line, AND it is not empty
    while( hasNextLine(file) && (line = getNextLine(file)) ) {
        loadStation(new, line);
    }

    BikeStation station = newBikeStation(1286, "Evans / Clark", 45.5110837, -73.5679775);

    assert( getStationsCount(new) == 996 );
    assert( getStation(new, 1286) != NULL );
    assert( compareStationsByName(getStation(new, 1286), station) == 0 );
    assert( getLongitude(getStation(new, 1286)) == getLongitude(station) );
    assert( getLatitude(getStation(new, 1286)) == getLatitude(station) );

    freeFileHandler(file);
    //process trip
    file = newFileHandler("./temp/bikesMON.csv");
    line = getNextLine(file); // ignore header line

    // While there's a line, AND it is not empty
    while( hasNextLine(file) && (line = getNextLine(file)) ) {
        processTrip(new, line);
    }

    orderStationsByTrips(new);

    toBeginAlphabeticOrder(new);
    while(hasNextAlphabeticOrder(new))
    {
        BikeStation station = nextAlphabeticOrder(new);
        size_t id = getId(station);
        char * name = getName(station);
        printf("[%ld] %s\n", id, name);
        free(name);
    }

    toBeginTripsOrder(new);
    printf("id;bikeStation;memberTrips;casualTrips;totalTrips\n");
    while(hasNextTripsOrder(new))
    {
        BikeStation station = nextTripsOrder(new);
        size_t id = getId(station);
        char * name = getName(station);
        size_t memberTrips = getMemberTrips(station);
        size_t casualTrips = getCasualTrips(station);
        size_t totalTrips = getAllTips(station);
        printf("%ld;%s;%ld;%ld;%ld\n", id, name, memberTrips, casualTrips, totalTrips);
        free(name);
    }

    freeStation(station);
    freeCityStations(new);
    freeFileHandler(file);

    return 0;
}
