/*!
 * \file as_bytes.hpp
 * \brief Exports the asBytes function.
**/
#ifndef INCG_PL_AS_BYTES_HPP
#define INCG_PL_AS_BYTES_HPP
#include "annotations.hpp" // PL_IN
#include "unrelated_pointer_cast.hpp" // pl::unrelated_pointer_cast
#include "byte.hpp" // pl::Byte
#include <memory> // std::addressof

namespace pl
{
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
} // namespace pl
#endif // INCG_PL_AS_BYTES_HPP
