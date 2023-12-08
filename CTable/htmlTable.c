#include "htmlTable.h"
#include <stdarg.h>
#include <stdlib.h>

#define TABLE_HEAD "thead"
#define TABLE_BODY "tbody"
#define TABLE_HEADING "th"
#define TABLE_ROW "tr"
#define TABLE_DATA "td"

struct table {
	FILE * file;
	unsigned int columns;
	
};

static void addNodes(const char * fatherNode, const char * childNode, htmlTable table, va_list arg);

htmlTable newTable (const char * fileName, unsigned int columns, ...) {
    errno = 0;
    FILE * file = fopen(fileName, "w");
    if ( file == NULL ) {
	    return NULL;
    }	    
    htmlTable table = malloc(sizeof(struct table));
    if ( errno == ENOMEM ) {
	    fclose(file);
	    return NULL;
    }
    table->file = file;
    table->columns = columns;
    va_list args;
    va_start(args, columns);
    fputs("<link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css\" rel=\"stylesheet\" "
          "integrity=\"sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3\" "
          "crossorigin=\"anonymous\">", file);
    fputs("<html><table class=\"table table-striped table-hover\">", file);
    fprintf(file, "<%s>", TABLE_HEAD);
    addNodes(TABLE_ROW, TABLE_HEADING, table, args);
    fprintf(file, "</%s><%s>", TABLE_HEAD, TABLE_BODY);
    return table;
}

void
addHTMLRow(const htmlTable table, ...) {
    va_list args;
    va_start(args, table);
    addNodes(TABLE_ROW, TABLE_DATA, table, args);
}

void
closeHTMLTable(htmlTable table) {
    fprintf(table->file, "</%s></table></html>", TABLE_BODY);
    fclose(table->file);
    free(table);
}

static void
addNodes(const char * fatherNode, const char * childNode, htmlTable table, va_list arg) {
    fprintf(table->file, "<%s>", fatherNode);
    for (int i = 0; i < table->columns; i++) {
        fprintf(table->file, "<%s>%s</%s>", childNode, va_arg(arg, char *), childNode);
    }
    va_end(arg);
    fprintf(table->file, "</%s>", fatherNode);
}
