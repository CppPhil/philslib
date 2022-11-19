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
 * \file concept_poly.hpp
 * \brief Exports the concept_poly template type that can be used to
 *        create runtime polymorphic objects with value semantics.
 **/
#ifndef INCG_PL_CONCEPT_POLY_HPP
#define INCG_PL_CONCEPT_POLY_HPP
#include "annotations.hpp"       // PL_IN, PL_INOUT
#include "assert.hpp"            // PL_DBG_CHECK_PRE
#include "meta/disable_if.hpp"   // pl::meta::disable_if_t
#include "meta/remove_cvref.hpp" // pl::meta::remove_cvref_t
#include <cstddef>               // std::nullptr_t
#include <memory>                // std::unique_ptr, std::make_unique
#include <type_traits>           // std::is_same
#include <utility>               // std::forward, std::swap

namespace pl {
/*!
 * \brief Type for concept based polymorphism.
 *
 * The 'concept' type must be a pure abstract base class that serves as the
 * type that defines the interface. All the member functions, excluding
 * the destructor, of the 'concept' type must be pure virtual.
 * The destructor of the 'concept' type must be declared virtual.
 * The 'concept' type must define a pure virtual 'clone' member function
 * that used for cloning (virtual copy constructor). The return type of
 * that 'clone' pure virtual member function must be std::unique_ptr<concept>.
 * The 'model' type must be a template type that has one template type
 * parameter, that template type parameter may be any type wrapped by the
 * 'model' template type. The 'model' template type must be derived from
 * 'concept' and implement all the virtual member functions of 'concept'.
 * The 'clone' virtual member function of 'model' shall return a copy
 * of itself as std::unique_ptr<concept>.
 * Can be used to 'put' types into a 'type-hierarchy' that cannot derive
 * from any type. Allows putting types that fulfill the concept through
 * the model into the corresponding concept_poly without the implementation
 * type needing to be derived from any type, resulting in looser coupling
 * and allowing the type to be used outside of any type-hierarchy, completely
 * avoiding virtual function call overhead. Provides value semantics rather
 * than reference semantics.
 **/
template<typename Concept, template<typename> class Model>
class concept_poly {
public:
  /*!
   * \brief An alias of this type.
   **/
  using this_type = concept_poly;

  /*!
   * \brief Type alias of the 'concept' type.
   *        Used to be able to query the 'concept' type.
   **/
  using concept_type = Concept;

  /*!
   * \brief Alias of the 'Model<???>' type.
   *        Used to be able to query the 'model' type.
   * \note You can check the dynamic type by comparing the std::type_info
   *       objects of different instantiations of the 'model' template type
   *       with the std::type_info object for the object returned by
   *       one of the accessor functions.
   **/
  template<typename Type>
  using model_type = Model<Type>;

  /*!
   * \brief The pointer type used by the underlying std::unique_ptr.
   *        An alias for Concept*.
   **/
  using pointer = typename std::unique_ptr<Concept>::pointer;

  /*!
   * \brief The element_type used by the underlying std::unique_ptr.
   *        An alias for Concept.
   **/
  using element_type = typename std::unique_ptr<Concept>::element_type;

  /*!
   * \brief The deleter_type used by the underlying std::unique_ptr.
   **/
  using deleter_type = typename std::unique_ptr<Concept>::deleter_type;

  /*!
   * \brief Constructs a concept_poly object from the object passed in.
   * \param impl The implementation object to use.
   * \note This constructor will only be enabled if 'Impl' is not
   *       of type concept_poly<Concept, Model>.
   * \warning Do not replace the second template type parameter of this
   *          constructor!
   **/
  template<
    typename Impl,
    typename = meta::disable_if_t<
      std::is_same<meta::remove_cvref_t<Impl>, this_type>::value,
      void>>
  explicit concept_poly(PL_IN Impl&& impl)
    : m_ptr{std::make_unique<Model<meta::remove_cvref_t<Impl>>>(
      std::forward<Impl>(impl))}
  {
  }

  /*!
   * \brief Copy constructs a concept_poly object from another one.
   * \param other The other concept_poly object to create a copy of.
   * \note Uses the 'clone' virtual member function of 'concept',
   *       which must return std::unique_ptr<Concept> and clone the
   *       underlying Model<???> type.
   * \warning Precondition: other is not in the moved-from state.
   **/
  concept_poly(PL_IN const this_type& other) : m_ptr{nullptr}
  {
    PL_DBG_CHECK_PRE(static_cast<bool>(other));
    m_ptr = other.m_ptr->clone();
  }

  /*!
   * \brief Defaulted move constructor.
   * \warning The object passed into the parameter is left in the
   *          moved-from state. The operator bool() member function
   *          of the concept_poly type can be used to determine whether
   *          the object is valid, that is, it is not in the moved from
   *          state.
   *
   * Move constructs a concept_poly object from another one.
   * Performs a member by member move.
   **/
  concept_poly(PL_IN this_type&&) noexcept = default;

  /*!
   * \brief Copy assignment operator. Copy assigns this object with 'other'.
   * \param other The other concept_poly object to become a copy of.
   * \return A reference to this object.
   * \note Destroys the current implementation object and replaces it
   *       with a copy of the parameter's.
   *       Uses the 'clone' virtual member function of the 'concept' type
   *       which must be correctly implemented by the derived Model<???>
   *       type and return a clone as std::unique_ptr<Concept>.
   * \warning Precondition: other is not in the moved-from state.
   **/
  this_type& operator=(PL_IN const this_type& other)
  {
    PL_DBG_CHECK_PRE(static_cast<bool>(other));
    m_ptr = other.m_ptr->clone();
    return *this;
  }

  /*!
   * \brief Move assigns this object with the one passed into the parameter.
   * \return A reference to this object.
   * \note Performs a member by member move.
   * \warning The object passed into the parameter is left in the moved-from
   *          state. The operator bool() member function can be used
   *          to check if a concept_poly object is valid, that is, it isn't
   *          in the moved-from state.
   **/
  this_type& operator=(PL_IN this_type&&) noexcept = default;

  /*!
   * \brief Swaps this object with the one passed into the parameter.
   * \param other The other object to swap with.
   * \note Just swaps the underlying std::unique_ptrs.
   **/
  void swap(PL_INOUT this_type& other) noexcept
  {
    std::swap(m_ptr, other.m_ptr);
  }

  /*!
   * \brief Accessor function to get to the object managed by this
   *        concept_poly.
   * \return A raw pointer of type Concept* to the object managed by
   *         this concept_poly.
   * \note Can be used to access the object directly.
   **/
  Concept* get() noexcept
  {
    return m_ptr.get();
  }
  /*!
   * \brief Accessor function to get to the object managed by this
   *        concept_poly.
   * \return A raw pointer of type const Concept* to the object managed by
   *         this concept_poly.
   * \note Can be used to access the object directly.
   **/
  const Concept* get() const noexcept
  {
    return const_cast<this_type*>(this)->get();
  }

  /*!
   * \brief Returns a Concept & to the object managed.
   * \return A Concept & to the object managed.
   * \warning Precondition: this object is not in the moved-from state.
   **/
  Concept& operator*()
  {
    PL_DBG_CHECK_PRE(this->operator bool());
    return *m_ptr;
  }

  /*!
   * \brief Returns a const Concept & to the object managed.
   * \return A const Concept & to the object managed.
   * \warning Precondition: this object is not in the moved-from state.
   **/
  const Concept& operator*() const
  {
    return const_cast<this_type*>(this)->operator*();
  }

  /*!
   * \brief Operator to call member functions on the object managed
   *        that are defined by the 'concept' interface type.
   * \return A Concept*.
   * \warning Precondition: this object is not in the moved-from state.
   **/
  Concept* operator->()
  {
    PL_DBG_CHECK_PRE(this->operator bool());
    return m_ptr.operator->();
  }

  /*!
   * \brief Operator to call const member functions on the object managed
   *        that are defined by the 'concept' interface type.
   * \return A const Concept*.
   * \warning Precondition: this object is not in the moved-from state.
   **/
  const Concept* operator->() const
  {
    return const_cast<this_type*>(this)->operator->();
  }

  /*!
   * \brief Checks whether this object is in the (invalid) moved-from
   *        state.
   * \return true if this object is valid.
   *         false if this object is in the moved-from state.
   **/
  explicit operator bool() const noexcept
  {
    return static_cast<bool>(m_ptr);
  }

private:
  std::unique_ptr<Concept> m_ptr; /*!< The underlying unique_ptr */
};

/*!
 * \brief Non member swap function for the concept_poly template type.
 *        Swaps the two parameters passed in with each other.
 * \param lhs The first parameter.
 * \param rhs The second parameter.
 * \note This function can be found by ADL (argument dependent lookup),
 *       unlike the .swap member function.
 **/
template<typename Concept, template<typename> class Model>
void swap(
  PL_INOUT concept_poly<Concept, Model>& lhs,
  PL_INOUT concept_poly<Concept, Model>& rhs) noexcept
{
  lhs.swap(rhs);
}
} // namespace pl
#endif // INCG_PL_CONCEPT_POLY_HPP
