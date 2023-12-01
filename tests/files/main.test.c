// This file is meant to be a template for all other tests
// This file is excluded from test runs and is not counted towards the total amount of tests ran

// Make sure assert macro expressions work correctly 👇
#undef NDEBUG

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int
main(void) {
    // Do not remove this check.
    // Meant to prevent tests from getting compiled with production code accidentally 👇
    #ifndef DEBUG_RUN_TESTS
    #error "File was not compiled as test. Be careful NOT to treat these the same as production. Do not compile tests manually, use the ./test.sh file"
    #endif

    // Your tests here👇
    assert(1 == 1);

    return 0;
}