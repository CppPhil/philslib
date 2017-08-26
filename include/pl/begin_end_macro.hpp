/*!
 * \file begin_end_macro.hpp
 * \brief Exports macros that simplify the definition of convenient to use
 *        function like macros.
**/
#ifndef INCG_PL_BEGIN_END_MACRO_HPP
#define INCG_PL_BEGIN_END_MACRO_HPP
#include "unused.hpp" // PL_UNUSED

/*!
 * \def PL_BEGIN_MACRO
 * \brief To be used to begin definitions of macros that shall be forced to
 *        require a semicolon when used.
 * \see PL_END_MACRO
**/

/*!
 * \def PL_END_MACRO
 * \brief To be used to end definitions of macros that shall be forced to
 *        require a semicolon when used.
 * \see PL_BEGIN_MACRO
**/

#define PL_BEGIN_MACRO do {

#define PL_END_MACRO } while (PL_UNUSED(0), 0) /* avoid warnings */
#endif // INCG_PL_BEGIN_END_MACRO_HPP
