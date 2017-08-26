/*!
 * \file random_number_generator.hpp
 * \brief Exports the RandomNumberGenerator type.
**/
#ifndef INCG_PL_RANDOM_NUMBER_GENERATOR_HPP
#define INCG_PL_RANDOM_NUMBER_GENERATOR_HPP
#include "assert.hpp" // PL_DBG_CHECK_PRE
#include "no_macro_substitution.hpp" // PL_NO_MACRO_SUBSTITUTION
#include "meta/identity.hpp" // pl::meta::identity_t
#include "meta/disable_if.hpp" // pl::meta::disable_if_t
#include "meta/unqualified.hpp" // pl::meta::unqualified_t
#include <cstddef> // std::size_t
#include <limits> // std::numeric_limits
#include <iterator> // std::begin, std::end
#include <memory> // std::unique_ptr
#include <type_traits> // std::is_floating_point, std::true_type, std::false_type, std::is_same, std::enable_if_t
#include <algorithm> // std::shuffle
#include <random> // std::random_device, std::mt19937

namespace pl
{
namespace detail
{
static constexpr std::size_t largeUrbgThreshold = 50U;

template <typename Urbg, bool IsLarge>
class UrbgStorageImpl
{
public:
    using this_type = UrbgStorageImpl;
    using element_type = Urbg;

    // assume isLarge == true

    explicit UrbgStorageImpl(std::random_device::result_type seed)
        : m_urbg{ std::make_unique<element_type>(seed) }
    {
    }

    element_type &get()
    {
        return *m_urbg;
    }

    const element_type &get() const
    {
        return const_cast<this_type *>(this)->get();
    }

private:
    std::unique_ptr<element_type> m_urbg;
};

template <typename Urbg>
class UrbgStorageImpl<Urbg, false>
{
public:
    using this_type = UrbgStorageImpl;
    using element_type = Urbg;

    explicit UrbgStorageImpl(std::random_device::result_type seed)
        : m_urbg{ seed }
    {
    }

    UrbgStorageImpl(const this_type &) = delete;

    this_type &operator=(const this_type &) = delete;

    element_type &get()
    {
        return m_urbg;
    }

    const element_type &get() const
    {
        return const_cast<this_type *>(this)->get();
    }

private:
    element_type m_urbg;
};

template <typename Urbg>
class UrbgStorage
    : public UrbgStorageImpl<Urbg, sizeof(Urbg) >= largeUrbgThreshold>
{
public:
    using this_type = UrbgStorage;
    using base_type = UrbgStorageImpl<Urbg, sizeof(Urbg) >= largeUrbgThreshold>;
    using element_type = typename base_type::element_type;

    using base_type::base_type;
};

template <typename Type>
struct distribution_of;

template <>
struct distribution_of<float>
{
    using type = std::uniform_real_distribution<float>;
};

template <>
struct distribution_of<double>
{
    using type = std::uniform_real_distribution<double>;
};

template <>
struct distribution_of<long double>
{
    using type = std::uniform_real_distribution<long double>;
};

template <>
struct distribution_of<short>
{
    using type = std::uniform_int_distribution<short>;
};

template <>
struct distribution_of<int>
{
    using type = std::uniform_int_distribution<int>;
};

template <>
struct distribution_of<long>
{
    using type = std::uniform_int_distribution<long>;
};

template <>
struct distribution_of<long long>
{
    using type = std::uniform_int_distribution<long long>;
};

template <>
struct distribution_of<unsigned short>
{
    using type = std::uniform_int_distribution<unsigned short>;
};

template <>
struct distribution_of<unsigned int>
{
    using type = std::uniform_int_distribution<unsigned int>;
};

template <>
struct distribution_of<unsigned long>
{
    using type = std::uniform_int_distribution<unsigned long>;
};

template <>
struct distribution_of<unsigned long long>
{
    using type = std::uniform_int_distribution<unsigned long long>;
};

template <typename Type>
using distribution_of_t = typename distribution_of<Type>::type;
} // namespace detail

/*!
 * \brief A random number generator type.
 *        Not thread-safe.
 *        It is recommended to have one RandomNumberGenerator declared as
 *        thread_local to get one RandomNumberGenerator per thread.
 *        Alternatively a single RandomNumberGenerator may be placed in a
 *        Monitor, which is then accessed from multiple threads incurring
 *        locking overhead.
 *        Generates non-deterministic random numbers.
 *        By default uses the std::mt19937 engine.
**/
template <typename Engine = std::mt19937>
class RandomNumberGenerator
{
public:
    using this_type = RandomNumberGenerator;
    using element_type = Engine;

    /*!
     * \brief Creates a RandomNumberGenerator.
     *        Initializes the underlying random_device and uses it
     *        to seed the engine.
    **/
    RandomNumberGenerator()
        : m_randomDevice{ },
          m_urbg{ m_randomDevice() }
    {
    }

    /*!
     * \brief this type is non-copyable.
    **/
    RandomNumberGenerator(const this_type &) = delete;

    /*!
     * \brief this type is non-copyable.
    **/
    this_type &operator=(const this_type &) = delete;

    /*!
     * \brief Generates a random number from the range of [begin,end)
     *        if 'Numeric' is a floating point number. Otherwise
     *        generates a random number from the range of [begin,end].
     * \param begin The lower bound of the range from which
     *              to receive a random number from.
     * \param end The upper bound of the range from which to
     *            receive a random number from.
     * \return The number generated.
     * \warning 'begin' must be less than 'end' if 'Numeric' is a floating
     *          point number, otherwise 'begin' must be less than or equal
     *          'end'.
     * \note Types such as char, signed char, unsigned char, std::uint8_t and
     *       std::int8_t are not allowed,
     *       see http://cplusplus.github.io/LWG/lwg-closed.html#2326.
    **/
    template <typename Numeric>
    auto generate(meta::identity_t<Numeric> begin
                      = std::numeric_limits<Numeric>::min PL_NO_MACRO_SUBSTITUTION(),
                  meta::identity_t<Numeric> end
                      = std::numeric_limits<Numeric>::max PL_NO_MACRO_SUBSTITUTION())
    -> meta::disable_if_t<std::is_same<meta::unqualified_t<Numeric>, bool>::value, Numeric>
    {
        return generateImpl<Numeric>(begin, end,
                                     typename std::is_floating_point<Numeric>::type{ });
    }

    /*!
     * \brief Generates a random boolean value.
     * \param trueChance the chance to generate true, defaults to 0.5.
     * \return the boolean value generated.
    **/
    template <typename Bool>
    auto generate(double trueChance = 0.5)
    -> std::enable_if_t<std::is_same<meta::unqualified_t<Bool>, bool>::value, bool>
    {
        std::bernoulli_distribution dist{ trueChance };
        return dist(m_urbg.get());
    }

    /*!
     * \brief Member function to shuffle a range randomly using the
     *        std::shuffle algorithm with this RandomNumberGenerator's
     *        engine. Shuffles the range [begin,end).
     * \param begin The begin iterator of the half open range to shuffle.
     * \param end The end iterator of the half open range to shuffle.
     * \return A reference to this RandomNumberGenerator.
    **/
    template <typename RandomAccessIterator>
    this_type &shuffle(RandomAccessIterator begin, RandomAccessIterator end)
    {
        std::shuffle(begin, end, m_urbg.get());
        return *this;
    }

    /*!
     * \brief Shuffles 'container'.
     * \param container The Container to shuffle.
     * \return A reference to this RandomNumberGenerator.
    **/
    template <typename Container>
    this_type &shuffle(Container &container)
    {
        return shuffle(std::begin(container), std::end(container));
    }

private:
    template <typename Numeric>
    Numeric generateImpl(meta::identity_t<Numeric> begin,
                         meta::identity_t<Numeric> end,
                         std::true_type)
    {
        PL_DBG_CHECK_PRE(begin < end);
        detail::distribution_of_t<Numeric> dist{ begin, end };
        return dist(m_urbg.get());
    }

    template <typename Numeric>
    Numeric generateImpl(meta::identity_t<Numeric> begin,
                         meta::identity_t<Numeric> end,
                         std::false_type)
    {
        PL_DBG_CHECK_PRE(begin <= end);
        detail::distribution_of_t<Numeric> dist{ begin, end };
        return dist(m_urbg.get());
    }

    std::random_device m_randomDevice;
    detail::UrbgStorage<element_type> m_urbg;
};
} // namespace pl
#endif // INCG_PL_RANDOM_NUMBER_GENERATOR_HPP
