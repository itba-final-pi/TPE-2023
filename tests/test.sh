#!/bin/bash
TOTAL_TESTS=0
ERROR=0

for file in `ls ./files -1 | egrep ".*.test.c"`
do
    echo "$file" | egrep '.*template.*' -q
    if [[ "$?" -ne 0 && $ERROR -eq 0 ]]
    then
        gcc "$file" -DDEBUG_RUN_TESTS -Wall -pedantic -std=c99 -Werror -fsanitize=address -o test.out
        GCC_EXITC=$?
        if [ $GCC_EXITC -ne 0 ]
        then
            echo "::error file={$file}::GCC failed to compile code for test: $file"
            ERROR=2
        fi

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
done