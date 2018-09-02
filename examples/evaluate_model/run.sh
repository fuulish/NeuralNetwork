#!/bin/bash

if [ ! -f ./ann.x ]; then
    echo "executable not found, trying to build"
    make ann.x
fi

./ann.x model.nn features.dat
