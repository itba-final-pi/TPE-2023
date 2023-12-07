#undef NDEBUG

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "tests.h"

#include "BikeStation.h"
#include "CityStations.h"

int
main(void) {
    
    BikeStation station = newBikeStation(1286, "Evans / Clark");
    setLatitude(station, 45.5110837);
    setLongitude(station, -73.5679775);

    CityStations new = newCityStations("./Datasets Alumnos SMALL/stationsMON.csv", "");
    assert( getStationsCount(new) == 9 );
    assert( getStation(new, 1286) != NULL );
    assert( compareStationsByName(getStation(new, 1286), station) == 0 );
    assert( getLongitude(getStation(new, 1286)) == getLongitude(station) );
    assert( getLatitude(getStation(new, 1286)) == getLatitude(station) );

    freeStation(station);

    freeCityStations(new);
    return 0;
}
