/*! \file compiler.hpp
 *  \brief Defines macros to determine the compiler being used.
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

#define PL_COMPILER_CLANG (0x0004)
#define PL_COMPILER_ICC (0x0005)
#define PL_COMPILER_MSVC (0x0006)
#define PL_COMPILER_GCC (0x0007)
#define PL_COMPILER_UNKNOWN (0x0008)

#if defined(__clang__)
#   define PL_COMPILER PL_COMPILER_CLANG
#elif defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC)
#   define PL_COMPILER PL_COMPILER_ICC
#elif defined(_MSC_VER)
#   define PL_COMPILER PL_COMPILER_MSVC
#elif defined(__GNUC__) || defined(__GNUG__)
#   define PL_COMPILER PL_COMPILER_GCC
#else
#   define PL_COMPILER PL_COMPILER_UNKNOWN
#   warning "Compiler could not be detected"
#endif
#endif // INCG_PL_COMPILER_HPP
