#undef NDEBUG

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include "tests.h"

#include "BikeStation.h"
#include "CityStations.h"
#include "FileHandler.h"
#include "constants.h"

int
main(void) {
    
#ifdef MON
    CityStations new = newCityStations();
    
    FileHandler file = newFileHandler("./Datasets Alumnos/stationsMON.csv");

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
    file = newFileHandler("./Datasets Alumnos/bikesMON.csv");
    line = getNextLine(file); // ignore header line

    // While there's a line, AND it is not empty
    while( hasNextLine(file) && (line = getNextLine(file)) ) {
        processTrip(new, line);
    }

    orderStationsByTrips(new);
    size_t total_stations = getStationsCount(new);

    size_t i = 0;
    char * aux = calloc(1, sizeof(char));

    toBeginAlphabeticOrder(new);

    while(hasNextAlphabeticOrder(new)) {
        BikeStation station = nextAlphabeticOrder(new);
        assert(station != NULL);

        char * name = getName(station);
        assert(name != NULL);

        assert( strcasecmp(aux, name) <= 0 );
        free(aux);
        aux = name;
        i++;
    }

    free(aux);

    assert(i == total_stations);

    size_t total_trips_aux = -1;
    i = 0;
    toBeginTripsOrder(new);
    while(hasNextTripsOrder(new)) {
        BikeStation station = nextTripsOrder(new);
        assert(station != NULL);
        assert(total_trips_aux >= getAllTrips(station));
        total_trips_aux = getAllTrips(station);
        i++;
    }
    assert(i == total_stations);

    freeStation(station);
    freeCityStations(new);
    freeFileHandler(file);
#endif

    return 0;
}
