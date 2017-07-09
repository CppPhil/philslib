/*!
 * \file memory.hpp
 * \brief This header defines various dynamic memory management utilities.
**/
#ifndef INCG_PL_MEMORY_HPP
#define INCG_PL_MEMORY_HPP
#include "macros.hpp" // PL_UNUSED
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
inline void checkedDelete(Ty *p)
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
inline void checkedArrayDelete(Ty *p)
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
inline void checkedDeleteAndNull(Ty *&p)
{
    checkedDelete(p);
    p = nullptr;
}

/*!
 * \brief Calls pl::checkedArrayDelete on the pointer passed in and then nulls the pointer.
 * \param p A reference to the pointer to caall pl::checkedArrayDelete on and then null.
 * \see pl::checkedArrayDelete
 */
template <typename Ty>
inline void checkedArrayDeleteAndNull(Ty *&p)
{
    checkedArrayDelete(p);
    p = nullptr;
}
} // namespace pl
#endif // INCG_PL_MEMORY_HPP
