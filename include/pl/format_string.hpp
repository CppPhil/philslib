/*!
 * \file format_string.hpp
 * \brief Exports a type alias to be used for printf-style format strings.
**/
#ifndef INCG_PL_FORMAT_STRING_HPP
#define INCG_PL_FORMAT_STRING_HPP

namespace pl
{
/*!
 * \brief Type alias of const char *. Only to be used for printf-style
 *        format strings.
**/
using FormatString = const char *;
} // namespace pl
#endif // INCG_PL_FORMAT_STRING_HPP
