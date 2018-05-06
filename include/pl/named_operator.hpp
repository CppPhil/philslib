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
 * \file named_operator.hpp
 * \brief Exports utilities for defining named operators.
**/
#ifndef INCG_PL_NAMED_OPERATOR_HPP
#define INCG_PL_NAMED_OPERATOR_HPP
#include "invoke.hpp" // pl::invoke
#include <utility>    // std::move

namespace pl {
namespace detail {
/*!
 * \brief Implementation wrapper type used to communicate between operator<
 *        and operator>.
**/
template <typename BinaryCallable, typename Type>
struct BinaryCallableWithValue {
    /*!
     * \brief Constructor.
     * \param p_BinaryCallable The BinaryCallable.
     * \param p_value The left hand side object.
    **/
    constexpr BinaryCallableWithValue(
        BinaryCallable p_BinaryCallable,
        Type&          p_value)
        : binaryCallable{std::move(p_BinaryCallable)}, value{p_value}
    {
    }

    BinaryCallable binaryCallable; /*!< The callable to run in operator> */
    Type&          value;          /*!< The left hand side value */
};
} // namespace detail

/*!
 * \brief Struct that holds a BinaryCallable to be used as a named operator.
 * \note Use makeNamedOperator to construct.
**/
template <typename BinaryCallable>
struct NamedOperator {
    /*!
     * \brief Constructor for NamedOperator.
     * \param p_binaryCallable The BinaryCallable to use for the NamedOperator.
    **/
    constexpr explicit NamedOperator(BinaryCallable p_binaryCallable)
        : binaryCallable{std::move(p_binaryCallable)}
    {
    }

    BinaryCallable binaryCallable; /*!< The callable to run in operator> */
};

/*!
 * \brief Creates a NamedOperator.
 * \param binaryCallable The callable that takes the left hand side and the
 *                       right hand side object of the named operator.
 * \return The NamedOperator object.
 * \example using namespace pl::named_operator;
 *
 *          auto pow = pl::makeNamedOperator([](double base, double exponent) {
 *              return std::pow(base, exponent);
 *          });
 *
 *          auto myValue = 2.0;
 *          myValue <pow>= 3.0;
 *          std::cout << myValue << '\n';
 *
 *          std::vector<int> v{ 1, 2, 3, 4, 5, 6 };
 *          auto contains = pl::makeNamedOperator([](const auto &container,
 *                                                   const auto &value) {
 *              const auto end = std::end(container);
 *
 *              return std::find(std::begin(container), end, value) != end;
 *          });
 *
 *          std::cout << (v <contains> 3) << '\n'
 *                    << (v <contains> 7) << '\n';
**/
template <typename BinaryCallable>
constexpr NamedOperator<BinaryCallable> makeNamedOperator(
    BinaryCallable binaryCallable)
{
    return NamedOperator<BinaryCallable>{binaryCallable};
}

inline namespace named_operator {
/*!
 * \brief The operator<, creates the BinaryCallableWithValue object.
 * \param value The left hand side object of the named operator.
 * \param namedOperator The named operator that the operator> shall apply.
 * \note Handles non-const left hand side objects.
**/
template <typename BinaryCallable, typename Type>
inline detail::BinaryCallableWithValue<BinaryCallable, Type> operator<(
    Type&                         value,
    NamedOperator<BinaryCallable> namedOperator)
{
    return detail::BinaryCallableWithValue<BinaryCallable, Type>{
        namedOperator.binaryCallable, value};
}

/*!
 * \brief The operator<, creates the BinaryCallableWithValue object.
 * \param value The left hand side object of the named operator.
 * \param namedOperator The named operator that the operator> shall apply.
 * \note Handles const qualified left hand side objects.
**/
template <typename BinaryCallable, typename Type>
inline detail::BinaryCallableWithValue<BinaryCallable, const Type> operator<(
    const Type&                   value,
    NamedOperator<BinaryCallable> namedOperator)
{
    return detail::BinaryCallableWithValue<BinaryCallable, const Type>{
        namedOperator.binaryCallable, value};
}

/*!
 * \brief Invokes the named operator on the left hand side and right hand
 *        side object of the named operator.
 * \param callableWithValue Object that contains a reference to the left
 *                          hand side object and the named operator.
 * \param value The right hand side object.
 * \return The result of invoking the named operator with the left hand side
 *         object and the right hand side object.
**/
template <typename BinaryCallable, typename Type1, typename Type2>
inline auto operator>(
    const detail::BinaryCallableWithValue<BinaryCallable, Type1>&
                 callableWithValue,
    const Type2& value) -> decltype(auto)
{
    return ::pl::invoke(
        callableWithValue.binaryCallable, callableWithValue.value, value);
}

/*!
 * \brief Invokes the named operator with the left hand side and right hand
 *        side objects and assigns the result through to the left hand side
 *        object.
 * \param callableWithValue Contains the left hand side object and the
 *                          named operator.
 * \param value The right hand side object.
 * \return The result of assigning the result of invoking the named operator
 *         with the left hand side and right hand side object to the left
 *         hand side object.
**/
template <typename BinaryCallable, typename Type1, typename Type2>
inline auto operator>=(
    const detail::BinaryCallableWithValue<BinaryCallable, Type1>&
                 callableWithValue,
    const Type2& value) -> decltype(auto)
{
    return callableWithValue.value = callableWithValue > value;
}
} // inline namespace named_operator
} // namespace pl
#endif // INCG_PL_NAMED_OPERATOR_HPP
