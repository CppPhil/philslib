/*!
 * \file erase.hpp
 * \brief Exports the erase and eraseIf algorithms that implement the
 *        erase remove idiom.
**/
#ifndef INCG_PL_ALGO_ERASE_HPP
#define INCG_PL_ALGO_ERASE_HPP
#include "../annotations.hpp" // PL_IN, PL_INOUT
#include "../meta/container_traits.hpp" // pl::meta::vectorlike_tag, pl::meta::listlike_tag, pl::meta::associative_tag, pl::meta::container_traits_category
#include <utility> // std::forward
#include <algorithm> // std::remove, std::remove_if

namespace pl
{
namespace algo
{
namespace detail
{
/*!
 * \brief Helper function used by pl::erase. Removes all occurences that
 *        compare equal to elementToRemove from a vectorlike container.
 * \param container The container to remove all occurences of elementToRemove from.
 * \param elementToRemove The element to remove. All elements of the container that
 *        compare equal to this will be removed from the container.
**/
template <typename Container, typename Type>
inline void
eraseHelper(PL_INOUT Container &container, PL_IN const Type &elementToRemove,
            meta::vectorlike_tag)
{
    container.erase(std::remove(container.begin(), container.end(),
                                elementToRemove),
                    container.end());
}

/*!
 * \brief helper function used by pl::eraseIf. Removes all elements for which
 *        unaryPredicate's call operator returns true from a vectorlike container.
 * \param container The container to remove all elements that satisfy unaryPredicate from.
 * \param unaryPredicate The unary predicate used to determine which elements to remove.
 *        All elements for which this object's call operator returns true will be removed
 *        from the container.
**/
template <typename Container, typename UnaryPredicate>
inline void
eraseIfHelper(PL_INOUT Container &container,
              PL_IN UnaryPredicate &&unaryPredicate, meta::vectorlike_tag)
{
    container.erase(
        std::remove_if(container.begin(), container.end(),
                       std::forward<UnaryPredicate>(unaryPredicate)),
        container.end()
    );
}

/*!
 * \brief Helper function used by pl::erase. Removes all occurences that
 *        compare equal to elementToRemove from a listlike container.
 * \param container The container to remove all occurences of elementToRemove from.
 * \param elementToRemove The element to remove. All elements of the container that
 *        compare equal to this will be removed from the container.
**/
template <typename Container, typename Type>
inline void
eraseHelper(PL_INOUT Container &container, PL_IN const Type &elementToRemove,
            meta::listlike_tag)
{
    container.remove(elementToRemove);
}

/*!
 * \brief helper function used by pl::eraseIf. Removes all elements for which
 *        unaryPredicate's call operator returns true from a listlike container.
 * \param container The container to remove all elements that satisfy unaryPredicate from.
 * \param unaryPredicate The unary predicate used to determine which elements to remove.
 *        All elements for which this object's call operator returns true will be removed
 *        from the container.
**/
template <typename Container, typename UnaryPredicate>
inline void
eraseIfHelper(PL_INOUT Container &container,
              PL_IN UnaryPredicate &&unaryPredicate, meta::listlike_tag)
{
    container.remove_if(std::forward<UnaryPredicate>(unaryPredicate));
}

/*!
 * \brief Helper function used by pl::erase. Removes all occurences that
 *        compare equivalent (for ordered containers)
 *        or equal (for unorderede containers)
 *        to elementToRemove from an associative container.
 * \param container The container to remove all occurences equivalent/equal to elementToRemove from.
 * \param elementToRemove The element to remove. All elements of the container that
 *        compare equivalent/equal to this will be removed from the container.
**/
template <typename Container, typename Type>
inline void
eraseHelper(PL_INOUT Container &container, PL_IN const Type &elementToRemove,
            meta::associative_tag)
{
    container.erase(elementToRemove);
}

/*!
 * \brief helper function used by pl::eraseIf. Removes all elements for which
 *        unaryPredicate's call operator returns true from a associative container.
 * \param container The container to remove all elements that satisfy unaryPredicate from.
 * \param unaryPredicate The unary predicate used to determine which elements to remove.
 *        All elements for which this object's call operator returns true will be removed
 *        from the container.
**/
template <typename Container, typename UnaryPredicate>
inline void
eraseIfHelper(PL_INOUT Container &container, UnaryPredicate unaryPredicate,
              meta::associative_tag)
{
    const auto endIter = container.end();
    for (auto iterator = container.begin(); iterator != endIter;) {
        if (unaryPredicate(*iterator)) {
            container.erase(iterator++);
        } else {
            ++iterator;
        }
    }
}
} // namespace detail

/*!
 * \brief Function to remove elements from a container.
 * \param container The container to remove elements from.
 * \param elementToRemove The value of the elements to remove.
 * \note If the container is a std::vector, std::deque, std::forward_list,
 *       std::list, std::unordered_set, std::unordered_map, std::unordered_multiset or a
 *       std::unordered_multimap all elements that compare equal
 *       (using operator==) will be removed from the container.
 * \note If the container is a std::set, std::map, std::multiset, or a std::multimap
 *       all pairs whose keys compare equivalent
 *       (using !((elementFromContainer < elementToRemove) || (elementFromContainer < elementToRemove)))
 *       will be removed from the container.
 * \note For std::set, std::map, std::multiset, std::multimap,
 *       std::unordered_set, std::unordered_map, std::unordered_multiset and
 *       std::unordered_multimap the function expects the key of the pair
 *       to remove from the container. So pass the key of the pair(s) to
 *       remove into elementToRemove.
**/
template <typename Container, typename Type>
inline void erase(PL_INOUT Container &container,
                  PL_IN const Type &elementToRemove)
{
    detail::eraseHelper(container, elementToRemove,
                        meta::container_traits_category<Container>{ });
}

/*!
 * \brief Removes all elements from container that satisfy unaryPredicate.
 * \param container The container to remove elements from.
 * \param unaryPredicate The unary predicate that will select elements for removal.
 *
 * All elements from container for which the call operator of unaryPredicate
 * returns true will be removed from the container. The call operator
 * of unaryPredicate is invoked with each element of the container to determine
 * if it is to be removed.
**/
template <typename Container, typename UnaryPredicate>
inline void eraseIf(PL_INOUT Container &container,
                    PL_IN UnaryPredicate &&unaryPredicate)
{
    detail::eraseIfHelper(
        container,
        std::forward<UnaryPredicate>(unaryPredicate),
        meta::container_traits_category<Container>{ }
    );
}
} // namespace algo
} // namespace pl
#endif // INCG_PL_ALGO_ERASE_HPP