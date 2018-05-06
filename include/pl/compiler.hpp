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
 * \file compiler.hpp
 * \brief Defines macros to determine the compiler
 *        and the version of that compiler being used.
**/
#ifndef INCG_PL_COMPILER_HPP
#define INCG_PL_COMPILER_HPP

/*!
 * \def PL_COMPILER_CLANG
 * \brief PL_COMPILER will be defined as this if clang is being used.
**/

/*!
 * \def PL_COMPILER_ICC
 * \brief PL_COMPILER will be defined as this
 *        if Intel C++ Compiler is being used.
**/

/*!
 * \def PL_COMPILER_MSVC
 * \brief PL_COMPILER will be defined as this if Microsoft Visual Compiler is
 *        being used.
**/

/*!
 * \def PL_COMPILER_GCC
 * \brief PL_COMPILER will be defined as this if gcc is being used.
**/

/*!
* \def PL_COMPILER_UNKNOWN
* \brief PL_COMPILER will be defined as this if the compiler being used
*        could not be determined.
**/

/*!
 * \def PL_COMPILER
 * \brief Will be defined as PL_COMPILER_CLANG, PL_COMPILER_ICC,
 *        PL_COMPILER_MSVC, PL_COMPILER_GCC or PL_COMPILER_UNKNOWN
 *        depending on which compiler is being used.
**/

#define PL_COMPILER_CLANG (0x0000)   /* meaningless number */
#define PL_COMPILER_ICC (0x0001)     /* meaningless number */
#define PL_COMPILER_MSVC (0x0002)    /* meaningless number */
#define PL_COMPILER_GCC (0x0003)     /* meaningless number */
#define PL_COMPILER_UNKNOWN (0xFFFF) /* meaningless number */

#if defined(__clang__)
#define PL_COMPILER PL_COMPILER_CLANG
#elif defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC)
#define PL_COMPILER PL_COMPILER_ICC
#elif defined(_MSC_VER)
#define PL_COMPILER PL_COMPILER_MSVC
#elif defined(__GNUC__) || defined(__GNUG__)
#define PL_COMPILER PL_COMPILER_GCC
#else
#define PL_COMPILER PL_COMPILER_UNKNOWN
#warning "Compiler could not be detected"
#endif

/*!
 * \def PL_COMPILER_MAJOR
 * \brief The major version of the compiler.
**/

/*!
 * \def PL_COMPILER_MINOR
 * \brief The minor version of the compiler.
**/

/*!
 * \def PL_COMPILER_PATCH
 * \brief The patch level of the compiler.
**/

/*!
 * \def PL_COMPILER_NAME
 * \brief The name of the compiler.
**/

#if PL_COMPILER == PL_COMPILER_CLANG
#define PL_COMPILER_MAJOR __clang_major__
#define PL_COMPILER_MINOR __clang_minor__
#define PL_COMPILER_PATCH __clang_patchlevel__
#define PL_COMPILER_NAME "Clang"
#elif PL_COMPILER == PL_COMPILER_ICC
#define PL_COMPILER_MAJOR __INTEL_COMPILER / 100
#define PL_COMPILER_MINOR __INTEL_COMPILER % 100 / 10
#define PL_COMPILER_PATCH __INTEL_COMPILER % 10
#define PL_COMPILER_NAME "Intel ICC"
#elif PL_COMPILER == PL_COMPILER_MSVC
#define PL_COMPILER_MAJOR _MSC_FULL_VER / 10000000
#define PL_COMPILER_MINOR _MSC_FULL_VER % 10000000 / 100000
#define PL_COMPILER_PATCH _MSC_FULL_VER % 100000
#define PL_COMPILER_NAME "Microsoft Visual C++ Compiler"
#elif PL_COMPILER == PL_COMPILER_GCC
#define PL_COMPILER_MAJOR __GNUC__
#define PL_COMPILER_MINOR __GNUC_MINOR__
#define PL_COMPILER_PATCH __GNUC_PATCHLEVEL__
#define PL_COMPILER_NAME "GCC"
#else
#define PL_COMPILER_MAJOR (0x00) /* 0 for unknown compiler */
#define PL_COMPILER_MINOR (0x00) /* 0 for unknown compiler */
#define PL_COMPILER_PATCH (0x00) /* 0 for unknown compiler */
#define PL_COMPILER_NAME "Unknown"
#endif

/*!
 * \def PL_COMPILER_VERSION_CHECK(major, minor, patch)
 * \brief Can be used to create a compiler version using a major, minor
 *        and patch number. Useful to compare the current compiler version
 *        to a specific version.
**/
#define PL_COMPILER_VERSION_CHECK(major, minor, patch) \
    (((major)*16777216) + ((minor)*65536)              \
     + (patch)) /* multipliers to 'push' the numbers leftward */

/*!
 * \def PL_COMPILER_VERSION
 * \brief The current compiler version, may be compared to a number generated
 *        with PL_COMPILER_VERSION_CHECK
**/
#define PL_COMPILER_VERSION    \
    PL_COMPILER_VERSION_CHECK( \
        PL_COMPILER_MAJOR, PL_COMPILER_MINOR, PL_COMPILER_PATCH)

#endif // INCG_PL_COMPILER_HPP
