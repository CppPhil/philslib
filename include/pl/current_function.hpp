/*!
 * \file current_function
 * \brief Exports an object like macro to get the name of the current function.
**/
#ifndef INCG_PL_CURRENT_FUNCTION_HPP
#define INCG_PL_CURRENT_FUNCTION_HPP
#include "compiler.hpp" // PL_COMPILER, PL_COMPILER_MSVC, PL_COMPILER_GCC, PL_COMPILER_CLANG

/*!
 * \def PL_CURRENT_FUNCTION
 * \brief Expands to a C-String literal that represents the current function.
 * \note Uses the 'prettiest' function macro that the compiler being used provides.
 * \warning Depending on the compiler used, this macro will expand to a different
 *          C-String literal!
 * \warning The result of the macro expansion can not be string concatenated
 *          by the preprocessor with other C-String literals.
**/

#if PL_COMPILER == PL_COMPILER_MSVC
#   define PL_CURRENT_FUNCTION __FUNCSIG__
#elif PL_COMPILER == PL_COMPILER_GCC || PL_COMPILER == PL_COMPILER_CLANG
#   define PL_CURRENT_FUNCTION __PRETTY_FUNCTION__
#else
#   define PL_CURRENT_FUNCTION __func__ /* use __func__ from C99 as fallback */
#endif
#endif // INCG_PL_CURRENT_FUNCTION_HPP
