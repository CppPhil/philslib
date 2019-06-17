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
 * \file begin_end.hpp
 * \brief Exports functions and macros to fetch begin and end iterators
 *        as well as reverse_iterators.
 **/
#ifndef INCG_PL_BEGIN_END_HPP
#define INCG_PL_BEGIN_END_HPP
#include "annotations.hpp"              // PL_IN
#include "meta/disable_if.hpp"          // pl::meta::disable_if_t
#include "meta/is_initializer_list.hpp" // pl::meta::is_initializer_list
#include "meta/remove_cvref.hpp"        // pl::meta::remove_cvref_t
#include <ciso646>                      // or
#include <cstddef>                      // std::size_t
#include <initializer_list>             // std::initializer_list
#include <iterator>                     // std::reverse_iterator
#include <type_traits>                  // std::is_array

namespace pl {
/*!
 * \brief Returns an iterator to the beginning of the container.
 * \param container The container for which to get an iterator to its
 *        beginning.
 * \return An iterator to the beginning of container.
 **/
template<typename Container>
constexpr auto begin(PL_IN Container& container) noexcept -> meta::disable_if_t<
    std::is_array<meta::remove_cvref_t<Container>>::value,
    decltype(container.begin())>
{
    return container.begin();
}

/*!
 * \brief Returns an iterator to the beginning of the array.
 * \param array The array for which to get an iterator to its beginning.
 * \return An iterator to the beginning of array.
 **/
template<typename Type, std::size_t Size>
constexpr Type* begin(PL_IN Type (&array)[Size]) noexcept
{
    return array;
}

/*!
 * \brief Returns a const_iterator to the beginning of the container.
 * \param container The container for which to get a const_iterator to its
 *        beginning.
 * \return A const_iterator to the beginning of the container.
 **/
template<typename Container>
constexpr auto cbegin(PL_IN const Container& container) noexcept
    -> decltype(auto)
{
    return ::pl::begin(container);
}

/*!
 * \brief Returns the end iterator of a container.
 * \param container The container to get the end iterator for.
 * \return The end iterator of container.
 **/
template<typename Container>
constexpr auto end(PL_IN Container& container) noexcept -> meta::disable_if_t<
    std::is_array<meta::remove_cvref_t<Container>>::value,
    decltype(container.end())>
{
    return container.end();
}

/*!
 * \brief Returns the end iterator of an array.
 * \param array The array to get the end iterator for.
 * \return The end iterator of array.
 **/
template<typename Type, std::size_t Size>
constexpr Type* end(PL_IN Type (&array)[Size]) noexcept
{
    return ::pl::begin(array) + Size;
}

/*!
 * \brief Returns the end const_iterator of a container.
 * \param container The container to get the end const_iterator for.
 * \return The end const_iterator of container.
 **/
template<typename Container>
constexpr auto cend(PL_IN const Container& container) noexcept -> decltype(auto)
{
    return ::pl::end(container);
}

/*!
 * \brief Returns the begin reverse_iterator of a container.
 * \param container The container to get the begin reverse_iterator for.
 * \return The begin reverse_iterator of container.
 **/
template<typename Container>
constexpr auto
rbegin(PL_IN Container& container) noexcept -> meta::disable_if_t<
    std::is_array<meta::remove_cvref_t<Container>>::value
        or meta::is_initializer_list<meta::remove_cvref_t<Container>>::value,
    decltype(container.rbegin())>
{
    return container.rbegin();
}

/*!
 * \brief Returns the begin reverse_iterator of an initializer_list.
 * \param il The initializer_list to get the begin reverse_iterator for.
 * \return The begin reverse_iterator of 'il'.
 **/
template<typename Element>
constexpr std::reverse_iterator<const Element*> rbegin(
    std::initializer_list<Element> il) noexcept
{
    return std::reverse_iterator<const Element*>{il.end()};
}

/*!
 * \brief Returns the begin reverse_iterator of an array.
 * \param array The array to get the begin reverse_iterator for.
 * \return The begin reverse_iterator of array.
 **/
template<typename Type, std::size_t Size>
constexpr std::reverse_iterator<Type*> rbegin(
    PL_IN Type (&array)[Size]) noexcept
{
    return std::reverse_iterator<Type*>{array + Size};
}

/*!
 * \brief Returns the begin const_reverse_iterator of a container.
 * \param container THe container to get the begin const_reverse_iterator for.
 * \return The begin const_reverse_iterator of container.
 **/
template<typename Container>
constexpr auto crbegin(PL_IN const Container& container) noexcept
    -> decltype(auto)
{
    return ::pl::rbegin(container);
}

/*!
 * \brief Returns the end reverse_iterator of a container.
 * \param container The container to get the end reverse_iterator for.
 * \return The end reverse_iterator of container.
 **/
template<typename Container>
constexpr auto rend(PL_IN Container& container) noexcept -> meta::disable_if_t<
    std::is_array<meta::remove_cvref_t<Container>>::value
        or meta::is_initializer_list<meta::remove_cvref_t<Container>>::value,
    decltype(container.rend())>
{
    return container.rend();
}

/*!
 * \brief Returns the end reverse_iterator of an initializer_list.
 * \param il The initializer_list to get the end reverse_iterator for.
 * \return The end reverse_iterator of 'il'.
 **/
template<typename Element>
constexpr std::reverse_iterator<const Element*> rend(
    std::initializer_list<Element> il) noexcept
{
    return std::reverse_iterator<const Element*>{il.begin()};
}

/*!
 * \brief Returns the end reverse_iterator of an array.
 * \param array The array to get the end reverse_iterator for.
 * \return The end reverse_iterator of array.
 **/
template<typename Type, std::size_t Size>
constexpr std::reverse_iterator<Type*> rend(PL_IN Type (&array)[Size]) noexcept
{
    return std::reverse_iterator<Type*>{array};
}

/*!
 * \brief Returns the end const_reverse_iterator of a container.
 * \param container The container to get the end const_reverse_iterator for.
 * \return The end const_reverse_iterator of container.
 **/
template<typename Container>
constexpr auto crend(PL_IN const Container& container) noexcept
    -> decltype(auto)
{
    return ::pl::rend(container);
}
} // namespace pl

/*!
 * \def PL_BEGIN_END(cont)
 * \brief Macro that can be used to call a function that expects begin and
 *        end iterators to cont.
 **/
#define PL_BEGIN_END(cont) ::pl::begin(cont), ::pl::end(cont)

/*!
 * \def PL_CBEGIN_CEND(cont)
 * \brief Macro that can be used to call a function that expects cbegin and
 *        cend iterators to cont.
 **/
#define PL_CBEGIN_CEND(cont) ::pl::cbegin(cont), ::pl::cend(cont)

/*!
 * \def PL_RBEGIN_REND(cont)
 * \brief Macro that can be used to call a function that expects rbegin and
 *        rend iterators to cont.
 **/
#define PL_RBEGIN_REND(cont) ::pl::rbegin(cont), ::pl::rend(cont)

/*!
 * \def PL_CRBEGIN_CREND(cont)
 * \brief Macro that can be used to call a function that expects crbegin and
 *        crend iterators to cont.
 **/
#define PL_CRBEGIN_CREND(cont) ::pl::crbegin(cont), ::pl::crend(cont)
#endif // INCG_PL_BEGIN_END_HPP
