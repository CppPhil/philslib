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
 * \file as_bytes.hpp
 * \brief Exports the as_bytes function.
**/
#ifndef INCG_PL_AS_BYTES_HPP
#define INCG_PL_AS_BYTES_HPP
#include "annotations.hpp"            // PL_IN
#include "byte.hpp"                   // pl::byte
#include "unrelated_pointer_cast.hpp" // pl::unrelated_pointer_cast
#include <memory>                     // std::addressof

namespace pl {
/*!
 * \brief Allows the user to view an object as just raw bytes.
 * \param object The object to be viewed as raw bytes.
 * \return The address of the beginning of object as byte*.
 * \note This overload deals with non-const objects.
 * \note The pointer returned will never be nullptr.
**/
template <typename Type>
constexpr byte* as_bytes(PL_IN Type& object) noexcept
{
    return ::pl::unrelated_pointer_cast<byte*>(std::addressof(object));
}

/*!
 * \brief Allows the user to view an object as just raw bytes.
 * \param object The object to be viewed as raw bytes.
 * \return The address of the beginning of object as const byte*.
 * \note This overload deals with const objects.
 * \note The pointer returned will never be nullptr.
**/
template <typename Type>
constexpr const byte* as_bytes(PL_IN const Type& object) noexcept
{
    return ::pl::unrelated_pointer_cast<const byte*>(std::addressof(object));
}

/*!
 * \brief Rvalues are not allowed.
**/
template <typename Type>
void as_bytes(PL_IN const Type&&) noexcept = delete;
} // namespace pl
#endif // INCG_PL_AS_BYTES_HPP
