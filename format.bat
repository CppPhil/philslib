@echo off

REM This script is used to run clang-format on the source files.

REM Directory containing this batch script.
set dir=%~dp0

REM Prologue
set prev_dir=%CD%
cd "%dir%"

REM Directories
set include_dir=%dir%\include
set test_dir=%dir%\test
set clang_fmt_dir=%dir%\deps\clang-format

REM files
set fmt_sh=%clang_fmt_dir%\fmt.sh
set dot_clang_format=%clang_fmt_dir%\.clang-format

REM Bash shell
set shell=C:\Program Files\Git\git-bash.exe

REM Format the source files.
call :run_formatter "%include_dir%"
call :run_formatter "%test_dir%"

REM Epilogue
cd "%prev_dir%"
exit /B 0

REM run_formatter function.
REM param %1: A directory to format the source files in.
:run_formatter
cd "%1"
if exist .clang-format (
  del /F /Q .clang-format
)
copy /Y "%dot_clang_format%" .clang-format
call "%shell%" %fmt_sh%
del /F /Q .clang-format
exit /B 0
