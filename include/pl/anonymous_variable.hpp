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
 * \file anonymous_variable.hpp
 * \brief Exports the PL_ANONYMOUS_VARIABLE macro.
**/
#ifndef INCG_PL_ANONYMOUS_VARIABLE_HPP
#define INCG_PL_ANONYMOUS_VARIABLE_HPP
#include "glue.hpp" // PL_GLUE

/*!
 * \def PL_ANONYMOUS_VARIABLE(type, init)
 * \brief Declares an anonymous variable of type 'type'
 *        'init' is used to initialize the object of type 'type'.
**/

#ifndef __COUNTER__
#   warning "Your C++ implementation does not define the non-standard __COUNTER__, anonymous variables will not be available"
#endif // __COUNTER__

#define PL_ANONYMOUS_VARIABLE(type, init) \
    type PL_GLUE(_anonymous, PL_GLUE(type, __COUNTER__)) init;
#endif // INCG_PL_ANONYMOUS_VARIABLE_HPP
