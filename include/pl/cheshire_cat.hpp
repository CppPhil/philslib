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
 * \file cheshire_cat.hpp
 * \brief Exports the cheshire_cat template type and the in_place_t type.
 **/
#ifndef INCG_PL_CHESHIRE_CAT_HPP
#define INCG_PL_CHESHIRE_CAT_HPP
#include "annotations.hpp"  // PL_IN, PL_INOUT
#include "type_traits.hpp"  // pl::enable_if_t
#include "voidify.hpp"      // PL_VOIDIFY
#include <ciso646>          // and
#include <cstddef>          // std::size_t, std::max_align_t
#include <initializer_list> // std::initializer_list
#include <new>              // ::operator new, __cpp_lib_launder, std::launder
#include <utility>          // std::move, std::forward

namespace pl {
/*!
 * \brief The in_place_t tag type, used to in place construct element_types of
 *        cheshire_cat objects.
 **/
struct in_place_t {
  /*!
   * \brief Default constructs an in_place_t object.
   **/
  explicit in_place_t() = default;
};

/*!
 * \brief The cheshire_cat template type.
 * \warning ElementType should be nothrow move constructible, nothrow move
 *          assignable, nothrow swappable as well as nothrow destructible.
 *
 * Wrapper type for an object. Provides storage for that object of size
 * BufferByteSize. To be used to hold an implementation type of some other type
 * much like the Pimpl pattern. The ElementType will typically be an incomplete
 * forward declared type which will only be defined in the corresponding source
 * file. Unlike Pimpl doesn't use dynamic memory allocation, but instead
 * uses a fixed size buffer of size BufferByteSize. The containing type should
 * have its destructor be defined in the source file. Offers value semantics.
 * If the ElementType is too large or does not fulfill the alignment
 * requirements a static assertion is triggered. If std::launder is available
 * the implementation will use that, otherwise memory overhead for an additional
 * pointer occurs. This allows the actual implementation to reside solely in
 * the source file, preventing the need to recompile that code every time it
 * is changed in every translation unit including the header file. Other
 * translation units including the header file will still have to recompile
 * if the buffer size provided for the element_type is changed, unlike with the
 * classic Pimpl pattern using dynamic memory allocation. The alignment can be
 * set using the Alignment non-type template parameter, by default it's set to
 * alignof(std::max_align_t).
 **/
template<
  typename ElementType,
  std::size_t BufferByteSize,
  std::size_t Alignment = alignof(std::max_align_t)>
class cheshire_cat {
public:
  using this_type       = cheshire_cat;
  using element_type    = ElementType;
  using value_type      = element_type;
  using pointer         = element_type*;
  using const_pointer   = const element_type*;
  using reference       = element_type&;
  using const_reference = const element_type&;

  static constexpr std::size_t buffer_byte_size = BufferByteSize;
  static constexpr std::size_t alignment        = Alignment;

  struct storage_type {
    alignas(alignment) unsigned char data[buffer_byte_size];
  };

private:
  template<typename... Args>
  void create(PL_INOUT Args&&... args) noexcept(
    std::is_nothrow_constructible<element_type, Args&&...>::value)
  {
    using incomplete_type_not_allowed
      = unsigned char[sizeof(ElementType) ? 1 : -1];
    (void)sizeof(incomplete_type_not_allowed);

    static_assert(
      sizeof(element_type) <= sizeof(m_storage),
      "An object of element_type would be too large.");
    static_assert(
      (alignof(storage_type) % alignof(element_type)) == 0U,
      "The alignment requirement is not a divisor of the alignment "
      "provided by the storage_type.");

#ifndef __cpp_lib_launder
    m_ptr =
#endif
      ::new (PL_VOIDIFY(m_storage)) element_type(std::forward<Args>(args)...);
  }

public:
  /*!
   * \brief Default constructs the element_type.
   **/
  cheshire_cat() : m_storage
  {
  }
#ifndef __cpp_lib_launder
  , m_ptr
  {
  }
#endif
  {
    create();
  }

  /*!
   * \brief Copy constructor.
   * \param other The other cheshire_cat to copy construct from.
   **/
  cheshire_cat(PL_IN const this_type& other) : cheshire_cat{*other}
  {
  }
  /*!
   * \brief Move constructor.
   * \param other The other cheshire_cat to move construct from.
   * \note 'other' will be left in its moved-from state.
   **/
  cheshire_cat(PL_INOUT this_type&& other) noexcept : cheshire_cat{*other}
  {
  }
  /*!
   * \brief Creates a cheshire_cat from an lvalue element_type.
   * \param value The lvalue element_type to construct from.
   **/
  explicit cheshire_cat(PL_IN const_reference value) : m_storage
  {
  }
#ifndef __cpp_lib_launder
  , m_ptr
  {
  }
#endif
  {
    create(value);
  }

  /*!
   * \brief Creates a cheshire_cat from an rvalue element_type
   * \param value The rvalue element_type to construct from.
   * \note 'value' will be left in its moved-from state.
   **/
  explicit cheshire_cat(PL_INOUT element_type&& value) noexcept : m_storage
  {
  }
#ifndef __cpp_lib_launder
  , m_ptr
  {
  }
#endif
  {
    create(std::move(value));
  }

  /*!
   * \brief In place constructor. Constructs an element_type from the 'args'
   *        provided.
   * \param args The arguments to in place construct from.
   **/
  template<
    typename... Args,
    typename = enable_if_t<std::is_constructible<element_type, Args...>::value>>
  explicit cheshire_cat(in_place_t, PL_INOUT Args&&... args) : m_storage
  {
  }
#ifndef __cpp_lib_launder
  , m_ptr
  {
  }
#endif
  {
    create(std::forward<Args>(args)...);
  }

  /*!
   * \brief In place initializer_list constructor.
   * \param il The initializer_list to in place construct from.
   * \param args Additional arguments to forward to the constructor of
   *             element_type along with the initializer_list.
   **/
  template<
    typename Ty,
    typename... Args,
    typename = enable_if_t<std::is_constructible<
      element_type,
      std::initializer_list<Ty>&,
      Args&&...>::value>>
  explicit cheshire_cat(
    in_place_t,
    std::initializer_list<Ty> il,
    PL_INOUT                  Args&&... args)
    : m_storage
  {
  }
#ifndef __cpp_lib_launder
  , m_ptr
  {
  }
#endif
  {
    create(il, std::forward<Args>(args)...);
  }

  /*!
   * \brief Copy assignment operator.
   * \param other The other cheshire_cat to copy assign with.
   * \return A reference to this object.
   **/
  this_type& operator=(PL_IN const this_type& other)
  {
    *this = *other;
    return *this;
  }

  /*!
   * \brief Move assignment operator.
   * \param other The other cheshire_cat to move assign with.
   * \return A reference to this object.
   * \note 'other' will be left in its moved-from state.
   **/
  this_type& operator=(PL_INOUT this_type&& other) noexcept
  {
    *this = *other;
    return *this;
  }

  /*!
   * \brief Assigns with an lvalue element_type.
   * \param value The lvalue element_type to assign with.
   * \return A reference to this object.
   **/
  this_type& operator=(PL_IN const_reference value)
  {
    **this = value;
    return *this;
  }

  /*!
   * \brief Assigns with an rvalue element_type
   * \param value The rvalue element_type to assign with.
   * \return A reference to this object.
   * \note 'value' will be left in its moved-from state.
   **/
  this_type& operator=(PL_INOUT element_type&& value) noexcept
  {
    **this = std::move(value);
    return *this;
  }

  /*!
   * \brief The destructor. Destroys the underlying element_type object.
   **/
  ~cheshire_cat() noexcept
  {
    destroy();
  }
  /*!
   * \brief Returns a low level const qualified pointer to the element_type
   *        object.
   * \return A low level const qualified pointer to the element_type object.
   **/
  const_pointer get() const noexcept
  {
    return const_cast<this_type*>(this)->get();
  }

  /*!
   * \brief Returns a pointer to the element_type object.
   * \return A pointer to the element_type object.
   **/
  pointer get() noexcept
  {
#ifdef __cpp_lib_launder
    return std::launder(
      reinterpret_cast<element_type*>(std::addressof(m_storage)));
#else
    return m_ptr;
#endif
  }

  /*!
   * \brief Returns a low level const qualified pointer to the element_type
   *        object.
   * \return A low level const qualified pointer to the element_type object.
   **/
  const_pointer operator->() const noexcept
  {
    return const_cast<this_type*>(this)->operator->();
  }

  /*!
   * \brief Returns a pointer to the element_type object.
   * \return A pointer to the element_type object.
   **/
  pointer operator->() noexcept
  {
    return get();
  }
  /*!
   * \brief Returns a const lvalue reference to the element_type object.
   * \return A const lvalue reference to the element_type object.
   **/
  const_reference operator*() const& noexcept
  {
    return *get();
  }
  /*!
   * \brief Returns an lvalue reference to the element_type object.
   * \return An lvalue reference to the element_type object.
   **/
  reference operator*() & noexcept
  {
    return *get();
  }
  /*!
   * \brief Returns a const rvalue reference to the element_type object.
   * \return A const rvalue reference to the element_type object.
   **/
  const element_type&& operator*() const&& noexcept
  {
    return std::move(*get());
  }

  /*!
   * \brief Returns an rvalue reference to the element_type object.
   * \return An rvalue reference to the element_type object.
   **/
  element_type&& operator*() && noexcept
  {
    return std::move(*get());
  }
  /*!
   * \brief Swaps this cheshire_cat with another one.
   * \param other The other cheshire_cat to swap with.
   **/
  void swap(this_type& other) noexcept
  {
    using std::swap;
    swap(**this, *other);
  }

private:
  void destroy() noexcept
  {
    get()->~element_type();
  }
  storage_type m_storage;
#ifndef __cpp_lib_launder
  element_type* m_ptr;
#endif
};

/*!
 * \brief Non-member swap function which can be found by ADL.
 * \param first The first cheshire_cat to swap with.
 * \param second The second cheshire_cat to swap with.
 * \note Swaps the two arguments provided as if by first.swap(second);
 **/
template<
  typename ElementType,
  std::size_t BufferByteSize,
  std::size_t Alignment>
inline void swap(
  PL_INOUT cheshire_cat<ElementType, BufferByteSize, Alignment>& first,
  PL_INOUT cheshire_cat<ElementType, BufferByteSize, Alignment>&
           second) noexcept
{
  first.swap(second);
}
} // namespace pl
#endif // INCG_PL_CHESHIRE_CAT_HPP
