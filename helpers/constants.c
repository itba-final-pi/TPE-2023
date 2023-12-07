#include <stdio.h>

#ifndef _constants_h
#define _constants_h

#define NUMBER_OF_FIELDS 4

typedef enum
{
    ID = 0,
    NAME,
    LATITUDE,
    LONGITUDE
} Fields;

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
