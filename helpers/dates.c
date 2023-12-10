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

// A more efficient way of getting the week day from a ISO 8601 date than using <time.h>.
// It increeses performance in aproximatelly 23% compared to using the <time.h> struct.
WeekDays isoToWeekDay(const char date[DATE_LEN]){
		// does not use atoi for speed, given that the amount of chars is a fixed number
		int y = 0;
		for (int i = 0; i < CHARS_FOR_YEAR; ++i) {
				y = y * 10 + (date[i] - '0');
		}
		int m = 0;
		for (int i = 5; i < CHARS_FOR_MONTH; ++i) {
				m = m * 10 + (date[i] - '0');
		}
		int d = 0;
		for (int i = 8; i < CHARS_FOR_DAY; ++i) {
				d = d * 10 + (date[i] - '0');
		}

		// A formula developed by Michael Keith (Mathematician and engineer) to turn a Gregorian date into a numerical day of the week.
		// Modified so the week starts on Monday (as in WeekDays enum in constants.h).
		int weekday  = (d += m < 3 ? y-- : y - 2, 23*m/9 + d + 4 + y/4- y/100 + y/400)%7;
		weekday = weekday - 1 > 0 ? weekday - 1 ? NUMBER_OF_WEEK_DAYS - 1;

		return weekday;
}

