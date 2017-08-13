/*!
 * \file alloca.hpp
 * \brief Defines the PL_ALLOCA function like macro.
**/
#ifndef INCG_PL_ALLOCA_HPP
#define INCG_PL_ALLOCA_HPP
#include "os.hpp" // PL_OS, PL_OS_LINUX, PL_OS_MAC, PL_OS_WINDOWS
#if PL_OS == PL_OS_LINUX || PL_OS == PL_OS_MAC
#   include <alloca.h> // alloca
#elif PL_OS == PL_OS_WINDOWS
#   include <malloc.h> // _alloca
#endif

/*!
 * \def PL_ALLOCA(countBytes)
 * \brief Allocates 'countBytes' bytes of raw memory that is local to the
 *        current function. That memory is allocated from the stack.
 *        The memory allocated is automatically deallocated when the
 *        current function returns to its caller.
 *        The macro 'returns' a pointer to that memory, which is of type void *.
 * \warning Using this macro can easily cause stack overflow.
 *          Do not allocate large amounts of bytes in one function using
 *          PL_ALLOCA. Beware of functions using PL_ALLOCA potentially being
 *          inlined, you may want to declare functions using PL_ALLOCA as
 *          PL_NEVER_INLINE. Beware of using PL_ALLOCA, or a potentially
 *          inlined function that uses PL_ALLOCA in a loop or in a recursive
 *          function. If the program causes stack overflow, the behavior of
 *          the program is undefined.
 *          Make sure that the 'countBytes' supplied is safe, i.e. not
 *          supplied by the user or some external source.
**/

#if PL_OS == PL_OS_LINUX || PL_OS == PL_OS_MAC
#   define PL_ALLOCA(countBytes) alloca(countBytes)
#elif PL_OS == PL_OS_WINDOWS
#   define PL_ALLOCA(countBytes) _alloca(countBytes)
#elif PL_OS == PL_OS_OTHER
#   ifdef MY_ALLOCA
#       define PL_ALLOCA(countBytes) MY_ALLOCA(countBytes)
#   else
#       warning "Unknown OS. Please define MY_ALLOCA(countBytes) to use PL_ALLOCA"
#   endif
#endif
#endif // INCG_PL_ALLOCA_HPP
