/*!
 * \file zero_memory.hpp
 * \brief Exports the pl::zeroMemory and the pl::secureZeroMemory functions.
**/
#ifndef INCG_PL_ZERO_MEMORY_HPP
#define INCG_PL_ZERO_MEMORY_HPP
#include "annotations.hpp" // PL_OUT
#include "inline.hpp" // PL_ALWAYS_INLINE
#include "byte.hpp" // pl::Byte
#include <cstddef> // std::size_t

namespace pl
{
/*!
 * \brief Copies a zero byte into each of the first countBytes
 *        characters of the object pointed to by dest.
 * \param dest Pointer to the object to fill with zero bytes.
 *        (May never be a null pointer!)
 * \param countBytes number of bytes to fill with zeroes.
 * \return dest (a copy of the first parameter as it was passed in)
 * \warning pl::zeroMemory may be optimized away if the object modified
 *          by this function is not accessed again for the rest of its lifetime.
 *          For that reason, this function cannot be used
 *          to scrub memory (e.g. to fill an array that stored a password
 *          with zeroes). Use secureZeroMemory in those cases as it will
 *          not be optimized.
 * \warning If the object pointed to by dest is not trivially-copyable
 *          (e.g., scalar, array, or a C-compatible struct),
 *          the behavior is undefined.
 * \warning If countBytes is greater than the size of the object pointed
 *          to by dest, the behavior is undefined.
 * \warning dest may not be a null pointer.
 * \see secureZeroMemory
**/
PL_ALWAYS_INLINE void *zeroMemory(
    PL_OUT void *dest,
    std::size_t countBytes) noexcept
{
    Byte *ptr{ static_cast<Byte *>(dest) };

    for (; countBytes != 0U; ++ptr, --countBytes) {
        *ptr = 0U;
    }

    return dest;
}

/*!
 * \brief Copies a zero byte into each of the first countBytes characters
 *        of the object pointed to by dest.
 * \param dest Pointer to the object to fill with zero bytes.
 *        (May never be a null pointer!)
 * \param countBytes number of bytes to fill with zeroes.
 * \return dest (a copy of the first parameter as it was passed in)
 * \note Unlike pl::zeroMemory a call to this function will never be
 *       optimized away.
 * \warning If the object pointed to by dest is not trivially-copyable
 *          (e.g., scalar, array, or a C-compatible struct), the behavior is
 *          undefined.
 * \warning If countBytes is greater than the size of the object pointed to by
 *          dest, the behavior is undefined.
 * \warning dest may not be a null pointer.
 * \see zeroMemory
 *
 * Zeroes bytes just like pl::zeroMemory, but ensures that the compiler
 * will not optimize the function call away. Use this function instead of
 * pl::zeroMemory when you want to ensure that the data will be zeroed out
 * even if the object pointed to by dest will not be referenced after
 * a call to this function.
**/
PL_ALWAYS_INLINE void *secureZeroMemory(
    PL_OUT void *dest,
    std::size_t countBytes) noexcept
{
    volatile Byte *ptr{ static_cast<volatile Byte *>(dest) };

    for (; countBytes != 0U; ++ptr, --countBytes) {
        *ptr = 0U;
    }

    return dest;
}
} // namespace pl
#endif // INCG_PL_ZERO_MEMORY_HPP
