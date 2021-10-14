/* This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * For more information, please refer to <http://unlicense.org/>
 */

/*!
 * \file print_bytes_as_hex.hpp
 * \brief Exports the print_bytes_as_hex type.
 **/
#ifndef INCG_PL_PRINT_BYTES_AS_HEX_HPP
#define INCG_PL_PRINT_BYTES_AS_HEX_HPP
#include "annotations.hpp" // PL_IN, PL_INOUT
#include "byte.hpp"        // pl::byte
#include "except.hpp" // PL_THROW_IF_NULL, pl::null_pointer_exception, pl::invalid_size_exception
#include <cstddef>     // std::size_t
#include <cstdint>     // std::uint16_t
#include <iomanip>     // std::setw, std::setfill
#include <ios>         // std::uppercase, std::hex
#include <ostream>     // std::ostream
#include <string>      // std::string
#include <type_traits> // std::is_nothrow_move_assignable, ...
#include <utility>     // std::move

namespace pl {
/*!
 * \brief Type to print raw memory as hexadecimal digits.
 **/
class print_bytes_as_hex {
public:
    using this_type = print_bytes_as_hex;

    /*!
     * \brief Creates a print_bytes_as_hex object.
     * \param data_to_print Pointer to the beginning (0th byte) of the memory
     *                      to be printed hexadecimally.
     * \param count_bytes The size of the memory to be printed in bytes.
     * \param delim The delimiter to print between each byte.
     *              Defaults to a space. Another reasonable option would be
     *              to effectively have no delimiter by passing "".
     * \throws pl::null_pointer_exception if 'data_to_print' is nullptr.
     *         pl::invalid_size_exception if count_bytes is 0.
     **/
    print_bytes_as_hex(
        PL_IN const void* data_to_print,
        std::size_t       count_bytes,
        std::string       delim = " ");

    /*!
     * \brief Defaulted copy constructor to suppress 'has pointer data members
     *        but does not override copy constructor or copy assignment
     *        operator' warning from -Weffc++.
     **/
    print_bytes_as_hex(const this_type&) noexcept(
        std::is_nothrow_copy_constructible<std::string>::value);

    /*!
     * \brief Defaulted move constructor.
     **/
    print_bytes_as_hex(this_type&&) noexcept(
        std::is_nothrow_move_constructible<std::string>::value);

    /*!
     * \brief Defaulted copy assignment operator to suppress 'has pointer data
     *        members but does not override copy constructor or copy assignment
     *        operator' warning from -Weffc++.
     **/
    this_type& operator=(const this_type&) noexcept(
        std::is_nothrow_copy_assignable<std::string>::value);

    /*!
     * \brief Defaulted move assignment operator.
     **/
    this_type& operator=(this_type&&) noexcept(
        std::is_nothrow_move_assignable<std::string>::value);

    /*!
     * \brief Prints a print_bytes_as_hex object to an ostream printing the
     *        memory the print_bytes_as_hex object points to hexadecimally.
     * \param os The ostream to print to.
     * \param to_print The print_bytes_as_hex object to print.
     * \return A reference to 'os'.
     **/
    friend std::ostream& operator<<(
        PL_INOUT std::ostream& os,
        PL_IN const this_type& to_print);

private:
    const void* m_data_to_print; /*!< Pointer to the data to print */
    std::size_t m_count_bytes;   /*!< The size of the data in bytes */
    std::string m_delim;         /*!< The delimiter */
};

inline print_bytes_as_hex::print_bytes_as_hex(
    PL_IN const void* data_to_print,
    std::size_t       count_bytes,
    std::string       delim)
    : m_data_to_print{data_to_print}
    , m_count_bytes{count_bytes}
    , m_delim{std::move(delim)}
{
    PL_THROW_IF_NULL(m_data_to_print);

    if (m_count_bytes == 0U) {
        throw invalid_size_exception{
            "count_bytes in pl::print_bytes_as_hex constructor was 0."};
    }
}

inline print_bytes_as_hex::print_bytes_as_hex(const this_type&) noexcept(
    std::is_nothrow_copy_constructible<std::string>::value)
    = default;

inline print_bytes_as_hex::print_bytes_as_hex(this_type&&) noexcept(
    std::is_nothrow_move_constructible<std::string>::value)
    = default;

inline print_bytes_as_hex&
print_bytes_as_hex::operator=(const this_type&) noexcept(
    std::is_nothrow_copy_assignable<std::string>::value)
    = default;

inline print_bytes_as_hex& print_bytes_as_hex::operator=(this_type&&) noexcept(
    std::is_nothrow_move_assignable<std::string>::value)
    = default;

inline std::ostream& operator<<(
    PL_INOUT std::ostream& os,
    PL_IN const print_bytes_as_hex& to_print)
{
    static constexpr auto nibbles_per_byte = 2;
    static constexpr auto fill_char        = '0';

    // save the format flags.
    const auto flags = os.flags();

    try {
        os << std::uppercase << std::hex;

        auto* data_to_print
            = static_cast<const byte*>(to_print.m_data_to_print);

        for (std::size_t i{0U}; i < to_print.m_count_bytes; ++i) {
            os << std::setw(nibbles_per_byte) << std::setfill(fill_char)
               << static_cast<std::uint16_t>(data_to_print[i]);

            if (i < (to_print.m_count_bytes - 1U)) {
                os << to_print.m_delim;
            }
        }
    }
    catch (...) {
        // restore the format flags
        os.flags(flags);
        throw;
    }

    // restore the format flags
    os.flags(flags);
    return os;
}
} // namespace pl
#endif // INCG_PL_PRINT_BYTES_AS_HEX_HPP
