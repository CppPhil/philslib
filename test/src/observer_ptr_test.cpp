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
#include "../../include/pl/observer_ptr.hpp" // pl::observer_ptr
#include "../include/static_assert.hpp"      // PL_TEST_STATIC_ASSERT
#include <ciso646>                           // not
#include <cstring>                           // std::strcmp
#include <functional>                        // std::hash
#include <string>                            // std::string
#include <type_traits>                       // std::is_same

TEST_CASE("observer_ptr_test")
{
    int         i{0U};
    std::string s{"sample text"};

    pl::observer_ptr<void>        null_ptr{nullptr};
    pl::observer_ptr<int>         pointer{&i};
    pl::observer_ptr<std::string> s_ptr{&s};

    SUBCASE("nullptr_init")
    {
        const pl::observer_ptr<double> a{};
        const pl::observer_ptr<float>  b{nullptr};
        const pl::observer_ptr<int>    c{static_cast<int*>(nullptr)};

        CHECK(a == null_ptr);
        CHECK(b == null_ptr);
        CHECK(c == null_ptr);
        CHECK(a == nullptr);
        CHECK(b == nullptr);
        CHECK(c == nullptr);
    }

    SUBCASE("converting_ctor")
    {
        const pl::observer_ptr<void> ptr{pointer};
        CHECK(ptr == pointer);
    }

    SUBCASE("release")
    {
        CHECK(pointer.get() == &i);
        int* const int_ptr{pointer.release()};
        CHECK(int_ptr == &i);
        CHECK(int_ptr != pointer.get());
        CHECK(pointer == nullptr);
    }

    SUBCASE("reset")
    {
        pointer.reset();
        CHECK(pointer == nullptr);
        pointer.reset(&i);
        CHECK(pointer.get() == &i);
    }

    SUBCASE("swap_member")
    {
        pl::observer_ptr<int> local_pointer{nullptr};
        local_pointer.swap(pointer);

        CHECK(pointer == nullptr);
        CHECK(local_pointer.get() == &i);
    }

    SUBCASE("swap_non_member")
    {
        pl::observer_ptr<int> ptr{};
        ::pl::swap(ptr, pointer);

        CHECK(pointer == nullptr);
        CHECK(ptr.get() == &i);
    }

    SUBCASE("get")
    {
        CHECK(null_ptr.get() == nullptr);
        CHECK(pointer.get() == &i);
    }

    SUBCASE("operator_bool")
    {
        CHECK_UNARY_FALSE(static_cast<bool>(null_ptr));
        CHECK_UNARY(static_cast<bool>(pointer));
        CHECK_UNARY(not static_cast<bool>(null_ptr));
        CHECK_UNARY_FALSE(not static_cast<bool>(pointer));
    }

    SUBCASE("indirection_operator")
    {
        CHECK(*pointer == i);
        CHECK(std::strcmp((*s_ptr).data(), "sample text") == 0);
    }

    SUBCASE("member_pointer_operator") { CHECK(s_ptr->front() == 's'); }
    SUBCASE("conversion_operator")
    {
        CHECK(static_cast<std::string*>(s_ptr) == &s);
    }

    SUBCASE("maker")
    {
        const auto op = pl::make_observer(&s);
        CHECK(op == s_ptr);

        const auto op2 = pl::make_observer(static_cast<void*>(nullptr));
        CHECK(op2 == null_ptr);
        CHECK(nullptr == op2);
    }

    SUBCASE("hash")
    {
        const auto val1 = std::hash<std::string*>{}(&s);
        const auto val2 = std::hash<pl::observer_ptr<std::string>>{}(s_ptr);
        CHECK(val1 == val2);
    }

    SUBCASE("low_level_constness")
    {
        pl::observer_ptr<const int> const_observer_ptr{&i};

        PL_TEST_STATIC_ASSERT(
            std::is_same<decltype(const_observer_ptr.release()), const int*>::
                value);
        PL_TEST_STATIC_ASSERT(
            std::is_same<decltype(const_observer_ptr.get()), const int*>::
                value);
        PL_TEST_STATIC_ASSERT(
            std::is_same<decltype(*const_observer_ptr), const int&>::value);
        PL_TEST_STATIC_ASSERT(std::is_same<
                              decltype(const_observer_ptr.operator->()),
                              const int*>::value);
        PL_TEST_STATIC_ASSERT(
            std::is_same<
                decltype(const_observer_ptr.operator const int*()),
                const int*>::value);

        CHECK(const_observer_ptr.get() == &i);
        CHECK(const_observer_ptr == pointer);
    }
}

TEST_CASE("observer_ptr_constexpr_test")
{
    static constexpr pl::observer_ptr<int> op{nullptr};
    PL_TEST_STATIC_ASSERT(op.get() == nullptr);
    PL_TEST_STATIC_ASSERT(not op.operator bool());

    CHECK_UNARY(true);
}
