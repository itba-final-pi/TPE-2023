# Testing

Automatic testing is meant to catch bugs and compilation issues early and often, instead of leading to hard to debug problems down the line

Here, various test files can be created to catch bugs, which will get ran on several platforms at once

## Testing targets
All tests are run on the following targets, simultaneously:

- ubuntu-22.04
- ubuntu-20.04
- ITBA's Pampero Server

## Compilation flags
Tests are compiled on each target using the following GCC flags

```sh
gcc $test_files \
-DDEBUG_RUN_TESTS \
-Wall \
-Werror \
-pedantic \
-std=c99 \
-fsanitize=address
```

Where:
- `DEBUG_RUN_TESTS` is meant to prevent accidental compilation of tests files alongside main project files, making sure tests are compiled deliberately
- `Werror` will fail tests if any GCC warning is present. This means compiled warnings **must** be addressed in order for tests to pass

## Test structure

```c
// Must be before including assert.h . Guarantees assert macro expressions always work correctly
#undef NDEBUG

#include <assert.h>

// Always include tests.h, makes sure tests are not compiled alongside regular code accidentally
#include "tests.h"

// include a main function
int
main(void) {
    // Your tests here👇
    assert(1 == 1);

    return 0;
}
```