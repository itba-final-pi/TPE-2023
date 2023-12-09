#include "csvTable.h"
#include <stdlib.h>
#include <stdarg.h>

struct table {
	FILE * file;
	unsigned int columns;
	
};

static void addRow(csvTable table, va_list arg);

csvTable newCsvTable(const char * fileName, unsigned int columns, ...) {
    errno = 0;
    FILE * file = fopen(fileName, "w");
    if ( file == NULL ) {
	    return NULL;
    }	    

    csvTable table = malloc(sizeof(struct table));
    if ( errno == ENOMEM ) {
	    fclose(file);
	    return NULL;
    }

    table->file = file;
    table->columns = columns;
    va_list args;
    va_start(args, columns);
    addRow(table, args);

    return table;
}

void
addCsvRow(const csvTable table, ...) {
    va_list args;
    va_start(args, table);
    addRow(table, args);
}

void
closeCsvTable(csvTable table) {
    fclose(table->file);
    free(table);
}

static void
addRow(csvTable table, va_list arg) {
    for (unsigned int i = 0; i < table->columns; i++) {
        fprintf(table->file, (i != table->columns - 1) ? "%s;" : "%s", va_arg(arg, char *));
    }
	fprintf(table->file, "\n");
    va_end(arg);
}
