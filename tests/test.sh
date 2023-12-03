#!/bin/bash
TOTAL_TESTS=0
ERROR=0

# Check if the code for the main source compiles
# The output binary isn't tested, the source is just checked to make sure it compiles
# @todo Replace with Makefile
gcc "../main.c" "../src/BikeStation.c" \
-I. -I../headers \
-Wall -Wextra -Werror -pedantic -std=c99 -fsanitize=address -I. -I../src/ -I../headers -o test.out

GCC_EXITC=$?

if [[ $GCC_EXITC -ne 0 ]]
then
    echo "::error file={main.c}::GCC failed to compile MAIN SOURCE CODE"
    ERROR=2
fi

rm -f test.out

for file in `ls -1 files | egrep ".*.test.c"`
do
    echo "$file" | egrep '.*template.*' -q
    if [[ "$?" -ne 0 && $ERROR -eq 0 ]]
    then
        # @todo Replace with Makefile
        gcc "./files/$file" "../src/BikeStation.c" \
        -I. -I../headers \
        -DDEBUG_RUN_TESTS -Wall -Wextra -Werror -pedantic -std=c99  -fsanitize=address -o test.out

        GCC_EXITC=$?
        if [ $GCC_EXITC -ne 0 ]
        then
            echo "::error file={$file}::GCC failed to compile code for test: $file"
            ERROR=2
        fi

        # If the code compiled succesfully, then try to execute it
        if [[ $ERROR -eq 0 ]]
        then
            ./test.out
            GCC_EXEC=$?
            rm -f ./test.out
            if [ $GCC_EXEC -ne 0 ]
            then
                echo "::error file={$file}::Code failed at runtime on test: $file"
                ERROR=3
            fi
            let TOTAL_TESTS=TOTAL_TESTS+1
        fi

        rm -f ./test.out

    fi
done
