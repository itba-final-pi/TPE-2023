#include <string.h>

#include "BikeStation.h"
#include "constants.h"
#include "dates.h"

typedef struct Trip{
	BikeStation endStation;
	char startedAt[DATE_LEN];
} Trip;

typedef struct BikeStationCDT {
    size_t id;
    char * name;
    double latitude;
    double longitude;
    size_t memberTrips;
    size_t casualTrips;
	Trip oldestTrip;
} BikeStationCDT;

BikeStation newBikeStation(const size_t id, const char * name, const double latitude, const double longitude){
    BikeStation new = calloc(1, sizeof(BikeStationCDT));
    new->id = id;
    new->name = malloc(strlen(name) + 1);
    strcpy(new->name, name);
    new->latitude = latitude;
    new->longitude = longitude;
    return new;
}

void freeStation(BikeStation station){
    free(station->name);
    free(station);
}

void setOldestTrip(BikeStation startStation, BikeStation endStation, const char startedAt[DATE_LEN]) {
	startStation->oldestTrip.endStation = endStation;
	strcpy(startStation->oldestTrip.startedAt, startedAt);
}

void incrementMemberTrips(BikeStation station) {
    station->memberTrips++;
}

void incrementCasualTrips(BikeStation station) {
    station->casualTrips++;
}

size_t getAllTrips(BikeStation station) {
    return station->memberTrips + station->casualTrips;
}

size_t getMemberTrips(BikeStation station) {
    return station->memberTrips;
}

size_t getCasualTrips(BikeStation station) {
    return station->casualTrips;
}

char * getName(BikeStation station) {
    char * aux = malloc(strlen(station->name) + 1);
    return strcpy(aux, station->name);
}

double getLatitude(BikeStation station) {
    return station->latitude;
}

double getLongitude(BikeStation station) {
    return station->longitude;
}

BikeStation getOldestTripEndStation(BikeStation station) {
	return station->oldestTrip.endStation;
}

char * getOldestTripDate(BikeStation station) {
    if (station->oldestTrip.startedAt[0] == '\0')
        return NULL;
    char * aux = malloc(DATE_LEN);
    return strcpy(aux, station->oldestTrip.startedAt);
}

size_t getId(BikeStation station) {
    return station->id;
}

int compareStationsByName(BikeStation a, BikeStation b){
	return strcasecmp(a->name, b->name);
}

int compareStationsByTrips(BikeStation a, BikeStation b){
    size_t aTrips = getAllTrips(a);
    size_t bTrips = getAllTrips(b);
    if (aTrips == bTrips)
        return compareStationsByName(a, b);
    return aTrips - bTrips;
}

int isOlderTrip(const BikeStation station, const char date[DATE_LEN]){
    if (station->oldestTrip.startedAt[0] == '\0'){
        return 1;
    }
	return dateCompare(station->oldestTrip.startedAt, date) > 0;
}
