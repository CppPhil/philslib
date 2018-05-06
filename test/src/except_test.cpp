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
#endif                                  // PL_COMPILER == PL_COMPILER_GCC
#include "../../include/pl/except.hpp"  // PL_DEFINE_EXCEPTION_TYPE, PL_THROW_WITH_SOURCE_INFO, PL_THROW_IF_NULL, PL_NOT_YET_IMPLEMENTED
#include "../include/static_assert.hpp" // PL_TEST_STATIC_ASSERT
#include <cstddef>                      // std::nullptr_t
#include <cstdint>                      // std::uintptr_t
#include <cstring>                      // std::strcmp, std::strstr
#include <memory>                       // std::unique_ptr, std::make_unique
#include <stdexcept>                    // std::runtime_error
#include <string> // std::string, std::literals::string_literals::operator""s
#include <type_traits> // std::is_base_of

namespace pl {
namespace test {
namespace {
PL_DEFINE_EXCEPTION_TYPE(TestException, std::runtime_error);

[[noreturn]] void throwWithSourceInfo(const char* message)
{
    PL_THROW_WITH_SOURCE_INFO(::pl::test::TestException, message);
}

[[noreturn]] void notYetImplemented() { PL_NOT_YET_IMPLEMENTED(); }
} // anonymous namespace
} // namespace test
} // namespace pl

TEST_CASE("define_exception_type_test")
{
    using namespace std::literals::string_literals;

    PL_TEST_STATIC_ASSERT(
        std::is_base_of<std::runtime_error, pl::test::TestException>::value);

    try {
        throw pl::test::TestException{"test1"};
    }
    catch (const pl::test::TestException& ex) {
        CHECK(std::strcmp(ex.what(), "test1") == 0);
    }

    try {
        throw pl::test::TestException{"test2"s};
    }
    catch (const pl::test::TestException& ex) {
        CHECK(ex.what() == "test2"s);
    }
}

TEST_CASE("throw_with_source_info_test")
{
    try {
        pl::test::throwWithSourceInfo("test1");
    }
    catch (const pl::test::TestException& ex) {
        const char* const msg{ex.what()};

        CHECK(std::strstr(msg, "test1") != nullptr);
        CHECK(std::strstr(msg, "except_test.cpp") != nullptr);
        CHECK(std::strstr(msg, "line: 53") != nullptr);
        CHECK(std::strstr(msg, "throwWithSourceInfo") != nullptr);
    }
}

#if PL_COMPILER == PL_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable : 4127) // conditional expression is constant
#endif                          // PL_COMPILER == PL_COMPILER_MSVC
TEST_CASE("throw_if_null_test")
{
    const void* const p1{nullptr};
    const void* const p2{
        reinterpret_cast<const void*>(static_cast<std::uintptr_t>(0xDEADC0DE))};
    const std::nullptr_t             null{nullptr};
    const std::unique_ptr<const int> up1{nullptr};
    const std::unique_ptr<const int> up2{std::make_unique<int>(3)};

    CHECK_THROWS_AS(PL_THROW_IF_NULL(p1), pl::NullPointerException);
    CHECK_NOTHROW(PL_THROW_IF_NULL(p2));
    CHECK_THROWS_AS(PL_THROW_IF_NULL(null), pl::NullPointerException);
    CHECK_THROWS_AS(PL_THROW_IF_NULL(up1), pl::NullPointerException);
    CHECK_NOTHROW(PL_THROW_IF_NULL(up2));

    try {
        int* p{nullptr};
        PL_THROW_IF_NULL(p);
    }
    catch (const pl::NullPointerException& ex) {
        CHECK(std::strstr(ex.what(), "p was null!") != nullptr);
    }
}
#if PL_COMPILER == PL_COMPILER_MSVC
#pragma warning(pop)
#endif // PL_COMPILER == PL_COMPILER_MSVC

TEST_CASE("not_yet_implemented_test")
{
    CHECK_THROWS_AS(
        pl::test::notYetImplemented(), pl::NotYetImplementedException);

    try {
        pl::test::notYetImplemented();
    }
    catch (const pl::NotYetImplementedException& ex) {
        const char* const msg{ex.what()};
        CHECK(
            std::strstr(msg, "function has not yet been implemented!")
            != nullptr);
        CHECK(std::strstr(msg, "notYetImplemented") != nullptr);
    }
}
