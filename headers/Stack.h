#include <stdlib.h>

#ifndef _stack_h
#define _stack_h

typedef struct StackCDT * Stack;

Stack newStack(size_t elem_size);

void push(Stack stack, void * elem);

void * pop(Stack stack);

int isEmpty(Stack stack);

size_t stackSize(Stack stack);

void freeStack(Stack stack);

#endif
