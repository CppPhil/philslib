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
#include "../../../include/pl/thd/thread_pool.hpp" // pl::thd::thread_pool
#include <cstddef>                                 // std::size_t
#include <future>                                  // std::future
#include <string>                                  // std::string
#include <thread> // std::thread::hardware_concurrency

namespace pl {
namespace test {
namespace {
int f1(int i) noexcept { return i * 2; }
void       f2() noexcept {}
class type {
public:
    double mem_fn1(double a) const noexcept { return a * 3.0; }
    void                  mem_fn2() const noexcept {}
};
} // anonymous namespace
} // namespace test
} // namespace pl

TEST_CASE("thread_pool_test")
{
    static constexpr std::size_t no_threads{0U};
    static constexpr std::size_t two_threads{2U};

    const unsigned hw_concurrency{std::thread::hardware_concurrency()};

    REQUIRE(hw_concurrency != 0U);

    pl::thd::thread_pool empty_thread_pool{no_threads};
    pl::thd::thread_pool two_threads_thread_pool{two_threads};
    pl::thd::thread_pool hw_concurrency_thread_pool{hw_concurrency};

    SUBCASE("thread_count_test")
    {
        CHECK(empty_thread_pool.thread_count() == no_threads);
        CHECK(two_threads_thread_pool.thread_count() == two_threads);
        CHECK(hw_concurrency_thread_pool.thread_count() == hw_concurrency);
    }

    SUBCASE("task_test")
    {
        pl::thd::thread_pool& tp{two_threads_thread_pool};

        std::future<int>    fut1{tp.add_task(&pl::test::f1, 5)};
        std::future<void>   fut2{tp.add_task(&pl::test::f2)};
        std::future<double> fut3{
            tp.add_task(&pl::test::type::mem_fn1, pl::test::type{}, 5.0)};
        std::future<void> fut4{
            tp.add_task(&pl::test::type::mem_fn2, pl::test::type{})};
        std::future<std::string> fut5{tp.add_task(
            [](const char* str) { return std::string{"text "} + str; },
            "test")};
        std::future<void> fut6{tp.add_task([] {})};

        CHECK(fut1.get() == 10);
        fut2.wait();
        CHECK(fut3.get() == doctest::Approx{15.0});
        fut4.wait();
        CHECK(fut5.get() == "text test");
        fut6.wait();
    }
}
