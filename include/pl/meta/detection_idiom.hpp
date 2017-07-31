/*!
 * \file detection_idiom.hpp
 * \brief Exports meta functions that implement the detection idiom.
**/
#ifndef INCG_PL_META_DETECTION_IDIOM_HPP
#define INCG_PL_META_DETECTION_IDIOM_HPP
#include "void_t.hpp" // pl::meta::void_t
#include <type_traits> // std::false_type, std::is_same, std::is_convertible

namespace pl
{
namespace meta
{
/*!
 * \brief A type used by detected_t to indicate detection failure.
 * \warning Do not instantiate this type.
**/
struct nonesuch
{
    nonesuch() = delete;
    ~nonesuch() = delete;
    nonesuch(nonesuch const &) = delete;
    void operator=(nonesuch const &) = delete;
};

namespace detail
{
/*!
 * \brief Exposition only struct serving as the implementation of the
 *        detection idiom.
 * \note Not to be used directly.
**/
template <typename Default, typename AlwaysVoid,
          template <typename ...> class Op, typename ...Args>
struct detector
{
    using value_t = std::false_type;
    using type = Default;
};

/*!
 * \brief Exposition only struct serving as the implementation of the
 *        detection idiom.
 * \note Not to be used directly.
**/
template <typename Default, template <typename ...> class Op, typename ...Args>
struct detector<Default, ::pl::meta::void_t<Op<Args ...>>, Op, Args ...>
{
    using value_t = std::true_type;
    using type = Op<Args ...>;
};
} // namespace detail

/*!
 * \brief Can be used to check if the trait like meta function 'Op' forms
 *        a well-formed expression if 'Args' is expanded into its template
 *        parameter list.
 *
 * Will be an alias of std::true_type if Op<Args ...> is well-formed.
 * Otherwise will be an alias of std::false_type.
**/
template <template <typename ...> class Op, typename ...Args>
using is_detected = typename detail::detector<nonesuch, void, Op, Args ...>::value_t;

/*!
 * \brief Behaves like is_detected except for that it will be an alias
 *        of Op<Args ...> if detection succeeds.
 *        If detection fails will be an alias of 'nonesuch'.
**/
template <template <typename ...> class Op, typename ...Args>
using detected_t = typename detail::detector<nonesuch, void, Op, Args ...>::type;

/*!
 * \brief An alias of the exposition only 'DETECTOR' type.
 *
 * Features two nested types, namely 'value_t' and 'type'.
 * If detection succeeded 'value_t' will be an alias of std::true_type.
 * If detection succeeded 'type' will be an alias of Op<Args ...>.
 * If detection failed 'value_t' will be an alias of std::false_type.
 * If detection failed 'type' will be an alias of type 'Default'.
**/
template <typename Default, template <typename ...> class Op, typename ...Args>
using detected_or = detail::detector<Default, void, Op, Args ...>;

/*!
 * \brief Will be an alias of Op<Args ...> if detection succeeds.
 *        If detection fails will be an alias of 'Default'.
 * \note May be useful in order to use some nested type of another type
 *       if that nested type exists and fallback to 'Default' otherwise.
**/
template <typename Default, template <typename ...> class Op, typename ...Args>
using detected_or_t = typename detected_or<Default, Op, Args ...>::type;

/*!
 * \brief Will be an alias of std::true_type if detection succeeded and the
 *        detected type (Op<Args ...>) is the same type as 'Expected'.
 *        Otherwise will be an alias of std::false_type.
**/
template <typename Expected, template <typename ...> class Op, typename ...Args>
using is_detected_exact = std::is_same<Expected, detected_t<Op, Args ...>>;

/*!
 * \brief Will be an alias of std::true_type if detection succeeded and the
 *        detected type (Op<Args ...>) is convertible to 'To'.
 *        Otherwise will be an alias of std::false_type.
**/
template <typename To, template <typename ...> class Op, typename ...Args>
using is_detected_convertible = std::is_convertible<detected_t<Op, Args ...>, To>;
} // namespace meta
} // namespace pl
#endif // INCG_PL_META_DETECTION_IDIOM_HPP
