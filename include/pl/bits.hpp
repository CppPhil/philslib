/*!
 * \file bits.hpp
 * \brief This header defines various functions for bitwise operations.
**/
#ifndef INCG_PL_BITS_HPP
#define INCG_PL_BITS_HPP
#include "annotations.hpp" // PL_INOUT
#include <type_traits> // std::is_unsigned

namespace pl
{
/*!
 * \brief Sets the bit at position bit of numeric.
 * \param numeric The number to have its bit bit set.
 * \param bit The bit to set in numeric. [0..bits(Numeric))
 * \return A reference to 'numeric'.
 * \warning Do not pass a value in bit that is larger than the amount
 *          of bits in Numeric - 1.
**/
template <typename Numeric>
inline Numeric &setBit(PL_INOUT Numeric &numeric, Numeric bit)
{
    static_assert(std::is_unsigned<Numeric>::value,
                  "Numeric in pl::setBit should be an unsigned type.");
    static constexpr Numeric activeBit = 1U;

    numeric |= (activeBit << bit);
    return numeric;
}

/*!
 * \brief Clears the bit bit in numeric.
 * \param numeric The number to have its bit bit cleared.
 * \param bit The bit to clear in numeric. [0..bits(Numeric))
 * \return A reference to 'numeric'.
 * \warning The value in bit must not be larger than the amount of bits in
 *          Numeric - 1.
**/
template <typename Numeric>
inline Numeric &clearBit(PL_INOUT Numeric &numeric, Numeric bit)
{
    static_assert(std::is_unsigned<Numeric>::value,
                  "Numeric in pl::clearBit should be an unsigned type.");
    static constexpr Numeric activeBit = 1U;

    numeric &= ~(activeBit << bit);
    return numeric;
}

/*!
 * \brief Toggles the bit bit in numeric.
 * \param numeric The number to have its bit bit toggled.
 * \param bit The bit in numeric to toggle. [0..bits(Numeric))
 * \return A reference to 'numeric'.
 * \warning Do not pass a value in bit that is larger than
 *          the number of bits in Numeric - 1.
 *
 * Toggles the bit that was passed into the parameter bit in the
 * numeric (first parameter). If the bit bit in numeric is 1 it will be
 * 0 after having executed this function. If the bit bit in numeric is 0 it
 * will be 1 after having executed this function.
**/
template <typename Numeric>
inline Numeric &toggleBit(PL_INOUT Numeric &numeric, Numeric bit)
{
    static_assert(std::is_unsigned<Numeric>::value,
                  "Numeric in pl::toggleBit should be an unsigned type.");
    static constexpr Numeric activeBit = 1U;

    numeric ^= (activeBit << bit);
    return numeric;
}

/*!
 * \brief Determines whether or not the bit bit in numeric is set.
 * \param numeric The number in which to check the bit bit.
 * \param bit The bit that is to be checked in number. [0..bits(Numeric))
 * \return true if the bit bit in numeric is set; false otherwise.
 * \warning Do not pass a value into the parameter bit that is larger than
 *          the number of bits in Numeric - 1.
**/
template <typename Numeric>
inline bool isBitSet(Numeric numeric, Numeric bit)
{
    static_assert(std::is_unsigned<Numeric>::value,
                  "Numeric in pl::isBitSet should be an unsigned type.");
    static constexpr Numeric activeBit = 1U;

    return ((numeric & (activeBit << bit)) != 0);
}
} // namespace pl
#endif // INCG_PL_BITS_HPP
