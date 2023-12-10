# Testing

Automatic testing is meant to catch bugs and compilation issues early and often, instead of leading to hard to debug problems down the line

Here, various test files can be created to catch bugs, which will get ran on several platforms at once

## Testing targets
All tests are run on the following targets, simultaneously:

- ubuntu-22.04
- ubuntu-20.04
- ITBA's Pampero Server

## Compilation flags
Tests are compiled on each target using the following GCC flags (see [Makefile](../Makefile))

```sh
gcc $test_files \
-DDEBUG_RUN_TESTS \
-Wall \
-Wextra \
-Werror \
-pedantic \
-std=c99 \
-fsanitize=address
```

Where:
- `DEBUG_RUN_TESTS` is meant to prevent accidental compilation of tests files alongside main project files, making sure tests are compiled deliberately, also allows some debugging functions to be conditionally added to source.
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

## Datasets

In order to get the datasets used by tests, you may need to run the following commands:

```sh
curl -o data.zip "$DATASET_URL"
unzip data.zip -d "DATASET_NAME"
```

Where the variables take on one of the following sets of values:

| Dataset  | $DATASET_NAME          | $DATASET_URL                                                               |
|----------|------------------------|----------------------------------------------------------------------------|
| Small    | Datasets Alumnos SMALL | https://storage.googleapis.com/datasets-tpe/Datasets%20Alumnos%20SMALL.zip |
| Complete | Datasets Alumnos       | https://storage.googleapis.com/datasets-tpe/Datasets\%20Alumnos.zip         |

In the unlikely event [`us-east1` is down](https://status.cloud.google.com/regional/americas) you may get the complete dataset from the original source

<details>

<summary>Follow these steps to build `Datasets Alumnos Small`</summary>

Download the complete source to the repo's parent directory, then run the following script

```sh
dir="../Datasets Alumnos"
files=`ls -1 "$dir"`

for file in $files
do
    echo "$file"
    if [[ -f "$dir/$file" ]]
    # This skips the "Mas" folder
    then
        head "$dir/$file" > "$dir SMALL/$file"
    fi
done

```

</details>

