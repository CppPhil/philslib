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

#include "../include/cheshire_cat_impl_type.hpp"
#include <cstddef> // std::nullptr_t
#include <new>     // operator new, operator delete
#include <utility> // std::swap

namespace pl {
namespace test {
cheshire_cat_impl_type::cheshire_cat_impl_type() : cheshire_cat_impl_type{0} {}
cheshire_cat_impl_type::cheshire_cat_impl_type(int val) : m_p{new int{val}} {}
cheshire_cat_impl_type::cheshire_cat_impl_type(std::initializer_list<int> il)
    : m_p{new int{*(il.begin())}}
{
}

cheshire_cat_impl_type::cheshire_cat_impl_type(
    const cheshire_cat_impl_type& other)
    : cheshire_cat_impl_type{*(other.m_p)}
{
}

cheshire_cat_impl_type::cheshire_cat_impl_type(
    cheshire_cat_impl_type&& other) noexcept : m_p{other.m_p}
{
    other.m_p = nullptr;
}

cheshire_cat_impl_type& cheshire_cat_impl_type::operator=(
    const cheshire_cat_impl_type& other) noexcept
{
    *m_p = *(other.m_p);
    return *this;
}

cheshire_cat_impl_type& cheshire_cat_impl_type::operator=(
    cheshire_cat_impl_type&& other) noexcept
{
    swap(other);
    return *this;
}

cheshire_cat_impl_type::~cheshire_cat_impl_type() { delete m_p; }
int  cheshire_cat_impl_type::value() const noexcept { return *m_p; }
void cheshire_cat_impl_type::swap(cheshire_cat_impl_type& other) noexcept
{
    using std::swap;
    swap(m_p, other.m_p);
}

void swap(cheshire_cat_impl_type& a, cheshire_cat_impl_type& b) noexcept
{
    a.swap(b);
}
} // namespace test
} // namespace pl
