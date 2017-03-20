/*!
 * \file iterator.hpp
 * \brief This file defines various utilities for working with iterators.
**/
#ifndef INCG_PL_ITERATOR_HPP
#define INCG_PL_ITERATOR_HPP
#include "macros.hpp" // PL_IN
#include <cstddef> // std::size_t
#include <iterator> // std::reverse_iterator
#include <type_traits> // std::true_type, std::false_type
/*!
 * \def PL_BEGIN_END(cont)
 * \brief Macro that can be used to call a function that expects begin and
 *        end iterators to cont.
**/

/*!
 * \def PL_CBEGIN_CEND(cont)
 * \brief Macro that can be used to call a function that expects cbegin and
 *        cend iterators to cont.
**/

/*!
 * \def PL_RBEGIN_REND(cont)
 * \brief Macro that can be used to call a function that expects rbegin and
 *        rend iterators to cont.
**/

/*!
 * \def PL_CRBEGIN_CREND(cont)
 * \brief Macro that can be used to call a function that expects crbegin and
 *        crend iterators to cont.
**/

namespace pl
{
/*!
 * \brief Returns an iterator to the beginning of the container.
 * \param container The container for which to get an iterator to its
 *        beginning.
 * \return An iterator to the beginning of container.
**/
template <typename Container>
constexpr auto begin(PL_IN Container &container) noexcept -> decltype(auto)
{
    return container.begin();
}

/*!
 * \brief Returns a const_iterator to the beginning of the container.
 * \param container The container for which to get a const_iterator to its
 *        beginning.
 * \return A const_iterator to the beginning of container.
**/
template <typename Container>
constexpr auto begin(PL_IN const Container &container) noexcept -> decltype(auto)
{
    return container.begin();
}

/*!
 * \brief Returns an iterator to the beginning of the array.
 * \param array The array for which to get an iterator to its beginning.
 * \return An iterator to the beginning of array.
**/
template <typename Type, std::size_t Size>
constexpr Type *begin(PL_IN Type (&array)[Size]) noexcept
{
    return array;
}

/*!
 * \brief Returns a const_iterator to the beginning of the array.
 * \param array The array for which to get a const_iterator to its beginning.
 * \return A const_iterator to the beginning of the array.
**/
template <typename Type, std::size_t Size>
constexpr const Type *begin(PL_IN const Type (&array)[Size]) noexcept
{
    return array;
}

/*!
 * \brief Returns a const_iterator to the beginning of the container.
 * \param container The container for which to get a const_iterator to its
 *        beginning.
 * \return A const_iterator to the beginning of the container.
**/
template <typename Container>
constexpr auto cbegin(PL_IN const Container &container) noexcept -> decltype(auto)
{
    return ::pl::begin(container);
}

/*!
 * \brief Returns a const_iterator to the beginning of the array
 * \param array The array for which to get a const_iterator to its beginning.
 * \return A const_iterator to the beginning of the array.
**/
template <typename Type, std::size_t Size>
constexpr auto cbegin(PL_IN const Type (&array)[Size]) noexcept -> decltype(auto)
{
    return ::pl::begin(array);
}

/*!
 * \brief Returns the end iterator of a container.
 * \param container The container to get the end iterator for.
 * \return The end iterator of container.
**/
template <typename Container>
constexpr auto end(PL_IN Container &container) noexcept -> decltype(auto)
{
    return container.end();
}

/*!
 * \brief Returns the end const_iterator of a container.
 * \param container The container to get the end const_iterator for.
 * \return The end cont_iterator of container.
**/
template <typename Container>
constexpr auto end(PL_IN const Container &container) noexcept -> decltype(auto)
{
    return container.end();
}

/*!
 * \brief Returns the end iterator of an array.
 * \param array The array to get the end iterator for.
 * \return The end iterator of array.
**/
template <typename Type, std::size_t Size>
constexpr Type *end(PL_IN Type (&array)[Size]) noexcept
{
    return ::pl::begin(array) + Size;
}

/*!
 * \brief Returns the end const_iterator of an array.
 * \param array The array to get the end const_iterator for.
 * \return The end const_iterator of array.
**/
template <typename Type, std::size_t Size>
constexpr const Type *end(PL_IN const Type (&array)[Size]) noexcept
{
    return ::pl::begin(array) + Size;
}

/*!
 * \brief Returns the end const_iterator of a container.
 * \param container The container to get the end const_iterator for.
 * \return The end const_iterator of container.
**/
template <typename Container>
constexpr auto cend(PL_IN const Container &container) noexcept -> decltype(auto)
{
    return ::pl::end(container);
}

/*!
 * \brief Returns the end const_iterator of an array.
 * \param array The array to get the end const_iterator for.
 * \return The end const_iterator of array.
**/
template <typename Type, std::size_t Size>
constexpr auto cend(PL_IN const Type (&array)[Size]) noexcept -> decltype(auto)
{
    return ::pl::end(array);
}

/*!
 * \brief Returns the begin reverse_iterator of a container.
 * \param container The container to get the the begin reverse_iterator for.
 * \return The begin reverse_iterator of container.
**/
template <typename Container>
constexpr auto rbegin(PL_IN Container &container) noexcept -> decltype(auto)
{
    return container.rbegin();
}

/*!
 * \brief Returns the begin const_reverse_iterator of a container.
 * \param container The containere to get the begin const_reverse_iterator for.
 * \return The begin const_reverse_iterator of container.
**/
template <typename Container>
constexpr auto rbegin(PL_IN const Container &container) noexcept -> decltype(auto)
{
    return container.rbegin();
}

/*!
 * \brief Returns the begin reverse_iterator of an array.
 * \param array The array to get the begin reverse_iterator for.
 * \return The begin reverse_iterator of array.
**/
template <typename Type, std::size_t Size>
constexpr std::reverse_iterator<Type *> rbegin(PL_IN Type (&array)[Size]) noexcept
{
    return std::reverse_iterator<Type *>{ array + Size };
}

/*!
 * \brief Returns the begin const_reverse_iterator of an array.
 * \param array The array to get the begin const_reverse_iterator for.
 * \return The begin const_reverse_iterator of array.
**/
template <typename Type, std::size_t Size>
constexpr std::reverse_iterator<const Type *> rbegin(PL_IN const Type (&array)[Size]) noexcept
{
    return std::reverse_iterator<const Type *>{ array + Size };
}

/*!
 * \brief Returns the begin const_reverse_iterator of a container.
 * \param container THe container to get the begin const_reverse_iterator for.
 * \return The begin const_reverse_iterator of container.
**/
template <typename Container>
constexpr auto crbegin(PL_IN const Container &container) noexcept -> decltype(auto)
{
    return ::pl::rbegin(container);
}

/*!
 * \brief Returns the begin const_reverse_iterator of an array.
 * \param array The array to get the begin const_reverse_iterator for.
 * \return The begin const_reverse_iterator of array.
**/
template <typename Type, std::size_t Size>
constexpr auto crbegin(PL_IN const Type (&array)[Size]) noexcept
{
    return ::pl::rbegin(array);
}

/*!
 * \brief Returns the end reverse_iterator of a container.
 * \param container The container to get the end reverse_iterator for.
 * \return The end reverse_iterator of container.
**/
template <typename Container>
constexpr auto rend(PL_IN Container &container) noexcept -> decltype(auto)
{
    return container.rend();
}

/*!
 * \brief Returns the end const_reverse_iterator of a container.
 * \param container The container to get the end const_reverse_iterator for.
 * \return The end const_reverse_iterator of container.
**/
template <typename Container>
constexpr auto rend(PL_IN const Container &container) noexcept -> decltype(auto)
{
    return container.rend();
}

/*!
 * \brief Returns the end reverse_iterator of an array.
 * \param array The array to get the end reverse_iterator for.
 * \return The end reverse_iterator of array.
**/
template <typename Type, std::size_t Size>
constexpr std::reverse_iterator<Type *> rend(PL_IN Type (&array)[Size]) noexcept
{
    return std::reverse_iterator<Type *>{ array };
}

/*!
 * \brief Returns the end const_reverse_iterator of an array.
 * \param array The array to get the end const_reverse_iterator for.
 * \return The end const_reverse_iterator of array.
**/
template <typename Type, std::size_t Size>
constexpr std::reverse_iterator<const Type *> rend(PL_IN const Type (&array)[Size]) noexcept
{
    return std::reverse_iterator<const Type *>{ array };
}

/*!
 * \brief Returns the end const_reverse_iterator of a container.
 * \param container The container to get the end const_reverse_iterator for.
 * \return The end const_reverse_iterator of container.
**/
template <typename Container>
constexpr auto crend(PL_IN const Container &container) noexcept -> decltype(auto)
{
    return ::pl::rend(container);
}

/*!
 * \brief Returns the end const_reverse_iterator of an array.
 * \param array The array to get the end const_reverse_iterator for.
 * \return The end const_reverse_iterator of array.
**/
template <typename Type, std::size_t Size>
constexpr auto crend(PL_IN const Type (&array)[Size]) noexcept -> decltype(auto)
{
    return ::pl::rend(array);
}

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
 * \brief A template alias of the nested type type of ::pl::detail::iterator_category.
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
 * \brief A template alias for the nested type type of pl::is_output_iterator.
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
 * \brief A template alias for the nested type type of pl::is_random_access_iterator
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
 * \brief A template alias for the nested type type of pl::is_bidirectional_iterator
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
 * \brief A template alias for the nested type type of pl::is_forward_iterator
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
 * \brief A template alias for the nested type type of pl::is_input_iterator
**/
template <typename Iter>
using is_input_iterator_t = typename is_input_iterator<Iter>::type;

namespace detail
{
/*!
 * \brief Type used by pl::iterateReversed. Used for non-const containers.
**/
template <typename Container>
class RevForAdapter final
{
public:
    using this_type = RevForAdapter;

    /*!
     * \brief Creates a pl::detail::RevForAdapter by storing a non-const lvalue
     *        reference to the container passed in.
     * \param container The container to iterate over.
    **/
    explicit RevForAdapter(PL_IN Container &container)
        : m_container{ container }
    {
    }

    /*!
     * \brief Returns the reverse begin iterator to the container.
     * \return The reverse begin iterator to the container.
     * \note This function is called by the range based for loop.
    **/
    auto begin() -> decltype(auto)
    {
        return ::pl::rbegin(m_container);
    }

    /*!
     * \brief Returns the reverse end iterator to the container.
     * \return The reverse end iterator to the container.
     * \note This function is called by the range based for loop.
    **/
    auto end() -> decltype(auto)
    {
        return ::pl::rend(m_container);
    }

private:
    Container &m_container; //!< reference to the container to iterate over.
};

/*!
 * \brief Type used by pl::iterateReversed. Used for const containers.
**/
template <typename Container>
class RevForAdapterConst final
{
public:
    using this_type = RevForAdapterConst;

    /*!
     * \brief Creates a pl::detail::RevForAdapterConst by storing a const lvalue
     *        reference to the container passed in.
     * \param container The container to iterate over.
    **/
    explicit RevForAdapterConst(PL_IN const Container &container)
        : m_container{ container }
    {
    }

    /*!
     * \brief Returns the const reverse begin iterator to the container.
     * \return The const reverse begin iterator to the container.
     * \note This function is called by the range based for loop.
    **/
    auto begin() const -> decltype(auto)
    {
        return ::pl::crbegin(m_container);
    }

    /*!
     * \brief Returns the const reverse end iterator to the container.
     * \return The const reverse end iterator to the container.
     * \note This function is called by the range based for loop.
    **/
    auto end() const -> decltype(auto)
    {
        return ::pl::crend(m_container);
    }

private:
    const Container &m_container; //!< const lvalue reference to the container to iterate over.
};
} // namespace detail

/*!
 * \brief Allows the user to iterate over a container in reversed order using
 *        a range based for loop.
 * \param container The container to iterate over in reversed order
 * \return An object that a range based for loop can operate on in order to
 *         iterate over the container in reversed order.
 * \note This overload handles non-const containers.
 * \example for (auto &e : pl::iterateReversed(cont)) {
 *              ++e;
 *              std::cout << e << ' ';
 *          }
**/
template <typename Container>
detail::RevForAdapter<Container> iterateReversed(PL_IN Container &container)
{
    return detail::RevForAdapter<Container>{ container };
}

/*!
 * \brief Allows the user to iterator over a container in reversed order using
 *        a range based for loop.
 * \param container The container to iterate over in reversed order
 * \return An object that a range based for loop can operate on in order to
 *         iterate over the container in reversed order.
 * \note This overload handles const containers.
 * \example for (const auto &e : pl::iterateReversed(cont)) {
 *              std::cout << e << ' ';
 *          }
**/
template <typename Container>
detail::RevForAdapterConst<Container> iterateReversed(PL_IN const Container &container)
{
    return detail::RevForAdapterConst<Container>{ container };
}
} // namespace pl
#define PL_BEGIN_END(cont) ::pl::begin(cont), ::pl::end(cont)
#define PL_CBEGIN_CEND(cont) ::pl::cbegin(cont), ::pl::cend(cont)
#define PL_RBEGIN_REND(cont) ::pl::rbegin(cont), ::pl::rend(cont)
#define PL_CRBEGIN_CREND(cont) ::pl::crbegin(cont), ::pl::crend(cont)
#endif // INCG_PL_ITERATOR_HPP
