cmake_minimum_required(VERSION 3.1)

project(philslib_project)

file(GLOB LIB_HEADERS
     include/pl/algo/*.hpp
     include/pl/cont/*.hpp
     include/pl/meta/*.hpp
     include/pl/thd/*.hpp
     include/pl/*.hpp)
     
add_library(philslib INTERFACE)
target_include_directories(philslib INTERFACE ${LIB_HEADERS})

add_library(CppPhil::philslib ALIAS philslib)

if(PL_BUILD_TESTS)
    if(MSVC)
        if(MSVC_VERSION GREATER_EQUAL "1911")
            set(CMAKE_CXX_STANDARD 17)
        else()
            set(CMAKE_CXX_STANDARD 14)
        endif()
    else()
        set(CMAKE_CXX_STANDARD 14)
    endif()

    set(CMAKE_CXX_STANDARD_REQUIRED ON)

    # Warning flags
    if(MSVC)
        if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
            string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
        else()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
        endif()
    elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra -Weffc++ -pedantic -pedantic-errors -Wcast-align -Wcast-qual -Wconversion -Wfloat-equal -Wmissing-field-initializers -Wmissing-include-dirs -Wmissing-noreturn -Wpointer-arith -Wredundant-decls -Wshadow -Wstrict-aliasing=2 -Wunreachable-code -Wunused -Wunused-parameter -Wlogical-op -Wold-style-cast -Wformat=2")
        
        if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 6.0)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wduplicated-cond -Wnull-dereference")
        endif()
        
        if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 7.0)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wduplicated-branches -Wrestrict")
        endif()    
    elseif(CMAKE_CXX_COMPILER MATCHES ".*clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Weverything")
    endif()

    if(MSVC)
        # Treat warnings as errors when using msvc.
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX")
    endif()

    # disable undesirable g++ warnings
    if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-noexcept-type -Wno-unused-function")
    endif()

    # disable undesirable clang warnings
    if(CMAKE_CXX_COMPILER MATCHES ".*clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-c++1z-extensions -Wno-c++98-compat -Wno-weak-vtables -Wno-documentation-unknown-command -Wno-padded -Wno-c++98-c++11-compat-pedantic -Wno-c++98-compat-pedantic -Wno-unknown-warning-option -Wno-double-promotion -Wno-unused-template -Wno-missing-prototypes -Wno-exit-time-destructors -Wno-unused-function")
    endif()

    # Optimization flags
    if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")    
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
    elseif(CMAKE_CXX_COMPILER MATCHES ".*clang")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
    elseif(MSVC)
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Od")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
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

    ### TEST
    enable_testing()

    find_package(Threads REQUIRED)

    set(UNIT_TEST_NAME unittest)

    file(GLOB TEST_HEADERS
         test/doctest.h
         test/include/*.hpp)

    file(GLOB TEST_SOURCES
         test/src/algo/*.cpp
         test/src/cont/*.cpp
         test/src/meta/*.cpp
         test/src/thd/*.cpp
         test/src/*.cpp)

    add_executable(${UNIT_TEST_NAME} 
        "${TEST_HEADERS}" 
        "${TEST_SOURCES}" 
        "${LIB_HEADERS}") 

    target_link_libraries(${UNIT_TEST_NAME} Threads::Threads)

    add_test(Unittest ${UNIT_TEST_NAME})
endif()

