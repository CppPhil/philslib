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
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wmissing-noreturn"
#endif // PL_COMPILER == PL_COMPILER_GCC
#include "../doctest.h"
#if PL_COMPILER == PL_COMPILER_GCC
#   pragma GCC diagnostic pop
#endif // PL_COMPILER == PL_COMPILER_GCC
#include "../include/static_assert.hpp" // PL_TEST_STATIC_ASSERT
#include "../../include/pl/raw_storage.hpp" // pl::RawStorage
#include <string> // std::string, std::literals::string_literals::operator""s
#include <type_traits> // std::is_same

namespace pl
{
namespace test
{
namespace
{
template <typename Ty>
class RawStorageDestroyer
{
public:
    using this_type = RawStorageDestroyer;

    explicit RawStorageDestroyer(pl::RawStorage<Ty> *ptr)
        : m_ptr{ ptr }
    {
    }

    RawStorageDestroyer(const this_type &) = default;

    RawStorageDestroyer(this_type &&) = default;

    this_type &operator=(const this_type &) = default;

    this_type &operator=(this_type &&) = default;

    ~RawStorageDestroyer()
    {
        m_ptr->destroy();
    }

private:
    pl::RawStorage<Ty> *m_ptr;
};

template <typename Ty>
auto makeRawStorageDestroyer(pl::RawStorage<Ty> *ptr)
{
    return RawStorageDestroyer<Ty>{ ptr };
}
} // anonymous namespace
} // namespace test
} // namespace pl

TEST_CASE("raw_storage_test")
{
    using namespace std::literals::string_literals;

    pl::RawStorage<std::string> rawStorage{ };
    rawStorage.construct("Text"s);
    auto rawStorageDestroyer = pl::test::makeRawStorageDestroyer(&rawStorage);

    SUBCASE("get_non_const") {
        PL_TEST_STATIC_ASSERT(
            std::is_same<decltype(rawStorage.get()), std::string &>::value);
        PL_TEST_STATIC_ASSERT(
            std::is_same<decltype(rawStorage.get().at(0U)), char &>::value);
        CHECK(rawStorage.get() == "Text"s);
        CHECK(rawStorage.get().at(0U) == 'T');
    }

    SUBCASE("get_const") {
        const pl::RawStorage<std::string> &r{ rawStorage };
        PL_TEST_STATIC_ASSERT(
            std::is_same<decltype(r.get()), const std::string &>::value);
        PL_TEST_STATIC_ASSERT(
            std::is_same<decltype(r.get().at(0U)), const char &>::value);
        CHECK(r.get() == "Text"s);
        CHECK(r.get().at(0U) == 'T');
    }

    SUBCASE("construct_parentheses") {
        using size_type = std::string::size_type;

        rawStorage.destroy();
        rawStorage.constructParentheses(static_cast<size_type>(7U), 'Y');

        CHECK(rawStorage.get() == "YYYYYYY"s);
    }

    SUBCASE("construct") {
        rawStorage.destroy();
        rawStorage.construct("Sample text");

        CHECK(rawStorage.get() == "Sample text"s);
    }
}
