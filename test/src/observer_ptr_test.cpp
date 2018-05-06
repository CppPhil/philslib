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
#include "../../include/pl/observer_ptr.hpp" // pl::ObserverPtr
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

    pl::ObserverPtr<void>        nullPtr{nullptr};
    pl::ObserverPtr<int>         pointer{&i};
    pl::ObserverPtr<std::string> sPtr{&s};

    SUBCASE("nullptr_init")
    {
        const pl::ObserverPtr<double> a{};
        const pl::ObserverPtr<float>  b{nullptr};
        const pl::ObserverPtr<int>    c{static_cast<int*>(nullptr)};

        CHECK(a == nullPtr);
        CHECK(b == nullPtr);
        CHECK(c == nullPtr);
        CHECK(a == nullptr);
        CHECK(b == nullptr);
        CHECK(c == nullptr);
    }

    SUBCASE("converting_ctor")
    {
        const pl::ObserverPtr<void> ptr{pointer};
        CHECK(ptr == pointer);
    }

    SUBCASE("release")
    {
        CHECK(pointer.get() == &i);
        int* const intPtr{pointer.release()};
        CHECK(intPtr == &i);
        CHECK(intPtr != pointer.get());
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
        pl::ObserverPtr<int> localPointer{nullptr};
        localPointer.swap(pointer);

        CHECK(pointer == nullptr);
        CHECK(localPointer.get() == &i);
    }

    SUBCASE("swap_non_member")
    {
        pl::ObserverPtr<int> ptr{};
        ::pl::swap(ptr, pointer);

        CHECK(pointer == nullptr);
        CHECK(ptr.get() == &i);
    }

    SUBCASE("get")
    {
        CHECK(nullPtr.get() == nullptr);
        CHECK(pointer.get() == &i);
    }

    SUBCASE("operator_bool")
    {
        CHECK_UNARY_FALSE(static_cast<bool>(nullPtr));
        CHECK_UNARY(static_cast<bool>(pointer));
        CHECK_UNARY(not static_cast<bool>(nullPtr));
        CHECK_UNARY_FALSE(not static_cast<bool>(pointer));
    }

    SUBCASE("indirection_operator")
    {
        CHECK(*pointer == i);
        CHECK(std::strcmp((*sPtr).data(), "sample text") == 0);
    }

    SUBCASE("member_pointer_operator") { CHECK(sPtr->front() == 's'); }
    SUBCASE("conversion_operator")
    {
        CHECK(static_cast<std::string*>(sPtr) == &s);
    }

    SUBCASE("maker")
    {
        const auto op = pl::makeObserver(&s);
        CHECK(op == sPtr);

        const auto op2 = pl::makeObserver(static_cast<void*>(nullptr));
        CHECK(op2 == nullPtr);
        CHECK(nullptr == op2);
    }

    SUBCASE("hash")
    {
        const auto val1 = std::hash<std::string*>{}(&s);
        const auto val2 = std::hash<pl::ObserverPtr<std::string>>{}(sPtr);
        CHECK(val1 == val2);
    }

    SUBCASE("low_level_constness")
    {
        pl::ObserverPtr<const int> constObserverPtr{&i};

        PL_TEST_STATIC_ASSERT(
            std::is_same<decltype(constObserverPtr.release()),
                         const int*>::value);
        PL_TEST_STATIC_ASSERT(
            std::is_same<decltype(constObserverPtr.get()), const int*>::value);
        PL_TEST_STATIC_ASSERT(
            std::is_same<decltype(*constObserverPtr), const int&>::value);
        PL_TEST_STATIC_ASSERT(
            std::is_same<decltype(constObserverPtr.operator->()),
                         const int*>::value);
        PL_TEST_STATIC_ASSERT(
            std::is_same<decltype(constObserverPtr.operator const int*()),
                         const int*>::value);

        CHECK(constObserverPtr.get() == &i);
        CHECK(constObserverPtr == pointer);
    }
}
