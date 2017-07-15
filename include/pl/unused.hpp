/*!
 * \file unused.hpp
 * \brief Exports a function like macro that can be used to mark things
 *        such as parameters of functions as unused within the function
 *        body in order to suppress compiler warnings.
**/
#ifndef INCG_PL_UNUSED_HPP
#define INCG_PL_UNUSED_HPP

/*!
 * \def PL_UNUSED(param)
 * \brief marks something as unused.
 *
 * Can be used to suppress compiler warnings about unused variables.
**/

#define PL_UNUSED(param) static_cast<void>((param))
#endif // INCG_PL_UNUSED_HPP
