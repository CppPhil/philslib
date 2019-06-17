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
#endif                                       // PL_COMPILER == PL_COMPILER_GCC
#include "../../include/pl/concept_poly.hpp" // pl::concept_poly
#include <cstddef>                           // std::size_t
#include <memory>  // std::unique_ptr, std::make_unique
#include <ostream> // std::ostream
#include <sstream> // std::ostringstream
#include <string>  // std::string, std::literals::string_literals::operator""s
#include <utility> // std::move

namespace pl {
namespace test {
namespace {
class implementation {
public:
    explicit implementation(std::string string) : m_string{std::move(string)} {}
    friend std::ostream&
    draw_it(const implementation& impl, std::ostream& os, std::size_t position);

private:
    std::string m_string;
};

std::ostream&
draw_it(const implementation& impl, std::ostream& os, std::size_t position)
{
    return os << std::string(position, ' ') << impl.m_string;
}

std::ostream& draw_it(int integer, std::ostream& os, std::size_t position)
{
    return os << std::string(position, '?') << ' ' << integer;
}

class draw_concept {
public:
    draw_concept()                                      = default;
    virtual ~draw_concept()                             = default;
    virtual std::unique_ptr<draw_concept> clone() const = 0;
    virtual std::ostream& draw(std::ostream& os, std::size_t position)
        const                         = 0;
    draw_concept(const draw_concept&) = delete;
    draw_concept& operator=(const draw_concept&) = delete;
};

template<typename Impl>
class draw_model : public draw_concept {
public:
    explicit draw_model(Impl impl) : draw_concept{}, m_impl{std::move(impl)} {}
    virtual std::unique_ptr<draw_concept> clone() const override
    {
        return std::make_unique<draw_model>(m_impl);
    }

    virtual std::ostream& draw(std::ostream& os, std::size_t position)
        const override
    {
        return ::pl::test::draw_it(m_impl, os, position);
    }

private:
    Impl m_impl;
};
} // anonymous namespace
} // namespace test
} // namespace pl

TEST_CASE("concept_poly_test")
{
    using namespace std::literals::string_literals;

    using drawable
        = pl::concept_poly<pl::test::draw_concept, pl::test::draw_model>;

    std::ostringstream oss{};

    drawable a{pl::test::implementation{"Test"s}};
    drawable b{5};

    REQUIRE_UNARY(static_cast<bool>(a));
    REQUIRE_UNARY(static_cast<bool>(b));

    SUBCASE("draw_test_a")
    {
        a->draw(oss, 3U);
        CHECK(oss.str() == "   Test"s);
    }

    SUBCASE("draw_test_b")
    {
        b->draw(oss, 2U);
        CHECK(oss.str() == "?? 5"s);
    }

    SUBCASE("copy_constructor")
    {
        drawable c{b};
        REQUIRE_UNARY(static_cast<bool>(c));
        REQUIRE_UNARY(static_cast<bool>(b));

        c->draw(oss, 2U);
        CHECK(oss.str() == "?? 5"s);
    }

    SUBCASE("move_constructor")
    {
        drawable c{drawable{7}};
        REQUIRE_UNARY(static_cast<bool>(c));
        c->draw(oss, 2U);
        CHECK(oss.str() == "?? 7"s);

        oss.str(std::string{});

        drawable d{std::move(c)};
        REQUIRE_UNARY(static_cast<bool>(d));
        CHECK_UNARY_FALSE(static_cast<bool>(c));
        d->draw(oss, 5U);
        CHECK(oss.str() == "????? 7"s);
    }

    SUBCASE("copy_assignment")
    {
        drawable c{3};
        REQUIRE_UNARY(static_cast<bool>(c));
        c = a;
        REQUIRE_UNARY(static_cast<bool>(c));
        REQUIRE_UNARY(static_cast<bool>(a));
        c->draw(oss, 1U);
        CHECK(oss.str() == " Test"s);
    }

    SUBCASE("move_assignment")
    {
        drawable c{a};
        REQUIRE_UNARY(static_cast<bool>(c));
        c = drawable{25};
        REQUIRE_UNARY(static_cast<bool>(c));
        c->draw(oss, 4U);
        CHECK(oss.str() == "???? 25"s);

        oss.str(std::string{});

        drawable d{1};
        REQUIRE_UNARY(static_cast<bool>(d));
        d = std::move(c);
        REQUIRE_UNARY(static_cast<bool>(d));
        REQUIRE_UNARY_FALSE(static_cast<bool>(c));
        d->draw(oss, 1U);
        CHECK(oss.str() == "? 25"s);
    }

    SUBCASE("swap_test")
    {
        swap(a, b);
        REQUIRE_UNARY(static_cast<bool>(a));
        REQUIRE_UNARY(static_cast<bool>(b));

        a->draw(oss, 2U);
        CHECK(oss.str() == "?? 5"s);

        oss.str(std::string{});

        b->draw(oss, 7U);
        CHECK(oss.str() == "       Test"s);
    }

    SUBCASE("get_test")
    {
        pl::test::draw_concept* p1{a.get()};
        pl::test::draw_concept* p2{b.get()};

        p1->draw(oss, 1U);
        CHECK(oss.str() == " Test"s);

        oss.str(std::string{});

        p2->draw(oss, 3U);
        CHECK(oss.str() == "??? 5");
    }

    SUBCASE("operator*")
    {
        pl::test::draw_concept& r1{*a};
        pl::test::draw_concept& r2{*b};

        r1.draw(oss, 5U);
        CHECK(oss.str() == "     Test"s);

        oss.str(std::string{});

        r2.draw(oss, 1U);
        CHECK(oss.str() == "? 5");
    }
}
