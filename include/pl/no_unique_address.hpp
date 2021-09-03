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
 * \file no_unique_address.hpp
 * \brief Exports the PL_NO_UNIQUE_ADDRESS macro.
 */
#ifndef INCG_PL_NO_UNIQUE_ADDRESS_HPP
#define INCG_PL_NO_UNIQUE_ADDRESS_HPP
#include "compiler.hpp" // PL_COMPILER, PL_COMPILER_MSVC, PL_COMPILER_GCC, PL_COMPILER_CLANG

/*!
 * \def PL_NO_UNIQUE_ADDRESS
 * \brief Macro to mark a data member as [[no_unique_address]] if the compiler
 *        used supports it. If the compiler doesn't support it will expand to
 *        nothing.
 **/

#if PL_COMPILER == PL_COMPILER_MSVC
#if _MSC_FULL_VER >= 192829913
#define PL_NO_UNIQUE_ADDRESS [[msvc::no_unique_address]]
#else
#define PL_NO_UNIQUE_ADDRESS /* nothing */
#endif
#elif PL_COMPILER == PL_COMPILER_GCC
#if PL_COMPILER_VERSION >= PL_COMPILER_VERSION_CHECK(9, 0, 0)
#define PL_NO_UNIQUE_ADDRESS [[no_unique_address]]
#else
#define PL_NO_UNIQUE_ADDRESS /* nothing */
#endif
#elif PL_COMPILER == PL_COMPILER_CLANG
#if PL_COMPILER_VERSION >= PL_COMPILER_VERSION_CHECK(9, 0, 0)
#define PL_NO_UNIQUE_ADDRESS [[no_unique_address]]
#else
#define PL_NO_UNIQUE_ADDRESS /* nothing */
#endif
#else
#define PL_NO_UNIQUE_ADDRESS /* nothing */
#endif
#endif // INCG_PL_NO_UNIQUE_ADDRESS_HPP
