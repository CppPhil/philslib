/*!
 * \file numeric.hpp
 * \brief This header file defines various utilities for working with numbers.
**/
#ifndef INCG_PL_NUMERIC_HPP
#define INCG_PL_NUMERIC_HPP
#include <ciso646> // not, and
#include <stdexcept> // std::invalid_argument
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
bool isEven(Numeric numeric)
{
    static constexpr Numeric zero = 0;
    static constexpr Numeric one = 1;
    return ((numeric & one) == zero);
}

/*!
 * \brief Determines whether a given number is odd
 * \param numeric The number to check.
 * \return true if numeric is odd; false otherwise.
 * \note Only pass in numbers.
**/
template <typename Numeric>
bool isOdd(Numeric numeric)
{
    return not ::pl::isEven(numeric);
}

/*!
 * \brief Checks if checkMe is within lowerBound and upperBound.
 *        May throw if bounds are invalid.
 * \param checkMe The number to check.
 * \param lowerBound The lower bound.
 * \param upperBound The upper bound.
 * \return true if checkMe is >= lowerBound and checkMe is also <= upperBound;
 *         false otherwise.
 * \throws std::invalid_argument if lowerBound > upperBound.
 * \note lowerBound must be <= upperBound; otherwise this function throws.
**/
template <typename Numeric>
bool isBetween(Numeric checkMe, Numeric lowerBound, Numeric upperBound)
{
    if (lowerBound > upperBound) {
        throw std::invalid_argument{
            "lowerBound was larger than upperBound "
            "in pl::isBetween"
        };
    }

    return ((checkMe >= lowerBound) and (checkMe <= upperBound));
}
} // namespace pl
#endif // INCG_PL_NUMERIC_HPP
