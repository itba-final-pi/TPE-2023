#include <stdio.h>
#include <string.h>

#include "dates.h"
#include "constants.h"

// Takes advantage of the alphabetical order present in ISO 8601 dates
int dateCompare(char date1[DATE_LEN], char date2[DATE_LEN]){
	return strcmp(date1, date2);
}

