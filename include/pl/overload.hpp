/*!
 * \file overload.hpp
 * \brief Defines the C++14 compatible overload machinery that
 *        creates callables combining different lambdas by deriving from them.
**/
#ifndef INCG_PL_OVERLOAD_HPP
#define INCG_PL_OVERLOAD_HPP
#include "annotations.hpp" // PL_IN
#include <utility> // std::forward
#include <type_traits> // std::remove_reference_t

namespace pl
{
/*!
 * \brief The primary 'Overloaded' template.
 *        Exports all the call operators of the lambdas, which are base types.
**/
template <typename Lambda1, typename ...Lambdas>
class Overloaded
    : public Lambda1,
      public Overloaded<Lambdas ...>
{
public:
    /*!
     * \brief Creates an 'Overloaded' object.
     * \param lambda1 The first lambda to construct.
     * \param lambdas The rest of the lambdas to construct.
    **/
    template <typename FirstLambda, typename ...OtherLambdas>
    Overloaded(PL_IN FirstLambda &&lambda1, PL_IN OtherLambdas &&...lambdas)
        : Lambda1{ std::forward<FirstLambda>(lambda1) },
          Overloaded<Lambdas ...>{ std::forward<OtherLambdas>(lambdas) ... }
    {
    }

    using Lambda1::operator();
    using Overloaded<Lambdas ...>::operator();
};

/*!
 * \brief The recursive base case of the 'Overloaded' machinery.
 *        Derives from Lambda1. A partial template specialization of the
 *        base template.
**/
template <typename Lambda1>
class Overloaded<Lambda1>
    : public Lambda1
{
public:
    /*!
     * \brief Constructs an 'Overloaded' object.
     * \param lambda1 The first lambda to construct.
    **/
    template <typename FirstLambda>
    Overloaded(PL_IN FirstLambda &&lambda1)
        : Lambda1{ std::forward<FirstLambda>(lambda1) }
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
template <typename ...Lambdas>
auto overload(PL_IN Lambdas &&...lambdas) -> decltype(auto)
{
    static_assert(sizeof...(Lambdas) > 0,
                  "You must supply at least one argument to pl::overload");

    return Overloaded<std::remove_reference_t<Lambdas> ...>{
               std::forward<Lambdas>(lambdas) ... };
}
} // namespace pl
#endif // INCG_PL_OVERLOAD_HPP
