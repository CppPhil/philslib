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
template <typename Default, typename AlwaysVoid,
          template <typename ...> class Op, typename ...Args>
struct detector
{
    using value_t = std::false_type;
    using type = Default;
};

template <typename Default, template <typename ...> class Op, typename ...Args>
struct detector<Default, ::pl::meta::void_t<Op<Args ...>>, Op, Args ...>
{
    using value_t = std::true_type;
    using type = Op<Args ...>;
};
} // namespace detail

template <template <typename ...> class Op, typename ...Args>
using is_detected = typename detail::detector<nonesuch, void, Op, Args ...>::value_t;

template <template <typename ...> class Op, typename ...Args>
using detected_t = typename detail::detector<nonesuch, void, Op, Args ...>::type;

template <typename Default, template <typename ...> class Op, typename ...Args>
using detected_or = detail::detector<Default, void, Op, Args ...>;

template <typename Default, template <typename ...> class Op, typename ...Args>
using detected_or_t = typename detected_or<Default, Op, Args ...>::type;

template <typename Expected, template <typename ...> class Op, typename ...Args>
using is_detected_exact = std::is_same<Expected, detected_t<Op, Args ...>>;

template <typename To, template <typename ...> class Op, typename ...Args>
using is_detected_convertible = std::is_convertible<detected_t<Op, Args ...>, To>;
} // namespace meta
} // namespace pl
#endif // INCG_PL_META_DETECTION_IDIOM_HPP
