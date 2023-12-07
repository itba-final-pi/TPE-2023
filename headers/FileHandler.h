#include <stdlib.h>

#ifndef _bike_stations_h
#define _bike_stations_h

#define LINE_BUFFER_SIZE 255

typedef struct FileHandlerCDT * FileHandler;

/**
 * @brief Creates a new FileHandler ADT
 * 
 * @param file path to the file to be opened
 * @return FileHandler 
 */
FileHandler newFileHandler(char * file);

/**
 * @brief Get the Next Line char *
 * 
 * @param handler FileHandler
 * @return char * 
 */
char * getNextLine(FileHandler handler);

/**
 * @brief Get whether another line of the file is available
 * 
 * @param handler FileHandler
 * @return int
 */
int hasNextLine(FileHandler handler);

/**
 * @brief Free's the file resource and FileHandler pointer
 * 
 * @param handler 
 * @return zero if error'ed, non-zero if successful
 */
int freeFileHandler(FileHandler handler);

#endif
