@echo off

bitsadmin.exe /transfer "doctest" "https://raw.githubusercontent.com/onqtam/doc
test/master/doctest/doctest.h" "%CD%\test\doctest.h"

cmake -G %1 .

cmake --build .

