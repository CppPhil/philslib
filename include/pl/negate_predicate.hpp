/*!
 * \file negate_predicate.hpp
 * \brief Exports the negatePredicate function.
**/
#ifndef INCG_PL_NEGATE_PREDICATE_HPP
#define INCG_PL_NEGATE_PREDICATE_HPP
#include "annotations.hpp" // PL_IN
#include <ciso646> // not
#include <utility> // std::move_if_noexcept, std::forward
#include <type_traits> // std::is_nothrow_move_constructible, std::remove_reference_t

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
        : m_predicate{ std::move_if_noexcept(predicate) }
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
        return not m_predicate(std::forward<Args>(args)...);
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
detail::NegatedPredicate<std::remove_reference_t<Predicate>>
negatePredicate(PL_IN Predicate &&predicate)
{
    return detail::NegatedPredicate<std::remove_reference_t<Predicate>>{
        std::forward<Predicate>(predicate)
    };
}
} // namespace pl
#endif // INCG_PL_NEGATE_PREDICATE_HPP
