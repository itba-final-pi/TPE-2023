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
#include "loadStations.h"
#include "processTrips.h"

int
main(void) {
    
#ifdef MON
    CityStations new = newCityStations();
    
    loadStations(new, "./Datasets Alumnos/stationsMON.csv");

    BikeStation station = newBikeStation(1286, "Evans / Clark", 45.5110837, -73.5679775);

    assert( getStationsCount(new) == 996 );
    assert( getStation(new, 1286) != NULL );
    assert( compareStationsByName(getStation(new, 1286), station) == 0 );
    assert( getLongitude(getStation(new, 1286)) == getLongitude(station) );
    assert( getLatitude(getStation(new, 1286)) == getLatitude(station) );


    //process trip
    processTrips(new, "./Datasets Alumnos/bikesMON.csv");

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

    size_t total_trips_aux = 0;
    i = 0;
    toBeginTripsOrder(new);
    BikeStation station_aux;
    while((station_aux = (BikeStation) nextTripsOrder(new)) != NULL) {
        assert(station_aux != NULL);
        assert(total_trips_aux <= getAllTrips(station_aux));
        total_trips_aux = getAllTrips(station_aux);
        i++;
    }
    printf("total_trips_aux: %zu\n", total_trips_aux);
    printf("i: %zu\n", i);
    assert(i == total_stations);

    freeStation(station);
    freeCityStations(new);
#endif

#ifdef NYC
    CityStations new = newCityStations();
    
    loadStations(new, "./Datasets Alumnos/stationsNYC.csv");

    BikeStation station = newBikeStation(728804, "Riverside Dr & W 72 St", 40.7805779901033, -73.9856243133545);

    assert( getStationsCount(new) == 1680 );
    assert( getStation(new, 728804) != NULL );
    assert( compareStationsByName(getStation(new, 728804), station) == 0 );
    assert( getLongitude(getStation(new, 728804)) == getLongitude(station) );
    assert( getLatitude(getStation(new, 728804)) == getLatitude(station) );
	
    //process trip
    processTrips(new, "./Datasets Alumnos/bikesNYC.csv");

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

    size_t total_trips_aux = 0;
    i = 0;
    toBeginTripsOrder(new);
    BikeStation station_aux;
    while((station_aux = (BikeStation) nextTripsOrder(new)) != NULL) {
        assert(station_aux != NULL);
        assert(total_trips_aux <= getAllTrips(station_aux));
        total_trips_aux = getAllTrips(station_aux);
        i++;
    }
    assert(i == total_stations);

    freeStation(station);
    freeCityStations(new);
#endif

    return 0;
}
