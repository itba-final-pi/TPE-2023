#undef NDEBUG

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "tests.h"

#include "BikeStation.h"
#include "CityStations.h"
#include "constants.h"

int
main(void) {
    
    // * MON

    #ifdef MON
        BikeStation station = newBikeStation(1286, "Evans / Clark");
        setLatitude(station, 45.5110837);
        setLongitude(station, -73.5679775);

        CityStations new = newCityStations("./Datasets Alumnos SMALL/stationsMON.csv", "./Datasets Alumnos SMALL/bikesMON.csv");
        assert( getStationsCount(new) == 9 );
        assert( getStation(new, 1286) != NULL );
        assert( compareStationsByName(getStation(new, 1286), station) == 0 );
        assert( getLongitude(getStation(new, 1286)) == getLongitude(station) );
        assert( getLatitude(getStation(new, 1286)) == getLatitude(station) );
        
        freeStation(station);

        freeCityStations(new);
    #endif

    // * NYC
    #ifdef NYC
        // 65 St & Broadway;40.7493722738996;-73.8973876833916;641711
        BikeStation station = newBikeStation(641711, "65 St & Broadway");
        setLatitude(station, 40.7493722738996);
        setLongitude(station, -73.8973876833916);

        CityStations new = newCityStations("./Datasets Alumnos SMALL/stationsNYC.csv", "./Datasets Alumnos SMALL/bikesNYC.csv");
        assert( getStationsCount(new) == 9 );
        assert( getStation(new, 641711) != NULL );
        assert( compareStationsByName(getStation(new, 641711), station) == 0 );
        assert( COMPARE_FLOATS(getLongitude(getStation(new, 641711)), getLongitude(station)) );
        assert( COMPARE_FLOATS(getLatitude(getStation(new, 641711)), getLatitude(station)) );

        freeStation(station);

        freeCityStations(new);
    #endif
    
    return 0;
}
