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

#ifndef INCG_PL_TEST_CHESHIRE_CAT_TEST_TYPE_HPP
#define INCG_PL_TEST_CHESHIRE_CAT_TEST_TYPE_HPP
#include "../../include/pl/cheshire_cat.hpp" // pl::cheshire_cat
#include "../../include/pl/string_view.hpp"  // pl::string_view
#include <cstdint>                           // std::uint32_t

namespace pl {
namespace test {
class cheshire_cat_test_type {
public:
    using this_type = cheshire_cat_test_type;

    cheshire_cat_test_type() noexcept;

    cheshire_cat_test_type(std::uint32_t a, pl::string_view sv) noexcept;

    cheshire_cat_test_type(const this_type&);

    cheshire_cat_test_type(this_type&&) noexcept;

    this_type& operator=(const this_type&);

    this_type& operator=(this_type&&) noexcept;

    ~cheshire_cat_test_type();

    void swap(this_type& other) noexcept;

    std::uint32_t sum() const noexcept;

    friend bool operator==(
        const cheshire_cat_test_type& a,
        const cheshire_cat_test_type& b) noexcept;

private:
    class implementation;

    pl::cheshire_cat<implementation, /* bytes */ 40U, /* alignment */ 8U> m_cc;
};

void swap(cheshire_cat_test_type& a, cheshire_cat_test_type& b) noexcept;

bool operator!=(
    const cheshire_cat_test_type& a,
    const cheshire_cat_test_type& b) noexcept;
} // namespace test
} // namespace pl
#endif // INCG_PL_TEST_CHESHIRE_CAT_TEST_TYPE_HPP
