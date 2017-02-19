/*! \file lowlevel.hpp
 *  \brief This header defines various low level utilities.
**/

#ifndef INCG_PL_LOWLEVEL_HPP
#define INCG_PL_LOWLEVEL_HPP
#include <type_traits> // std::is_pointer, std::remove_pointer_t, std::is_const
#include <memory> // std::addressof
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
CastTo unrelated_pointer_cast(void *p)
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
CastTo unrelated_pointer_cast(const void *p)
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
Byte *asBytes(Type &object)
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
const Byte *asBytes(const Type &object)
{
    return unrelated_pointer_cast<const Byte *>(std::addressof(object));
}



} // namespace pl
#endif // INCG_PL_LOWLEVEL_HPP
