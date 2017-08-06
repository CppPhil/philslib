/*!
 * \file invoke.hpp
 * \brief Exports the invoke function template.
**/
#ifndef INCG_PL_INVOKE_HPP
#define INCG_PL_INVOKE_HPP
#include "annotations.hpp" // PL_IN
#include <ciso646> // not
#include <type_traits> // std::enable_if_t, std::is_member_pointer, std::decay_t, std::result_of_t
#include <functional> // std::mem_fn
#include <utility> // std::forward

namespace pl
{
/*!
 * \brief Calls 'callable' with 'args'.
 * \param callable The callable object to be invoked.
 * \param args The arguments to pass to 'callable'.
 * \return The result of invoking 'callable' with 'args'.
 *
 * Calls the callable 'callable' with 'args'.
 * Offers a uniform interface to invoke free functions,
 * function objects (including lambdas), member function pointers,
 * as well as access non-static data members through member object pointers.
**/
template <typename Callable, typename ...Args>
auto invoke(PL_IN Callable &&callable, PL_IN Args &&...args)
    noexcept(noexcept(std::mem_fn(callable)(std::forward<Args>(args) ...)))
    -> std::enable_if_t<
           std::is_member_pointer<std::decay_t<Callable>>::value,
           std::result_of_t<Callable &&(Args &&...)>>
{
    return std::mem_fn(callable)(std::forward<Args>(args) ...);
}

/*!
* \brief Calls 'callable' with 'args'.
* \param callable The callable object to be invoked.
* \param args The arguments to pass to 'callable'.
* \return The result of invoking 'callable' with 'args'.
*
* Calls the callable 'callable' with 'args'.
* Offers a uniform interface to invoke free functions,
* function objects (including lambdas), member function pointers,
* as well as access non-static data members through member object pointers.
**/
template <typename Callable, typename ...Args>
auto invoke(PL_IN Callable &&callable, PL_IN Args &&...args)
    noexcept(noexcept(std::forward<Callable>(callable)(std::forward<Args>(args) ...)))
    -> std::enable_if_t<
           not std::is_member_pointer<std::decay_t<Callable>>::value,
           std::result_of_t<Callable &&(Args &&...)>>
{
    return std::forward<Callable>(callable)(std::forward<Args>(args) ...);
}
} // namespace pl
#endif // INCG_PL_INVOKE_HPP
