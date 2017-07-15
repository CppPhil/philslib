/*!
 * \file restrict.hpp
 * \brief Exports a macro that allows the user to declare a pointer as restrict
 *        with the supported compilers, behaves like the restrict keyword from
 *        C that C++ lacks.
**/
#ifndef INCG_PL_RESTRICT_HPP
#define INCG_PL_RESTRICT_HPP
#include "compiler.hpp" // PL_COMPILER, PL_COMPILER_GCC, PL_COMPILER_CLANG, PL_COMPILER_ICC, PL_COMPILER_MSVC, PL_COMPILER_UNKNOWN

/*!
 * \def PL_RESTRICT
 * \brief Declares a pointer as a restrict pointer.
 * \warning If an independent pointer accesses the object pointed
 *          to by the pointer declared with PL_RESTRICT
 *          undefined behavior occurs.
 *
 * For the lifetime of the pointer declared with PL_RESTRICT
 * only the pointer itself and values directly derived
 * from the pointer (such as pointer + 1) may be used to access the
 * pointed to object. Using this macro when appropriate may aid
 * compiler optimizations as the effects of pointer aliasing are limited.
**/

#if PL_COMPILER == PL_COMPILER_GCC
#   define PL_RESTRICT __restrict__
#elif PL_COMPILER == PL_COMPILER_CLANG
#   define PL_RESTRICT __restrict__
#elif PL_COMPILER == PL_COMPILER_ICC
#   define PL_RESTRICT restrict
#elif PL_COMPILER == PL_COMPILER_MSVC
#   define PL_RESTRICT __restrict
#elif PL_COMPILER == PL_COMPILER_UNKNOWN
#   define PL_RESTRICT /* nothing */
#endif
#endif // INCG_PL_RESTRICT_HPP
