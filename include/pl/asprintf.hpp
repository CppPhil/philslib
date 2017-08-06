/*!
 * \file asprintf.hpp
 * \brief Exports asprinf functions.
**/
#ifndef INCG_PL_ASPRINTF_HPP
#define INCG_PL_ASPRINTF_HPP
#include "annotations.hpp" // PL_OUT, PL_IN, PL_FMT_STR, PL_NODISCARD
#include "except.hpp" // pl::AsprintfFailureException
#include "meta/all.hpp" // pl::meta::AllTrue
#include <cstddef> // std::size_t
#include <cstdio> // std::snprintf
#include <string> // std::string
#include <memory> // std::unique_ptr
#include <type_traits> // std::is_pod

namespace pl
{
/*!
 * \brief Allocates a new C-style string that is filled in a printf-style.
 * \param fmtStr The printf-style format string. May not be nullptr!
 * \param args The arguments that match with the format specifiers in 'fmtStr'.
 * \return The string.
 * \note If there are no characters to write the string to be returned
 *       will be an empty string.
 * \warning Be careful not to use incorrect format specifiers or an incorrect
 *          amount of arguments for the printf-style string.
 * \throws pl::AsprintfFailureException if an error occurred.
**/
template <typename ...Args>
PL_NODISCARD inline std::unique_ptr<char[]> asprintfUptr(PL_IN PL_FMT_STR(const char *)fmtStr,
                                                         const Args &...args)
{
    static_assert(pl::meta::All<std::is_pod<Args> ...>::value,
                  "All elements of the template type parameter pack in function pl::asprintf must be pod.");

    const auto bytesToWrite
        = static_cast<std::size_t>(std::snprintf(nullptr, 0U, fmtStr, args ...));

    auto retVal = std::make_unique<char[]>(bytesToWrite);

    if (bytesToWrite == 0U) {
        return std::make_unique<char[]>(1);
    }

    if (std::snprintf(retVal.get(), bytesToWrite, fmtStr, args ...) < 0) {
        throw AsprintfFailureException {
            "pl::asprintf failed!"
        };
    }

    return retVal;
}

/*!
 * \brief Allocates a new string that is filled in a printf-style.
 * \param fmtStr The printf-style format string. May not be nullptr!
 * \param args The arguments that match with the format specifiers in 'fmtStr'.
 * \return The string
 * \note If there are no characters to write the string returned
 *       will be an empty string.
 * \warning Be careful not to use incorrect format specifiers or an incorrect
 *          amount of arguments for the printf-style string.
 * \throws pl::AsprinfFailureException if an error occurred.
**/
template <typename ...Args>
PL_NODISCARD inline std::string asprintfStr(PL_IN PL_FMT_STR(const char *)fmtStr,
                                            const Args &...args)
{
    static_assert(pl::meta::All<std::is_pod<Args> ...>::value,
                  "All elements of the template type parameter pack in function pl::asprintf must be pod.");

    const auto bytesToWrite
        = static_cast<std::size_t>(std::snprintf(nullptr, 0U, fmtStr, args ...));

    if (bytesToWrite == 0U) {
        return std::string{ };
    }

    std::string retVal(bytesToWrite, '\0');

    if (std::snprintf(&retVal[0], bytesToWrite, fmtStr, args ...) < 0) {
        throw AsprintfFailureException{
            "pl::asprintf failed!"
        };
    }

    return retVal;
}
} // namespace pl
#endif // INCG_PL_ASPRINTF_HPP
