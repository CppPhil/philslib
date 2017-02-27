/*! \file lowlevel.hpp
 *  \brief This header defines various low level utilities.
**/

#ifndef INCG_PL_LOWLEVEL_HPP
#define INCG_PL_LOWLEVEL_HPP
#include "macros.hpp" // PL_IN, PL_IN_OPT
#include <cstddef> // std::size_t
#include <type_traits> // std::is_pointer, std::remove_pointer_t, std::is_const, std::is_unsigned
#include <memory> // std::addressof
#include <algorithm> // std::reverse
namespace pl
{
/*!
 * \brief The Byte type. To be used when viewing something as raw bytes.
 *        An alias for unsigned char. This type is effectively a 1 byte large
 *        unsigned integer.
**/
using Byte = unsigned char;

/*!
 * \brief Casts a raw pointer type to another unrelated pointer type.
 * \param p The pointer to cast to CastTo.
 * \return The result of casting p to type CastTo
 * \note Note that all raw pointers without low level constness
 *       are implicitly convertible to void *, so you can just pass your raw
 *       pointer in as is.
 * \note The type to cast to called CastTo must be a raw pointer type.
 * \note This is the overload for pointers without low level constness.
 * \note You must supply the template type parameter CastTo.
**/
template <typename CastTo>
CastTo unrelated_pointer_cast(PL_IN_OPT void *p)
{
    static_assert(std::is_pointer<CastTo>::value,
        "The type to cast to must be a raw pointer type in pl::unrelated_pointer_cast (non-const)");

    return static_cast<CastTo>(p);
}

/*!
 * \brief Casts a raw pointer type to another unrelated raw pointer type.
 * \param p The raw pointer to be casted to type CastTo.
 * \return The result of casting p to type CastTo.
 * \note Note that all raw pointers with low level constness
 *       are implicitly convertible to const void *, so you can just pass
 *       your raw pointer in as is.
 * \note CastTo must be a raw pointer type.
 * \note CastTo must have low level constness
 * \note This is the overload for raw pointers with low level constness.
 * \note You must supply the template type parameter CastTo.
**/
template <typename CastTo>
CastTo unrelated_pointer_cast(PL_IN_OPT const void *p)
{
    static_assert(std::is_pointer<CastTo>::value,
        "The type to cast to must be a raw pointer type in pl::unrelated_pointer_cast (const)");
    static_assert(std::is_const<std::remove_pointer_t<CastTo>>::value,
        "The type to cast to must have low level constness in pl::unrelated_pointer_cast (const)");

    return static_cast<CastTo>(p);
}

/*!
 * \brief Allows the user to view an object as just raw bytes.
 * \param object The object to be viewed as raw bytes.
 * \return The address of the beginning of object as Byte *.
 * \note This overload deals with non-const objects.
 * \note The pointer returned will never be nullptr.
**/
template <typename Type>
Byte *asBytes(PL_IN Type &object)
{
    return unrelated_pointer_cast<Byte *>(std::addressof(object));
}

/*!
 * \brief Allows the user to view an object as just raw bytes.
 * \param object The object to be viewed as raw bytes.
 * \return The address of the beginning of object as const Byte *.
 * \note This overload deals with const objects.
 * \note The pointer returned will never be nullptr.
**/
template <typename Type>
const Byte *asBytes(PL_IN const Type &object)
{
    return unrelated_pointer_cast<const Byte *>(std::addressof(object));
}

/*!
 * \brief Sets the bit at position bit of numeric.
 * \param numeric The number to have its bit bit set.
 * \param bit The bit to set in numeric. [0..bits(Numeric))
 * \warning Do not pass a value in bit that is larger than the amount
 *          of bits in Numeric - 1.
**/
template <typename Numeric>
void setBit(PL_INOUT Numeric &numeric, Numeric bit)
{
    static_assert(std::is_unsigned<Numeric>::value,
                  "Numeric in pl::setBit should be an unsigned type.");
    static constexpr Numeric activeBit = 1U;

    numeric |= (activeBit << bit);
}

/*!
 * \brief Clears the bit bit in numeric.
 * \param numeric The number to have its bit bit cleared.
 * \param bit The bit to clear in numeric. [0..bits(Numeric))
 * \warning The value in bit must not be larger than the amount of bits in
 *          Numeric - 1.
**/
template <typename Numeric>
void clearBit(PL_INOUT Numeric &numeric, Numeric bit)
{
    static_assert(std::is_unsigned<Numeric>::value,
                  "Numeric in pl::clearBit should be an unsigned type.");
    static constexpr Numeric activeBit = 1U;

    numeric &= ~(activeBit << bit);
}

/*!
 * \brief Toggles the bit bit in numeric.
 * \param numeric The number to have its bit bit toggled.
 * \param bit The bit in numeric to toggle. [0..bits(Numeric))
 * \warning Do not pass a value in bit that is larger than
 *          the number of bits in Numeric - 1.
 *
 * Toggles the bit that was passed into the parameter bit in the
 * numeric (first parameter). If the bit bit in numeric is 1 it will be
 * 0 after having executed this function. If the bit bit in numeric is 0 it
 * will be 1 after having executed this function.
**/
template <typename Numeric>
void toggleBit(PL_INOUT Numeric &numeric, Numeric bit)
{
    static_assert(std::is_unsigned<Numeric>::value,
                  "Numeric in pl::toggleBit should be an unsigned type.");
    static constexpr Numeric activeBit = 1U;

    numeric ^= (activeBit << bit);
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
bool isBitSet(Numeric numeric, Numeric bit)
{
    static_assert(std::is_unsigned<Numeric>::value,
                  "Numeric in pl::isBitSet should be an unsigned type.");
    static constexpr Numeric activeBit = 1U;

    return ((numeric & (activeBit << bit)) != 0);
}

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
Type bswap(Type ty)
{
    auto begin = asBytes(ty);
    auto const end = begin + sizeof(Type);

    std::reverse(begin, end);

    return ty;
}

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
void *zeroMemory(PL_OUT void *dest, std::size_t countBytes);

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
 *          (e.g., scalar, array, or a C-compatible struct), the behaviour is
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
void *secureZeroMemory(PL_OUT void *dest, std::size_t countBytes);

} // namespace pl
#endif // INCG_PL_LOWLEVEL_HPP
