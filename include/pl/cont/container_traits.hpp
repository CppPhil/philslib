#ifndef INCG_PL_CONT_CONTAINER_TRAITS_HPP
#define INCG_PL_CONT_CONTAINER_TRAITS_HPP
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
namespace cont
{
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
 *        called category. Makes usage simpler as it doesn't require the typename
 *        keyword.
**/
template <typename Container>
using container_traits_category = typename container_traits<Container>::category;
} // namespace cont
} // namespace pl
#endif // INCG_PL_CONT_CONTAINER_TRAITS_HPP
