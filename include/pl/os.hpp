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
 *        GNU/Linux
 * \note Everything running a linux kernel will be considered linux.
**/

/*!
 * \def PL_OS_UNKNOWN
 * \brief PL_OS will be defined as this if the operating system used
 *        could not be determined.
**/

/*!
 * \def PL_OS
 * \brief Will be defined as PL_OS_WINDOWS, PL_OS_MAC, PL_OS_LINUX or
 *        PL_OS_UNKNOWN
**/

#define PL_OS_WINDOWS (0x0000) /* meaningless number */
#define PL_OS_MAC (0x0001) /* meaningless number */
#define PL_OS_LINUX (0x0002) /* meaningless number */
#define PL_OS_UNKNOWN (0x0003) /* meaningless number */

#if defined(_WIN32)
#   define PL_OS PL_OS_WINDOWS
#elif defined(__APPLE__)
#   define PL_OS PL_OS_MAC
#elif defined(__linux__)
#   define PL_OS PL_OS_LINUX
#else
#   define PL_OS PL_OS_UNKNOWN
#   warning "Operating system could not be detected"
#endif
#endif // INCG_PL_OS_HPP
