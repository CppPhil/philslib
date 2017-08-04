#ifndef INCG_PL_STRDUP_HPP
#define INCG_PL_STRDUP_HPP
#include "annotations.hpp" // PL_NODISCARD, PL_IN, PL_NULL_TERMINATED
#include <cstddef> // std::size_t
#include <memory> // std::unique_ptr

namespace pl
{
/*!
 * \brief Creates a copy of a null-terminated string.
 * \param str Pointer to the null-terminated byte string to duplicate.
 *            May not be nullptr!
 * \return The copy.
**/
PL_NODISCARD std::unique_ptr<char[]> strdup(PL_IN PL_NULL_TERMINATED(const char *)str);

/*!
 * \brief Creates a unique_ptr that holds a null-terminated byte string.
 * \param str Pointer to the null-terminated byte string to duplicate.
 *            May not be nullptr!
 * \param size Maximum number of bytes to copy from 'str'.
 * \return The duplicated string.
 *
 * Creates a unique_ptr that holds a null-terminated byte string,
 * which contains copies of at most 'size' bytes from the string pointed
 * to by 'str'. If the null terminator is not encountered in the first
 * 'size' bytes, it is added to the duplicated string.
**/
PL_NODISCARD std::unique_ptr<char[]> strndup(PL_IN PL_NULL_TERMINATED(const char *)str,
                                             std::size_t size);
} // namespace pl
#endif // INCG_PL_STRDUP_HPP
