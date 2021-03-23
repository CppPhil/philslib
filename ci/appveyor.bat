@echo off

if "%COMPILER%"=="MinGW" (
  call test.bat
  
  if errorlevel 1 (
    EXIT /B 1
  )
) else (
  call ci\msvc.bat
  
  if errorlevel 1 (
  EXIT /B 1
  )
)

EXIT /B 0
