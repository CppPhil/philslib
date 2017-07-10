/*!
 * \file bswap.hpp
 * \brief Exports the bswap function template that allows reversing the bytes
 *        of any object.
**/
#ifndef INCG_PL_BSWAP_HPP
#define INCG_PL_BSWAP_HPP
#include "as_bytes.hpp" // pl::asBytes
#include <algorithm> // std::reverse

namespace pl
{
/*!
 * \brief Reverses the bytes of the argument passed and returns the result.
 * \param ty The object for which to receive a copy of that has its bytes
 *        reversed.
 * \return An object of type Type that has its bytes reversed.
 * \note Can be used to get the big endian version of something when passing
 *       little endian data and vice versa.
 * \note You probably don't want to pass large objects as they're copied into
 *       the parameter.
 *
 * Takes a copy of the argument passed and puts that copy into the parameter.
 * The bytes of that copy are then reversed and the result is passed back out.
**/
template <typename Type>
inline Type bswap(Type ty)
{
    auto begin = asBytes(ty);
    const auto end = begin + sizeof(Type);

    std::reverse(begin, end);

    return ty;
}
} // namespace pl
#endif // INCG_PL_BSWAP_HPP
