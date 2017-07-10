/*!
 * \file iterate_reversed.hpp
 * \brief Exports the iterateReversed function that can be used to
 *        iterate over a container in reversed order in a range based for loop.
**/
#ifndef INCG_PL_ITERATE_REVERSED_HPP
#define INCG_PL_ITERATE_REVERSED_HPP
#include "macros.hpp" // PL_IN
#include "begin_end.hpp" // pl::begin, ...

namespace pl
{
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
#endif // INCG_PL_ITERATE_REVERSED_HPP
