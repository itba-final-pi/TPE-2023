// Do not remove this check.
// Meant to prevent tests from getting compiled with production code accidentally 👇
#ifndef DEBUG_RUN_TESTS
    #error "File was not compiled as test. Be careful NOT to treat these the same as production. Do not compile tests manually, use the ./test.sh file"
#endif

#define FLOAT_EPSILON 0.00001

#define COMPARE_FLOATS(f0, f1) ( ( (f0) - (f1) > -FLOAT_EPSILON) && ( (f0) - (f1) < FLOAT_EPSILON) )
