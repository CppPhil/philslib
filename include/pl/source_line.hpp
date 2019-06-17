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
 * \file source_line.hpp
 * \brief Exports an object like macro that expands to a C-style string
 *        of the current line number in the source code.
 **/
#ifndef INCG_PL_SOURCE_LINE_HPP
#define INCG_PL_SOURCE_LINE_HPP
#include "stringify.hpp" // PL_STRINGIFY

/*!
 * \def PL_SOURCE_LINE
 * \brief The current line in the current source file.
 * \note Note that the line number may have been manipulated using #line.
 *
 * Macro that expands to a C-String literal of the current line in the current
 * source file. Equivalent to the stringification of the standard predefined
 * macro __LINE__
 **/

#define PL_SOURCE_LINE PL_STRINGIFY(__LINE__)
#endif // INCG_PL_SOURCE_LINE_HPP
