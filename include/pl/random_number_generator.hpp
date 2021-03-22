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
 * \file random_number_generator.hpp
 * \brief Exports the random_number_generator type.
 **/
#ifndef INCG_PL_RANDOM_NUMBER_GENERATOR_HPP
#define INCG_PL_RANDOM_NUMBER_GENERATOR_HPP
#include "annotations.hpp"           // PL_INOUT
#include "assert.hpp"                // PL_DBG_CHECK_PRE
#include "meta/disable_if.hpp"       // pl::meta::disable_if_t
#include "meta/remove_cvref.hpp"     // pl::meta::remove_cvref_t
#include "meta/type_identity.hpp"    // pl::meta::type_identity_t
#include "no_macro_substitution.hpp" // PL_NO_MACRO_SUBSTITUTION
#include <algorithm>                 // std::shuffle
#include <cstddef>                   // std::size_t
#include <iterator>                  // std::begin, std::end
#include <limits>                    // std::numeric_limits
#include <memory>                    // std::unique_ptr
#include <random>                    // std::random_device, std::mt19937_64
#include <type_traits> // std::is_floating_point, std::true_type, std::false_type, std::is_same, std::enable_if_t

namespace pl {
namespace detail {
static constexpr std::size_t large_urbg_threshold = 50U;

template<typename Urbg, bool IsLarge>
class urbg_storage_impl {
public:
    using this_type    = urbg_storage_impl;
    using element_type = Urbg;

    // assume isLarge == true

    explicit urbg_storage_impl(std::random_device::result_type seed)
        : m_urbg{std::make_unique<element_type>(seed)}
    {
    }

    element_type&       get() { return *m_urbg; }
    const element_type& get() const
    {
        return const_cast<this_type*>(this)->get();
    }

private:
    std::unique_ptr<element_type> m_urbg;
};

template<typename Urbg>
class urbg_storage_impl<Urbg, false> {
public:
    using this_type    = urbg_storage_impl;
    using element_type = Urbg;

    explicit urbg_storage_impl(std::random_device::result_type seed)
        : m_urbg{seed}
    {
    }

    urbg_storage_impl(const this_type&) = delete;

    this_type& operator=(const this_type&) = delete;

    element_type&       get() { return m_urbg; }
    const element_type& get() const
    {
        return const_cast<this_type*>(this)->get();
    }

private:
    element_type m_urbg;
};

template<typename Urbg>
class urbg_storage
    : public urbg_storage_impl<Urbg, sizeof(Urbg) >= large_urbg_threshold> {
public:
    using this_type = urbg_storage;
    using base_type
        = urbg_storage_impl<Urbg, sizeof(Urbg) >= large_urbg_threshold>;
    using element_type = typename base_type::element_type;

    using base_type::base_type;
};

template<typename Type>
struct distribution_of;

template<>
struct distribution_of<float> {
    using type = std::uniform_real_distribution<float>;
};

template<>
struct distribution_of<double> {
    using type = std::uniform_real_distribution<double>;
};

template<>
struct distribution_of<long double> {
    using type = std::uniform_real_distribution<long double>;
};

template<>
struct distribution_of<short> {
    using type = std::uniform_int_distribution<short>;
};

template<>
struct distribution_of<int> {
    using type = std::uniform_int_distribution<int>;
};

template<>
struct distribution_of<long> {
    using type = std::uniform_int_distribution<long>;
};

template<>
struct distribution_of<long long> {
    using type = std::uniform_int_distribution<long long>;
};

template<>
struct distribution_of<unsigned short> {
    using type = std::uniform_int_distribution<unsigned short>;
};

template<>
struct distribution_of<unsigned int> {
    using type = std::uniform_int_distribution<unsigned int>;
};

template<>
struct distribution_of<unsigned long> {
    using type = std::uniform_int_distribution<unsigned long>;
};

template<>
struct distribution_of<unsigned long long> {
    using type = std::uniform_int_distribution<unsigned long long>;
};

template<typename Type>
using distribution_of_t = typename distribution_of<Type>::type;
} // namespace detail

/*!
 * \brief A random number generator type.
 *        Not thread-safe.
 *        It is recommended to have one random_number_generator declared as
 *        thread_local to get one random_number_generator per thread.
 *        Alternatively a single random_number_generator may be placed in a
 *        Monitor, which is then accessed from multiple threads incurring
 *        locking overhead.
 *        Generates non-deterministic random numbers.
 *        By default uses the std::mt19937_64 engine.
 **/
template<typename Engine = std::mt19937_64>
class random_number_generator {
public:
    using this_type    = random_number_generator;
    using element_type = Engine;

    /*!
     * \brief Creates a random_number_generator.
     *        Initializes the underlying random_device and uses it
     *        to seed the engine.
     **/
    random_number_generator() : m_random_device{}, m_urbg{m_random_device()} {}
    /*!
     * \brief this type is non-copyable.
     **/
    random_number_generator(const this_type&) = delete;

    /*!
     * \brief this type is non-copyable.
     **/
    this_type& operator=(const this_type&) = delete;

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
    template<typename Numeric>
    auto generate(
        meta::type_identity_t<Numeric>      begin
        = std::numeric_limits<Numeric>::min PL_NO_MACRO_SUBSTITUTION(),
        meta::type_identity_t<Numeric>      end
        = std::numeric_limits<Numeric>::max PL_NO_MACRO_SUBSTITUTION())
        -> meta::disable_if_t<
            std::is_same<meta::remove_cvref_t<Numeric>, bool>::value,
            Numeric>
    {
        return generate_impl<Numeric>(
            begin, end, typename std::is_floating_point<Numeric>::type{});
    }

    /*!
     * \brief Generates a random boolean value.
     * \param true_chance the chance to generate true, defaults to 0.5.
     * \return the boolean value generated.
     **/
    template<typename Bool>
    auto generate(double true_chance = 0.5) -> std::
        enable_if_t<std::is_same<meta::remove_cvref_t<Bool>, bool>::value, bool>
    {
        std::bernoulli_distribution dist{true_chance};
        return dist(m_urbg.get());
    }

    /*!
     * \brief Member function to shuffle a range randomly using the
     *        std::shuffle algorithm with this random_number_generator's
     *        engine. Shuffles the range [begin,end).
     * \param begin The begin iterator of the half open range to shuffle.
     * \param end The end iterator of the half open range to shuffle.
     * \return A reference to this random_number_generator.
     **/
    template<typename RandomAccessIterator>
    this_type& shuffle(RandomAccessIterator begin, RandomAccessIterator end)
    {
        std::shuffle(begin, end, m_urbg.get());
        return *this;
    }

    /*!
     * \brief Shuffles 'container'.
     * \param container The Container to shuffle.
     * \return A reference to this random_number_generator.
     **/
    template<typename Container>
    this_type& shuffle(PL_INOUT Container& container)
    {
        return shuffle(std::begin(container), std::end(container));
    }

private:
    template<typename Numeric>
    Numeric generate_impl(
        meta::type_identity_t<Numeric> begin,
        meta::type_identity_t<Numeric> end,
        std::true_type)
    {
        PL_DBG_CHECK_PRE(begin < end);
        detail::distribution_of_t<Numeric> dist{begin, end};
        return dist(m_urbg.get());
    }

    template<typename Numeric>
    Numeric generate_impl(
        meta::type_identity_t<Numeric> begin,
        meta::type_identity_t<Numeric> end,
        std::false_type)
    {
        PL_DBG_CHECK_PRE(begin <= end);
        detail::distribution_of_t<Numeric> dist{begin, end};
        return dist(m_urbg.get());
    }

    std::random_device                 m_random_device;
    detail::urbg_storage<element_type> m_urbg;
};
} // namespace pl
#endif // INCG_PL_RANDOM_NUMBER_GENERATOR_HPP
