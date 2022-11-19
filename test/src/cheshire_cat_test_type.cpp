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

#include "../include/cheshire_cat_test_type.hpp" // pl::test::cheshire_cat_test_type
#include <ciso646>                               // and, not
#include <string>                                // std::string, std::stoull
#include <utility>                               // std::move, std::swap

#include <iostream>

namespace pl {
namespace test {
class cheshire_cat_test_type::implementation {
public:
  implementation(std::uint32_t p_a, std::string p_s) noexcept
    : a{p_a}, s{std::move(p_s)}
  {
  }

  std::uint32_t a;
  std::string   s;
};

cheshire_cat_test_type::cheshire_cat_test_type() noexcept
  : cheshire_cat_test_type{0U, "0"}
{
}

cheshire_cat_test_type::cheshire_cat_test_type(
  std::uint32_t   a,
  pl::string_view sv) noexcept
  : m_cc{pl::in_place_t{}, a, sv.to_string()}
{
}

cheshire_cat_test_type::cheshire_cat_test_type(const this_type&) = default;

cheshire_cat_test_type::cheshire_cat_test_type(this_type&&) noexcept = default;

cheshire_cat_test_type& cheshire_cat_test_type::operator=(const this_type&)
  = default;

cheshire_cat_test_type& cheshire_cat_test_type::operator=(
  this_type&&) noexcept = default;

cheshire_cat_test_type::~cheshire_cat_test_type() = default;

void cheshire_cat_test_type::swap(this_type& other) noexcept
{
  using std::swap;
  swap(m_cc->a, other.m_cc->a);
  swap(m_cc->s, other.m_cc->s);
}

std::uint32_t cheshire_cat_test_type::sum() const noexcept
{
  return m_cc->a + static_cast<std::uint32_t>(std::stoull(m_cc->s));
}

bool operator==(
  const cheshire_cat_test_type& a,
  const cheshire_cat_test_type& b) noexcept
{
  return (a.m_cc->a == b.m_cc->a) and (a.m_cc->s == b.m_cc->s);
}

void swap(cheshire_cat_test_type& a, cheshire_cat_test_type& b) noexcept
{
  a.swap(b);
}

bool operator!=(
  const cheshire_cat_test_type& a,
  const cheshire_cat_test_type& b) noexcept
{
  return not(a == b);
}
} // namespace test
} // namespace pl
