### GLOBAL SETTINGS
cmake_minimum_required(VERSION 3.1)

project("philslib" CXX)

# Options
option(PHILISLIB_BUILD_TESTS "Build the unit test suite" ON)

# Use latest standard available but at least C++-14
if    (DEFINED CMAKE_CXX20_STANDARD_COMPILE_OPTION OR DEFINED CMAKE_CXX20_EXTENSION_COMPILE_OPTION)
	set(CMAKE_CXX_STANDARD 20)
elseif(DEFINED CMAKE_CXX17_STANDARD_COMPILE_OPTION OR DEFINED CMAKE_CXX17_EXTENSION_COMPILE_OPTION)
	set(CMAKE_CXX_STANDARD 17)
else()
	set(CMAKE_CXX_STANDARD 14)
endif()

set(CMAKE_CXX_STANDARD_REQUIRED ON)

## Dependencies
find_package(Threads REQUIRED)

# Header only Library
set(LIBRARY_NAME "philslib")

file(GLOB_RECURSE LIB_HEADERS
	"include/*.hpp")

# Defined as header only library
add_library(${LIBRARY_NAME} INTERFACE)

target_include_directories(${LIBRARY_NAME} INTERFACE "include")
target_link_libraries(${LIBRARY_NAME} INTERFACE Threads::Threads)

# Hack for IDE's like MSVC see https://stackoverflow.com/a/29214327
add_custom_target(${LIBRARY_NAME}_ide SOURCES ${LIB_HEADERS})

# NDEBUG preprocessor symbol
if (NOT CMAKE_BUILD_TYPE MATCHES Debug)
	target_compile_definitions(${LIBRARY_NAME} INTERFACE "NDEBUG")
endif()

# processor architecture
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER MATCHES ".*clang")
	if(ARCH STREQUAL "x86")
		target_compile_options(${LIBRARY_NAME} PRIVATE "-m32")
	elseif(ARCH STREQUAL "x64")
		target_compile_options(${LIBRARY_NAME} PRIVATE "-m64")
	endif()
endif()

### TEST
if (PHILISLIB_BUILD_TESTS)
	enable_testing()

	set(UNIT_TEST_NAME "unittest")

	file(GLOB_RECURSE TEST_HEADERS
		"test/doctest.h"
		"test/include/*.hpp")

	file(GLOB_RECURSE TEST_SOURCES
		"test/src/*.cpp")

	add_executable(${UNIT_TEST_NAME}
		"${TEST_HEADERS}"
		"${TEST_SOURCES}")

	target_link_libraries(${UNIT_TEST_NAME} ${LIBRARY_NAME})
	target_include_directories(${UNIT_TEST_NAME} PRIVATE "test/include")

	add_test(Unittest ${UNIT_TEST_NAME})

	# MSVC Settings
	if (MSVC)
		# Warning flags
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "/W4" "/WX")

		 # Disable MSVC extensions
		if(MSVC_VERSION GREATER_EQUAL "1912")
			target_compile_options(${UNIT_TEST_NAME} PRIVATE "/permissive-")
		endif()

		# Optimization flags
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "$<$<CONFIG:DEBUG>:/Od>")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "$<$<CONFIG:RELEASE>:/O2>")

	# GCC Settings
	elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
		# Warning flags
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Werror" "-Wall" "-Wextra" "-Weffc++" "-pedantic" "-pedantic-errors" "-Wcast-align" "-Wcast-qual" "-Wconversion" "-Wfloat-equal" "-Wmissing-field-initializers" "-Wmissing-include-dirs" "-Wmissing-noreturn" "-Wpointer-arith" "-Wredundant-decls" "-Wshadow" "-Wstack-protector" "-Wstrict-aliasing=2" "-Wunreachable-code" "-Wunused" "-Wunused-parameter" "-Wlogical-op" "-Wold-style-cast" "-Wformat=2")

		if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 6.0)
			target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wduplicated-cond" "-Wnull-dereference")
		endif()

		if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 7.0)
			target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wduplicated-branches" "-Wrestrict")
		endif()

		# Disable undesirable warnings
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wno-noexcept-type" "-Wno-unused-function")

	    # Optimization flags
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "$<$<CONFIG:DEBUG>:-O0>")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "$<$<CONFIG:RELEASE>:-O3>")
	# [Apple]Clang Settings
	elseif(CMAKE_CXX_COMPILER MATCHES ".*clang")
		# Warning flags
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Werror" "-Weverything")

		# Disable undesirable warnings
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wno-c++1z-extensions" "-Wno-c++98-compat" "-Wno-weak-vtables" "-Wno-documentation-unknown-command" "-Wno-padded" "-Wno-c++98-c++11-compat-pedantic" "-Wno-c++98-compat-pedantic" "-Wno-unknown-warning-option" "-Wno-double-promotion" "-Wno-unused-template" "-Wno-missing-prototypes" "-Wno-exit-time-destructors" "-Wno-unused-function")

		# Optimization flags
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "$<$<CONFIG:DEBUG>:-O0>")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "$<$<CONFIG:RELEASE>:-O3>")
	endif()
endif()
