// This file is meant to be a template for all other tests
// This file is excluded from test runs and is not counted towards the total amount of tests ran

// Make sure assert macro expressions work correctly 👇
#undef NDEBUG

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "tests.h"

#include "BikeStation.h"

int
main(void) {
    BikeStation bs0 = newBikeStation( 0, "bs0");
    BikeStation bs1 = newBikeStation( 0, "bs1");

    assert( getAllTips(bs0) == 0 );
    assert( getAllTips(bs1) == 0 );
    assert( strcmp(getName(bs0), "bs0") == 0 );
    assert( COMPARE_FLOATS(getLatitude(bs0), 0.0) );

    for (int i = 0; i < 5; i++)
        incrementCasualTrips(bs0);
    
    assert( getAllTips(bs0) == 5 );
    assert( getCasualTrips(bs0) == 5 );
    assert( getMemberTrips(bs0) == 0 );

    assert( getAllTips(bs1) == 0 );

    incrementMemberTrips(bs1);
    assert( getAllTips(bs1) == 1 );
    assert( getMemberTrips(bs1) == 1 );

    freeStation(bs0);

    return 0;
}