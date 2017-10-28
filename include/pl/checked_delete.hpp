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
 * \file checked_delete.hpp
 * \brief This header defines functions to call delete and delete[] operators
 *        on raw pointers while ensuring that the pointed to type is a complete
 *        type.
**/
#ifndef INCG_PL_CHECKED_DELETE_HPP
#define INCG_PL_CHECKED_DELETE_HPP
#include "annotations.hpp" // PL_IN_OPT, PL_INOUT
#include <new> // operator delete, operator delete[]
#include <cstddef> // std::nullptr_t

namespace pl
{
/*!
 * \brief Calls delete on the pointer passed in.
 * \param p The pointer to call delete on.
 * \note Will cause a compilation error if the pointed to type is incomplete,
 *       preventing undefined behavior to occur.
 *       To be used as a replacement for operator delete.
 * \warning Only pass in raw pointers to a dynamically allocated object.
 *          The raw pointer passed in must be the sole owner of the pointed to
 *          object.
**/
template <typename Ty>
inline void checkedDelete(PL_IN_OPT Ty *p) noexcept
{
    using incompleteTypeNotAllowed = unsigned char[sizeof(Ty) ? 1 : -1];
    (void)sizeof(incompleteTypeNotAllowed);
    delete p;
}

/*!
 * \brief Calls delete[] on the pointer passed in.
 * \param p The pointer to call delete[] on.
 * \note Will cause a compilation error if the pointed to type is incomplete,
 *       preventing undefined behavior to occur.
 *       To be used as a replacement for operator delete[].
 * \warning Only pass in raw pointers to dynamically allocated C-style arrays.
 *          The raw pointer passed in must be the sole owner of the
 *          pointed to C-style array.
 */
template <typename Ty>
inline void checkedArrayDelete(PL_IN_OPT Ty *p) noexcept
{
    using incompleteTypeNotAllowed = unsigned char[sizeof(Ty) ? 1 : -1];
    (void)sizeof(incompleteTypeNotAllowed);
    delete[] p;
}

/*!
 * \brief Calls pl::checkedDelete on the pointer passed in and then nulls the pointer.
 * \param p A reference to the pointer to call pl::checkedDelete on and then null.
 * \see pl::checkedDelete
 */
template <typename Ty>
inline void checkedDeleteAndNull(PL_INOUT Ty *&p) noexcept
{
    ::pl::checkedDelete(p);
    p = nullptr;
}

/*!
 * \brief Calls pl::checkedArrayDelete on the pointer passed in and then nulls the pointer.
 * \param p A reference to the pointer to caall pl::checkedArrayDelete on and then null.
 * \see pl::checkedArrayDelete
 */
template <typename Ty>
inline void checkedArrayDeleteAndNull(PL_INOUT Ty *&p) noexcept
{
    ::pl::checkedArrayDelete(p);
    p = nullptr;
}
} // namespace pl
#endif // INCG_PL_CHECKED_DELETE_HPP
