/*!
 * \file disable_if.hpp
 * \brief Exports the disable_if meta function.
**/
#ifndef INCG_PL_META_DISABLE_IF_HPP
#define INCG_PL_META_DISABLE_IF_HPP

namespace pl
{
namespace meta
{
/*!
 * \brief The disable_if meta function.
 * \note This is the false case.
 *
 * disable_if behaves like an inverted std::enable_if,
 * that is if the condition 'BoolVal' is false the
 * nested type 'type' will be defined.
 * If 'BoolVal' is true the nested type 'type' will not be defined.
**/
template <bool BoolVal, typename Ty = void>
struct disable_if
{
    // BoolVal is false -> ok.
    using type = Ty;
};

/*!
 * \brief The disable_if meta function.
 * \note This is the true case.
 *
 * disable_if behaves like an inverted std::enable_if,
 * that is if the condition 'BoolVal' is false the
 * nested type 'type' will be defined.
 * If 'BoolVal' is true the nested type 'type' will not be defined.
**/
template <typename Ty>
struct disable_if<true, Ty>
{
    // BoolVal is true -> SFINAE away.
};

/*!
 * \brief C++14 style helper template alias for disable_if.
**/
template <bool BoolVal, typename Ty = void>
using disable_if_t = typename disable_if<BoolVal, Ty>::type;
} // namespace meta
} // namespace pl
#endif // INCG_PL_META_DISABLE_IF_HPP
