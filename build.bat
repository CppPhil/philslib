@echo off

If "%~1"=="" goto ERROR

If "%~2"=="" goto ERROR

bitsadmin.exe /transfer "doctest" "https://raw.githubusercontent.com/onqtam/doctest/master/doctest/doctest.h" "%CD%\test\doctest.h"

If "%2"=="Debug" (
    mkdir Debug
    cd Debug
    cmake -G %1 -DCMAKE_BUILD_TYPE=Debug ..
    cmake --build . --config Debug
)

If "%2"=="Release" (
    mkdir Release
    cd Release
    cmake -G %1 -DCMAKE_BUILD_TYPE=Release ..
    cmake --build . --config Release
)

EXIT /B 0

:ERROR
    echo "Invalid parameters. You must pass Visual Studio 15 for instance and Debug or Release"
    EXIT /B 1

