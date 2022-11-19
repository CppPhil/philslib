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
#include "../../../include/pl/algo/destroy.hpp" // pl::algo::destroy
#include "../../../include/pl/algo/uninitialized_default_construct.hpp"
#include "../../../include/pl/algo/uninitialized_default_construct_n.hpp"
#include "../../../include/pl/algo/uninitialized_move.hpp"
#include "../../../include/pl/algo/uninitialized_move_n.hpp"
#include "../../../include/pl/algo/uninitialized_value_construct.hpp"
#include "../../../include/pl/algo/uninitialized_value_construct_n.hpp"
#include "../../include/freeer.hpp" // pl::test::freeer
#include <array>                    // std::array
#include <cstddef>                  // std::size_t
#include <cstdlib>                  // std::malloc
#include <iterator>                 // std::begin, std::end
#include <memory>                   // std::unique_ptr

namespace pl {
namespace test {
namespace {
class test_type {
public:
  test_type() noexcept : m_constructed{true}, m_was_move_constructed{false}
  {
  }
  test_type(const test_type&) = default;

  test_type& operator=(const test_type&) = default;

  test_type(test_type&&) noexcept
    : m_constructed{true}, m_was_move_constructed{true}
  {
  }

  bool is_constructed() const noexcept
  {
    return m_constructed;
  }
  bool was_move_constructed() const noexcept
  {
    return m_was_move_constructed;
  }

private:
  bool m_constructed;
  bool m_was_move_constructed;
};
} // anonymous namespace
} // namespace test
} // namespace pl

TEST_CASE("unitialized_construction")
{
  static constexpr std::size_t size{15U};

  std::unique_ptr<unsigned char, pl::test::freeer> up{
    static_cast<unsigned char*>(
      std::malloc(size * sizeof(pl::test::test_type))),
    pl::test::freeer{}};

  auto* begin = reinterpret_cast<pl::test::test_type*>(up.get());
  auto* end   = begin + size;

  SUBCASE("default_construct")
  {
    pl::algo::uninitialized_default_construct(begin, end);

    for (auto* it = begin; it != end; ++it) {
      CHECK_UNARY(it->is_constructed());
      CHECK_UNARY_FALSE(it->was_move_constructed());
    }

    pl::algo::destroy(begin, end);
  }

  SUBCASE("default_construct_n")
  {
    const auto ret_val
      = pl::algo::uninitialized_default_construct_n(begin, size);

    for (auto* it = begin; it != end; ++it) {
      CHECK_UNARY(it->is_constructed());
      CHECK_UNARY_FALSE(it->was_move_constructed());
    }

    CHECK(ret_val == end);

    pl::algo::destroy(begin, end);
  }

  SUBCASE("move")
  {
    std::array<pl::test::test_type, size> array{};
    array.fill(pl::test::test_type{});

    const auto ret_val
      = pl::algo::uninitialized_move(std::begin(array), std::end(array), begin);

    for (auto* it = begin; it != end; ++it) {
      CHECK_UNARY(it->is_constructed());
      CHECK_UNARY(it->was_move_constructed());
    }

    CHECK(ret_val == end);

    pl::algo::destroy(begin, end);
  }

  SUBCASE("move_n")
  {
    std::array<pl::test::test_type, size> array{};
    array.fill(pl::test::test_type{});

    const auto pair
      = pl::algo::uninitialized_move_n(std::begin(array), size, begin);

    for (auto* it = begin; it != end; ++it) {
      CHECK_UNARY(it->is_constructed());
      CHECK_UNARY(it->was_move_constructed());
    }

    CHECK(pair.first == std::end(array));
    CHECK(pair.second == end);

    pl::algo::destroy(begin, end);
  }

  SUBCASE("value_construct")
  {
    pl::algo::uninitialized_value_construct(begin, end);

    for (auto* it = begin; it != end; ++it) {
      CHECK_UNARY(it->is_constructed());
      CHECK_UNARY_FALSE(it->was_move_constructed());
    }

    pl::algo::destroy(begin, end);
  }

  SUBCASE("value_construct_n")
  {
    const auto ret_val = pl::algo::uninitialized_value_construct_n(begin, size);

    for (auto* it = begin; it != end; ++it) {
      CHECK_UNARY(it->is_constructed());
      CHECK_UNARY_FALSE(it->was_move_constructed());
    }

    CHECK(ret_val == end);

    pl::algo::destroy(begin, end);
  }
}
