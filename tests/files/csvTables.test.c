#undef NDEBUG

#include <stdlib.h>
#include <stdio.h>
 #include <assert.h>
#include <string.h>

 #include "tests.h"
#include "csvTable.h"
#include "FileHandler.h"

#define OUTPUT_FILE "./tests/test-out/csvTable.csv"
int
main(void) {
    csvTable table = newCsvTable(OUTPUT_FILE, 2, "Column 1", "Column 2");
	FileHandler file = newFileHandler(OUTPUT_FILE);

	assert(table != NULL);

    for(int i = 0; i < 10; i++) {
		char field1[25];
		char field2[25];
		snprintf(field1, 20, "Letra nro. %d", i);
		snprintf(field2, 20, "%c", 'a'+i);

        addCsvRow(table, field1, field2);
    }
    closeCsvTable(table);

	assert(hasNextLine(file));
	char * line = getNextLine(file); 
	assert(strcmp(line, "Column 1;Column 2\n") == 0);
	line = getNextLine(file); 
	assert(strcmp(line, "Letra nro. 0;a\n") == 0);
	line = getNextLine(file); 
	assert(strcmp(line, "Letra nro. 1;b\n") == 0);
	line = getNextLine(file); 
	assert(strcmp(line, "Letra nro. 2;c\n") == 0);

    freeFileHandler(file);

    return 0;
}

