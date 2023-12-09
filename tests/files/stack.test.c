#undef NDEBUG

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "tests.h"

#include "Stack.h"

int
main(void) {
    Stack stack = newStack();
    int values[] = { 1, 2, 3, 4, 5, 42 };
    int value_count = sizeof(values)/sizeof(*values);

    assert( isEmptyStack(stack) == 1 );

    for (int i = 0; i < value_count; i++) {
        push(stack, (void *) (values + i));
    }

    assert( isEmptyStack(stack) == 0 );
    assert( (int) stackSize(stack) == value_count );

    // First In -> Last Out
    for (int i = value_count - 1; i >= 0; i--) {
        assert( pop(stack) == (void *) (values + i) );
    }

    push(stack, values);

    assert( *(int *)pop(stack) == *values );
    assert( pop(stack) == NULL );

    freeStack(stack);

    return 0;
}
