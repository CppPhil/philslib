/*!
 * \file memxor.hpp
 * \brief Exports the memxor function.
**/
#ifndef INCG_PL_MEMXOR_HPP
#define INCG_PL_MEMXOR_HPP
#include "annotations.hpp" // PL_IN, PL_INOUT
#include "restrict.hpp" // PL_RESTRICT
#include "byte.hpp" // pl::Byte
#include <cstddef> // std::size_t

namespace pl
{
/*!
 * \brief Bytewise xor-assigns the memory pointed to by 'destination'
 *        with the memory pointed to by 'source'.
 * \param destination The buffer that will be xor-assigned to.
 *                    May not be nullptr!
 * \param source The buffer with which 'destination' shall be xored.
 *               May not be nullptr!
 * \param byteCount The size in bytes of the source buffer.
 *                  The destination buffer must be at least as large as
 *                  'byteCount'. You probably want to use buffers of equal
 *                  byte size for 'destination' and 'source'.
 * \return 'destination' is returned.
 * \warning Make sure 'byteCount' is correct!
**/
constexpr void *memxor(
    PL_INOUT void * PL_RESTRICT destination,
    PL_IN const void * PL_RESTRICT source,
    std::size_t byteCount)
{
    auto dest = static_cast<Byte * PL_RESTRICT>(destination);
    auto src  = static_cast<const Byte * PL_RESTRICT>(source);

    while (byteCount > 0) {
        *dest ^= *src;

        --byteCount;
        ++dest;
        ++src;
    }

    return destination;
}
} // namespace pl
#endif // INCG_PL_MEMXOR_HPP
