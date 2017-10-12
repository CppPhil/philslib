/*!
 * \file asprintf.hpp
 * \brief Exports asprintf functions.
**/
#ifndef INCG_PL_ASPRINTF_HPP
#define INCG_PL_ASPRINTF_HPP
#include "annotations.hpp" // PL_OUT, PL_IN, PL_FMT_STR, PL_NODISCARD, ...
#include <cstdarg> // std::va_list
#include <string> // std::string
#include <memory> // std::unique_ptr

namespace pl
{
/*!
 * \brief Allocates a string and prints to it in a printf style.
 * \param strp Pointer to a unique_ptr<char[]>. The unique_ptr<char[]> pointed
 *             to will be replaced with a new unique_ptr<char[]> that will
 *             own the newly allocated memory which will contain the resulting
 *             string. May not be nullptr!
 * \param fmt A null-terminated byte character string to be used as the
 *            printf style format string. May not be nullptr!
 * \param ap The va_list that contains the arguments as specified by 'fmt'.
 * \return The number of bytes written on success or a negative number on
 *         error.
 * \warning Will cause undefined behavior if 'strp' or 'fmt' is nullptr.
 * \note In general you probably want to be using asprintf instead.
**/
PL_NODISCARD int vasprintf(
    PL_OUT std::unique_ptr<char[]> *strp,
    PL_IN PL_FMT_STR(const char *)fmt,
    std::va_list ap) noexcept PL_PRINTF_FUNCTION(2, 0);

/*!
 * \brief Creates a string and prints to it in a printf style.
 * \param strp Pointer to a string. The string pointed to will be resized
 *             to be large enough and be filled with the resulting string.
 *             May not be nullptr!
 * \param fmt A null-terminated byte character string to be used as the
 *            printf style format string. May not be nullptr!
 * \param ap The va_list that contains the arguments as specified by 'fmt'.
 * \return The number of bytes written on success or a negative number on
 *         error.
 * \warning Will cause undefined behavior if 'strp' or 'fmt' is nullptr.
 * \note In general you probably want to be using asprintf instead.
**/
PL_NODISCARD int vasprintf(
    PL_OUT std::string *strp,
    PL_IN PL_FMT_STR(const char *)fmt,
    std::va_list ap) noexcept PL_PRINTF_FUNCTION(2, 0);

/*!
 * \brief Allocates a string and prints to it in a printf style.
 * \param strp Pointer to a unique_ptr<char[]>. The unique_ptr<char[]> will be
 *             replaced with a newly created unique_ptr<char[]> that owns
 *             newly allocated memory containing the resulting string.
 *             May not be nullptr!
 * \param fmt A null-terminated byte character string to be used as the printf
 *            style format string. May not be nullptr!
 * \return The number of bytes written on success or a negative number on error.
 * \warning Will cause undefined behavior if 'strp' or 'fmt' is nullptr.
**/
PL_NODISCARD int asprintf(
    PL_OUT std::unique_ptr<char[]> *strp,
    PL_IN PL_FMT_STR(const char *)fmt,
    ...) noexcept PL_PRINTF_FUNCTION(2, 3);

/*!
 * \brief Creates a string and prints to it in a printf style.
 * \param strp Pointer to a string. The string will be resized to be large
 *             enough and will be made to contain the resulting string.
 *             May not be nullptr!
 * \param fmt A null-terminated byte character string to be used as the printf
 *            style format string. May not be nullptr!
 * \return The number of bytes written on success or a negative number on error.
 * \warning Will cause undefined behavior if 'strp' or 'fmt' is nullptr.
**/
PL_NODISCARD int asprintf(
    PL_OUT std::string *strp,
    PL_IN PL_FMT_STR(const char *)fmt,
    ...) noexcept PL_PRINTF_FUNCTION(2, 3);
} // namespace pl
#endif // INCG_PL_ASPRINTF_HPP
