#!/usr/bin/env bash
# actavated venv ans run script where is arg
# wykys 2018

SCRIPTS_DIR=.scripts
PWD_TMP=$(pwd)

if [ -d $SCRIPTS_DIR ]; then
    cd $SCRIPTS_DIR
elif [[ $(pwd) != */$SCRIPTS_DIR ]]; then
    echo "Error: You must go to the root folder of the project!"
    exit -1
fi

if [ ! -d ".venv" ]; then
    echo ".venv not exist"
    ./venv.sh
fi

. .venv/bin/activate

cd $PWD_TMP
"$@"
