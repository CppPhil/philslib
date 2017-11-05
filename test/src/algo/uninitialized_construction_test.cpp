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
#include "../../include/freeer.hpp" // pl::test::Freer
#include "../../../include/pl/algo/uninitialized_default_construct.hpp"
#include "../../../include/pl/algo/uninitialized_default_construct_n.hpp"
#include "../../../include/pl/algo/uninitialized_move.hpp"
#include "../../../include/pl/algo/uninitialized_move_n.hpp"
#include "../../../include/pl/algo/uninitialized_value_construct.hpp"
#include "../../../include/pl/algo/uninitialized_value_construct_n.hpp"
#include "../../../include/pl/algo/destroy.hpp" // pl::algo::destroy
#include <cstddef> // std::size_t
#include <cstdlib> // std::malloc
#include <memory> // std::unique_ptr
#include <iterator> // std::begin, std::end
#include <array> // std::array

namespace pl
{
namespace test
{
namespace
{
class TestType
{
public:
    TestType() noexcept
        : m_constructed{ true },
          m_wasMoveConstructed{ false }
    {
    }

    TestType(const TestType &) = default;

    TestType &operator=(const TestType &) = default;

    TestType(TestType &&) noexcept
        : m_constructed{ true },
          m_wasMoveConstructed{ true }
    {
    }

    bool isConstructed() const noexcept
    {
        return m_constructed;
    }

    bool wasMoveConstructed() const noexcept
    {
        return m_wasMoveConstructed;
    }

private:
    bool m_constructed;
    bool m_wasMoveConstructed;
};
} // anonymous namespace
} // namespace test
} // namespace pl

TEST_CASE("unitialized_construction")
{
    static constexpr std::size_t size{ 15U };

    std::unique_ptr<unsigned char, pl::test::Freeer> up{
        static_cast<unsigned char *>(
            std::malloc(size * sizeof(pl::test::TestType))),
        pl::test::Freeer{ }
    };

    auto *begin = reinterpret_cast<pl::test::TestType *>(up.get());
    auto *end   = begin + size;

    SUBCASE("default_construct") {
        pl::algo::uninitialized_default_construct(begin, end);

        for (auto *it = begin; it != end; ++it) {
            CHECK_UNARY(it->isConstructed());
            CHECK_UNARY_FALSE(it->wasMoveConstructed());
        }

        pl::algo::destroy(begin, end);
    }

    SUBCASE("default_construct_n") {
        const auto retVal
            = pl::algo::uninitialized_default_construct_n(begin, size);

        for (auto *it = begin; it != end; ++it) {
            CHECK_UNARY(it->isConstructed());
            CHECK_UNARY_FALSE(it->wasMoveConstructed());
        }

        CHECK(retVal == end);

        pl::algo::destroy(begin, end);
    }

    SUBCASE("move") {
        std::array<pl::test::TestType, size> array{ };
        array.fill(pl::test::TestType{ });

        const auto retVal = pl::algo::uninitialized_move(
            std::begin(array),
            std::end(array),
            begin);

        for (auto *it = begin; it != end; ++it) {
            CHECK_UNARY(it->isConstructed());
            CHECK_UNARY(it->wasMoveConstructed());
        }

        CHECK(retVal == end);

        pl::algo::destroy(begin, end);
    }

    SUBCASE("move_n") {
        std::array<pl::test::TestType, size> array{ };
        array.fill(pl::test::TestType{ });

        const auto pair = pl::algo::uninitialized_move_n(
            std::begin(array),
            size,
            begin);

        for (auto *it = begin; it != end; ++it) {
            CHECK_UNARY(it->isConstructed());
            CHECK_UNARY(it->wasMoveConstructed());
        }

        CHECK(pair.first  == std::end(array));
        CHECK(pair.second == end);

        pl::algo::destroy(begin, end);
    }

    SUBCASE("value_construct") {
        pl::algo::uninitialized_value_construct(begin, end);

        for (auto *it = begin; it != end; ++it) {
            CHECK_UNARY(it->isConstructed());
            CHECK_UNARY_FALSE(it->wasMoveConstructed());
        }

        pl::algo::destroy(begin, end);
    }

    SUBCASE("value_construct_n") {
        const auto retVal
            = pl::algo::uninitialized_value_construct_n(begin, size);

        for (auto *it = begin; it != end; ++it) {
            CHECK_UNARY(it->isConstructed());
            CHECK_UNARY_FALSE(it->wasMoveConstructed());
        }

        CHECK(retVal == end);

        pl::algo::destroy(begin, end);
    }
}
