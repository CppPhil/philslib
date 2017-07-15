/*!
 * \file stringify.hpp
 * \brief Exports a macro that can be used to turn any sequence of tokens
 *        into a C-string literal at preprocessing time.
**/
#ifndef INCG_PL_STRINGIFY_HPP
#define INCG_PL_STRINGIFY_HPP

/*!
 * \def PL_DETAIL_STRINGIFY(tokens)
 * \brief Implementation macro for PL_STRINGIFY
 * \warning Do not use.
 * \see PL_STRINGIFY
**/

/*!
 * \def PL_STRINGIFY(tokens)
 * \brief Turns a contiguous sequence of tokens passed in into a
 *        C-String literal.
 * \example PL_STRINGIFY(helloWorld) results in:
 *          "helloWorld"
**/

#define PL_DETAIL_STRINGIFY(tokens) #tokens

#define PL_STRINGIFY(tokens) PL_DETAIL_STRINGIFY(tokens)
#endif // INCG_PL_STRINGIFY_HPP
