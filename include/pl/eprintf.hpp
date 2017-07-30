/*!
 * \file eprintf.hpp
 * \brief Exports the eprintf function.
**/
#ifndef INCG_PL_EPRINTF_HPP
#define INCG_PL_EPRINTF_HPP
#include "annotations.hpp" // PL_IN, PL_FMT_STR, PL_PRINTF_FUNCTION

namespace pl
{
/*!
 * \brief printf-style function that prints to stderr, rather than stdout.
 * \param formatString A null-terminated printf-style format string to use for printing.
 *                     May never be nullptr.
 * \return Number of characters written if successful
 *         or negative value if an error occurred.
 * \note Behaves exactly like std::printf, but prints to stderr rather than stdout.
**/
int eprintf(PL_IN PL_FMT_STR(const char *)formatString, ...) PL_PRINTF_FUNCTION(1, 2);
} // namespace pl
#endif // INCG_PL_EPRINTF_HPP
