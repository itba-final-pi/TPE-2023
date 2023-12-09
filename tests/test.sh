#!/bin/bash
TOTAL_TESTS=0
ERROR=0

CITIES="MON NYC"

for CITY in $CITIES
do

    # Check if the code for the main source compiles
    # The output binary isn't tested, the source is just checked to make sure it compiles
    make all CITY=$CITY
    GCC_EXITC=$?

    if [[ $GCC_EXITC -ne 0 ]]
    then
        echo "::error title={Failed to compile main. CITY=$CITY} file={main.c}::GCC failed to compile MAIN SOURCE CODE"
        ERROR=2
    fi

    make clean

    test_files=`ls -1 ./tests/files | egrep ".*.test.c"`

    for file in $test_files
    do
        echo "$file" | egrep '.*template.*' -q
        if [[ "$?" -ne 0 && $ERROR -eq 0 ]]
        then
			      rm -rf ./tests/test-out/*
            make test file="./tests/files/$file" CITY=$CITY

            GCC_EXITC=$?
            if [ $GCC_EXITC -ne 0 ]
            then
                echo "::error file={$file}::GCC failed to compile code for test: $file. CITY=$CITY"
                ERROR=2
            fi

            # If the code compiled succesfully, then try to execute it
            if [[ $ERROR -eq 0 ]]
            then
                ./tests/test.out
                GCC_EXEC=$?
                rm -f ./tests/test.out
                if [ $GCC_EXEC -ne 0 ]
                then
                    echo "::error file={$file}::Code failed at runtime on test: $file. CITY=$CITY"
                    ERROR=3
                fi
                let TOTAL_TESTS=TOTAL_TESTS+1
            fi

            rm -f ./tests/test.out

        fi
    done


    if [[ $ERROR -ne 0 ]]; then
      break
    fi

done
