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
 * \file make_from_tuple.hpp
 * \brief This header file exports the makeFromTuple function.
**/
#ifndef INCG_PL_MAKE_FROM_TUPLE_HPP
#define INCG_PL_MAKE_FROM_TUPLE_HPP
#include "annotations.hpp" // PL_IN
#include <type_traits> // std::decay_t
#include <tuple> // std::get, std::tuple_size
#include <utility> // std::integer_sequence, std::make_index_sequence, std::forward
#include <cstddef> // std::size_t

namespace pl
{
namespace detail
{
/*!
 * \brief Helper function for makeFromTuple.
 * \warning Not to be used directly, use pl::makeFromTuple!.
**/
template <typename Ty, typename TupleLike, std::size_t ...Indices>
constexpr Ty makeFromTupleImpl(
    PL_IN TupleLike &&tupleLike,
    std::index_sequence<Indices ...>)
{
    return Ty(std::get<Indices>(std::forward<TupleLike>(tupleLike)) ...);
}
} // namespace detail

/*!
 * \brief Construct an object of type 'Ty',
 *        using the elements of the tuple 'tupleLike' as the arguments to the constructor.
 * \param tupleLike tuple whose elements to be used as arguments to the constructor of 'Ty'
 * \return The constructed 'Ty' object.
 * \note The tuple need not be std::tuple, and instead may be anything that
 *        supports std::get and std::tuple_size;
 *        in particular, std::array and std::pair may be used.
**/
template <typename Ty, typename TupleLike>
constexpr Ty makeFromTuple(PL_IN TupleLike &&tupleLike)
{
    return detail::makeFromTupleImpl<Ty>(
        std::forward<TupleLike>(tupleLike),
        std::make_index_sequence<std::tuple_size<std::decay_t<TupleLike>>::value>{ });
}
} // namespace pl
#endif // INCG_PL_MAKE_FROM_TUPLE_HPP
