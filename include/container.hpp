/*! \file container.hpp
 *  \brief Defines a few utility functions for working with containers.
**/

#ifndef INCG_PL_CONTAINER_HPP
#define INCG_PL_CONTAINER_HPP
#include "macros.hpp" // PL_IN
#include <cstddef> // std::size_t
#include <memory> // std::addressof
#include <array> // std::array
#include <type_traits> // std::common_type_t
#include <utility> // std::forward
namespace pl
{
/*!
 * \brief Gets the first element of a container.
 * \param cont The container to get the first element of.
 * \return The first element of the container.
 * \warning Undefined behavior occurs if the container passed is empty.
**/
template <typename Cont>
auto front(PL_IN Cont &cont) -> decltype(auto)
{
    return cont.front();
}

/*!
 * \brief Gets the first element of a C-Array.
 * \param arr The C-Array to get the first element of.
 * \return The first element of the C-Array.
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
auto data(PL_IN Cont &cont) -> decltype(auto)
{
    return cont.data();
}

/*!
 * \brief Function to get a pointer to the first element of a C-Array.
 * \param arr The C-Array for which
 *        to get the pointer to its first element from.
**/
template <typename Type, std::size_t Size>
auto data(PL_IN Type (&arr)[Size]) -> decltype(auto)
{
    return std::addressof(arr[0]);
}

/*!
 * \brief Creates a std::array from a template type parameter pack.
 * \param args The arguments to construct the std::array returned from.
 * \return The resulting std::array.
 * \note The resulting std::array will use the common type for all of its
 *       elements. Some of the values passed in may be implicitly
 *       converted to that common type.
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
} // namespace pl
#endif // INCG_PL_CONTAINER_HPP
