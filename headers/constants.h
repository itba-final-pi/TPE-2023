#include <stdio.h>

#ifndef _constants_h
#define _constants_h

#define NUMBER_OF_FIELDS_S 4
#define NUMBER_OF_FIELDS_T 6

typedef enum
{
    ID = 0,
    NAME,
    LATITUDE,
    LONGITUDE
} FieldsStation;

typedef enum
{
    START_DATE = 0,
    START_STATION_ID,
    END_DATE,
    END_STATION_ID,
    IS_MEMBER,
    RIDEABLE_TYPE
} FieldsTrips;

// indica para qué csv se quiere compilar
#define MON

// incluyendo el \0
#define DATE_LEN 20

typedef enum
{
    OK = 0,
    ERROR
} Status;

#endif
