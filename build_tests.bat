@echo off

If "%~1"=="" goto ERROR

If "%~2"=="" goto ERROR

If "%~3"=="" goto ERROR

set NLM=^


set NL=^^^%NLM%%NLM%^%NLM%%NLM%

echo ### GLOBAL SETTINGS %NL%^
cmake_minimum_required(VERSION 3.1) %NL%^
 %NL%^
project(Project) %NL%^
 %NL%^
if(MSVC) %NL%^
    if(MSVC_VERSION GREATER_EQUAL "1911") %NL%^
        set(CMAKE_CXX_STANDARD 17) %NL%^
    else() %NL%^
        set(CMAKE_CXX_STANDARD 14) %NL%^
    endif() %NL%^
else() %NL%^
    set(CMAKE_CXX_STANDARD 14) %NL%^
endif() %NL%^
 %NL%^
set(CMAKE_CXX_STANDARD_REQUIRED ON) %NL%^
 %NL%^
# Warning flags %NL%^
if(MSVC) %NL%^
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]") %NL%^
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}") %NL%^
    else() %NL%^
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4") %NL%^
    endif() %NL%^
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX) %NL%^
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra -Weffc++ -pedantic -pedantic-errors -Wcast-align -Wcast-qual -Wconversion -Wfloat-equal -Wmissing-field-initializers -Wmissing-include-dirs -Wmissing-noreturn -Wpointer-arith -Wredundant-decls -Wshadow -Wstrict-aliasing=2 -Wunreachable-code -Wunused -Wunused-parameter -Wlogical-op -Wold-style-cast -Wformat=2") %NL%^
     %NL%^
    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 6.0) %NL%^
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wduplicated-cond -Wnull-dereference") %NL%^
    endif() %NL%^
     %NL%^
    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 7.0) %NL%^
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wduplicated-branches -Wrestrict") %NL%^
    endif() %NL%^
elseif(CMAKE_CXX_COMPILER MATCHES ".*clang") %NL%^
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Weverything") %NL%^
endif() %NL%^
 %NL%^
if(MSVC) %NL%^
    # Treat warnings as errors when using msvc. %NL%^
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX") %NL%^
endif() %NL%^
 %NL%^
# disable undesirable g++ warnings %NL%^
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX) %NL%^
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-noexcept-type -Wno-unused-function") %NL%^
endif() %NL%^
 %NL%^
# disable undesirable clang warnings %NL%^
if(CMAKE_CXX_COMPILER MATCHES ".*clang") %NL%^
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-c++1z-extensions -Wno-c++98-compat -Wno-weak-vtables -Wno-documentation-unknown-command -Wno-padded -Wno-c++98-c++11-compat-pedantic -Wno-c++98-compat-pedantic -Wno-unknown-warning-option -Wno-double-promotion -Wno-unused-template -Wno-missing-prototypes -Wno-exit-time-destructors -Wno-unused-function") %NL%^
endif() %NL%^
 %NL%^
# Optimization flags %NL%^
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX) %NL%^
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0") %NL%^
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3") %NL%^
elseif(CMAKE_CXX_COMPILER MATCHES ".*clang") %NL%^
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0") %NL%^
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3") %NL%^
elseif(MSVC) %NL%^
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Od") %NL%^
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2") %NL%^
endif() %NL%^
 %NL%^
# NDEBUG preprocessor symbol %NL%^
if (NOT CMAKE_BUILD_TYPE MATCHES Debug) %NL%^
    add_definitions(-DNDEBUG) %NL%^
endif() %NL%^
 %NL%^
# processor architecture %NL%^
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER MATCHES ".*clang") %NL%^
    if(ARCH STREQUAL "x86") %NL%^
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32") %NL%^
    elseif(ARCH STREQUAL "x64") %NL%^
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64") %NL%^
    endif() %NL%^
endif() %NL%^
 %NL%^
### TEST %NL%^
enable_testing() %NL%^
 %NL%^
find_package(Threads REQUIRED) %NL%^
 %NL%^
file(GLOB LIB_HEADERS %NL%^
     include/pl/algo/*.hpp %NL%^
     include/pl/cont/*.hpp %NL%^
     include/pl/meta/*.hpp %NL%^
     include/pl/thd/*.hpp %NL%^
     include/pl/*.hpp) %NL%^
 %NL%^
set(UNIT_TEST_NAME unittest) %NL%^
 %NL%^
file(GLOB TEST_HEADERS %NL%^
     test/doctest.h %NL%^
     test/include/*.hpp) %NL%^
 %NL%^
file(GLOB TEST_SOURCES %NL%^
     test/src/algo/*.cpp %NL%^
     test/src/cont/*.cpp %NL%^
     test/src/meta/*.cpp %NL%^
     test/src/thd/*.cpp %NL%^
     test/src/*.cpp) %NL%^
 %NL%^
add_executable(${UNIT_TEST_NAME} %NL%^
    "${TEST_HEADERS}" %NL%^
    "${TEST_SOURCES}" %NL%^
    "${LIB_HEADERS}") %NL%^
 %NL%^
target_link_libraries(${UNIT_TEST_NAME} Threads::Threads) %NL%^
 %NL%^
add_test(Unittest ${UNIT_TEST_NAME}) > CMakeLists.txt

set isx86=false
set isx64=false
set platformStr=""

If "%3"=="x86" (
    set isx86=true
    set platformStr="Win32"
) Else (
    If "%3"=="x64" (
        set isx64=true
        set platformStr="x64"
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
    
    cmake -G %1 -DCMAKE_BUILD_TYPE=Debug ..
    msbuild Project.sln /p:Configuration=Debug;Platform="%platformStr%" /maxcpucount
    cd ..
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
    
    cmake -G %1 -DCMAKE_BUILD_TYPE=Release ..
    msbuild Project.sln /p:Configuration=Release;Platform="%platformStr%" /maxcpucount
    cd ..
)

del "CMakeLists.txt"
EXIT /B 0

:ERROR
    echo "Invalid parameters. You must pass Visual Studio 15 2017 [Win64] or Visual Studio 14 2015 [Win64] for the first parameter, Debug or Release for the second parameter and x86 or x64 for the third parameter."
    del "CMakeLists.txt"
    EXIT /B 1

