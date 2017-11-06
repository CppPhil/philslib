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
#include <cstddef> // std::size_t
#include <array> // std::array
#include <vector> // std::vector
#include <deque> // std::deque
#include <list> // std::list
#include <queue> // std::queue
#include <string> // std::string
#include "../../../include/pl/cont/back.hpp" // pl::cont::back

TEST_CASE("std_array_back_test")
{
    static constexpr std::size_t size{ 5U };
    const std::array<int, size> array{ { 1, 2, 3, 4, 5 } };
    CHECK(pl::cont::back(array) == 5);
}

TEST_CASE("std_vector_back_test")
{
    const std::vector<int> v{ 1, 2, 3 };
    CHECK(pl::cont::back(v) == 3);
}

TEST_CASE("std_deque_back_test")
{
    const std::deque<int> deque{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    CHECK(pl::cont::back(deque) == 9);
}

TEST_CASE("std_list_back_test")
{
    const std::list<int> list{ 1, 2, 3, 4, 5 };
    CHECK(pl::cont::back(list) == 5);
}

TEST_CASE("c_array_back_test")
{
    const int cArray[] = { 1, 2, 3, 4, 5, 6, 7 };
    const char cString[] = "Text";
    CHECK(pl::cont::back(cArray)  == 7);
    CHECK(pl::cont::back(cString) == '\0');
}

TEST_CASE("std_queue_back_test")
{
    std::queue<int> queue{ };
    queue.push(1);
    queue.push(2);
    queue.push(3);
    CHECK(pl::cont::back(queue) == 3);
}

TEST_CASE("std_string_back_test")
{
    const std::string string{ "Hello World!" };
    CHECK(pl::cont::back(string) == '!');
}
