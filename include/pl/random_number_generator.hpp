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
#include <array>                     // std::array
#include <cstddef>                   // std::size_t
#include <iterator>                  // std::begin, std::end
#include <limits>                    // std::numeric_limits
#include <random>                    // std::random_device, std::mt19937_64
#include <type_traits> // std::is_floating_point, std::true_type, std::false_type, std::is_same, std::enable_if_t

namespace pl {
namespace detail {
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
   *        Seeds the underlying UniformRandomBitGenerator.
   **/
  random_number_generator()
    : m_urbg{create_uniform_random_bit_generator<element_type>()}
  {
  }

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
    return dist(m_urbg);
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
    std::shuffle(begin, end, m_urbg);
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
  template<typename UniformRandomBitGenerator>
  static UniformRandomBitGenerator create_uniform_random_bit_generator()
  {
    static constexpr std::size_t byte_count{
      UniformRandomBitGenerator::state_size
      * sizeof(typename UniformRandomBitGenerator::result_type)};
    std::random_device random_device{};
    std::array<
      std::random_device::result_type,
      (byte_count - 1) / sizeof(std::random_device::result_type) + 1>
      seed_buffer{};
    std::generate(seed_buffer.begin(), seed_buffer.end(), [&random_device] {
      return random_device();
    });
    std::seed_seq seed_sequence(seed_buffer.begin(), seed_buffer.end());
    return UniformRandomBitGenerator{seed_sequence};
  }

  template<typename Numeric>
  Numeric generate_impl(
    meta::type_identity_t<Numeric> begin,
    meta::type_identity_t<Numeric> end,
    std::true_type) // floating point
  {
    PL_DBG_CHECK_PRE(begin < end);
    detail::distribution_of_t<Numeric> dist{begin, end};
    return dist(m_urbg);
  }

  template<typename Numeric>
  Numeric generate_impl(
    meta::type_identity_t<Numeric> begin,
    meta::type_identity_t<Numeric> end,
    std::false_type) // non floating point
  {
    PL_DBG_CHECK_PRE(begin <= end);
    detail::distribution_of_t<Numeric> dist{begin, end};
    return dist(m_urbg);
  }

  element_type m_urbg; /*!< UniformRandomBitGenerator */
};
} // namespace pl
#endif // INCG_PL_RANDOM_NUMBER_GENERATOR_HPP
