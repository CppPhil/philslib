/*!
 * \file named_operator.hpp
 * \brief Exports utilities for defining named operators.
**/
#ifndef INCG_PL_NAMED_OPERATOR_HPP
#define INCG_PL_NAMED_OPERATOR_HPP
#include "invoke.hpp" // pl::invoke

namespace pl
{
namespace detail
{
/*!
 * \brief Implementation wrapper type used to communicate between operator<
 *        and operator>.
**/
template <typename BinaryCallable, typename Type>
struct BinaryCallableWithValue
{
    BinaryCallable binaryCallable; /*!< The callable to run in operator> */
    Type &value; /*!< The left hand side value */
};
} // namespace detail

/*!
 * \brief Struct that holds a BinaryCallable to be used as a named operator.
 * \note Use makeNamedOperator to construct.
**/
template <typename BinaryCallable>
struct NamedOperator
{
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
constexpr NamedOperator<BinaryCallable>
makeNamedOperator(BinaryCallable binaryCallable)
{
    return { binaryCallable };
}

inline namespace named_operator
{
/*!
 * \brief The operator<, creates the BinaryCallableWithValue object.
 * \param value The left hand side object of the named operator.
 * \param namedOperator The named operator that the operator> shall apply.
 * \note Handles non-const left hand side objects.
**/
template <typename BinaryCallable, typename Type>
inline detail::BinaryCallableWithValue<BinaryCallable, Type>
operator<(Type &value, NamedOperator<BinaryCallable> namedOperator)
{
    return { namedOperator.binaryCallable, value };
}

/*!
 * \brief The operator<, creates the BinaryCallableWithValue object.
 * \param value The left hand side object of the named operator.
 * \param namedOperator The named operator that the operator> shall apply.
 * \note Handles const qualified left hand side objects.
**/
template <typename BinaryCallable, typename Type>
inline detail::BinaryCallableWithValue<BinaryCallable, const Type>
operator<(const Type &value, NamedOperator<BinaryCallable> namedOperator)
{
    return { namedOperator.binaryCallable, value };
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
inline auto
operator>(const detail::BinaryCallableWithValue<BinaryCallable, Type1> &callableWithValue,
          const Type2 &value) -> decltype(auto)
{
    return ::pl::invoke(callableWithValue.binaryCallable,
                        callableWithValue.value, value);
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
inline auto
operator>=(const detail::BinaryCallableWithValue<BinaryCallable, Type1> &callableWithValue,
           const Type2 &value) -> decltype(auto)
{
    return callableWithValue.value = callableWithValue > value;
}
} // inline namespace named_operator
} // namespace pl
#endif // INCG_PL_NAMED_OPERATOR_HPP
