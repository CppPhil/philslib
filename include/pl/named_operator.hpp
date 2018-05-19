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
struct binary_callable_with_value {
    /*!
     * \brief Constructor.
     * \param p_binary_callable The BinaryCallable.
     * \param p_value The left hand side object.
    **/
    constexpr binary_callable_with_value(
        BinaryCallable p_binary_callable,
        Type&          p_value)
        : binary_callable{std::move(p_binary_callable)}, value{p_value}
    {
    }

    BinaryCallable binary_callable; /*!< The callable to run in operator> */
    Type&          value;           /*!< The left hand side value */
};
} // namespace detail

/*!
 * \brief Struct that holds a BinaryCallable to be used as a named operator.
 * \note Use make_named_operator to construct.
**/
template <typename BinaryCallable>
struct named_oper {
    /*!
     * \brief Constructor for named_oper.
     * \param p_binary_callable The BinaryCallable to use for the
     *                          named_operator.
    **/
    constexpr explicit named_oper(BinaryCallable p_binary_callable)
        : binary_callable{std::move(p_binary_callable)}
    {
    }

    BinaryCallable binary_callable; /*!< The callable to run in operator> */
};

/*!
 * \brief Creates a named_oper.
 * \param binary_callable The callable that takes the left hand side and the
 *                        right hand side object of the named operator.
 * \return The named_oper object.
**/
template <typename BinaryCallable>
constexpr named_oper<BinaryCallable> make_named_operator(
    BinaryCallable binary_callable)
{
    return named_oper<BinaryCallable>{binary_callable};
}

inline namespace named_operator {
/*!
 * \brief The operator<, creates the binary_callable_with_value object.
 * \param value The left hand side object of the named operator.
 * \param named_operator The named operator that the operator> shall apply.
 * \note Handles non-const left hand side objects.
**/
template <typename BinaryCallable, typename Type>
inline detail::binary_callable_with_value<BinaryCallable, Type> operator<(
    Type&                      value,
    named_oper<BinaryCallable> named_operator)
{
    return detail::binary_callable_with_value<BinaryCallable, Type>{
        named_operator.binary_callable, value};
}

/*!
 * \brief The operator<, creates the binary_callable_with_value object.
 * \param value The left hand side object of the named operator.
 * \param named_operator The named operator that the operator> shall apply.
 * \note Handles const qualified left hand side objects.
**/
template <typename BinaryCallable, typename Type>
inline detail::binary_callable_with_value<BinaryCallable, const Type> operator<(
    const Type&                value,
    named_oper<BinaryCallable> named_operator)
{
    return detail::binary_callable_with_value<BinaryCallable, const Type>{
        named_operator.binary_callable, value};
}

/*!
 * \brief Invokes the named operator on the left hand side and right hand
 *        side object of the named operator.
 * \param callable_with_value Object that contains a reference to the left
 *                            hand side object and the named operator.
 * \param value The right hand side object.
 * \return The result of invoking the named operator with the left hand side
 *         object and the right hand side object.
**/
template <typename BinaryCallable, typename Type1, typename Type2>
inline auto operator>(
    const detail::binary_callable_with_value<BinaryCallable, Type1>&
                 callable_with_value,
    const Type2& value) -> decltype(auto)
{
    return ::pl::invoke(
        callable_with_value.binary_callable, callable_with_value.value, value);
}

/*!
 * \brief Invokes the named operator with the left hand side and right hand
 *        side objects and assigns the result through to the left hand side
 *        object.
 * \param callable_with_value Contains the left hand side object and the
 *                            named operator.
 * \param value The right hand side object.
 * \return The result of assigning the result of invoking the named operator
 *         with the left hand side and right hand side object to the left
 *         hand side object.
**/
template <typename BinaryCallable, typename Type1, typename Type2>
inline auto operator>=(
    const detail::binary_callable_with_value<BinaryCallable, Type1>&
                 callable_with_value,
    const Type2& value) -> decltype(auto)
{
    return callable_with_value.value = callable_with_value > value;
}
} // inline namespace named_operator
} // namespace pl
#endif // INCG_PL_NAMED_OPERATOR_HPP
