@echo off

REM calculate the amount of command line parameters
set argC=0
for %%x in (%*) do Set /A argC+=1

If NOT %argC% EQU %playernum% (
    echo "Invalid command line parameters. Pass Visual Studio 14 for instance and Debug or Release"
    EXIT /B 1
)

bitsadmin.exe /transfer "doctest" "https://raw.githubusercontent.com/onqtam/doctest/master/doctest/doctest.h" "%CD%\test\doctest.h"

If "%2"=="Debug" (
    mkdir Debug
    cd Debug
    cmake -G %1 -DCMAKE_BUILD_TYPE=Debug ..
)

If "%2"=="Release" (
    mkdir Release
    cd Release
    cmake -G %1 -DCMAKE_BUILD_TYPE=Release ..
)

EXIT /B 0

