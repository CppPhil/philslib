#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "Illegal number of parameters. Enter Debug or Release for the first parameter and x86 or x64 for the second parameter."
    exit 1
fi

if [ ! -f ./test/doctest.h ]; then
    wget -q https://raw.githubusercontent.com/onqtam/doctest/master/doctest/doctest.h -P ./test
fi

isx86=false
isx64=false

if [ "$2" == "x86" ]; then
    isx86=true
fi

if [ "$2" == "x64" ]; then
    isx64=true
fi

if [ "$1" == "Debug" ]; then
    if [ "$isx86" = true ]; then
        mkdir Debug_x86
        cd Debug_x86
    elif [ "$isx64" = true ]; then
        mkdir Debug_x64
        cd Debug_x64
    else
        echo "Invalid architecture. The second parameter must be x86 or x64"
        exit 1
    fi

    cmake -DCMAKE_BUILD_TYPE=Debug -DARCH=$2 ..
fi

if [ "$1" == "Release" ]; then
    if [ "$isx86" = true ]; then
        mkdir Release_x86
        cd Release_x86
    elif [ "$isx64" = true ]; then
        mkdir Release_x64
        cd Release_x64
    else
        echo "Invalid architecture. The second parameter must be x86 or x64"
        exit 1
    fi
    cmake -DCMAKE_BUILD_TYPE=Release -DARCH=$2 ..
fi

exit 0

