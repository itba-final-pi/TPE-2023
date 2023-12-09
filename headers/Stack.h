#include <stdlib.h>

#ifndef _stack_h
#define _stack_h

typedef struct StackCDT * Stack;

Stack newStack(void);

void push(Stack stack, void * elem);

void * pop(Stack stack);

int isEmptyStack(Stack stack);

size_t stackSize(Stack stack);

void freeStack(Stack stack);

#endif
