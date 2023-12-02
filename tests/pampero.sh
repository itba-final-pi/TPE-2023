#!/bin/bash

#########################################
# This code is not meant to run locally
# This will get copied and run on Pampero
# Please take this into consideration if editing the file
#
# If you want to test locally and not in CI:
#   - Create a local env variable GIT_SECRET with your PAT
#   - Use your own login credentials for Pampero
#     test-c.yml (ITBA_USR_PAMPERO/ ITBA_PWD_PAMPERO)
#
# If you are running this with your own Pampero user login credential please do note:
# *** This code will force delete the repository located under /$USER/Github/$FOLDER ***
#########################################

FOLDER="TPE-2023"
REPO="itba-final-pi/TPE-2023"
BRANCH_NAME="master"

# Clone the $GIT_REF repo into ./Github/$FOLDER using the corresponding $GIT_SECRET
if [ ! -d "Github" ]; then mkdir "Github" ; fi
cd ./Github

if [ -d "./$FOLDER" ]; then rm -Rf "./$FOLDER" ; fi

git clone "https://$GIT_SECRET@github.com/$REPO.git" "./$FOLDER"

if [ $? -ne 0 ]
then
    echo "Failed to clone repo"
    exit 1
fi

cd "./$FOLDER"
git checkout $BRANCH_NAME

# Run tests
cd "./tests"

# defines: TOTAL_TEST, ERROR
source ./test.sh

if [[ $ERROR -eq 0 ]]
then
    echo "::notice::All ($TOTAL_TESTS) tests ran successfully on Pampero"
else
    echo "::warning::Pampero had a non-zero exit code ($ERROR). Tests run: $TOTAL_TESTS."
fi

exit $ERROR