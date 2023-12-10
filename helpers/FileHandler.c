#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "FileHandler.h"

typedef struct FileHandlerCDT {
    FILE * file;
    char line[LINE_BUFFER_SIZE];
} FileHandlerCDT;

FileHandler newFileHandler(char * file) {
    FileHandler new = calloc(1, sizeof(FileHandlerCDT));
    new->file = fopen(file, "r");

    if (new->file == NULL || errno == ENOENT) {
        // ERROR
        free(new);
        return NULL;
    }

    return new;
}

char * getNextLine(FileHandler handler) {
    if (handler == NULL || handler->file == NULL || fgets(handler->line, LINE_BUFFER_SIZE, handler->file) == NULL) {
        if (handler) *handler->line = 0;
        return NULL;
    }

    return handler->line;
}

int hasNextLine(FileHandler handler) {
    return handler != NULL && handler->file != NULL && !feof(handler->file);
}

/**
 * @brief Closes the file
 * 
 * @param handler FileHandler
 * @return zero if error'ed, non-zero if successful
 */
static int closeFileHandler(FileHandler handler) {
    if (handler == NULL || handler->file == NULL) {
        return 1;
    }

    return fclose(handler->file) != EOF;
}

int freeFileHandler(FileHandler handler) {
    if ( closeFileHandler(handler) == 0 )
        return 0;
    
    free(handler);

    return 1;
}
