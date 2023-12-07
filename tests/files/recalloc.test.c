#undef NDEBUG

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "tests.h"

#include "recalloc.h"

#define SIZE 5
#define NEW_SIZE 10

int
main(void) {
    int * vector = malloc(SIZE * sizeof(int));

    for (int i = 0; i < SIZE; i++)
        vector[i] = i;
    
    vector = recalloc(vector, SIZE * sizeof(int), NEW_SIZE * sizeof(int));

    if (vector == NULL) {
        fprintf(stderr, "In the unlikely event reallocation of 40 bytes fails, fail the test and force to run again");
        return 1;
    }

    for (int i = 0; i < SIZE; i++)
        vector[i] = i;

    for (int i = SIZE; i < NEW_SIZE; i++)
        assert(vector[i] == 0);

    free(vector);

    return 0;
}
