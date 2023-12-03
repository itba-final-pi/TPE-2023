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
    CityStations new = newCityStations("./tests/data/test.csv", "");
    assert( getStationsCount(new) == 9 );
    freeCityStations(new);
    return 0;
}
