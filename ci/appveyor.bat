@echo off

set gen_num=

set gen_year=

call :generator %COMPILER% gen_num gen_year

echo "Debug x86"
mkdir "Debug_x86"
cd "Debug_x86"
cmake -G "Visual Studio %gen_num% %gen_year%" -A Win32 -DCMAKE_BUILD_TYPE=Debug -DPL_BUILD_TESTS=ON ..
If errorlevel 1 (
  EXIT /B 1
)
msbuild philslib_project.sln -property:Configuration=Debug /maxcpucount
If errorlevel 1 (
  EXIT /B 1
)
ctest --verbose .
If errorlevel 1 (
  EXIT /B 1
)
cd ..

echo "Release x86"
mkdir "Release_x86"
cd "Release_x86"
cmake -G "Visual Studio %gen_num% %gen_year%" -A Win32 -DCMAKE_BUILD_TYPE=Release -DPL_BUILD_TESTS=ON ..
If errorlevel 1 (
  EXIT /B 1
)
msbuild philslib_project.sln -property:Configuration=Release /maxcpucount
If errorlevel 1 (
  EXIT /B 1
)
ctest --verbose .
If errorlevel 1 (
  EXIT /B 1
)
cd ..

echo "Debug x64"
mkdir "Debug_x64"
cd "Debug_x64"
cmake -G "Visual Studio %gen_num% %gen_year%" -A x64 -DCMAKE_BUILD_TYPE=Debug -DPL_BUILD_TESTS=ON ..
If errorlevel 1 (
  EXIT /B 1
)
msbuild philslib_project.sln -property:Configuration=Debug /maxcpucount
If errorlevel 1 (
  EXIT /B 1
)
ctest --verbose .
If errorlevel 1 (
  EXIT /B 1
)
cd ..

echo "Release x64"
mkdir "Release_x64"
cd "Release_x64"
cmake -G "Visual Studio %gen_num% %gen_year%" -A x64 -DCMAKE_BUILD_TYPE=Release -DPL_BUILD_TESTS=ON ..
If errorlevel 1 (
  EXIT /B 1
)
msbuild philslib_project.sln -property:Configuration=Release /maxcpucount
If errorlevel 1 (
  EXIT /B 1
)
ctest --verbose .
If errorlevel 1 (
  EXIT /B 1
)
cd ..

EXIT /B 0

:generator
If "%1"=="msvc15" (
  set "%~2=14"
  set "%~3=2015"
  EXIT /B 0
)
If "%1"=="msvc17" (
  set "%~2=15"
  set "%~3=2017"
  EXIT /B 0
)
set "%~2=16"
set "%~3=2019"
EXIT /B 0
