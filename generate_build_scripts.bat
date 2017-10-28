@echo off

bitsadmin.exe /transfer "doctest" "https://raw.githubusercontent.com/onqtam/doctest/master/doctest/doctest.h" "%CD%\test\doctest.h"

cmake -G %1 .

