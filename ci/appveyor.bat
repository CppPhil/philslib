@echo off

set gen=

call :generator %COMPILER% gen

set build_types = Debug Release

set archs = x86 x64

(for %%build_type in (%build_types%) do (
  (for %%arch in (%archs%) do (
    echo "%%build_type %%arch"

    set platform=
    call :platform_str %%arch platform
  
    mkdir "%%build_type_%%arch"
    cd "%%build_type_%%arch"
  
    If %COMPILER%=="msvc19" (
      cmake -G "%gen%" -A %platform% -DCMAKE_BUILD_TYPE=%%build_type -DPL_BUILD_TESTS=ON ..
      msbuild philslib_project.sln -property:Configuration=%%build_type /maxcpucount
    ) Else (
      cmake -G "%gen%" -DCMAKE_BUILD_TYPE=%%build_type -DPL_BUILD_TESTS=ON ..
      msbuild philslib_project.sln /p:Configuration=%%build_type;Platform="%platform%" /maxcpucount
    )
    
    cd ..
  ))
))

EXIT /B 0

:generator
If "%1"=="msvc15" (
  set %2="Visual Studio 14 2015"
) Else (
  If "%1"=="msvc17" (
    set %2="Visual Studio 15 2017"
  ) Else (
    set %2="Visual Studio 16 2019"
  )
)
EXIT /B 0

:platform_str
If "%1"=="x86" (
  set %2="Win32"
) Else (
  set %2="x64"
)
EXIT /B 0

