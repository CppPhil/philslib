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
 * \file begin_end_macro.hpp
 * \brief Exports macros that simplify the definition of convenient to use
 *        function like macros.
**/
#ifndef INCG_PL_BEGIN_END_MACRO_HPP
#define INCG_PL_BEGIN_END_MACRO_HPP

/*!
 * \def PL_BEGIN_MACRO
 * \brief To be used to begin definitions of macros that shall be forced to
 *        require a semicolon when used.
 * \see PL_END_MACRO
**/
#define PL_BEGIN_MACRO do {

/*!
 * \def PL_END_MACRO
 * \brief To be used to end definitions of macros that shall be forced to
 *        require a semicolon when used.
 * \see PL_BEGIN_MACRO
**/
#define PL_END_MACRO } while ((void)0, 0) /* avoid warnings */
#endif // INCG_PL_BEGIN_END_MACRO_HPP
