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

#include "../../../include/pl/compiler.hpp"
#if PL_COMPILER == PL_COMPILER_GCC
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wmissing-noreturn"
#endif // PL_COMPILER == PL_COMPILER_GCC
#include "../../doctest.h"
#if PL_COMPILER == PL_COMPILER_GCC
#   pragma GCC diagnostic pop
#endif // PL_COMPILER == PL_COMPILER_GCC
#include "../../../include/pl/cont/empty.hpp" // pl::cont::empty
#include <cstddef> // std::size_t
#include <vector> // std::vector
#include <array> // std::array
#include <deque> // std::deque
#include <initializer_list> // std::initializer_list

TEST_CASE("empty_test")
{
    std::vector<int> vec1{ 1, 2, 3 };
    std::vector<double> vec2{ };

    static constexpr std::size_t arraySize{ 3U };
    constexpr std::array<int, arraySize> a{ { 1, 2, 3 } };

    std::deque<long long> deque{ 1LL };

    const int ary[]{ 1, 2, 3, 4, 5 };
    const int ary2[]{ 1 };

    const std::initializer_list<void *> il{ nullptr };

    const std::initializer_list<int> il2{ };

    SUBCASE("empty_tests") {
        vec1.clear();

        CHECK_UNARY(pl::cont::empty(vec1));
        CHECK_UNARY(pl::cont::empty(vec2));

        deque.clear();
        CHECK_UNARY(pl::cont::empty(deque));

        CHECK_UNARY(pl::cont::empty(il2));
    }

    SUBCASE("non_empty_tests") {
        CHECK_UNARY_FALSE(pl::cont::empty(vec1));

        vec2.push_back(1.0);
        CHECK_UNARY_FALSE(pl::cont::empty(vec2));

        CHECK_UNARY_FALSE(pl::cont::empty(a));

        CHECK_UNARY_FALSE(pl::cont::empty(deque));

        CHECK_UNARY_FALSE(pl::cont::empty(ary));
        CHECK_UNARY_FALSE(pl::cont::empty(ary2));

        CHECK_UNARY_FALSE(pl::cont::empty(il));
    }
}
