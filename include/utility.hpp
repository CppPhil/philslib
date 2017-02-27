/*! \file utility.hpp
 *  \brief Defines various general utilities.
**/

#ifndef INCG_PL_UTILITY_HPP
#define INCG_PL_UTILITY_HPP
#include "macros.hpp" // PL_INOUT
#include <cstdint> // std::uint8_t
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
bool toggleBool(PL_INOUT bool &b);

/*!
 * \brief Converts a character to an integer.
 * \param ch The character to be converted.
 * \return Returns a value of [0..9] for a character of the range ['0'..'9'].
 * \warning Do not pass in characters outside of the range ['0'..'9'].
**/
std::uint8_t charToInt(unsigned char ch);
} // namespace pl
#endif // INCG_PL_UTILITY_HPP
