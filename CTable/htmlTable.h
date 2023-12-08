#ifndef __ctable_h_
#define __ctable_h_
#include <stdio.h>
#include <errno.h>

/*
* htmlTable es un puntero a un struct desconocido. Si bien tiene la forma de un TAD, no 
* es algo genÃrico ni exclusivamente de backend.
*/
typedef struct table * htmlTable;

/*
 * @returns Puntero a la esructura con lo necesario para agregar columnas a una tabla HTML
            En caso de error (no se pudo crear el archivo) retorn NULL
 * @param fileName Nombre del archivo a crear
 * @param columns Cantidad de columnas que tendría la tabla
 * @param ...  Título de cada una de las columnas. Debería haber tantos
 *             strings como columnas se indicaron. En caso de poner más se ignoran
 *             En caso de poner menos o tipos incorrectos el resultado es impredecible
 *             (como si a printf se le pasan menos argumentos o tipos incorrectos)
 *             
 */
htmlTable newTable(const char * fileName, unsigned int columns, ...);


/*
 * Agrega una fila a la tabla. Se deben enviar tantos strings como columnas se hayan indicado
 *             En caso de poner menos o tipos incorrectos el resultado es impredecible
 *             (como si a printf se le pasan menos argumentos o tipos incorrectos)
 * 
*/
void addHTMLRow(htmlTable table, ...);

/**
 * Finaliza la tabla, cierra el archivo y libera toda la memoria reservada
*/ 
void closeHTMLTable(htmlTable table);

#endif
