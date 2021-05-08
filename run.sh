#!/bin/bash
echo "build the program ..."

VAR=$(make clean && make)

if [ $? -eq 0 ]; then
echo "successfuly build"
echo "run the program"
./Calculator
fi

VAR=$(make clean)

if [ $? -eq 0 ]; then
echo "build files removed successfully!"
fi

