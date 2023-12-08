#include <stdio.h>

#ifndef _constants_h
#define _constants_h

#define NUMBER_OF_FIELDS_S 4
#define NUMBER_OF_FIELDS_T 6

// date length including '\0'
#define DATE_LEN 20

#define STACK_REALLOC_SIZE 20

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



typedef enum
{
    OK = 0,
    ERROR
} Status;

#endif
