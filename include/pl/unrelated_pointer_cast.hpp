/*!
 * \file unrelated_pointer_cast.hpp
 * \brief Exports the unrelated_pointer_cast function.
**/
#ifndef INCG_PL_UNRELATED_POINTER_CAST_HPP
#define INCG_PL_UNRELATED_POINTER_CAST_HPP
#include "macros.hpp" // PL_IN_OPT
#include <type_traits> // std::is_pointer, std::is_const, std::remove_pointer_t

namespace pl
{
/*!
 * \brief Casts a raw pointer type to another unrelated pointer type.
 *        This partially replaces reinterpret_cast, only use reinterpret_cast
 *        for pointer to integer (and vice versa) conversions.
 * \param p The pointer to cast to CastTo.
 * \return The result of casting p to type CastTo
 * \note Note that all raw pointers without low level constness
 *       are implicitly convertible to void *, so you can just pass your raw
 *       pointer in as is.
 * \note The type to cast to called CastTo must be a raw pointer type.
 * \note This is the overload for pointers without low level constness.
 * \note You must supply the template type parameter CastTo.
 * \warning Like with reinterpret_cast it is easy to violate the strict aliasing rules
 *          with this function. Two pointers may never refer to the same object
 *          if they have different types, unless at least one of the pointers
 *          is cv void *, cv char *, cv unsigned char *, cv std::byte * (since C++17),
 *          or there there is a based/derived relation between the pointed to types
 *          or there merely is an unsigned/signed mismatch between the pointed to types.
 *          Note that std::uint8_t and std::int8_t are not required to be exceptions!
 *          This also makes common code like
 *          // assuming unsigned long long and double have the same width in bytes
 *          double d;
 *          unsigned long long ull = 0;
 *          d = *reinterpret_cast<double *>(&ull);
 *          undefined behavior.
 *          Note that in many cases you can use std::memcpy, defined in <cstring>
 *          instead.
 *          Basically any usage of reinterpret_cast and pl::unrelated_pointer_cast
 *          should be suspect.
**/
template <typename CastTo>
CastTo unrelated_pointer_cast(PL_IN_OPT void *p)
{
    static_assert(std::is_pointer<CastTo>::value,
        "The type to cast to must be a raw pointer type in pl::unrelated_pointer_cast (non-const)");

    return static_cast<CastTo>(p);
}

/*!
 * \brief Casts a raw pointer type to another unrelated raw pointer type.
 *        This partially replaces reinterpret_cast, only use reinterpret_cast
 *        for pointer to integer (and vice versa) conversions.
 * \param p The raw pointer to be casted to type CastTo.
 * \return The result of casting p to type CastTo.
 * \note Note that all raw pointers with low level constness
 *       are implicitly convertible to const void *, so you can just pass
 *       your raw pointer in as is.
 * \note CastTo must be a raw pointer type.
 * \note CastTo must have low level constness
 * \note This is the overload for raw pointers with low level constness.
 * \note You must supply the template type parameter CastTo.
 * \warning Like with reinterpret_cast it is easy to violate the strict aliasing rules
 *          with this function. Two pointers may never refer to the same object
 *          if they have different types, unless at least one of the pointers
 *          is cv void *, cv char *, cv unsigned char *, cv std::byte * (since C++17),
 *          or there there is a based/derived relation between the pointed to types
 *          or there merely is an unsigned/signed mismatch between the pointed to types.
 *          Note that std::uint8_t and std::int8_t are not required to be exceptions!
 *          This also makes common code like
 *          // assuming unsigned long long and double have the same width in bytes
 *          double d;
 *          unsigned long long ull = 0;
 *          d = *reinterpret_cast<double *>(&ull);
 *          undefined behavior.
 *          Note that in many cases you can use std::memcpy, defined in <cstring>
 *          instead.
 *          Basically any usage of reinterpret_cast and pl::unrelated_pointer_cast
 *          should be suspect.
**/
template <typename CastTo>
CastTo unrelated_pointer_cast(PL_IN_OPT const void *p)
{
    static_assert(std::is_pointer<CastTo>::value,
        "The type to cast to must be a raw pointer type in pl::unrelated_pointer_cast (const)");
    static_assert(std::is_const<std::remove_pointer_t<CastTo>>::value,
        "The type to cast to must have low level constness in pl::unrelated_pointer_cast (const)");

    return static_cast<CastTo>(p);
}
} // namespace pl
#endif // INCG_PL_UNRELATED_POINTER_CAST_HPP
