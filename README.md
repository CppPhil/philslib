# philslib
A C++ header-only library of various utilities.  
This library exists to not have to implement the same   
functionality over and over again in different projects.  
The library implements some C++17 standard library features, as well as  
some features of some of the technical specifications.  
Additionally it provides portable versions of otherwise non-portable functions, as well as
some other utilities.  

## Prerequisites
- A C++14-capable C++ compiler  
- CMake (to build the tests)  
- Doxygen (to generate the documentation)  


## Compilers
The library code and the test code is known to function with:  

- g++ 5.4.1 and newer
- clang++ 3.8 and newer
- msvc15 and newer
 
 
## Installation
As this is a header-only library all you have to do is  
add the `include` subdirectory to your compiler's  
include path.  


## Disabling optional C++17 features
The library optionally uses some C++17 features such as `[[nodiscard]]` and `[[fallthrough]]` if the compiler being used is new enough to support them.  
You can disable C++17 features, even if your compiler supports them, by defining the `PL_NO_CPP17` preprocessor symbol.  
It is recommended to define the `PL_NO_CPP17` globally through your build system, rather than in the source directly.  


## Generating the documentation
To generate the documentation run:  
`doxygen ./Doxyfile `  
To view the generated html documentation using firefox run:  
`firefox ./doc/html/index.html &`  


## Building the tests
### Using a GNU/Linux OS
To build the tests for x86 without optimizations run:  
`bash ./build_tests.sh Debug x86`  

To build the tests for x86 with optimizations run:  
`bash ./build_tests.sh Release x86`  

To build the tests for x64 without optimizations run:  
`bash ./build_tests.sh Debug x64`  

To build the tests for x64 with optimizations run:  
`bash ./build_tests.sh Release x64`   

### Using a Windows OS
Open a Visual Studio Developer Command Prompt of the  
Microsoft Visual C++ Compiler version to be used (msvc15 or newer).  

To build the tests for x86 without optimizations using msvc15 run:  
`build_tests.bat "Visual Studio 14 2015" Debug x86`  

To build the tests for x86 with optimizations using msvc15 run:  
`build_tests.bat "Visual Studio 14 2015" Release x86`  

To build the tests for x64 without optimizations using msvc15 run:  
`build_tests.bat "Visual Studio 14 2015 Win64" Debug x64`  

To build the tests for x64 with optimizations using msvc15 run:  
`build_tests.bat "Visual Studio 14 2015 Win64" Release x64`  

To build the tests for x86 without optimizations using msvc17 run:  
`build_tests.bat "Visual Studio 15 2017" Debug x86`  

To build the tests for x86 with optimizations using msvc17 run:  
`build_tests.bat "Visual Studio 15 2017" Release x86`  

To build the tests for x64 without optimizations using msvc17 run:  
`build_tests.bat "Visual Studio 15 2017 Win64" Debug x64`  

To build the tests for x64 with optimizations using msvc17 run:  
`build_tests.bat "Visual Studio 15 2017 Win64" Release x64`  

## Running the tests
To run the tests after having built the tests  
navigate into the subdirectory named  
`Debug_x86`,  
`Release_x86`,  
`Debug_x64`, or  
`Release_x64`,  
depending on which version was built.  
Then run:  
`ctest --verbose .`  


## Components
This header-only library in the include subdirectory is sub-divided into 5 parts.  

- The algorithm component, corresponding to the algo subdirectory, which implements generic algorithms.  
- The container component, corresponding to the cont subdirectory, which implements utility functions operating on container-like objects.  
- The metaprogramming component, corresponding to the meta subdirectory, which implements various meta functions.  
- The threading component, corresponding to the thd subdirectory, which implements utilities with regard to multithreading.  
- As well as a generic component, corresponding to the header files directly within the include/pl directory, for all other utilities.  


## Overview by file
include/pl/algo/clamp.hpp: The clamp function from C++17.  
include/pl/algo/destroy.hpp: The destroy algorithm from C++17.  
include/pl/algo/destroy_at.hpp: The destroy_at function from C++17.  
include/pl/algo/destroy_n.hpp: The destroy_n algorithm from C++17.  
include/pl/algo/erase.hpp: A convenient implementation of the erase-remove_if idiom, somewhat similar to the uniform container erasure from library fundamentals TS v2.  
include/pl/algo/for_each_n.hpp: The for_each_n algorithm from C++17.  
include/pl/algo/ranged_algorithms.hpp: 'Ranged' versions of many of the C++ standard library algorithms, taking a container rather than a pair of iterators.  
include/pl/algo/slide.hpp: The slide algorithm.  
include/pl/algo/uninitialized_default_construct.hpp: The uninitialized_default_construct algorithm from C++17.  
include/pl/algo/uninitialized_default_construct_n.hpp: The uninitialized_default_construct_n algorithm from C++17.  
include/pl/algo/uninitialized_move.hpp: The uninitialized_move algorithm from C++17.  
include/pl/algo/uninitialized_move_n.hpp: The uninitialized_move_n algorithm from C++17.  
include/pl/algo/uninitialized_value_construct.hpp: The uninitialized_value_construct algorithm from C++17.  
include/pl/algo/uninitialized_value_construct_n.hpp: The uninitialized_value_construct_n algorithm from C++17.  
include/pl/cont/at.hpp: Bounds checked index based access to containers, built-in arrays and initializer_lists.  
include/pl/cont/back.hpp: Non-member back function that also works for built-in arrays.  
include/pl/cont/data.hpp: The data function from C++17.  
include/pl/cont/empty.hpp: The empty function from C++17.  
include/pl/cont/front.hpp: Non-member front function that also works for built-in arrays.  
include/pl/cont/make_array.hpp: Function to conveniently create a std::array, like the one from library fundamentals TS v2.  
include/pl/cont/size.hpp: The size function from C++17.  
include/pl/cont/to_array.hpp: Function to create a std::array from a built-in array, like the one from library fundamentals TS v2.  
include/pl/meta/bool_constant.hpp: bool_constant from C++17.  
include/pl/meta/conjunction.hpp: The conjunction meta function from C++17.  
include/pl/meta/detection_idiom.hpp: An implementation of the detection idiom from library fundamentals TS v2.  
include/pl/meta/disable_if.hpp: disable_if, analogous to std::enable_if.  
include/pl/meta/disjunction.hpp: The disjunction meta function from C++17.  
include/pl/meta/identify.hpp: Meta function to prevent undesired type deduction.  
include/pl/meta/is_initializer_list.hpp: Meta function to determine whether a type is an initializer_list type.  
include/pl/meta/is_reference_wrapper.hpp: Meta functions to determine whether a type is a reference_wrapper type or not.  
include/pl/meta/iterator_traits.hpp: Iterator traits  implementing the hierarchy of the kinds of iterators. Can be used to check whether a given iterator satisfies the minimum iterator requirement.  
include/pl/meta/negation.hpp: The negation meta function from C++17.  
include/pl/meta/nested_types.hpp: Template aliases to access common nested types.  
include/pl/meta/none.hpp: Meta function to determine whether none of the traits given are satisfied, analogous to disjunction and conjunction from C++17.  
include/pl/meta/remove_cvref.hpp: The remove_cvref meta function from C++20.  
include/pl/meta/void_t.hpp: void_t from C++17.  
include/pl/thd/concurrent.hpp: Thread safe concurrency adaptor to 'run' an object in a new thread, behaves like a non-blocking monitor as the callables accessing the object are run on the underlying thread.  
include/pl/thd/monitor.hpp: A monitor providing thread-safe access to an object by using locks.  
include/pl/thd/then.hpp: Then continuations for futures, similar to the ones from concurrency TS.  
include/pl/thd/thread_pool.hpp: A thread pool.  
include/pl/thd/thrad_safe_queue: A thread safe queue using locks.  
include/pl/alloca.hpp: Macro for a portable alloca.  
include/pl/annotations.hpp: Macros serving as source code annotations.  
include/pl/apply.hpp The apply function from C++17. Can be used to call something with a tuple.  
include/pl/as_bytes.hpp: Function to interpret an object as just raw bytes.  
include/pl/as_const.hpp: Function to view an object as const. Like as_const from C++17.  
include/pl/asprintf.hpp: asprintf implementation similar to the one known from POSIX or the C dynamic memory TR.  
include/pl/assert.hpp: Assertion macros for pre- and postconditions to ease contract based programming until contracts are available in standard C++.  
include/pl/begin_end.hpp: An implementation of the non-member functions to fetch iterators. Also provides convenience macros to call iterator based algorithms with 'containers'.  
include/pl/begin_end_macro.hpp: Macros to facilitate definition of other macros so they must be used with a semicolon, providing a more 'natural' syntax.  
include/pl/bitmask.hpp: Macro to allow the usage of bitwise operators with scoped enums.  
include/pl/bits.hpp: Convenience function for some bitwise operations.  
include/pl/bswap.hpp: A portable bswap.  
include/pl/byte.hpp: A 'Byte' type alias.  
include/pl/char_to_int.hpp: Function to convert a decimal 'character' value to a 'numeric' value.  
include/pl/checked_delete.hpp: Functions to call delete / delete[] that avoid undefined behavior if the pointed to type is incomplete. Also provides functions that null the pointer after calling delete / delete[].  
include/pl/compiler.hpp: Compiler detection and version checking macros.  
include/pl/concept_poly.hpp: A class template for concept based polymorphism.  
include/pl/current_function.hpp: Portable macro to get the 'prettiest' string for the current function.  
include/pl/eprintf.hpp: printf that prints to stderr.  
include/pl/except.hpp: Exception related utilities.  
include/pl/for_each_argument.hpp: Function template to call a callable with every element of a template parameter pack.  
include/pl/glue.hpp: The classic token pasting GLUE macro.  
include/pl/hash.hpp: Utility function to combine hashes to ease definition of std::hash specializations for UDTs.  
include/pl/inline.hpp: Portable macros to force and prevent function inlining.  
include/pl/integer.hpp: Fixed size integer types as template aliases.  
include/pl/invoke.hpp: The invoke function from C++17.  
include/pl/iterate_reversed.hpp: Adaptor to iterate in reverse order using a range based for loop.  
include/pl/make_from_tuple.hpp: Function template to invoke a constructor by 'unpacking' a tuple, like make_from_tuple from C++17.  
include/pl/memxor.hpp: Function to bytewise xor-assign one range of memory to another.  
include/pl/named_operator.hpp: Function to define named operators.  
include/pl/negate_predicate.hpp: Adaptor to create the negation of a predicate, similar to not_fn from C++17.  
include/pl/no_macro_substitution.hpp: Macro to prevent undesirable macro substitution.  
include/pl/noncopyable.hpp: Macro to declare a type as non-copyable.  
include/pl/numeric.hpp: isEven, isOdd and isBetween function templates.  
include/pl/observer_ptr: observer pointer like observer_ptr from library fundamentals TS v2.  
include/pl/os.hpp: Operating system detection macros.  
include/pl/overload.hpp: Utility to create an 'overload set object' from 1 or more user provided lambdas. Useful for C++17 std::variant visitation.  
include/pl/packed.hpp: Portable macros to be able to define packed structures.  
include/pl/print_bytes_as_hex.hpp: Utility to print a memory region as hexadecimals.  
include/pl/random_number_generator.hpp: A random number generator type.  
include/pl/raw_memory_array.hpp: Class template to treat a memory region as an array.  
include/pl/raw_storage.hpp: Convenience wrapper for aligned_storage.  
include/pl/restrict.hpp: Portable macro to define a restrict pointer.  
include/pl/source_line.hpp: Macro that expands to a string literal of the current line in the current source file.  
include/pl/strdup.hpp: strdup and strndup functions similar to the ones known from POSIX or the C dynamic memory TR.  
include/pl/stringify.hpp: The classic stringification macro.  
include/pl/timer.hpp: Simple timer class to measure durations of time.  
include/pl/toggle_bool.hpp: Function to invert the value of a bool object.  
include/pl/unrelated_pointer_cast.hpp: Function template for unrelated pointer casts, leaving reinterpret_cast for just integer to pointer and pointer to integer conversions.  
include/pl/unused.hpp: Macro to suppress warnings about objects being unused.  
include/pl/vla.hpp: Macro to be able to define VLAs by using alloca.  
include/pl/zero_memory.hpp: zeroMemory and secureZeroMemory functions to zero regions of memory.
