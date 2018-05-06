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
 * \file os.hpp
 * \brief defines macros to detect the operating system used.
**/
#ifndef INCG_PL_OS_HPP
#define INCG_PL_OS_HPP

/*!
 * \def PL_OS_WINDOWS
 * \brief PL_OS will be defined as this if the operating system used is
 *        Microsoft Windows.
**/

/*!
 * \def PL_OS_MAC
 * \brief PL_OS will be defined as this if the operating system used is
 *        Apple Macintosh.
**/

/*!
 * \def PL_OS_LINUX
 * \brief PL_OS will be defined as this if the operating system used is
 *        GNU/Linux.
**/

/*!
 * \def PL_OS_ANDROID
 * \brief PL_OS will be defined as this if the operating system used is
 *        Android.
**/

/*!
 * \def PL_OS_FREEBSD
 * \brief PL_OS will be defined as this if the operating system used is
 *        FreeBSD.
**/

/*!
 * \def PL_OS_SOLARIS
 * \brief PL_OS will be defined as this if the operating system used is
 *        Oracle Solaris.
**/

/*!
 * \def PL_OS_UNKNOWN
 * \brief PL_OS will be defined as this if the operating system used
 *        could not be determined.
**/

/*!
 * \def PL_OS
 * \brief Will be defined as PL_OS_WINDOWS, PL_OS_MAC, PL_OS_LINUX,
 *        PL_OS_ANDROID, PL_OS_FREEBSD, PL_OS_SOLARIS or PL_OS_UNKNOWN
**/

/*!
 * \def PL_OS_NAME
 * \brief The name of the operating system.
**/

#define PL_OS_WINDOWS (0x0000) /* meaningless number */
#define PL_OS_MAC (0x0001)     /* meaningless number */
#define PL_OS_LINUX (0x0002)   /* meaningless number */
#define PL_OS_ANDROID (0x0003) /* meaningless number */
#define PL_OS_FREEBSD (0x0004) /* meaningless number */
#define PL_OS_SOLARIS (0x0005) /* meaningless number */
#define PL_OS_UNKNOWN (0xFFFF) /* meaningless number */

#if defined(_WIN32)
#define PL_OS PL_OS_WINDOWS
#define PL_OS_NAME "Windows"
#elif defined(__APPLE__)
#define PL_OS PL_OS_MAC
#define PL_OS_NAME "MacOS"
#elif defined(__unix__)
#if defined(__ANDROID__)
#define PL_OS PL_OS_ANDROID
#define PL_OS_NAME "Android"
#elif defined(__linux__)
#define PL_OS PL_OS_LINUX
#define PL_OS_NAME "Linux"
#elif defined(__FreeBSD__)
#define PL_OS PL_OS_FREEBSD
#define PL_OS_NAME "FreeBSD"
#else
#define PL_OS PL_OS_UNKNOWN
#define PL_OS_NAME "Unknown"
#warning "Unknown Unix based operating system"
#endif
#elif defined(__sun) && defined(__SVR4)
#define PL_OS PL_OS_SOLARIS
#define PL_OS_NAME "Solaris"
#else
#define PL_OS PL_OS_UNKNOWN
#define PL_OS_NAME "Unknown"
#warning "Operating system could not be detected"
#endif
#endif // INCG_PL_OS_HPP
