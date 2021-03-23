@echo off

REM Builds and runs the tests using MinGW.
REM Builds in Debug mode for x64 architecture.

set dir=%~dp0
set prev_dir=%CD%

cd "%dir%"

set mingw_dir=mingw_dist

mkdir %mingw_dir%
cd %mingw_dir%

set nuwen_archive=mingw-17.1-without-git.exe
set url=https://nuwen.net/files/mingw/%nuwen_archive%

if exist %mingw_dir%\ (
  echo %mingw_dir% exists, assuming it contains a valid MinGW distribution!
) else (
  bitsadmin.exe /transfer "MinGW Download" "%url%" "%cd%\%nuwen_archive%"

  if errorlevel 1 (
    echo Failure to download MinGW!
    exit /B 1
  )

  %nuwen_archive% -y

  if errorlevel 1 (
    echo Could not extract self-extracting MinGW archive!
    exit /B 1
  )
)

cd ..

mkdir build

cd ..\%mingw_dir%\MinGW && set_distro_paths.bat && cd ..\..\build && cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -DARCH=x64 -DPL_BUILD_TESTS=ON ..

if errorlevel 1 (
  echo Failure to run CMake generator
  exit /B 1
)

cd ..\%mingw_dir%\MinGW && set_distro_paths.bat && cd ..\..\build && make

if errorlevel 1 (
  echo make failed. MinGW build aborted, exiting.
  exit /B 1
)

ctest --verbose .

if errorlevel 1 (
  echo ctest failed, exiting.
  exit /B 1
)

cd "%prev_dir%"
exit /B 0

