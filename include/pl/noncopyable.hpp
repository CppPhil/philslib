/*!
 * \file noncopyable.hpp
 * \brief Exports the Noncopyable type that may be used as a private base type.
**/
#ifndef INCG_PL_NONCOPYABLE_HPP
#define INCG_PL_NONCOPYABLE_HPP

namespace pl
{
namespace detail_noncopyable
{
/*!
 * \brief Implementation of Noncopyable. Use the pl::Noncopyable type alias.
**/
class NoncopyableImpl
{
protected:
    constexpr NoncopyableImpl() = default;

    ~NoncopyableImpl() = default;

    NoncopyableImpl(const NoncopyableImpl &) = delete;

    NoncopyableImpl &operator=(const NoncopyableImpl &) = delete;
};
} // namespace detail_noncopyable

/*!
 * \brief Privately derive from this type to make a type noncopyable.
**/
using Noncopyable = ::pl::detail_noncopyable::NoncopyableImpl;
} // namespace pl
#endif // INCG_PL_NONCOPYABLE_HPP
