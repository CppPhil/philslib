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
 * \file version.hpp
 * \brief Defines macros to determine the version
 *        of the library being used.
 **/
#ifndef INCG_PL_VERSION_HPP
#define INCG_PL_VERSION_HPP
#include "stringify.hpp" // PL_STRINGIFY

/*!
 * \def PL_VERSION_MAJOR
 * \brief The major version of the library
 **/

/*!
 * \def PL_VERSION_MINOR
 * \brief The minor version of the library
 **/

/*!
 * \def PL_VERSION_PATCH
 * \brief The patch level of the library
 **/

/*!
 * \def PL_VERSION
 * \brief A string literal of the version of the library
 **/

#define PL_VERSION_MAJOR 1

#define PL_VERSION_MINOR 0

#define PL_VERSION_PATCH 0

#define PL_VERSION                 \
    PL_STRINGIFY(PL_VERSION_MAJOR) \
    "." PL_STRINGIFY(PL_VERSION_MINOR) "." PL_STRINGIFY(PL_VERSION_PATCH)

#endif // INCG_PL_VERSION_HPP
