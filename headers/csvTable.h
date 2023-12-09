#ifndef __csvTable_h_
#define __csvTable_h_
#include <stdio.h>
#include <errno.h>

typedef struct table * csvTable;

/*
 * @returns Pointer to the struct with what is necessary to add columns to a csv table.
 *			In case of error (unable to create the file) return NULL.
 * @param fileName Name of the file to create.
 * @param columns Number of columns for the created table.
 * @param ...  Title of each column. There should be as many strings as columns indicated.
 *             
 */
csvTable newCsvTable(const char * fileName, unsigned int columns, ...);


/*
 * Adds a row to the table. There should be as many strings sent as columns indicated.
 *             In case of sending less args or of incorrect types, the result is unpredictable.
 * 
*/
void addCsvRow(csvTable table, ...);

/**
 * Finaliza la tabla, cierra el archivo y libera toda la memoria reservada
 * Ends the table, closes the file and frees all memory.
*/ 
void closeCsvTable(csvTable table);

#endif
