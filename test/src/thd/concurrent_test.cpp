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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-noreturn"
#endif // PL_COMPILER == PL_COMPILER_GCC
#include "../../doctest.h"
#if PL_COMPILER == PL_COMPILER_GCC
#pragma GCC diagnostic pop
#endif // PL_COMPILER == PL_COMPILER_GCC
#include "../../../include/pl/thd/concurrent.hpp" // pl::thd::Concurrent
#include <future>                                 // std::future
#include <stdexcept>                              // std::logic_error
#include <vector>                                 // std::vector

TEST_CASE("concurrent_test")
{
    pl::thd::Concurrent<std::vector<int>> concurrent{std::vector<int>{}};

    std::future<std::vector<int>::size_type> fut1{
        concurrent([](std::vector<int>& v) {
            v.push_back(1);
            return v.size();
        })};

    std::future<int> fut2{concurrent([](std::vector<int>& v) {
        v.push_back(2);
        return v.front();
    })};

    std::future<std::vector<int>::size_type> fut3{
        concurrent(&std::vector<int>::size)};

    std::future<void> fut4{concurrent(
        [](std::vector<int>&) { throw std::logic_error{"test error"}; })};

    CHECK(fut1.get() == 1U);
    CHECK(fut2.get() == 1);
    CHECK(fut3.get() == 2U);
    CHECK_THROWS_AS(fut4.get(), std::logic_error);
}
