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
 * \file stringify.hpp
 * \brief Exports a macro that can be used to turn any sequence of tokens
 *        into a C-string literal at preprocessing time.
**/
#ifndef INCG_PL_STRINGIFY_HPP
#define INCG_PL_STRINGIFY_HPP

/*!
 * \def PL_DETAIL_STRINGIFY(tokens)
 * \brief Implementation macro for PL_STRINGIFY
 * \warning Do not use.
 * \see PL_STRINGIFY
**/

/*!
 * \def PL_STRINGIFY(tokens)
 * \brief Turns a contiguous sequence of tokens passed in into a
 *        C-String literal.
 * \example PL_STRINGIFY(helloWorld) results in:
 *          "helloWorld"
**/

#define PL_DETAIL_STRINGIFY(tokens) #tokens

#define PL_STRINGIFY(tokens) PL_DETAIL_STRINGIFY(tokens)
#endif // INCG_PL_STRINGIFY_HPP
