@echo off

FOR /F "tokens=* USEBACKQ" %%F IN (`dir *.cpp *hh *hpp *h /b/s`) DO (
    SET var=%%F
)

clang-format -i %var%
