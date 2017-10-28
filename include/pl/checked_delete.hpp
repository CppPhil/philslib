/*!
 * \file checked_delete.hpp
 * \brief This header defines functions to call delete and delete[] operators
 *        on raw pointers while ensuring that the pointed to type is a complete
 *        type.
**/
#ifndef INCG_PL_CHECKED_DELETE_HPP
#define INCG_PL_CHECKED_DELETE_HPP
#include "annotations.hpp" // PL_IN, PL_INOUT
#include "unused.hpp" // PL_UNUSED
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
inline void checkedDelete(PL_IN Ty *p) noexcept
{
    using incompleteTypeNotAllowed = unsigned char[sizeof(Ty) ? 1 : -1];
    PL_UNUSED(sizeof(incompleteTypeNotAllowed));
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
inline void checkedArrayDelete(PL_IN Ty *p) noexcept
{
    using incompleteTypeNotAllowed = unsigned char[sizeof(Ty) ? 1 : -1];
    PL_UNUSED(sizeof(incompleteTypeNotAllowed));
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
