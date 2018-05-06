/*!
 * \file noncopyable.hpp
 * \brief Exports a macro to declare a type as noncopyable.
**/
#ifndef INCG_PL_NONCOPYABLE_HPP
#define INCG_PL_NONCOPYABLE_HPP

/*!
 * \def PL_NONCOPYABLE(typeIdentifier)
 * \brief Macro to be placed in the public section of a type.
 *        Pass the identifier of the type into this macro.
 *        Used to declare a type as noncopyable.
**/

#define PL_NONCOPYABLE(typeIdentifier)              \
    typeIdentifier(const typeIdentifier&) = delete; \
    typeIdentifier& operator=(const typeIdentifier&) = delete

#endif // INCG_PL_NONCOPYABLE_HPP
