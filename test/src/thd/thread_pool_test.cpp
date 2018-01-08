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
#include "../../../include/pl/thd/thread_pool.hpp" // pl::thd::ThreadPool
#include <cstddef> // std::size_t
#include <string> // std::string
#include <thread> // std::thread::hardware_concurrency
#include <future> // std::future

namespace pl
{
namespace test
{
namespace
{
int f1(int i) noexcept
{
    return i * 2;
}

void f2() noexcept
{
}

class Type
{
public:
    double memFn1(double a) const noexcept
    {
        return a * 3.0;
    }

    void memFn2() const noexcept
    {
    }
};
} // anonymous namespace
} // namespace test
} // namespace pl

TEST_CASE("thread_pool_test")
{
    static constexpr std::size_t noThreads{ 0U };
    static constexpr std::size_t twoThreads{ 2U };

    const unsigned hwConcurrency{ std::thread::hardware_concurrency() };

    REQUIRE(hwConcurrency != 0U);

    pl::thd::ThreadPool emptyThreadPool{ noThreads };
    pl::thd::ThreadPool twoThreadsThreadPool{ twoThreads };
    pl::thd::ThreadPool hwConcurrencyThreadPool{ hwConcurrency };

    SUBCASE("thread_count_test") {
        CHECK(emptyThreadPool.getThreadCount() == noThreads);
        CHECK(twoThreadsThreadPool.getThreadCount() == twoThreads);
        CHECK(hwConcurrencyThreadPool.getThreadCount() == hwConcurrency);
    }

    SUBCASE("task_test") {
        pl::thd::ThreadPool &tp{ twoThreadsThreadPool };

        std::future<int> fut1{ tp.addTask(&pl::test::f1, 5) };
        std::future<void> fut2{ tp.addTask(&pl::test::f2) };
        std::future<double> fut3{ tp.addTask(
            &pl::test::Type::memFn1, pl::test::Type{ }, 5.0)
        };
        std::future<void> fut4{ tp.addTask(
            &pl::test::Type::memFn2, pl::test::Type{ })
        };
        std::future<std::string> fut5{ tp.addTask(
            [](const char *str) {
                return std::string{ "text " } + str;
            },
            "test")
        };
        std::future<void> fut6{ tp.addTask([]{ }) };

        CHECK(fut1.get() == 10);
        fut2.wait();
        CHECK(fut3.get() == doctest::Approx{ 15.0 });
        fut4.wait();
        CHECK(fut5.get() == "text test");
        fut6.wait();
    }
}
