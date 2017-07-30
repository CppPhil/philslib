/*!
 * \file void_t.hpp
 * \brief Exports the void_t metafunction from C++17.
**/
#ifndef INCG_PL_META_VOID_T_HPP
#define INCG_PL_META_VOID_T_HPP

namespace pl
{
namespace meta
{
namespace detail
{
/*!
 * \brief Implementation struct of pl::meta::void_t, not to be used directly.
**/
template <typename ...Args>
struct void_t_impl
{
    using type = void;
};
} // namespace detail

/*!
 * \brief Utility metafunction that maps a sequence of any types to the type void.
 * \note This is just like std::void_t from C++17.
 *
 * This metafunction is used in template metaprogramming to detect
 * ill-formed types in SFINAE contexts.
**/
template <typename ...Args>
using void_t = typename detail::void_t_impl<Args ...>::type;
} // namespace meta
} // namespace pl
#endif // INCG_PL_META_VOID_T_HPP
