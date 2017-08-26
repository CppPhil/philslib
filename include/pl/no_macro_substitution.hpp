/*!
 * \file no_macro_substitution.hpp
 * \brief Exports a macro that can be used to prevent macro substitution.
**/
#ifndef INCG_PL_NO_MACRO_SUBSTITUTION_HPP
#define INCG_PL_NO_MACRO_SUBSTITUTION_HPP

/*!
 * \def PL_NO_MACRO_SUBSTITUTION
 * \brief Used to prevent macro substitution.
 * \example // Assuming a min macro is defined.
 *          int i = std::numeric_limits<int>::min PL_NO_MACRO_SUBSTITUTION();
**/

#define PL_NO_MACRO_SUBSTITUTION /* nothing */
#endif // INCG_PL_NO_MACRO_SUBSTITUTION_HPP
