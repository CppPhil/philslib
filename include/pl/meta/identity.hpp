/*!
 * \file identity.hpp
 * \brief Exports the identity meta function.
**/
#ifndef INCG_PL_META_IDENTITY_HPP
#define INCG_PL_META_IDENTITY_HPP

namespace pl
{
namespace meta
{
/*!
 * \brief The identity meta function.
 *        Returns Ty unchanged.
 *
 * The identity meta function.
 * This meta function may be used in a function's parameter list
 * instead of Ty directly in order to prevent type deduction of Ty.
**/
template <typename Ty>
struct identity
{
    using type = Ty;
};

/*!
 * \brief C++14 style helper template alias for the identity meta function.
**/
template <typename Ty>
using identity_t = typename identity<Ty>::type;
} // namespace meta
} // namespace pl
#endif // INCG_PL_META_IDENTITY_HPP
