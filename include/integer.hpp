/*! \file integer.hpp
 *  \brief This header defines various fixed size integer types.
**/

#ifndef INCG_PL_INTEGER_HPP
#define INCG_PL_INTEGER_HPP
#include <cstdint> // std::int8_t, std::int16_t, std::int32_t, std::int64_t, std::uint8_t, std::uint16_t, std::uint32_t, std::uint64_t
namespace pl
{
namespace detail
{
template <int Bytes>
struct IntImpl;

template <>
struct IntImpl<1>
{
    using type = std::int8_t;
};

template <>
struct IntImpl<2>
{
    using type = std::int16_t;
};

template <>
struct IntImpl<4>
{
    using type = std::int32_t;
};

template <>
struct IntImpl<8>
{
    using type = std::int64_t;
};

template <int Bytes>
struct UintImpl;

template <>
struct UintImpl<1>
{
    using type = std::uint8_t;
};

template <>
struct UintImpl<2>
{
    using type = std::uint16_t;
};

template <>
struct UintImpl<4>
{
    using type = std::uint32_t;
};

template <>
struct UintImpl<8>
{
    using type = std::uint64_t;
};
} // namespace detail

/*!
 * \brief Fixed size signed integer type.
 * \note The only valid values for the template parameter are 1, 2, 4 and 8.
**/
template <int Bytes>
using Int = typename detail::IntImpl<Bytes>::type;

/*!
 * \brief Fixed size unsigned integer type.
 * \note The only valid values for the template parameter are 1, 2, 4 and 8.
**/
template <int Bytes>
using Uint = typename detail::UintImpl<Bytes>::type;
} // namespace pl
#endif // INCG_PL_INTEGER_HPP
