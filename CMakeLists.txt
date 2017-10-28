### GLOBAL SETTINGS ###
cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Weffc++ -pedantic -pedantic-errors -Wcast-align -Wcast-qual -Wconversion -Wfloat-equal -Wmissing-field-initializers -Wmissing-include-dirs -Wmissing-noreturn -Wpointer-arith -Wredundant-decls -Wshadow -Wstack-protector -Wstrict-aliasing=2 -Wunreachable-code -Wunused -Wunused-parameter")
endif()

find_package(Threads REQUIRED)

### STATICALLY LINKED LIBRARY ###
set(LIBRARY_NAME philslib)

set(LIB_HEADERS
    include/pl/algo/clamp.hpp
    include/pl/algo/destroy.hpp
    include/pl/algo/destroy_at.hpp
    include/pl/algo/erase.hpp
    include/pl/algo/for_each_n.hpp
    include/pl/algo/ranged_algorithms.hpp
    include/pl/algo/slide.hpp
    include/pl/algo/uninitialized_default_construct.hpp
    include/pl/algo/uninitialized_default_construct_n.hpp
    include/pl/algo/uninitialized_move.hpp
    include/pl/algo/uninitialized_move_n.hpp
    include/pl/algo/uninitialized_value_construct.hpp
    include/pl/algo/uninitialized_value_construct_n.hpp
    include/pl/cont/back.hpp
    include/pl/cont/data.hpp
    include/pl/cont/front.hpp
    include/pl/cont/make_array.hpp
    include/pl/cont/size.hpp
    include/pl/cont/to_array.hpp
    include/pl/meta/bool_constant.hpp
    include/pl/meta/conjunction.hpp
    include/pl/meta/container_traits.hpp
    include/pl/meta/detection_idiom.hpp
    include/pl/meta/disable_if.hpp
    include/pl/meta/disjunction.hpp
    include/pl/meta/identity.hpp
    include/pl/meta/is_reference_wrapper.hpp
    include/pl/meta/iterator_traits.hpp
    include/pl/meta/negation.hpp
    include/pl/meta/nested_types.hpp
    include/pl/meta/none.hpp
    include/pl/meta/uncvref.hpp
    include/pl/meta/void_t.hpp
    include/pl/thd/concurrent.hpp
    include/pl/thd/monitor.hpp
    include/pl/thd/then.hpp
    include/pl/thd/thread_pool.hpp
    include/pl/thd/thread_safe_queue.hpp
    include/pl/alloca.hpp
    include/pl/annotations.hpp
    include/pl/anonymous_variable.hpp
    include/pl/apply.hpp
    include/pl/as_bytes.hpp
    include/pl/as_const.hpp
    include/pl/asprintf.hpp
    include/pl/assert.hpp
    include/pl/begin_end.hpp
    include/pl/begin_end_macro.hpp
    include/pl/bitmask.hpp
    include/pl/bits.hpp
    include/pl/bswap.hpp
    include/pl/byte.hpp
    include/pl/char_to_int.hpp
    include/pl/checked_delete.hpp
    include/pl/compiler.hpp
    include/pl/concept_poly.hpp
    include/pl/current_function.hpp
    include/pl/eprintf.hpp
    include/pl/except.hpp
    include/pl/for_each_argument.hpp
    include/pl/glue.hpp
    include/pl/hash.hpp
    include/pl/inline.hpp
    include/pl/integer.hpp
    include/pl/invoke.hpp
    include/pl/iterate_reversed.hpp
    include/pl/make_from_tuple.hpp
    include/pl/memxor.hpp
    include/pl/named_operator.hpp
    include/pl/negate_predicate.hpp
    include/pl/no_macro_substitution.hpp
    include/pl/numeric.hpp
    include/pl/observer_ptr.hpp
    include/pl/os.hpp
    include/pl/overload.hpp
    include/pl/packed.hpp
    include/pl/print_bytes_as_hex.hpp
    include/pl/random_number_generator.hpp
    include/pl/raw_memory_array.hpp
    include/pl/raw_storage.hpp
    include/pl/restrict.hpp
    include/pl/source_line.hpp
    include/pl/strdup.hpp
    include/pl/stringify.hpp
    include/pl/timer.hpp
    include/pl/toggle_bool.hpp
    include/pl/unrelated_pointer_cast.hpp
    include/pl/unused.hpp
    include/pl/vla.hpp
    include/pl/zero_memory.hpp)

set(LIB_SOURCES
    src/pl/thd/thread_pool.cpp
    src/pl/asprintf.cpp
    src/pl/eprintf.cpp
    src/pl/except.cpp
    src/pl/print_bytes_as_hex.cpp
    src/pl/strdup.cpp
    src/pl/timer.cpp)

add_library(${LIBRARY_NAME} STATIC "${LIB_HEADERS}" "${LIB_SOURCES}")

target_link_libraries(${LIBRARY_NAME} Threads::Threads)

### TEST ###
enable_testing()

set(UNIT_TEST_NAME unittest)

set(TEST_SOURCES
    test/src/test_main.cpp)

add_executable(${UNIT_TEST_NAME} "${TEST_SOURCES}" "${LIB_HEADERS}") 

target_link_libraries(${UNIT_TEST_NAME} Threads::Threads)
target_link_libraries(${UNIT_TEST_NAME} ${LIBRARY_NAME})

add_test(Unittest ${UNIT_TEST_NAME})

