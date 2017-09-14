/*!
 * \file print_bytes_as_hex.hpp
 * \brief Exports the PrintBytesAsHex type.
**/
#ifndef INCG_PL_PRINT_BYTES_AS_HEX_HPP
#define INCG_PL_PRINT_BYTES_AS_HEX_HPP
#include "annotations.hpp" // PL_IN, PL_INOUT
#include "except.hpp" // PL_THROW_IF_NULL, pl::NullPointerException, pl::InvalidSizeException
#include <cstddef> // std::size_t
#include <iosfwd> // std::ostream
#include <string> // std::string

namespace pl
{
/*!
 * \brief Type to print raw memory as hexadecimal digits.
**/
class PrintBytesAsHex
{
public:
    using this_type = PrintBytesAsHex;

    /*!
     * \brief Creates a PrintBytesAsHex object.
     * \param dataToPrint Pointer to the beginning (0th byte) of the memory
     *                    to be printed hexadecimally.
     * \param countBytes The size of the memory to be printed in bytes.
     * \param delim The delimiter to print between each byte.
     *              Defaults to a space. Another reasonable option would be
     *              to effectively have no delimiter by passing "".
     * \throws pl::NullPointerException if 'dataToPrint' is nullptr.
     *         pl::InvalidSizeException if countBytes is 0.
    **/
    PrintBytesAsHex(PL_IN const void *dataToPrint, std::size_t countBytes,
                    std::string delim = " ");

    /*!
     * \brief Defaulted copy constructor to suppress 'has pointer data members
     *        but does not override copy constructor or copy assignment operator'
     *        warning from -Weffc++.
    **/
    PrintBytesAsHex(const this_type &);

    /*!
     * \brief Defaulted move constructor.
    **/
    PrintBytesAsHex(this_type &&);

    /*!
     * \brief Defaulted copy assignment operator to suppress 'has pointer data members
     *        but does not override copy constructor or copy assignment operator'
     *        warning from -Weffc++.
    **/
    this_type &operator=(const this_type &);

    /*!
     * \brief Defaulted move assignment operator.
    **/
    this_type &operator=(this_type &&);

    /*!
     * \brief Prints a PrintBytesAsHex object to an ostream printing the memory
     *        the PrintBytesAsHex object points to hexadecimally.
     * \param os The ostream to print to.
     * \param toPrint The PrintBytesAsHex object to print.
     * \return A reference to 'os'.
    **/
    friend std::ostream &operator<<(PL_INOUT std::ostream &os,
                                    PL_IN const this_type &toPrint);

private:
    const void *m_dataToPrint; /*!< Pointer to the data to print */
    std::size_t m_countBytes; /*!< The size of the data in bytes */
    std::string m_delim; /*!< The delimiter */
};
} // namespace pl
#endif // INCG_PL_PRINT_BYTES_AS_HEX_HPP
