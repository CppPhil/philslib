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
#endif // PL_COMPILER == PL_COMPILER_GCC
#include "../../include/pl/algo/ranged_algorithms.hpp" // pl::algo::all_of
#include "../../include/pl/as_const.hpp"               // pl::asConst
#include "../../include/pl/byte.hpp"                   // pl::Byte
#include "../../include/pl/iterate_reversed.hpp"       // pl::iterateReversed
#include "../../include/pl/raw_memory_array.hpp"       // pl::RawMemoryArray
#include "../include/freeer.hpp"                       // pl::test::Freeer
#include <algorithm>                                   // std::all_of
#include <cstddef>                                     // std::size_t
#include <cstdlib>                                     // std::calloc
#include <iterator> // std::crbegin, std::crend
#include <memory>   // std::unique_ptr
#include <string>   // std::string, std::literals::string_literals::operator""s

TEST_CASE("raw_memory_array_test")
{
    using namespace std::literals::string_literals;

    using size_type = pl::RawMemoryArray<std::string>::size_type;

    static constexpr std::size_t strSiz{sizeof(std::string)};
    static constexpr std::size_t amtOfStrings{10U};
    static constexpr std::size_t byteCount{strSiz * amtOfStrings};

    std::unique_ptr<pl::Byte, pl::test::freeer> memoryHolder1{
        static_cast<pl::Byte*>(std::calloc(amtOfStrings, strSiz)),
        pl::test::freeer{}};
    void* const                     memory1{memoryHolder1.get()};
    pl::RawMemoryArray<std::string> ary1{memory1, byteCount};

    std::unique_ptr<pl::Byte, pl::test::freeer> memoryHolder2{
        static_cast<pl::Byte*>(std::calloc(amtOfStrings, strSiz)),
        pl::test::freeer{}};
    void* const                     memory2{memoryHolder2.get()};
    pl::RawMemoryArray<std::string> ary2{memory2, byteCount, "Text"s};

    pl::RawMemoryArray<std::string> empty{nullptr, 0U};

    SUBCASE("at")
    {
        const pl::RawMemoryArray<std::string>& r{ary2};

        REQUIRE(ary1.size() == ary2.size());

        for (size_type i{}; i < ary1.size(); ++i) {
            CHECK(ary1.at(i) != r.at(i));
        }

        for (size_type i{}; i < ary1.size(); ++i) {
            ary1.at(i) = r.at(i);
        }

        for (size_type i{}; i < ary1.size(); ++i) {
            CHECK(ary1.at(i) == r.at(i));
        }

        CHECK_THROWS_AS((void)ary1.at(ary1.size()), std::out_of_range);
        CHECK_THROWS_AS((void)r.at(r.size()), std::out_of_range);
        CHECK_THROWS_AS((void)empty.at(0U), std::out_of_range);
    }

    SUBCASE("front")
    {
        CHECK(pl::asConst(ary1).front() == ""s);
        CHECK(ary2.front() == "Text"s);
        ary1.front() = "Test"s;
        CHECK(pl::asConst(ary1).front() == "Test"s);
    }

    SUBCASE("back")
    {
        CHECK(pl::asConst(ary2).back() == "Text"s);
        ary2.back() = "Another text"s;
        CHECK(ary2.back() == "Another text"s);
    }

    SUBCASE("data")
    {
        CHECK(static_cast<void*>(ary1.data()) == memory1);
        CHECK(static_cast<void*>(ary2.data()) == memory2);
        CHECK(
            static_cast<const void*>(ary1.constData())
            == static_cast<const void*>(memory1));
        CHECK(
            static_cast<const void*>(ary2.constData())
            == static_cast<const void*>(memory2));
        CHECK(empty.data() == nullptr);
    }

    SUBCASE("iterate_forwards")
    {
        for (std::string& s : ary1) {
            CHECK_UNARY(s.empty());
            s = "Test"s;
        }

        CHECK_UNARY(pl::algo::all_of(ary1, [](const std::string& s) {
            return s == "Test"s;
        }));

        const pl::RawMemoryArray<std::string>& r{ary2};

        for (const std::string& s : r) {
            CHECK(s == "Text"s);
        }
    }

    SUBCASE("iterate_backwards")
    {
        for (std::string& s : pl::iterateReversed(ary2)) {
            CHECK(s == "Text"s);
            s = "Test"s;
        }

        CHECK_UNARY(
            std::all_of(
                std::crbegin(ary2), std::crend(ary2), [](const std::string& s) {
                    return s == "Test"s;
                }));

        for (const std::string& s : pl::iterateReversed(pl::asConst(ary1))) {
            CHECK_UNARY(s.empty());
        }
    }

    SUBCASE("empty")
    {
        CHECK_UNARY_FALSE(ary1.empty());
        CHECK_UNARY_FALSE(ary2.empty());
        CHECK_UNARY(empty.empty());
    }

    SUBCASE("size")
    {
        CHECK(ary1.size() == amtOfStrings);
        CHECK(ary2.size() == amtOfStrings);
        CHECK(empty.size() == 0U);
        CHECK(ary1.max_size() == amtOfStrings);
        CHECK(ary2.max_size() == amtOfStrings);
        CHECK(empty.max_size() == 0U);
    }

    SUBCASE("fill")
    {
        const auto& retVal = ary1.fill("sample text"s);
        CHECK(retVal == ary1);

        CHECK_UNARY(pl::algo::all_of(ary1, [](const std::string& s) {
            return s == "sample text"s;
        }));

        empty.assign("20");
        CHECK_UNARY(empty.empty());
    }

    SUBCASE("equality")
    {
        CHECK(ary1 != ary2);
        ary2.fill(""s);
        CHECK(ary1 == ary2);
        CHECK(ary1 != empty);
        CHECK(ary2 != empty);
    }

    SUBCASE("ordering")
    {
        CHECK(ary1 < ary2);
        CHECK(ary2 > ary1);
        CHECK(ary1 <= ary2);
        CHECK(ary2 >= ary1);
        CHECK(empty < ary1);
        CHECK(empty < ary2);

        ary1.fill("Text"s);
        CHECK(ary1 <= ary2);
        CHECK(ary1 >= ary2);
    }
}
