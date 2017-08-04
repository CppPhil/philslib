/*!
 * \file asprintf.hpp
 * \brief Exports the asprintf overload set.
**/
#ifndef INCG_PL_ASPRINTF_HPP
#define INCG_PL_ASPRINTF_HPP
#include "annotations.hpp" // PL_OUT, PL_IN, PL_FMT_STR, PL_NODISCARD
#include "meta/all_true.hpp" // pl::meta::AllTrue
#include <cstddef> // std::size_t
#include <cstdio> // std::snprintf
#include <string> // std::string
#include <memory> // std::unique_ptr
#include <type_traits> // std::is_pod

namespace pl
{
/*!
 * \brief Allocates a new C-style string in 'buf' that is filled in a printf-style.
 * \param buf A reference to the buffer to store the string in.
 * \param fmtStr The printf-style format string. May not be nullptr!
 * \param args The arguments that match with the format specifiers in 'fmtStr'.
 * \return The number of characters written (not including the terminating
 *         null-character) or a negative number if an error occurred.
 * \note If there are no characters to write the string will be an empty string.
 * \warning Be careful not to use incorrect format specifiers or an incorrect
 *          amount of arguments for the printf-style string.
**/
template <typename ...Args>
PL_NODISCARD inline int asprintf(PL_OUT std::unique_ptr<char[]> &buf,
                                 PL_IN PL_FMT_STR(const char *)fmtStr,
                                 const Args &...args)
{
    static_assert(pl::meta::AllTrue<std::is_pod<Args>::value ...>::value,
                  "All elements of the template type parameter pack in function pl::asprintf must be pod.");

    const auto bytesToWrite
        = static_cast<std::size_t>(std::snprintf(nullptr, 0U, fmtStr, args ...));

    buf = std::make_unique<char[]>(bytesToWrite);

    if (bytesToWrite == 0U) {
        return static_cast<int>(bytesToWrite);
    }

    return std::snprintf(buf.get(), bytesToWrite, fmtStr, args ...);
}

/*!
 * \brief Allocates a new string in 'buf' that is filled in a printf-style.
 * \param buf A reference to the buffer to store the string in.
 * \param fmtStr The printf-style format string. May not be nullptr!
 * \param args The arguments that match with the format specifiers in 'fmtStr'.
 * \return The number of characters written (not including the terminating
 *         null-character) or a negative number if an error occurred.
 * \note If there are no characters to write the string will be an empty string.
 * \warning Be careful not to use incorrect format specifiers or an incorrect
 *          amount of arguments for the printf-style string.
**/
template <typename ...Args>
PL_NODISCARD inline int asprintf(PL_OUT std::string &buf,
                                 PL_IN PL_FMT_STR(const char *)fmtStr,
                                 const Args &...args)
{
    static_assert(pl::meta::AllTrue<std::is_pod<Args>::value ...>::value,
                  "All elements of the template type parameter pack in function pl::asprintf must be pod.");

    const auto bytesToWrite
        = static_cast<std::size_t>(std::snprintf(nullptr, 0U, fmtStr, args ...));

    if (bytesToWrite == 0U) {
        buf = "";
        return static_cast<int>(bytesToWrite);
    }

    buf.resize(bytesToWrite);

    return std::snprintf(&buf[0], bytesToWrite, fmtStr, args ...);
}
} // namespace pl
#endif // INCG_PL_ASPRINTF_HPP
