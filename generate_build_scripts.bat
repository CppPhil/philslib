@echo off

If "%~1"=="" goto ERROR

If "%~2"=="" goto ERROR

If "%~3"=="" goto ERROR

bitsadmin.exe /transfer "doctest" "https://raw.githubusercontent.com/onqtam/doctest/master/doctest/doctest.h" "%CD%\test\doctest.h"

set isx86=false
set isx64=false
set stringToUse=""

If "%3"=="x86" (
    set isx86=true
    set stringToUse=""
) Else (
    If "%3"=="x64" (
        set isx64=true
        set stringToUse="Win64"
    )
)

If "%2"=="Debug" (
    If %isx86% equ true (
        mkdir Debug_x86
        cd Debug_x86
    ) Else (
        If %isx64% equ true (
            mkdir Debug_x64
            cd Debug_x64
        ) Else (
            goto ERROR
        )
    )
    
    cmake -G "%1 %stringToUse%" -DCMAKE_BUILD_TYPE=Debug ..
)

If "%2"=="Release" (
    If %isx86% equ true (
        mkdir Release_x86
        cd Release_x86
    ) Else (
        If %isx64% equ true (
            mkdir Release_x64
            cd Release_x64
        ) Else (
            goto ERROR
        )
    )
    
    cmake -G "%1 %stringtoUse%" -DCMAKE_BUILD_TYPE=Release ..
)

cd ..
EXIT /B 0

:ERROR
    echo "Invalid parameters. You must pass Visual Studio 15 Win32/64 or Visual Studio 14 for the first parameter, Debug or Release for the second parameter and x86 or x64 for the third parameter."
    EXIT /B 1

