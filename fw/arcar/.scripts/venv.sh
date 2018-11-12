#!/usr/bin/env bash
# create and install python enviroment
# wykys 2018

SCRIPTS_DIR=.scripts

if [ -d $SCRIPTS_DIR ]; then
    cd $SCRIPTS_DIR
elif [[ $(pwd) != */$SCRIPTS_DIR ]]; then
    echo "Error: You must go to the root folder of the project!"
    exit -1
fi

if [ -d ".venv" ]; then
    echo "remove old venv"
    rm .venv -rf
fi

echo "create new venv"
python3 -m venv .venv

echo "activate venv"
. .venv/bin/activate

echo "upgrade pip"
pip install --upgrade pip

echo "install modules from requirements"
pip install -r requirements.txt

echo "installed modules"
pip freeze
