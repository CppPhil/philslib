/*!
 * \file glue.hpp
 * \brief Exports a macro that can be used to glue two sequences of tokens
 *        together in order to form a single sequence of tokens at
 *        preprocessing time.
**/
#ifndef INCG_PL_GLUE_HPP
#define INCG_PL_GLUE_HPP

/*!
 * \def PL_DETAIL_GLUE(a, b)
 * \brief Implementation macro for PL_GLUE
 * \warning Do not use.
 * \see PL_GLUE
**/

/*!
 * \def PL_GLUE(a, b)
 * \brief Token pastes two contiguous sequences of tokens together as one.
 * \example PL_GLUE(hello, world) results in:
 *          helloworld
**/

#define PL_DETAIL_GLUE(a, b) a##b

#define PL_GLUE(a, b) PL_DETAIL_GLUE(a, b)
#endif // INCG_PL_GLUE_HPP
