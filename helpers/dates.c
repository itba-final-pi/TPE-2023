#include <stdio.h>
#include <string.h>

#include "dates.h"
#include "constants.h"

#define CHARS_FOR_YEAR 4
#define CHARS_FOR_MONTH 2
#define CHARS_FOR_DAY 2

// Takes advantage of the alphabetical order present in ISO 8601 dates.
int dateCompare(const char date1[DATE_LEN], const char date2[DATE_LEN]){
	return strcmp(date1, date2);
}


