#include <stdlib.h>

#include "Stack.h"
#include "constants.h"

typedef struct StackCDT {
    void * * elems;
    size_t count;
} StackCDT;

Stack newStack(void) {
    Stack new = calloc(1, sizeof(StackCDT));
    return new;
}

void push(Stack stack, void * elem) {
    if(stack->count % STACK_REALLOC_SIZE == 0) {
        stack->elems = realloc(stack->elems, (stack->count + STACK_REALLOC_SIZE) * sizeof(stack->elems[0]));
    }
    stack->elems[stack->count++] = elem;
}

void * pop(Stack stack) {
    if(isEmptyStack(stack)) {
        return NULL;
    }
    return stack->elems[--stack->count];
}

int isEmptyStack(Stack stack) {
    return stack->count == 0;
}

size_t stackSize(Stack stack) {
    return stack->count;
}

void freeStack(Stack stack) {
    if (stack) free(stack->elems);
    free(stack);
}
