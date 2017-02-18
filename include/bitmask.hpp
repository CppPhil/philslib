/*! \file bitmask.hpp
 *  \brief Defines a macro to allow the user to enable bitmask operators for
 *         scoped enum types.
**/

#ifndef INCG_PL_BITMASK_HPP
#define INCG_PL_BITMASK_HPP
#include "macros.hpp" // PL_INOUT
#include <type_traits> // std::enable_if_t, std::underlying_type_t

/*!
 * \def PL_ENABLE_BITMASK_OPERATORS(ScopedEnumType)
 * \brief Enables bitmask operators for the scoped enum type passed in.
 * \warning Must appear in the same namespace the scoped enum type passed in
 *          is defined in.
 * \example namespace user
 *          {
 *              enum class ScopedEnum : std::uint8_t
 *              {
 *                  optionA = 0B1U,  // 1
 *                  optionB = 0B10U, // 2
 *                  optionC = 0B100U // 4
 *              };
 *              PL_ENABLE_BITMASK_OPERATORS(ScopedEnum);
 *          }
 *          int main()
 *          {
 *              std::cout << std::boolalpha;
 *              auto enm = user::ScopedEnum::optionA | user::ScopedEnum::optionB; // enm is A and B toggled on
 *              enm &= ~user::ScopedEnum::optionA; // toggle A off
 *              std::cout << (enm == user::ScopedEnum::optionB) // it's just B now
 *                        << std::endl;
 *          }
**/

namespace pl
{
namespace bitmask_detail
{
template <typename ScopedEnum>
constexpr bool enableBitmaskOperators(ScopedEnum)
{
    return false;
}

template <typename ScopedEnum>
constexpr std::enable_if_t<enableBitmaskOperators(ScopedEnum{ }), ScopedEnum>
operator|(ScopedEnum lhs, ScopedEnum rhs)
{
    using Underlying = std::underlying_type_t<ScopedEnum>;
    return static_cast<ScopedEnum>(
        static_cast<Underlying>(lhs) | static_cast<Underlying>(rhs));
}

template <typename ScopedEnum>
constexpr std::enable_if_t<enableBitmaskOperators(ScopedEnum{ }), ScopedEnum>
operator&(ScopedEnum lhs, ScopedEnum rhs)
{
    using Underlying = std::underlying_type_t<ScopedEnum>;
    return static_cast<ScopedEnum>(
        static_cast<Underlying>(lhs) & static_cast<Underlying>(rhs));
}

template <typename ScopedEnum>
constexpr std::enable_if_t<enableBitmaskOperators(ScopedEnum{ }), ScopedEnum>
operator^(ScopedEnum lhs, ScopedEnum rhs)
{
    using Underlying = std::underlying_type_t<ScopedEnum>;
    return static_cast<ScopedEnum>(
        static_cast<Underlying>(lhs) ^ static_cast<Underlying>(rhs));
}

template <typename ScopedEnum>
constexpr std::enable_if_t<enableBitmaskOperators(ScopedEnum{ }), ScopedEnum>
operator~(ScopedEnum lhs)
{
    using Underlying = std::underlying_type_t<ScopedEnum>;
    return static_cast<ScopedEnum>(
        ~static_cast<Underlying>(lhs));
}

template <typename ScopedEnum>
constexpr std::enable_if_t<enableBitmaskOperators(ScopedEnum{ }), ScopedEnum &>
operator|=(PL_INOUT ScopedEnum &lhs, ScopedEnum rhs)
{
    using Underlying = std::underlying_type_t<ScopedEnum>;
    lhs = static_cast<ScopedEnum>(
        static_cast<Underlying>(lhs) | static_cast<Underlying>(rhs));
    return lhs;
}

template <typename ScopedEnum>
constexpr std::enable_if_t<enableBitmaskOperators(ScopedEnum{ }), ScopedEnum &>
operator&=(PL_INOUT ScopedEnum &lhs, ScopedEnum rhs)
{
    using Underlying = std::underlying_type_t<ScopedEnum>;
    lhs = static_cast<ScopedEnum>(
        static_cast<Underlying>(lhs) & static_cast<Underlying>(rhs));
    return lhs;
}

template <typename ScopedEnum>
constexpr std::enable_if_t<enableBitmaskOperators(ScopedEnum{ }), ScopedEnum &>
operator^=(PL_INOUT ScopedEnum &lhs, ScopedEnum rhs)
{
    using Underlying = std::underlying_type_t<ScopedEnum>;
    lhs = static_cast<ScopedEnum>(
        static_cast<Underlying>(lhs) ^ static_cast<Underlying>(rhs));
    return lhs;
}
} // namespace bitmask_detail
} // namespace pl

#define PL_ENABLE_BITMASK_OPERATORS(ScopedEnumType) \
    constexpr bool enableBitmaskOperators(ScopedEnumType) \
    { \
        return true; \
    } \
    using ::pl::bitmask_detail::operator|; \
    using ::pl::bitmask_detail::operator|=; \
    using ::pl::bitmask_detail::operator&=; \
    using ::pl::bitmask_detail::operator&; \
    using ::pl::bitmask_detail::operator^; \
    using ::pl::bitmask_detail::operator^=; \
    using ::pl::bitmask_detail::operator~
#endif // INCG_PL_BITMASK_HPP
