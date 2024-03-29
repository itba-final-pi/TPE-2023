#undef NDEBUG

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <errno.h>

#include "tests.h"

#include "FileHandler.h"

int
main(void) {
    FileHandler empty = newFileHandler("");
    assert( getNextLine(empty) == NULL );
    assert( hasNextLine(empty) == 0 );
    freeFileHandler(empty);
    assert( errno == ENOENT );
    errno = 0;

#ifdef MON
    FileHandler montreal = newFileHandler("./Datasets Alumnos/bikesMON.csv");
    assert( strcmp(getNextLine(montreal), "start_date;emplacement_pk_start;end_date;emplacement_pk_end;is_member\n") == 0 );
    freeFileHandler(montreal);
#endif

    return 0;
}
