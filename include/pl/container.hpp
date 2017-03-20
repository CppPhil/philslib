/*!
 * \file container.hpp
 * \brief Defines a few utility functions for working with containers.
**/
#ifndef INCG_PL_CONTAINER_HPP
#define INCG_PL_CONTAINER_HPP
#include "macros.hpp" // PL_IN
#include <cstddef> // std::size_t
#include <memory> // std::addressof
#include <array> // std::array
#include <type_traits> // std::common_type_t
#include <utility> // std::forward
#include <deque> // std::deque
#include <forward_list> // std::forward_list
#include <list> // std::list
#include <map> // std::map, std::multimap
#include <set> // std::set, std::multiset
#include <unordered_map> // std::unordered_map, std::unordered_multimap
#include <unordered_set> // std::unordered_set, std::unordered_multiset
#include <vector> // std::vector
namespace pl
{
/*!
 * \brief Gets the first (index 0) element of a container.
 * \param cont The container to get the first (index 0) element of.
 * \return The first (index 0) element of the container.
 * \warning Undefined behavior occurs if the container passed is empty.
**/
template <typename Cont>
auto front(PL_IN Cont &cont) -> decltype(auto)
{
    return cont.front();
}

/*!
 * \brief Gets the first (index 0) element of a C-Array.
 * \param arr The C-Array to get the first (index 0) element of.
 * \return The first (index 0) element of the C-Array.
**/
template <typename Type, std::size_t Size>
auto front(PL_IN Type (&arr)[Size]) -> decltype(auto)
{
    return arr[static_cast<std::size_t>(0U)];
}

/*!
 * \brief Gets the last element of a container.
 * \param cont The container to get the last element of.
 * \return The last element of the container.
 * \warning Undefined behavior occurs if the container passed in is empty.
**/
template <typename Cont>
auto back(PL_IN Cont &cont) -> decltype(auto)
{
    return cont.back();
}

/*!
 * \brief Gets the last element of a C-Array.
 * \param arr The C-Array to get the last element of.
 * \return The last element of the C-Array.
**/
template <typename Type, std::size_t Size>
auto back(PL_IN Type (&arr)[Size]) -> decltype(auto)
{
    return arr[Size - static_cast<std::size_t>(1U)];
}

/*!
 * \brief Calls .data() on the container passed in.
 * \param cont The container to call .data() on.
 * \return The result of calling .data() on cont.
 * \warning Do not dereference the pointer returned by this function if
 *          the container passed in was empty.
**/
template <typename Cont>
auto data(PL_IN Cont &cont) noexcept -> decltype(auto)
{
    return cont.data();
}

/*!
 * \brief Function to get a pointer to the first (index 0) element of a C-Array.
 * \param arr The C-Array for which
 *        to get the pointer to its first (index 0) element from.
**/
template <typename Type, std::size_t Size>
auto data(PL_IN Type (&arr)[Size]) noexcept -> decltype(auto)
{
    return std::addressof(arr[0]);
}

/*!
 * \brief Gets the size of a container, which is the amount of elements
 *        currently stored in that container.
 * \param cont The container to get the size of.
 * \return The size of the container passed into the parameter.
**/
template <typename Cont>
auto size(PL_IN Cont &cont) noexcept -> decltype(auto)
{
    return cont.size();
}

/*!
 * \brief Gets the size of a C-Array.
 * \param arr The C-Array to get the size of.
 * \return The size of the C-Array passed into the parameter is returned.
**/
template <typename Type, std::size_t Size>
std::size_t size(PL_IN Type (&arr)[Size]) noexcept
{
    PL_UNUSED(arr);
    return Size;
}

/*!
 * \brief Creates a std::array from a template type parameter pack.
 * \param args The arguments to construct the std::array returned from.
 * \return The resulting std::array.
 * \note The resulting std::array will use the common type for all of its
 *       elements. Some of the values passed in may be converted to that common type.
**/
template <typename ...Args>
constexpr auto makeArray(PL_IN Args &&...args)
    -> std::array<std::common_type_t<Args ...>, sizeof...(args)>
{
    return {
        static_cast<std::common_type_t<Args ...>>(
            std::forward<Args>(args)
        )...
    };
}

/*!
 * \brief Tag for vector-like containers.
 *
 * Tag used for std::vector and std::deque.
**/
struct vectorlike_tag
{
};

/*!
 * \brief Tag for list-like containers.
 *
 * Tag used for std::list and std::forward_list.
**/
struct listlike_tag
{
};

/*!
 * \brief Tag for associative containers.
 *
 * Tag used for std::set, std::multiset, std::unordered_set, std::unordered_multiset,
 * std::map, std::multimap, std::unordered_map and std::unordered_multimap.
**/
struct associative_tag
{
};

/*!
 * \brief struct that has a nested type called category that is an alias
 *        of the tag type that corresponds to the standard library
 *        container type that this struct's template type parameter
 *        was instantiated with.
**/
template <typename Container>
struct container_traits;

/*!
 * \brief template specialization for std::vector.
 *        category is defined as vectorlike_tag.
**/
template <typename Type, typename Allocator>
struct container_traits<std::vector<Type, Allocator>>
{
    using category = vectorlike_tag;
};

/*!
 * \brief template specialization for std::deque.
 *        category is defined as vectorlike_tag.
**/
template <typename Type, typename Allocator>
struct container_traits<std::deque<Type, Allocator>>
{
    using category = vectorlike_tag;
};

/*!
 * \brief template specialization for std::list.
 *        category is defined as listlike_tag.
**/
template <typename Type, typename Allocator>
struct container_traits<std::list<Type, Allocator>>
{
    using category = listlike_tag;
};

/*!
 * \brief template specialization for std::forward_list.
 *        category is defined as listlike_tag.
**/
template <typename Type, typename Allocator>
struct container_traits<std::forward_list<Type, Allocator>>
{
    using category = listlike_tag;
};

/*!
 * \brief template specialization for std::set.
 *        category is defined as associative_tag.
**/
template <typename Type, typename Comparator, typename Allocator>
struct container_traits<std::set<Type, Comparator, Allocator>>
{
    using category = associative_tag;
};

/*!
 * \brief template specialization for std::multiset.
 *        category is defined as associative_tag.
**/
template <typename Type, typename Comparator, typename Allocator>
struct container_traits<std::multiset<Type, Comparator, Allocator>>
{
    using category = associative_tag;
};

/*!
 * \brief template specialization for std::unordered_set.
 *        category is defined as associative_tag.
**/
template <typename Type, typename Comparator, typename Allocator>
struct container_traits<std::unordered_set<Type, Comparator, Allocator>>
{
    using category = associative_tag;
};

/*!
 * \brief template specialization for std::unordered_multiset.
 *        category is defined as associative_tag.
**/
template <typename Type, typename Comparator, typename Allocator>
struct container_traits<std::unordered_multiset<Type, Comparator, Allocator>>
{
    using category = associative_tag;
};

/*!
 * \brief template specialization for std::map.
 *        category is defined as associative_tag.
**/
template <typename Type, typename Comparator, typename Allocator>
struct container_traits<std::map<Type, Comparator, Allocator>>
{
    using category = associative_tag;
};

/*!
 * \brief template specialization for std::multimap.
 *        category is defined as associative_tag.
**/
template <typename Type, typename Comparator, typename Allocator>
struct container_traits<std::multimap<Type, Comparator, Allocator>>
{
    using category = associative_tag;
};

/*!
 * \brief template specialization for std::unordered_map.
 *        category is defined as associative_tag.
**/
template <typename Type, typename Comparator, typename Allocator>
struct container_traits<std::unordered_map<Type, Comparator, Allocator>>
{
    using category = associative_tag;
};

/*!
 * \brief template specialization for std::unordered_multimap.
 *        category is defined as associative_tag.
**/
template <typename Type, typename Comparator, typename Allocator>
struct container_traits<std::unordered_multimap<Type, Comparator, Allocator>>
{
    using category = associative_tag;
};

/*!
 * \brief C++14 style template type alias for the nested type of container_traits
 *        called category. Make usage simpler as it doesn't require the typename
 *        keyword.
**/
template <typename Container>
using container_traits_category = typename container_traits<Container>::category;
} // namespace pl
#endif // INCG_PL_CONTAINER_HPP
