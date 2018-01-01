/* This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * For more information, please refer to <http://unlicense.org/>
 */

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
#   define PL_ALWAYS_INLINE __attribute__((always_inline)) inline
#   define PL_NEVER_INLINE __attribute__((noinline))
#elif PL_COMPILER == PL_COMPILER_ICC
#   define PL_ALWAYS_INLINE __attribute__((always_inline)) inline
#   define PL_NEVER_INLINE __attribute__((noinline))
#elif PL_COMPILER == PL_COMPILER_MSVC
#   define PL_ALWAYS_INLINE __forceinline
#   define PL_NEVER_INLINE __declspec(noinline)
#elif PL_COMPILER == PL_COMPILER_UNKNOWN
#   define PL_ALWAYS_INLINE inline
#   define PL_NEVER_INLINE /* nothing */
#endif
#endif // INCG_PL_INLINE_HPP
