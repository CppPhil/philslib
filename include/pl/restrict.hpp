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
#define PL_RESTRICT __restrict__
#elif PL_COMPILER == PL_COMPILER_CLANG
#define PL_RESTRICT __restrict__
#elif PL_COMPILER == PL_COMPILER_ICC
#define PL_RESTRICT restrict
#elif PL_COMPILER == PL_COMPILER_MSVC
#define PL_RESTRICT __restrict
#elif PL_COMPILER == PL_COMPILER_UNKNOWN
#define PL_RESTRICT /* nothing */
#endif
#endif // INCG_PL_RESTRICT_HPP
