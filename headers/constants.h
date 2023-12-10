#include <stdio.h>

#ifndef _constants_h
#define _constants_h

#define NUMBER_OF_FIELDS_STATIONS 4
#define NUMBER_OF_FIELDS_TRIPS 6

// date length including '\0'
#define DATE_LEN 20
#define SIZE_T_CHAR_LEN 20

#define STACK_REALLOC_SIZE 20

#define LINE_SIZE 255
#define DELIM ";"

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
	MONDAY = 0,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY,
	SUNDAY,
} WeekDays;

#define NUMBER_OF_WEEK_DAYS (SUNDAY - MONDAY + 1)

#define VALIDATE_ARGS(condition, rtn) if(condition) { errno = EINVAL ; return rtn;}

typedef enum
{
    OK = 0,
    ERROR
} Status;

typedef enum
{
    SORT_ASCENDING = -1,
    SORT_DESCENDING = 1
} SortOrder;

#endif
