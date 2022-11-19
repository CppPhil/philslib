/*!
 * \file noncopyable.hpp
 * \brief Exports a macro to declare a type as noncopyable.
 **/
#ifndef INCG_PL_NONCOPYABLE_HPP
#define INCG_PL_NONCOPYABLE_HPP

/*!
 * \def PL_NONCOPYABLE(type_identifier)
 * \brief Macro to be placed in the public section of a type.
 *        Pass the identifier of the type into this macro.
 *        Used to declare a type as noncopyable.
 **/

#define PL_NONCOPYABLE(type_identifier)             \
  type_identifier(const type_identifier&) = delete; \
  type_identifier& operator=(const type_identifier&) = delete

#endif // INCG_PL_NONCOPYABLE_HPP
