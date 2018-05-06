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
 * \file iterate_reversed.hpp
 * \brief Exports the iterateReversed function that can be used to
 *        iterate over a container in reversed order in a range based for loop.
**/
#ifndef INCG_PL_ITERATE_REVERSED_HPP
#define INCG_PL_ITERATE_REVERSED_HPP
#include "annotations.hpp" // PL_IN
#include "begin_end.hpp"   // pl::begin, ...

namespace pl {
namespace detail {
/*!
 * \brief Type used by pl::iterateReversed. Used for non-const containers.
**/
template <typename Container>
class RevForAdapter final {
public:
    using this_type = RevForAdapter;

    /*!
     * \brief Creates a pl::detail::RevForAdapter by storing a non-const lvalue
     *        reference to the container passed in.
     * \param container The container to iterate over.
    **/
    explicit RevForAdapter(PL_IN Container& container) : m_container{container}
    {
    }

    /*!
     * \brief Returns the reverse begin iterator to the container.
     * \return The reverse begin iterator to the container.
     * \note This function is called by the range based for loop.
    **/
    auto begin() -> decltype(auto) { return ::pl::rbegin(m_container); }
    /*!
     * \brief Returns the reverse end iterator to the container.
     * \return The reverse end iterator to the container.
     * \note This function is called by the range based for loop.
    **/
    auto end() -> decltype(auto) { return ::pl::rend(m_container); }
private:
    Container& m_container; //!< reference to the container to iterate over.
};

/*!
 * \brief Type used by pl::iterateReversed. Used for const containers.
**/
template <typename Container>
class RevForAdapterConst final {
public:
    using this_type = RevForAdapterConst;

    /*!
     * \brief Creates a pl::detail::RevForAdapterConst by storing a const lvalue
     *        reference to the container passed in.
     * \param container The container to iterate over.
    **/
    explicit RevForAdapterConst(PL_IN const Container& container)
        : m_container{container}
    {
    }

    /*!
     * \brief Returns the const reverse begin iterator to the container.
     * \return The const reverse begin iterator to the container.
     * \note This function is called by the range based for loop.
    **/
    auto begin() const -> decltype(auto) { return ::pl::crbegin(m_container); }
    /*!
     * \brief Returns the const reverse end iterator to the container.
     * \return The const reverse end iterator to the container.
     * \note This function is called by the range based for loop.
    **/
    auto end() const -> decltype(auto) { return ::pl::crend(m_container); }
private:
    const Container& m_container; //!< const lvalue reference to the container
                                  //!to iterate over.
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
detail::RevForAdapter<Container> iterateReversed(PL_IN Container& container)
{
    return detail::RevForAdapter<Container>{container};
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
detail::RevForAdapterConst<Container> iterateReversed(
    PL_IN const Container& container)
{
    return detail::RevForAdapterConst<Container>{container};
}
} // namespace pl
#endif // INCG_PL_ITERATE_REVERSED_HPP
