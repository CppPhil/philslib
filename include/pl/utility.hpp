/*!
 * \file utility.hpp
 * \brief Defines various general utilities.
**/
#ifndef INCG_PL_UTILITY_HPP
#define INCG_PL_UTILITY_HPP
#include "macros.hpp" // PL_INOUT, PL_UNUSED
#include <cstdint> // std::uint8_t
#include <initializer_list> // std::initializer_list
#include <utility> // std::forward
#include <cstddef> // std::nullptr_t
#include <ciso646> // not

namespace pl
{
/*!
 * \brief Generic type of function pointer.
 * \warning The function pointer stored in a variable of this type must be
 *          cast back to its actual type before being used!
 * \note It is illegal to store function pointers in non-function pointer types
 *       like void *.
 * \example #include <pl/utility.hpp>
 *          #include <iostream>
 *
 *          namespace app
 *          {
 *          void myFunction(void *p)
 *          {
 *              std::cout << "hello address: " << p << '\n';
 *          }
 *          } // namespace app
 *
 *          int main()
 *          {
 *              // store the function pointer in a generic type of function pointer.
 *              pl::FunctionPointer p = reinterpret_cast<pl::FunctionPointer>(&app::myFunction);
 *
 *              // to use it must be cast back to its actual type.
 *              reinterpret_cast<void (*)(void *)>(p)(nullptr);
 *
 *              std::cout << std::flush;
 *          }
 *
 * May be used to store pointers to functions. To call the function stored in
 * a variable of this type you must first cast it back to its actual type.
 * This type serves as a generic type of function pointer.
**/
using FunctionPointer = void (*)();

/*!
 * \brief Toggles the boolean passed in.
 * \param b The boolean to be toggled.
 * \return The new value of the the boolean passed in.
 *
 * If the boolean passed in is true it will be assigned false and the
 * value returned will be false.
 * If the boolean passed in is false it will be assigned true and the
 * value return will be true.
**/
bool toggleBool(PL_INOUT bool &b);

/*!
 * \brief Converts a character to an integer.
 * \param ch The character to be converted.
 * \return Returns a value of [0..9] for a character of the range ['0'..'9'].
 * \warning Do not pass in characters outside of the range ['0'..'9'].
**/
std::uint8_t charToInt(unsigned char ch);

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
void forEachArgument(Callable &&callable, Args &&...args)
{
    PL_UNUSED(
        std::initializer_list<int>{
            (callable(std::forward<Args>(args)), 0)...
        }
    );
}

/*!
 * \brief Determines if the object passed into the parameter is 'null' or not.
 * \param object The object to check against null.
 * \return true if the object passed into the parameter is 'null'; false otherwise.
 * \note The object passed into the parameter is compared to nullptr using operator==
 *       to determine the result of this function.
**/
template <typename PointerLike>
constexpr bool isNull(const PointerLike &object) noexcept
{
    return object == nullptr;
}

/*!
 * \brief Determines if the object passed into the parameter is not null.
 * \param object The object to check.
 * \return true if the object compares false to nullptr; false otherwise.
 * \note Calls isNull and negates the result. isNull internally uses
 *       operator== to compare the object with nullptr.
**/
template <typename PointerLike>
constexpr bool isNotNull(const PointerLike &object) noexcept
{
    return not isNull(object);
}
} // namespace pl
#endif // INCG_PL_UTILITY_HPP
