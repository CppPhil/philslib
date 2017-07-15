/*!
 * \file iterator_traits.hpp
 * \brief This header file defines trait-like metafunctions that operate
 *        on iterator types.
**/
#ifndef INCG_PL_META_ITERATOR_TRAITS_HPP
#define INCG_PL_META_ITERATOR_TRAITS_HPP
#include <type_traits> // std::false_type, std::true_type
#include <iterator> // std::output_iterator_tag, ...

namespace pl
{
namespace meta
{
namespace detail
{
/*!
 * \brief Anything else is not an output iterator.
**/
template <typename IterTag>
struct is_output_tag
    : public std::false_type
{
};

/*!
 * \brief Only output iterators are output iterators.
**/
template <>
struct is_output_tag<std::output_iterator_tag>
    : public std::true_type
{
};

/*!
 * \brief Anything else is not a random access iterator.
**/
template <typename IterTag>
struct is_random_access_tag
    : public std::false_type
{
};

/*!
 * \brief Only random access iterators are random access iterators.
**/
template <>
struct is_random_access_tag<std::random_access_iterator_tag>
    : public std::true_type
{
};

/*!
 * \brief Anything else is not a bidirectional iterator.
**/
template <typename IterTag>
struct is_bidi_tag
    : public std::false_type
{
};

/*!
 * \brief Bidirectional iterators are bidirectional iterators.
**/
template <>
struct is_bidi_tag<std::bidirectional_iterator_tag>
    : public std::true_type
{
};

/*!
 * \brief Random access iterators are bidirectional iterators.
**/
template <>
struct is_bidi_tag<std::random_access_iterator_tag>
    : public std::true_type
{
};

/*!
 * \brief Anything else is not a forward iterator.
**/
template <typename IterTag>
struct is_forward_tag
    : public std::false_type
{
};

/*!
 * \brief Forward iterators are forward iterators.
**/
template <>
struct is_forward_tag<std::forward_iterator_tag>
    : public std::true_type
{
};

/*!
 * \brief Bidirectional iterators are forward iterators.
**/
template <>
struct is_forward_tag<std::bidirectional_iterator_tag>
    : public std::true_type
{
};

/*!
 * \brief Random access iterators are forward iterators.
**/
template <>
struct is_forward_tag<std::random_access_iterator_tag>
    : public std::true_type
{
};

/*!
 * \brief Anything else is not an input iterator.
**/
template <typename IterTag>
struct is_input_tag
    : public std::false_type
{
};

/*!
 * \brief Input iterators are input iterators.
**/
template <>
struct is_input_tag<std::input_iterator_tag>
    : public std::true_type
{
};

/*!
 * \brief Forward iterators are input iterators.
**/
template <>
struct is_input_tag<std::forward_iterator_tag>
    : public std::true_type
{
};

/*!
 * \brief Bidirectional iterators are input iterators.
**/
template <>
struct is_input_tag<std::bidirectional_iterator_tag>
    : public std::true_type
{
};

/*!
 * \brief Random access iterators are input iterators.
**/
template <>
struct is_input_tag<std::random_access_iterator_tag>
    : public std::true_type
{
};

/*!
 * \brief Defines its nested type type as the iterator_category, which is the
 *        iterator tag of the iterator type passed into the template type parameter.
**/
template <typename Iter>
struct iterator_category
{
    using type
    = typename std::iterator_traits<std::remove_cv_t<std::remove_reference_t<Iter>>>::iterator_category;
};

/*!
 * \brief A template alias of the nested type type of ::pl::meta::detail::iterator_category.
**/
template <typename Iter>
using iterator_category_t = typename iterator_category<Iter>::type;
} // namespace detail

/*!
 * \brief Type trait to check if an iterator is an output iterator.
 * \note See: http://en.cppreference.com/w/cpp/types/integral_constant
 *       for documentation of std::true_type and std::false_type.
 * \note Note that only output iterators are considered output iterators.
 *
 * If the template type parameter is an output iterator the template
 * instantiation will be derived from std::true_type. Otherwise it will be
 * derived from std::false_type.
**/
template <typename Iter>
struct is_output_iterator
    : public detail::is_output_tag<detail::iterator_category_t<Iter>>
{
};

/*!
 * \brief A template alias for the nested type type of pl::meta::is_output_iterator.
**/
template <typename Iter>
using is_output_iterator_t = typename is_output_iterator<Iter>::type;

/*!
 * \brief Type trait to check if an iterator is a random access iterator.
 * \note See: http://en.cppreference.com/w/cpp/types/integral_constant
 *       for documentation of std::true_type and std::false_type.
 * \note Note that only random access iterators are considered random access
 *       iterators.
 *
 * If the template type parameter is a random access iterator the template
 * instantiation will be derived from std::true_type. Otherwise it will be
 * derived from std::false_type.
**/
template <typename Iter>
struct is_random_access_iterator
    : public detail::is_random_access_tag<detail::iterator_category_t<Iter>>
{
};

/*!
 * \brief A template alias for the nested type type of pl::meta::is_random_access_iterator
**/
template <typename Iter>
using is_random_access_iterator_t = typename is_random_access_iterator<Iter>::type;

/*!
 * \brief Type trait to check if an iterator is a bidirectional iterator.
 * \note See: http://en.cppreference.com/w/cpp/types/integral_constant
 *       for documentation of std::true_type and std::false_type.
 * \note Note that both bidirectional iterators and random access iterators
 *       are considered bidirectional iterators.
 *
 * If the template type parameter is a bidirectional iterator the template
 * instantiation will be derived from std::true_type. Otherwise it will be
 * derived from std::false_type.
**/
template <typename Iter>
struct is_bidirectional_iterator
    : public detail::is_bidi_tag<detail::iterator_category_t<Iter>>
{
};

/*!
 * \brief A template alias for the nested type type of pl::meta::is_bidirectional_iterator
**/
template <typename Iter>
using is_bidirectional_iterator_t = typename is_bidirectional_iterator<Iter>::type;

/*!
 * \brief Type trait to check if an iterator is a forward iterator.
 * \note See: http://en.cppreference.com/w/cpp/types/integral_constant
 *       for documentation of std::true_type and std::false_type.
 * \note Note that forward iterators, bidirectional iterators as well as
 *       random access iterators are considered forward iterators.
 *
 * If the template type parameter is a forward iterator the template
 * instantiation will be derived from std::true_type. Otherwise it will be
 * derived from std::false_type.
**/
template <typename Iter>
struct is_forward_iterator
    : public detail::is_forward_tag<detail::iterator_category_t<Iter>>
{
};

/*!
 * \brief A template alias for the nested type type of pl::meta::is_forward_iterator
**/
template <typename Iter>
using is_forward_iterator_t = typename is_forward_iterator<Iter>::type;

/*!
 * \brief Type trait to check if an iterator is an input iterator.
 * \note See: http://en.cppreference.com/w/cpp/types/integral_constant
 *       for documentation of std::true_type and std::false_type.
 * \note Note that input iterators, forward iterators, bidirectional iterators,
 *       as well as random access iterators are considered input iterators.
 *
 * If the template type parameter is an input iterator the template
 * instantiation will be derived from std::true_type. Otherwise it will be
 * derived from std::false_type.
**/
template <typename Iter>
struct is_input_iterator
    : public detail::is_input_tag<detail::iterator_category_t<Iter>>
{
};

/*!
 * \brief A template alias for the nested type type of pl::meta::is_input_iterator
**/
template <typename Iter>
using is_input_iterator_t = typename is_input_iterator<Iter>::type;
} // namespace meta
} // namespace pl
#endif // INCG_PL_META_ITERATOR_TRAITS_HPP
