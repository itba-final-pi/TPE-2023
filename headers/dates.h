#include <stdio.h>
#include "constants.h"

#ifndef _dates_h_
#define _dates_h_

/**
 * @brief Compares two string representing ISO 8601 dates.
 * 
 * @param date1 a string representing an ISO 8601 date.
 * @param date2 a string representing an ISO 8601 date.
 * @return 0 if both are the same, < 0 if date1 < date2, > 0 if date1 > date2. 
 */
int dateCompare(const char date1[DATE_LEN], const char date2[DATE_LEN]);

#endif
