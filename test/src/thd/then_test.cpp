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
#endif                                      // PL_COMPILER == PL_COMPILER_GCC
#include "../../../include/pl/thd/then.hpp" // pl::thd::then
#include <future>  // std::async, std::launch::async, std::future
#include <string>  // std::string
#include <utility> // std::move

TEST_CASE("then_test")
{
    std::future<int> fut1{pl::thd::then(
        pl::thd::then(
            std::async(
                std::launch::async, [](int i) { return i * 2; }, 3),
            [](int j) { return j + 2; }),
        [](int k) { return k / 2; })};

    CHECK(fut1.get() == 4);

    std::string string1{};
    std::string string2{};

    std::future<void> fut2{std::async(
        std::launch::async, [&string1] { string1 = "async task completed"; })};

    std::future<void> fut3{pl::thd::then(
        std::move(fut2), [&string2] { string2 = "continuation completed"; })};

    fut3.wait();

    CHECK(string1 == "async task completed");
    CHECK(string2 == "continuation completed");
}
