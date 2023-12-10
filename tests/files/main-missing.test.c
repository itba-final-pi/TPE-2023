#undef NDEBUG

#include <assert.h>
#include "tests.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#include "CityStations.h"
#include "FileHandler.h"
#include "htmlTable.h"
#include "csvTable.h"
#include "constants.h"
#include "loadStations.h"
#include "processTrips.h"

#define QUERY_1_OUTPUT_FILE "./tests/test-out/query1"
#define QUERY_2_OUTPUT_FILE "./tests/test-out/query2"
#define QUERY_3_OUTPUT_FILE "./tests/test-out/query3"

#define QUERY_1_COLUMNS 4
#define QUERY_2_COLUMNS 3
#define QUERY_3_COLUMNS 3

#define QUERY_1_HEADERS "bikeStation", "memberTrips", "casualTrips", "allTrips"
#define QUERY_2_HEADERS "bikeStation", "bikeEndStation", "oldestDateTime"
#define QUERY_3_HEADERS "weekDay", "startedTrips", "endedTrips"

static const char *week_day_names[NUMBER_OF_WEEK_DAYS] = {
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday",
    "Sunday"};

int main(void)
{
#ifdef MON
    char *stations_path = "./Datasets Alumnos/Mas/missingStationsMON.csv";
    char *trips_path = "./Datasets Alumnos SMALL/bikesMON.csv";

    htmlTable html_table;
    csvTable csv_table;

    CityStations city_stations = newCityStations();

    loadStations(city_stations, stations_path);
    if (getStationsCount(city_stations) != 0)
        processTrips(city_stations, trips_path);
    orderStationsByTrips(city_stations);

    // ---- QUERY 1 ----

    html_table = newTable(QUERY_1_OUTPUT_FILE ".html", QUERY_1_COLUMNS, QUERY_1_HEADERS);
    csv_table = newCsvTable(QUERY_1_OUTPUT_FILE ".csv", QUERY_1_COLUMNS, QUERY_1_HEADERS);

    toBeginTripsOrder(city_stations);
    while (hasNextTripsOrder(city_stations))
    {
        BikeStation station = nextTripsOrder(city_stations);

        char *name = getName(station);
        char member_trips[SIZE_T_CHAR_LEN];
        char casual_trips[SIZE_T_CHAR_LEN];
        char all_trips[SIZE_T_CHAR_LEN];

        sprintf(member_trips, "%zu", getMemberTrips(station));
        sprintf(casual_trips, "%zu", getCasualTrips(station));
        sprintf(all_trips, "%zu", getAllTrips(station));

        addHTMLRow(html_table, name, member_trips, casual_trips, all_trips);
        addCsvRow(csv_table, name, member_trips, casual_trips, all_trips);

        free(name);
    }
    closeHTMLTable(html_table);
    closeCsvTable(csv_table);

    // ---- QUERY 2 ----

    html_table = newTable(QUERY_2_OUTPUT_FILE ".html", QUERY_2_COLUMNS, QUERY_2_HEADERS);
    csv_table = newCsvTable(QUERY_2_OUTPUT_FILE ".csv", QUERY_2_COLUMNS, QUERY_2_HEADERS);

    toBeginAlphabeticOrder(city_stations);
    while (hasNextAlphabeticOrder(city_stations))
    {
        BikeStation station = nextAlphabeticOrder(city_stations);
        BikeStation oldest_end_station = getOldestTripEndStation(station);

        if (oldest_end_station == NULL)
            // The station has no trips, so no trip is the oldest.
            continue;

        char *name = getName(station);
        char *end_station_name = getName(oldest_end_station);
        char *date = getOldestTripDate(station);

        // Format the output date
        struct tm date_time;
        strptime(date, "%Y-%m-%d %H:%M:%S", &date_time);
        strftime(date, DATE_LEN, "%d/%m/%Y %H:%M:%S", &date_time);

        addHTMLRow(html_table, name, end_station_name, date);
        addCsvRow(csv_table, name, end_station_name, date);

        free(name);
        free(end_station_name);
        free(date);
    }
    closeHTMLTable(html_table);
    closeCsvTable(csv_table);

    // ---- QUERY 3 ----

    html_table = newTable(QUERY_3_OUTPUT_FILE ".html", QUERY_3_COLUMNS, QUERY_3_HEADERS);
    csv_table = newCsvTable(QUERY_3_OUTPUT_FILE ".csv", QUERY_3_COLUMNS, QUERY_3_HEADERS);

    WeekDays day;
    for (day = MONDAY; day < NUMBER_OF_WEEK_DAYS; day++)
    {
        char started_trips[SIZE_T_CHAR_LEN];
        char ended_trips[SIZE_T_CHAR_LEN];

        sprintf(started_trips, "%zu", getStartedTripsByDay(city_stations, day));
        sprintf(ended_trips, "%zu", getEndedTripsByDay(city_stations, day));

        addHTMLRow(html_table, week_day_names[day], started_trips, ended_trips);
        addCsvRow(csv_table, week_day_names[day], started_trips, ended_trips);
    }
    closeHTMLTable(html_table);
    closeCsvTable(csv_table);

    freeCityStations(city_stations);
#endif

#ifdef NYC
    char *stations_path = "./Datasets Alumnos/Mas/missingStationsNYC.csv";
    char *trips_path = "./Datasets Alumnos SMALL/bikesNYC.csv";

    htmlTable html_table;
    csvTable csv_table;

    CityStations city_stations = newCityStations();

    loadStations(city_stations, stations_path);
    processTrips(city_stations, trips_path);
    orderStationsByTrips(city_stations);

    // ---- QUERY 1 ----

    html_table = newTable(QUERY_1_OUTPUT_FILE ".html", QUERY_1_COLUMNS, QUERY_1_HEADERS);
    csv_table = newCsvTable(QUERY_1_OUTPUT_FILE ".csv", QUERY_1_COLUMNS, QUERY_1_HEADERS);

    toBeginTripsOrder(city_stations);
    while (hasNextTripsOrder(city_stations))
    {
        BikeStation station = nextTripsOrder(city_stations);

        char *name = getName(station);
        char member_trips[SIZE_T_CHAR_LEN];
        char casual_trips[SIZE_T_CHAR_LEN];
        char all_trips[SIZE_T_CHAR_LEN];

        sprintf(member_trips, "%zu", getMemberTrips(station));
        sprintf(casual_trips, "%zu", getCasualTrips(station));
        sprintf(all_trips, "%zu", getAllTrips(station));

        addHTMLRow(html_table, name, member_trips, casual_trips, all_trips);
        addCsvRow(csv_table, name, member_trips, casual_trips, all_trips);

        free(name);
    }
    closeHTMLTable(html_table);
    closeCsvTable(csv_table);

    // ---- QUERY 2 ----

    html_table = newTable(QUERY_2_OUTPUT_FILE ".html", QUERY_2_COLUMNS, QUERY_2_HEADERS);
    csv_table = newCsvTable(QUERY_2_OUTPUT_FILE ".csv", QUERY_2_COLUMNS, QUERY_2_HEADERS);

    toBeginAlphabeticOrder(city_stations);
    while (hasNextAlphabeticOrder(city_stations))
    {
        BikeStation station = nextAlphabeticOrder(city_stations);
        BikeStation oldest_end_station = getOldestTripEndStation(station);

        if (oldest_end_station == NULL)
            // The station has no trips, so no trip is the oldest.
            continue;

        char *name = getName(station);
        char *end_station_name = getName(oldest_end_station);
        char *date = getOldestTripDate(station);

        // Format the output date
        struct tm date_time;
        strptime(date, "%Y-%m-%d %H:%M:%S", &date_time);
        strftime(date, DATE_LEN, "%d/%m/%Y %H:%M:%S", &date_time);

        addHTMLRow(html_table, name, end_station_name, date);
        addCsvRow(csv_table, name, end_station_name, date);

        free(name);
        free(end_station_name);
        free(date);
    }
    closeHTMLTable(html_table);
    closeCsvTable(csv_table);

    // ---- QUERY 3 ----

    html_table = newTable(QUERY_3_OUTPUT_FILE ".html", QUERY_3_COLUMNS, QUERY_3_HEADERS);
    csv_table = newCsvTable(QUERY_3_OUTPUT_FILE ".csv", QUERY_3_COLUMNS, QUERY_3_HEADERS);

    WeekDays day;
    for (day = MONDAY; day < NUMBER_OF_WEEK_DAYS; day++)
    {
        char started_trips[SIZE_T_CHAR_LEN];
        char ended_trips[SIZE_T_CHAR_LEN];

        sprintf(started_trips, "%zu", getStartedTripsByDay(city_stations, day));
        sprintf(ended_trips, "%zu", getEndedTripsByDay(city_stations, day));

        addHTMLRow(html_table, week_day_names[day], started_trips, ended_trips);
        addCsvRow(csv_table, week_day_names[day], started_trips, ended_trips);
    }
    closeHTMLTable(html_table);
    closeCsvTable(csv_table);

    freeCityStations(city_stations);
#endif

    return 0;
}
