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
 * \file erase.hpp
 * \brief Exports the erase and erase_if algorithms that implement the
 *        erase remove idiom.
 **/
#ifndef INCG_PL_ALGO_ERASE_HPP
#define INCG_PL_ALGO_ERASE_HPP
#include "../annotations.hpp"           // PL_IN, PL_INOUT
#include "../meta/container_traits.hpp" // pl::meta::vectorlike_tag, pl::meta::listlike_tag, pl::meta::associative_tag, pl::meta::container_traits_category
#include <algorithm>                    // std::remove, std::remove_if
#include <utility>                      // std::forward

namespace pl {
namespace algo {
namespace detail {
/*!
 * \brief Helper function used by pl::erase. Removes all occurrences that
 *        compare equal to element_to_remove from a vectorlike container.
 * \param container The container to remove all occurrences of element_to_remove
 *                  from.
 * \param element_to_remove The element to remove. All elements of the container
 *                          that compare equal to this will be removed from
 *                          the container.
 **/
template<typename Container, typename Type>
inline void erase_helper(
    PL_INOUT Container& container,
    PL_IN const Type& element_to_remove,
    meta::vectorlike_tag)
{
    container.erase(
        std::remove(container.begin(), container.end(), element_to_remove),
        container.end());
}

/*!
 * \brief helper function used by pl::erase_if. Removes all elements for which
 *        unary_predicate's call operator returns true from a vectorlike
 *        container.
 * \param container The container to remove all elements that satisfy
 *                  unary_predicate from.
 * \param unary_predicate The unary predicate used to determine which elements
 *                        to remove. All elements for which this object's call
 *                        operator returns true will be removed from
 *                        the container.
 **/
template<typename Container, typename UnaryPredicate>
inline void erase_if_helper(
    PL_INOUT Container& container,
    PL_IN UnaryPredicate&& unary_predicate,
    meta::vectorlike_tag)
{
    container.erase(
        std::remove_if(
            container.begin(),
            container.end(),
            std::forward<UnaryPredicate>(unary_predicate)),
        container.end());
}

/*!
 * \brief Helper function used by pl::erase. Removes all occurrences that
 *        compare equal to element_to_remove from a listlike container.
 * \param container The container to remove all occurrences of element_to_remove
 *                  from.
 * \param element_to_remove The element to remove. All elements of the container
 *                          that compare equal to this will be removed from
 *                          the container.
 **/
template<typename Container, typename Type>
inline void erase_helper(
    PL_INOUT Container& container,
    PL_IN const Type& element_to_remove,
    meta::listlike_tag)
{
    container.remove(element_to_remove);
}

/*!
 * \brief helper function used by pl::erase_if. Removes all elements for which
 *        unary_predicate's call operator returns true from a listlike
 *        container.
 * \param container The container to remove all elements that satisfy
 *                  unary_predicate from.
 * \param unary_predicate The unary predicate used to determine which elements
 *                        to remove. All elements for which this object's
 *                        call operator returns true will be removed
 *                        from the container.
 **/
template<typename Container, typename UnaryPredicate>
inline void erase_if_helper(
    PL_INOUT Container& container,
    PL_IN UnaryPredicate&& unary_predicate,
    meta::listlike_tag)
{
    container.remove_if(std::forward<UnaryPredicate>(unary_predicate));
}

/*!
 * \brief Helper function used by pl::erase. Removes all occurrences that
 *        compare equivalent (for ordered containers)
 *        or equal (for unordered containers)
 *        to element_to_remove from an associative container.
 * \param container The container to remove all occurrences equivalent/equal to
 *                  element_to_remove from.
 * \param element_to_remove The element to remove. All elements of the container
 *                          that compare equivalent/equal to this will be
 *                          removed from the container.
 **/
template<typename Container, typename Type>
inline void erase_helper(
    PL_INOUT Container& container,
    PL_IN const Type& element_to_remove,
    meta::associative_tag)
{
    container.erase(element_to_remove);
}

/*!
 * \brief helper function used by pl::erase_if. Removes all elements for which
 *        unary_predicate's call operator returns true from a associative
 *        container.
 * \param container The container to remove all elements that satisfy
 *                  unary_predicate from.
 * \param unary_predicate The unary predicate used to determine which elements
 *                        to remove. All elements for which this object's call
 *                        operator returns true will be removed from
 *                        the container.
 **/
template<typename Container, typename UnaryPredicate>
inline void erase_if_helper(
    PL_INOUT Container& container,
    UnaryPredicate      unary_predicate,
    meta::associative_tag)
{
    const auto end_iter = container.end();

    for (auto iterator = container.begin(); iterator != end_iter;) {
        if (unary_predicate(*iterator)) {
            container.erase(iterator++);
        }
        else {
            ++iterator;
        }
    }
}
} // namespace detail

/*!
 * \brief Function to remove elements from a container.
 * \param container The container to remove elements from.
 * \param element_to_remove The value of the elements to remove.
 *                          If 'container' is a map-like type
 *                          'element_to_remove' must be the 'key' to remove.
 * \note If the container is a std::vector, std::deque, std::forward_list,
 *       std::list, std::unordered_set, std::unordered_map,
 *       std::unordered_multiset or a std::unordered_multimap all elements
 *       that compare equal (using operator==) will be removed from
 *       the container.
 * \note If the container is a std::set, std::map, std::multiset, or a
 *       std::multimap
 *       all pairs whose keys compare equivalent
 *       (using !((element_from_container < element_to_remove) ||
 *                (element_from_container < element_to_remove)))
 *       will be removed from the container.
 * \note For std::set, std::map, std::multiset, std::multimap,
 *       std::unordered_set, std::unordered_map, std::unordered_multiset and
 *       std::unordered_multimap the function expects the key of the pair
 *       to remove from the container. So pass the key of the pair(s) to
 *       remove into element_to_remove.
 **/
template<typename Container, typename Type>
inline void erase(
    PL_INOUT Container& container,
    PL_IN const Type& element_to_remove)
{
    detail::erase_helper(
        container,
        element_to_remove,
        meta::container_traits_category<Container>{});
}

/*!
 * \brief Removes all elements from container that satisfy unaryPredicate.
 * \param container The container to remove elements from.
 * \param unary_predicate The unary predicate that will select elements for
 *                        removal.
 *
 * All elements from container for which the call operator of unary_predicate
 * returns true will be removed from the container. The call operator
 * of unary_predicate is invoked with each element of the container to determine
 * if it is to be removed.
 **/
template<typename Container, typename UnaryPredicate>
inline void erase_if(
    PL_INOUT Container& container,
    PL_IN UnaryPredicate&& unary_predicate)
{
    detail::erase_if_helper(
        container,
        std::forward<UnaryPredicate>(unary_predicate),
        meta::container_traits_category<Container>{});
}
} // namespace algo
} // namespace pl
#endif // INCG_PL_ALGO_ERASE_HPP
