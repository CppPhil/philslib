#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Illegal number of parameters. Enter Debug or Release."
    exit 1
fi

if [ ! -f ./test/doctest.h ]; then
    wget -q https://raw.githubusercontent.com/onqtam/doctest/master/doctest/doctest.h -P ./test
fi

if [ "$1" == "Debug" ]; then
    mkdir Debug
    cd Debug
    cmake -DCMAKE_BUILD_TYPE=Debug ..
fi

if [ "$1" == "Release" ]; then
    mkdir Release
    cd Release
    cmake -DCMAKE_BUILD_TYPE=Release ..
fi

exit 0

