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
 * \file clamp.hpp
 * \brief Exports the clamp-algorithm from the C++17 standard library.
**/
#ifndef INCG_PL_ALGO_CLAMP_HPP
#define INCG_PL_ALGO_CLAMP_HPP
#include "../annotations.hpp" // PL_IN
#include "../assert.hpp" // PL_DBG_CHECK_PRE
#include <functional> // std::less
#include <ciso646> // not

namespace pl
{
namespace algo
{
/*!
 * \brief If comp('value', 'lowerBound') is true, returns 'lowerBound';
 *        otherwise if comp('upperBound', 'value') is true
 *        returns 'upperBound'; otherwise returns 'value'.
 * \param value The value to clamp.
 * \param lowerBound The lower boundary to clamp 'value' to.
 * \param upperBound The upper boundary to clamp 'value' to.
 * \param comp Comparison function object (i.e. an object that satisfies the
 *             requirements of Compare,
 *             see: http://en.cppreference.com/w/cpp/concept/Compare) which
 *             returns true if the first argument is "less" than the second.
 *             The signature of the comparison function should be equivalent to
 *             the following:
 *             bool cmp(const Type1 &a, const Type2 &b);
 *             The signature does not need to have const &, but the function
 *             object must not modify the objects passed to it. The types Type1
 *             and Type2 must be such that an object of type 'Ty' can be
 *             implicitly converted to both of them. ​
 * \return Reference to 'lowerBound' if comp('value', 'lowerBound') is true,
 *         reference to 'upperBound' if comp('upperBound', 'value') is true,
 *         otherwise reference to 'value'
 * \note Complexity of at most two comparisons.
 *       If 'value' compares "equivalent" to either bound,
 *       returns a reference to 'value', not the bound.
 * \warning The behavior is undefined if comp('upperBound', 'lowerBound') is true.
 *          Capturing the result of clamp by reference if one of the parameters
 *          is rvalue produces a dangling reference if that parameter is returned!
 *          Only works for floating-point 'Ty' if NaNs are avoided.
**/
template <typename Ty, typename BinaryComparator>
constexpr const Ty &clamp(
    PL_IN const Ty &value,
    PL_IN const Ty &lowerBound,
    PL_IN const Ty &upperBound,
    BinaryComparator comp)
{
    PL_DBG_CHECK_PRE(not comp(upperBound, lowerBound));

    return ((comp(value, lowerBound)) ? (lowerBound)
                                      : ((comp(upperBound, value)) ? (upperBound)
                                                                   : (value)));
}

/*!
 * \brief If 'value' compares less than 'lowerBound', returns 'lowerBound';
 *        otherwise if 'upperBound' compares less than 'value'
 *        returns 'upperBound'; otherwise returns 'value'.
 * \param value The value to clamp.
 * \param lowerBound The lower boundary to clamp 'value' to.
 * \param upperBound The upper boundary to clamp 'value' to.
 * \return Reference to 'lowerBound' if 'value' is less than 'lowerBound',
 *         reference to 'upperBound' if 'upperBound' is less than 'value',
 *         otherwise reference to 'value'.
 * \note 'Ty' must be less than comparable.
 *       Complexity of at most two comparisons.
 *       If 'value' compares equivalent to either bound,
 *       returns a reference to 'value', not the bound.
 * \warning The behavior is undefined if 'lowerBound' is greater than 'upperBound'.
 *          Capturing the result of clamp by reference if one of the parameters
 *          is rvalue produces a dangling reference if that parameter is returned!
 *          Only works for floating-point 'Ty' if NaNs are avoided.
**/
template <typename Ty>
constexpr const Ty &clamp(
    PL_IN const Ty &value,
    PL_IN const Ty &lowerBound,
    PL_IN const Ty &upperBound)
{
    return ::pl::algo::clamp(value, lowerBound, upperBound, std::less<>{ });
}
} // namespace algo
} // namespace pl
#endif // INCG_PL_ALGO_CLAMP_HPP
