#include <stdlib.h>

#include "Stack.h"
#include "constants.h"

typedef struct StackCDT {
    void * * elems;
    size_t count;
    size_t elem_size;
} StackCDT;

Stack newStack(size_t elem_size) {
    Stack new = calloc(1, sizeof(StackCDT));
    new->elem_size = elem_size;
    return new;
}

void push(Stack stack, void * elem) {
    if(stack->count % STACK_REALLOC_SIZE == 0) {
        stack->elems = realloc(stack->elems, (stack->count + STACK_REALLOC_SIZE) * sizeof(stack->elems[0]));
    }
    stack->elems[stack->count++] = elem;
}

void * pop(Stack stack) {
    if(isEmpty(stack)) {
        return NULL;
    }
    return stack->elems[--stack->count];
}

int isEmpty(Stack stack) {
    return stack->count == 0;
}

size_t stackSize(Stack stack) {
    return stack->count;
}

void freeStack(Stack stack) {
    free(stack->elems);
    free(stack);
}
