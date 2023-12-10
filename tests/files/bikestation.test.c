#undef NDEBUG

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "tests.h"

#include "BikeStation.h"

int
main(void) {
    BikeStation bs0 = newBikeStation( 0, "bs0", 0.0, 0.0);
    assert( getId(bs0) == 0 );
    BikeStation bs1 = newBikeStation( 1, "bs1", 1.0, 1.0);
    assert( getId(bs1) == 1 );

    assert( getAllTrips(bs0) == 0 );
    assert( getAllTrips(bs1) == 0 );

    char * bs0Name = getName(bs0);
    assert( strcmp(bs0Name, "bs0") == 0 );
    free(bs0Name);

    assert( COMPARE_FLOATS(getLatitude(bs0), 0.0) );

    for (int i = 0; i < 5; i++)
        incrementCasualTrips(bs0);
    
    assert( getAllTrips(bs0) == 5 );
    assert( getCasualTrips(bs0) == 5 );
    assert( getMemberTrips(bs0) == 0 );

    assert( getAllTrips(bs1) == 0 );

    incrementMemberTrips(bs1);
    assert( getAllTrips(bs1) == 1 );
    assert( getMemberTrips(bs1) == 1 );


    char * date = "2020-01-01 00:00:00";

    char * date_old = getOldestTripDate(bs0);
    assert( date_old == NULL );
    free(date_old);

    setOldestTrip(bs0, bs1, date);
    assert( strcmp(date_old = getOldestTripDate(bs0), date) == 0 );
    assert( getOldestTripEndStation(bs0) == bs1 );
    free(date_old);

    freeStation(bs0);
    freeStation(bs1);

    return 0;
}
