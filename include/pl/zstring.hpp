/*!
 * \file zstring.hpp
 * \brief Exports type aliases for zero terminated C-style strings.
**/
#ifndef INCG_PL_ZSTRING_HPP
#define INCG_PL_ZSTRING_HPP

namespace pl
{
/*!
 * \brief A zero terminated non-const C-style string as char *.
 * \note Only to be used for null-terminated strings.
**/
using zstring = char *;

/*!
 * \brief A zero terminated const C-style string as const char *.
 * \note Only to be used for null-terminated strings.
**/
using czstring = const char *;

/*!
 * \brief A zero terminated non-const C-style string as char[].
 * \note Only to be used for null-terminated strings.
**/
using zastring = char[];

/*!
 * \brief A zero terminated const C-style string as const char[].
 * \note Only to be used for null-terminated strings.
**/
using czastring = const char[];
} // namespace pl
#endif // INCG_PL_ZSTRING_HPP
