#include <stdio.h>
#include <string.h>

#include "dates.h"
#include "constants.h"

// Takes advantage of the alphabetical order present in ISO 8601 dates
int dateCompare(const char date1[DATE_LEN], const char date2[DATE_LEN]){
	return strcmp(date1, date2);
}

