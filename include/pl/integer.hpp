/*!
 * \file integer.hpp
 * \brief This header defines various fixed size integer types.
**/
#ifndef INCG_PL_INTEGER_HPP
#define INCG_PL_INTEGER_HPP
#include <cstdint> // std::int8_t, std::int16_t, std::int32_t, std::int64_t, std::uint8_t, std::uint16_t, std::uint32_t, std::uint64_t

namespace pl
{
namespace detail
{
template <int Bits>
struct IntImpl;

template <>
struct IntImpl<8>
{
    using type = std::int8_t;
};

template <>
struct IntImpl<16>
{
    using type = std::int16_t;
};

template <>
struct IntImpl<32>
{
    using type = std::int32_t;
};

template <>
struct IntImpl<64>
{
    using type = std::int64_t;
};

template <int Bits>
struct UintImpl;

template <>
struct UintImpl<8>
{
    using type = std::uint8_t;
};

template <>
struct UintImpl<16>
{
    using type = std::uint16_t;
};

template <>
struct UintImpl<32>
{
    using type = std::uint32_t;
};

template <>
struct UintImpl<64>
{
    using type = std::uint64_t;
};
} // namespace detail

/*!
 * \brief Fixed size signed integer type.
 * \note The only valid values for the template parameter are 8, 16, 32 and 64.
**/
template <int Bits>
using Int = typename detail::IntImpl<Bits>::type;

/*!
 * \brief Fixed size unsigned integer type.
 * \note The only valid values for the template parameter are 8, 16, 32 and 64.
**/
template <int Bits>
using Uint = typename detail::UintImpl<Bits>::type;
} // namespace pl
#endif // INCG_PL_INTEGER_HPP
