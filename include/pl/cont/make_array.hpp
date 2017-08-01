/*!
 * \file make_array.hpp
 * \brief Exports the makeArray function that creates a std::array
 *        from a given template type parameter pack.
**/
#ifndef INCG_PL_CONT_MAKE_ARRAY_HPP
#define INCG_PL_CONT_MAKE_ARRAY_HPP
#include "../meta/conjunction.hpp" // pl::meta::conjunction
#include "../meta/is_reference_wrapper.hpp" // pl::meta::is_not_reference_wrapper
#include "../annotations.hpp" // PL_IN
#include <utility> // std::forward
#include <array> // std::array
#include <type_traits> // std::common_type

namespace pl
{
namespace cont
{
namespace detail
{
/*!
 * \brief Implementation of makeArray. Do not use directly.
**/
template <typename DesiredType, typename ...>
struct ReturnTypeHelper
{
    using type = DesiredType;
};

/*!
 * \brief Implementation of makeArray. Do not use directly.
**/
template <typename ...Types>
struct ReturnTypeHelper<void, Types ...>
    : public std::common_type<Types ...>
{
    static_assert(::pl::meta::conjunction<::pl::meta::is_not_reference_wrapper<Types> ...>::value,
                  "Types cannot contain reference_wrappers when DesiredType is void");
};

/*!
 * \brief Implementation of makeArray. Do not use directly.
**/
template <typename DesiredType, typename ...Types>
using ReturnType = std::array<typename ReturnTypeHelper<DesiredType, Types ...>::type, sizeof...(Types)>;
} // namespace detail

/*!
 * \brief Creates a std::array from a template type parameter pack.
 * \param args The arguments to construct the std::array returned from.
 * \return The resulting std::array.
**/
template <typename DesiredType = void, typename ...Args>
constexpr detail::ReturnType<DesiredType, Args ...> makeArray(Args &&...args)
{
    return { std::forward<Args>(args)... };
}
} // namespace cont
} // namespace pl
#endif // INCG_PL_CONT_MAKE_ARRAY_HPP
