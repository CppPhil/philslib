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
#endif // CR_COMPILER == CR_COMPILER_GCC
#include "../../doctest.h"
#if PL_COMPILER == PL_COMPILER_GCC
#   pragma GCC diagnostic pop
#endif // CR_COMPILER == CR_COMPILER_GCC
#include "../../../include/pl/thd/thread_safe_queue.hpp" // pl::thd::ThreadSafeQueue
#include <future> // std::future, std::async, std::launch::async

TEST_CASE("thread_safe_queue_test")
{
    pl::thd::ThreadSafeQueue<int> q{ };

    CHECK_UNARY(q.empty());
    CHECK(q.size() == 0U);

    static constexpr int i{ 5 };

    q.push(1);
    q.push(i);

    CHECK_UNARY_FALSE(q.empty());
    CHECK(q.size() == 2U);

    SUBCASE("add_elements") {
        q.push(1);
        q.push(i);

        CHECK_UNARY_FALSE(q.empty());
        CHECK(q.size() == 4U);
    }

    SUBCASE("remove_elements") {
        int val{ };

        val = q.pop();

        CHECK(val == 1);
        CHECK_UNARY_FALSE(q.empty());
        CHECK(q.size() == 1U);

        val = q.pop();

        CHECK(val == i);
        CHECK_UNARY(q.empty());
        CHECK(q.size() == 0U);
    }

    SUBCASE("multithreaded") {
        std::future<int> fut{ std::async(
            std::launch::async,
            [&q] {
                q.pop();
                q.pop();
                return q.pop();
            })
        };

        q.push(20);
        CHECK(fut.get() == 20);

        CHECK_UNARY(q.empty());
        CHECK(q.size() == 0U);
    }
}
