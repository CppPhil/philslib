/*!
 * \file bool_pack.hpp
 * \brief Declares the BoolPack type.
**/
#ifndef INCG_PL_META_BOOL_PACK_HPP
#define INCG_PL_META_BOOL_PACK_HPP

namespace pl
{
namespace meta
{
/*!
 * \brief Type of an arbitrary amount of compile time booleans.
**/
template <bool ...>
struct BoolPack;
} // namespace meta
} // namespace pl
#endif // INCG_PL_META_BOOL_PACK_HPP
