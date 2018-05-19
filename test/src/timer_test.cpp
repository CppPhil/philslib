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

#include "../../include/pl/compiler.hpp"
#if PL_COMPILER == PL_COMPILER_GCC
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-noreturn"
#endif // PL_COMPILER == PL_COMPILER_GCC
#include "../doctest.h"
#if PL_COMPILER == PL_COMPILER_GCC
#pragma GCC diagnostic pop
#endif                                // PL_COMPILER == PL_COMPILER_GCC
#include "../../include/pl/timer.hpp" // pl::timer
#include <chrono>                     // std::literals::chrono_literals::operator""ms, std::chrono::duration_cast, std::chrono::milliseconds
#include <thread>                     // std::this_thread::sleep_for

TEST_CASE("timer_test")
{
    namespace chrono = std::chrono;
    using namespace std::literals::chrono_literals;
    using Ms = chrono::milliseconds;

    pl::timer timer{};
    std::this_thread::sleep_for(100ms);
    CHECK(chrono::duration_cast<Ms>(timer.elapsed_time()) >= 100ms);

    timer.reset();
    std::this_thread::sleep_for(150ms);
    CHECK(chrono::duration_cast<Ms>(timer.elapsed_time()) >= 150ms);
}
