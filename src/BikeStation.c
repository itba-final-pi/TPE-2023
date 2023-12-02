// @todo #2 Refactor import paths
#include <string.h>

#include "../headers/BikeStation.h"

BikeStation newBikeStation(size_t id, char * name) {
    BikeStation new = calloc(1, sizeof(BikeStationCDT));
    new->id = id;
    strcpy(new->name, name);
    return new;
}

void setLatitude(BikeStation station, double latitude) {
    station->latitude = latitude;
}

void setLongitude(BikeStation station, double longitude){
    station->longitude = longitude;
}

void incrementMemberTrips(BikeStation station) {
    station->memberTrips++;
};

void incrementCasualTrips(BikeStation station) {
    station->casualTrips++;
};

size_t getAllTips(BikeStation station) {
    return station->memberTrips + station->casualTrips;
}

size_t getMemberTrips(BikeStation station) {
    return station->memberTrips;
}

size_t getCasualTrips(BikeStation station) {
    return station->casualTrips;
}
