#!/bin/sh
cd ~/numguesser++
clear
make ng++
make build-pkg
if [ $1 ]; then
    clear
    ng++ $1 $2
else
    clear
    ng++
fi
