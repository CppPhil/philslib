/*!
 * \file toggle_bool.hpp
 * \brief Exports a function to toggle the value of a bool variable.
**/
#ifndef INCG_PL_TOGGLE_BOOL_HPP
#define INCG_PL_TOGGLE_BOOL_HPP
#include "annotations.hpp" // PL_INOUT
#include <ciso646> // not

namespace pl
{
/*!
 * \brief Toggles the boolean passed in.
 * \param b The boolean to be toggled.
 * \return The new value of the the boolean passed in.
 *
 * If the boolean passed in is true it will be assigned false and the
 * value returned will be false.
 * If the boolean passed in is false it will be assigned true and the
 * value return will be true.
**/
constexpr bool toggleBool(PL_INOUT bool &b)
{
    b = not b;
    return b;
}
} // namespace pl
#endif // INCG_PL_TOGGLE_BOOL_HPP
