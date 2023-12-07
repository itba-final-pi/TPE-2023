#undef NDEBUG

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "tests.h"
#include "dateCompare.h"

int
main(void) {
	char * date = "2023-03-02 12:06:24";
	char * olderDate = "2023-01-02 12:06:24";
	char * oldestDate = "2023-01-02 12:05:24";

	assert(dateCompare(date, date) == 0);
	assert(dateCompare(date, olderDate) > 0);
	assert(dateCompare(date, oldestDate) > 0);
	assert(dateCompare(olderDate, oldestDate) > 0);
	assert(dateCompare(oldestDate, date) < 0);

    return 0;
}
