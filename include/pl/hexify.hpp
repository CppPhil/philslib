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
 * \file hexify.hpp
 * \brief Exports the hexify function.
 **/
#ifndef INCG_PL_HEXIFY_HPP
#define INCG_PL_HEXIFY_HPP
#include "print_bytes_as_hex.hpp" // pl::print_bytes_as_hex
#include <sstream>                // std::ostringstream
#include <utility>                // std::move

namespace pl {
/*!
 * \brief Converts binary data to a hex encoded string.
 * \param data The base address of the memory region containing binary data.
 * \param byte_count The size of the memory region pointed to by `data` in
 *        bytes.
 * \param delimiter The delimiter to use to delimit each pair of hexits.
 * \return The resulting hex encoded string.
 **/
inline std::string
hexify(PL_IN const void* data, std::size_t byte_count, std::string delimiter)
{
    std::ostringstream oss{};
    oss << pl::print_bytes_as_hex{data, byte_count, std::move(delimiter)};
    return oss.str();
}
} // namespace pl
#endif // INCG_PL_HEXIFY_HPP
