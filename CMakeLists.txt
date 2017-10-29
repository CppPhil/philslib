### GLOBAL SETTINGS
cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Warning flags
if(MSVC)
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra -Weffc++ -pedantic -pedantic-errors -Wcast-align -Wcast-qual -Wconversion -Wfloat-equal -Wmissing-field-initializers -Wmissing-include-dirs -Wmissing-noreturn -Wpointer-arith -Wredundant-decls -Wshadow -Wstack-protector -Wstrict-aliasing=2 -Wunreachable-code -Wunused -Wunused-parameter")
elseif(CMAKE_CXX_COMPILER MATCHES ".*clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Weverything")
endif()

# disable some clang warnings
if(CMAKE_CXX_COMPILER MATCHES ".*clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-c++1z-extensions -Wno-c++98-compat -Wno-weak-vtables -Wno-documentation-unknown-command -Wno-padded")
endif()

# Optimization flags
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")    
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
endif()

# NDEBUG preprocessor symbol
if (NOT CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DNDEBUG)
endif()

# processor architecture
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER MATCHES ".*clang")
    if(ARCH STREQUAL "x86")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
    elseif(ARCH STREQUAL "x64")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")
    endif()
endif()

# have clang use a modern libstdc++
if(CMAKE_CXX_COMPILER MATCHES ".*clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --gcc-toolchain=/usr")
endif()

find_package(Threads REQUIRED)

### STATICALLY LINKED LIBRARY
set(LIBRARY_NAME philslib)

file(GLOB LIB_HEADERS
    include/pl/algo/*.hpp
    include/pl/cont/*.hpp
    include/pl/meta/*.hpp
    include/pl/thd/*.hpp
    include/pl/*.hpp)

file(GLOB LIB_SOURCES
    src/pl/algo/*.cpp
    src/pl/cont/*.cpp
    src/pl/meta/*.cpp
    src/pl/thd/*.cpp
    src/pl/*.cpp)

add_library(${LIBRARY_NAME} STATIC "${LIB_HEADERS}" "${LIB_SOURCES}")

target_link_libraries(${LIBRARY_NAME} Threads::Threads)

### TEST
enable_testing()

set(UNIT_TEST_NAME unittest)

set(TEST_HEADERS
    test/doctest.h)

file(GLOB TEST_SOURCES
    test/src/algo/*.cpp
    test/src/*.cpp)

add_executable(${UNIT_TEST_NAME} 
    "${TEST_HEADERS}" 
    "${TEST_SOURCES}" 
    "${LIB_HEADERS}") 

target_link_libraries(${UNIT_TEST_NAME} Threads::Threads)
target_link_libraries(${UNIT_TEST_NAME} ${LIBRARY_NAME})

add_test(Unittest ${UNIT_TEST_NAME})

