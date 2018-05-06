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

/*!
 * \file overload.hpp
 * \brief Defines the C++14 compatible overload machinery that
 *        creates callables combining different lambdas by deriving from them.
**/
#ifndef INCG_PL_OVERLOAD_HPP
#define INCG_PL_OVERLOAD_HPP
#include "annotations.hpp"       // PL_IN
#include "meta/remove_cvref.hpp" // pl::meta::remove_cvref_t
#include <utility>               // std::forward

namespace pl {
/*!
 * \brief The primary 'Overloaded' template.
 *        Exports all the call operators of the lambdas, which are base types.
**/
template <typename Lambda1, typename... Lambdas>
class Overloaded : public Lambda1, public Overloaded<Lambdas...> {
public:
    /*!
     * \brief Creates an 'Overloaded' object.
     * \param lambda1 The first lambda to construct.
     * \param lambdas The rest of the lambdas to construct.
    **/
    template <typename FirstLambda, typename... OtherLambdas>
    Overloaded(PL_IN FirstLambda&& lambda1, PL_IN OtherLambdas&&... lambdas)
        : Lambda1{std::forward<FirstLambda>(lambda1)}
        , Overloaded<Lambdas...>{std::forward<OtherLambdas>(lambdas)...}
    {
    }

    using Lambda1::operator();
    using Overloaded<Lambdas...>::operator();
};

/*!
 * \brief The recursive base case of the 'Overloaded' machinery.
 *        Derives from Lambda1. A partial template specialization of the
 *        base template.
**/
template <typename Lambda1>
class Overloaded<Lambda1> : public Lambda1 {
public:
    /*!
     * \brief Constructs an 'Overloaded' object.
     * \param lambda1 The first lambda to construct.
    **/
    template <typename FirstLambda>
    explicit Overloaded(PL_IN FirstLambda&& lambda1)
        : Lambda1{std::forward<FirstLambda>(lambda1)}
    {
    }

    using Lambda1::operator();
};

/*!
 * \brief Maker function for an 'Overloaded'.
 * \param lambdas The lambdas to be combined.
 * \return An object that features all the call operators of all the
 *         lambdas passed into the parameter list.
 * \note The parameter list may not be empty.
**/
template <typename... Lambdas>
auto overload(PL_IN Lambdas&&... lambdas)
{
    static_assert(
        sizeof...(Lambdas) > 0,
        "You must supply at least one argument to pl::overload");

    return Overloaded<meta::remove_cvref_t<Lambdas>...>{
        std::forward<Lambdas>(lambdas)...};
}
} // namespace pl
#endif // INCG_PL_OVERLOAD_HPP
