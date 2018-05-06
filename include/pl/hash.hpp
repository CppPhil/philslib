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
 * \file hash.hpp
 * \brief Header file that defines hashing utilities.
 *        So that implementing hash functions for user defined types
 *        becomes easier.
**/
#ifndef INCG_PL_HASH_HPP
#define INCG_PL_HASH_HPP
#include "annotations.hpp"  // PL_IN, PL_INOUT
#include <cstddef>          // std::size_t
#include <functional>       // std::hash
#include <initializer_list> // std::initializer_list

namespace pl {
namespace detail {
/*!
 * \brief Adds the hash generated for hashable to the current hashSeed.
 * \param hashSeed The hash seed to have the newly generated hash value be
 *        added to.
 * \param hashable The object to generate a hash for.
**/
template <typename Hashable>
void addHash(
    PL_INOUT std::size_t& hashSeed,
    PL_IN const Hashable& hashable) noexcept
{
    static constexpr auto shiftRight  = 0x2;
    static constexpr auto shiftLeft   = 0x6;
    static constexpr auto goldenRatio = 0x9E3779B9;

    std::hash<Hashable> hasher{};
    hashSeed ^= hasher(hashable) + goldenRatio + (hashSeed << shiftLeft)
                + (hashSeed >> shiftRight);
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
template <typename... Args>
std::size_t hash(PL_IN const Args&... args) noexcept
{
    std::size_t hashSeed{0U};

    (void)std::initializer_list<int>{(detail::addHash(hashSeed, args), 0)...};

    return hashSeed;
}
} // namespace pl
#endif // INCG_PL_HASH_HPP
