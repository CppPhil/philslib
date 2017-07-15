/*!
 * \file inline.hpp
 * \brief Exports macros to force or forbid inlining of a function.
**/
#ifndef INCG_PL_INLINE_HPP
#define INCG_PL_INLINE_HPP
#include "compiler.hpp" // PL_COMPILER, PL_COMPILER_GCC, PL_COMPILER_CLANG, PL_COMPILER_ICC, PL_COMPILER_MSVC, PL_COMPILER_UNKNOWN

/*!
 * \def PL_ALWAYS_INLINE
 * \brief Declares a function as always to be inlined (if possible).
 * \warning Overrides the compiler's cost-benefit-analysis in regards to
 *          inlining. Only use when certain. May not work if compiler is
 *          unknown.
**/

/*!
 * \def PL_NEVER_INLINE
 * \brief Declares a function as never to be inlined.
 * \warning May not work if compiler is unknown.
**/

#if PL_COMPILER == PL_COMPILER_GCC
#   define PL_ALWAYS_INLINE __attribute__((always_inline)) inline
#   define PL_NEVER_INLINE __attribute__((noinline))
#elif PL_COMPILER == PL_COMPILER_CLANG
#   define PL_ALWAYS_INLINE __attribute__((always_inline))
#   define PL_NEVER_INLINE __attribute__((noinline))
#elif PL_COMPILER == PL_COMPILER_ICC
#   define PL_ALWAYS_INLINE __attribute__((always_inline))
#   define PL_NEVER_INLINE __attribute__((noinline))
#elif PL_COMPILER == PL_COMPILER_MSVC
#   define PL_ALWAYS_INLINE __forceinline
#   define PL_NEVER_INLINE __declspec(noinline)
#elif PL_COMPILER == PL_COMPILER_UNKNOWN
#   define PL_ALWAYS_INLINE inline
#   define PL_NEVER_INLINE /* nothing */
#endif
#endif // INCG_PL_INLINE_HPP
