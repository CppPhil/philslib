/* This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * For more information, please refer to <http://unlicense.org/>
 */

/*!
 * \file numeric.hpp
 * \brief This header file defines various utilities for working with numbers.
**/
#ifndef INCG_PL_NUMERIC_HPP
#define INCG_PL_NUMERIC_HPP
#include <ciso646> // not, and
#include <cstddef> // std::size_t

namespace pl
{
/*!
 * \brief Determines whether a given number is even.
 * \param numeric The number to check.
 * \return true if numeric is even; false otherwise.
 * \note Only pass in numbers.
**/
template <typename Numeric>
constexpr bool isEven(Numeric numeric)
{
    return ((numeric & Numeric{ 1 }) == Numeric{ });
}

/*!
 * \brief Determines whether a given number is odd
 * \param numeric The number to check.
 * \return true if numeric is odd; false otherwise.
 * \note Only pass in numbers.
**/
template <typename Numeric>
constexpr bool isOdd(Numeric numeric)
{
    return not ::pl::isEven(numeric);
}

/*!
 * \brief Checks if checkMe is within lowerBound and upperBound.
 * \param checkMe The number to check.
 * \param lowerBound The lower bound.
 * \param upperBound The upper bound.
 * \return true if checkMe is >= lowerBound and checkMe is also <= upperBound;
 *         false otherwise.
 * \warning lowerBound must be <= upperBound
**/
template <typename Numeric>
constexpr bool isBetween(Numeric checkMe, Numeric lowerBound, Numeric upperBound)
{
    return ((checkMe >= lowerBound) and (checkMe <= upperBound));
}
} // namespace pl
#endif // INCG_PL_NUMERIC_HPP
