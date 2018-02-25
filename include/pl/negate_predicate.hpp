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
 * \file negate_predicate.hpp
 * \brief Exports the negatePredicate function.
**/
#ifndef INCG_PL_NEGATE_PREDICATE_HPP
#define INCG_PL_NEGATE_PREDICATE_HPP
#include "annotations.hpp" // PL_IN
#include "meta/remove_cvref.hpp" // pl::meta::remove_cvref_t
#include "invoke.hpp" // pl::invoke
#include <ciso646> // not
#include <utility> // std::move, std::forward
#include <type_traits> // std::is_nothrow_move_constructible

namespace pl
{
namespace detail
{
/*!
 * \brief A NegatedPredicate. Type returned by negatePredicate function.
 *        Stores the predicate passed. Will call the predicate in its call
 *        operator and negate the result.
**/
template <typename Predicate>
class NegatedPredicate final
{
public:
    using this_type = NegatedPredicate;
    using return_type = bool;
    using value_type = Predicate;

    /*!
     * \brief Constructs a NegatedPredicate.
     * \param predicate The predicate callable that is to be stored and negated.
    **/
    explicit NegatedPredicate(value_type predicate)
    noexcept(std::is_nothrow_move_constructible<value_type>::value)
        : m_predicate{ std::move(predicate) }
    {
    }

    /*!
     * \brief Calls the stored predicate and negates the result.
     * \param args The arguments to call the stored predicate callable with.
     * \return The negation of the result of calling m_predicate with args.
    **/
    template <typename ...Args>
    return_type operator()(PL_IN Args &&...args)
    {
        return not ::pl::invoke(m_predicate, std::forward<Args>(args) ...);
    }

private:
    value_type m_predicate; //!< the stored predicate that is negated.
};
} // namespace detail

/*!
 * \brief Creates a predicate functor that is the negation of the predicate
 *        functor passed into the parameter.
 * \param predicate The predicate functor to create the negation of.
 * \return A predicate functor that is the negation of the predicate functor
 *         passed into the parameter.
**/
template <typename Predicate>
detail::NegatedPredicate<meta::remove_cvref_t<Predicate>> negatePredicate(
    PL_IN Predicate &&predicate)
{
    return detail::NegatedPredicate<meta::remove_cvref_t<Predicate>>{
        std::forward<Predicate>(predicate)
    };
}
} // namespace pl
#endif // INCG_PL_NEGATE_PREDICATE_HPP
