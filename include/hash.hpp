/*! \file hash.hpp
 *  \brief Header file that defines hashing utilities.
 *         So that implementing hash functions for user defined types
 *         becomes easier.
**/

#ifndef INCG_PL_HASH_HPP
#define INCG_PL_HASH_HPP
#include "macros.hpp" // PL_IN, PL_INOUT, PL_UNUSED
#include <functional> // std::hash
#include <cstddef> // std::size_t
#include <initializer_list> // std::initializer_list
namespace pl
{
namespace detail
{
/*!
 * \brief Adds the hash generated for hashable to the current hashSeed.
 * \param hashSeed The hash seed to have the newly generated hash value be
 *        added to.
 * \param hashable The object to generate a hash for.
**/
template <typename Hashable>
void addHash(PL_INOUT std::size_t &hashSeed, PL_IN const Hashable &hashable)
{
    static constexpr auto shiftRight = 0x2;
    static constexpr auto shiftLeft = 0x6;
    static constexpr auto goldenRatio = 0x9E3779B9;

    auto hasher = std::hash<Hashable>{ };
    hashSeed ^= hasher(hashable) + goldenRatio
                + (hashSeed << shiftLeft) + (hashSeed >> shiftRight);
}
} // namespace detail

/*!
 * \brief Computes a hash for the arguments passed in.
 * \param args The arguments to get a hash for.
 * \return The computed hash value.
 *
 * This function can be used for explicit specializations of std::hash
 * for user defined types. All of the type's data members are passed to
 * this function.
**/
template <typename ...Args>
std::size_t hash(PL_IN const Args &...args) {
    auto hashSeed = static_cast<std::size_t>(0U);

    PL_UNUSED(std::initializer_list<int>{
        (detail::addHash(hashSeed, args), 0)...
    });

    return hashSeed;
}
} // namespace pl
#endif // INCG_PL_HASH_HPP
