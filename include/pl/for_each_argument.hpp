/*!
 * \file for_each_argument.hpp
 * \brief Exports the forEachArgument function template.
**/
#ifndef INCG_PL_FOR_EACH_ARGUMENT_HPP
#define INCG_PL_FOR_EACH_ARGUMENT_HPP
#include "annotations.hpp" // PL_IN
#include "invoke.hpp" // pl::invoke
#include <initializer_list> // std::initializer_list
#include <utility> // std::forward

namespace pl
{
/*!
 * \brief Calls a unary callable with every argument in the template type
 *        parameter pack individually.
 * \param callable The unary callable to be invoked with every argument of
 *        the template type parameter pack.
 * \param args The arguments that callable will be called with. callable will
 *        be called with each and every element of this template type
 *        parameter pack individually one after the other.
 * \example pl::forEachArgument([](const auto &e) { std::cout << e << ' ';},
 *                              1, 2.1, "hello", .3F, 44U, std::string{ "world" });
**/
template <typename Callable, typename ...Args>
void forEachArgument(PL_IN Callable &&callable, PL_IN Args &&...args)
{
    static_cast<void>(
        std::initializer_list<int>{
            ((void)::pl::invoke(callable, std::forward<Args>(args)), 0)...
        }
    );
}
} // namespace pl
#endif // INCG_PL_FOR_EACH_ARGUMENT_HPP
