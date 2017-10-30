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
 * \brief Exports the ConceptPoly template type that can be used to
 *        create runtime polymorphic objects with value semantics.
**/
#ifndef INCG_PL_CONCEPT_POLY_HPP
#define INCG_PL_CONCEPT_POLY_HPP
#include "annotations.hpp" // PL_IN, PL_INOUT
#include "meta/remove_cvref.hpp" // pl::meta::remove_cvref_t
#include "assert.hpp" // PL_DBG_CHECK_PRE
#include <cstddef> // std::nullptr_t
#include <ciso646> // not, and
#include <utility> // std::forward, std::swap
#include <memory> // std::unique_ptr, std::make_unique
#include <type_traits> // std::is_base_of, std::enable_if_t, std::is_same

namespace pl
{
/*!
 * \brief Type for concept based polymorphism.
 * \example class Implementation // Implementation class, not derived from any type.
 *          {
 *          public:
 *              explicit Implementation(std::string string)
 *                  : m_string{ std::move(string ) }
 *              {
 *              }
 *
 *              // Function to 'draw' an 'Implementation' object.
 *              friend void drawIt(
 *                  const Implementation &impl,
 *                  std::ostream &os,
 *                  std::size_t position)
 *              {
 *                  os << std::string(position, ' ') << impl.m_string << '\n';
 *              }
 *
 *          private:
 *              std::string m_string;
 *          };
 *
 *          // Function to draw an int.
 *          void drawIt(int integer, std::ostream &os, std::size_t position)
 *          {
 *              os << std::string(position, '?') << ' ' << integer << '\n';
 *          }
 *
 *          class DrawConcept
 *          {
 *          public:
 *              // Default constructor. There is nothing to initialize of this object
 *              // in the constructor of DrawModel.
 *              DrawConcept() = default;
 *
 *              // Mandatory virtual destructor.
 *              virtual ~DrawConcept() = default;
 *
 *              // Mandatory pure virtual clone member function.
 *              virtual std::unique_ptr<DrawConcept> clone() const = 0;
 *
 *              // Pure virtual member functions for the interface ...
 *              virtual void draw(std::ostream &os, std::size_t position) const = 0;
 *
 *              // Pure abstract base classes like this should be non-copyable.
 *              DrawConcept(const DrawConcept &) = delete;
 *              DrawConcept &operator=(const DrawConcept &) = delete;
 *          };
 *
 *          template <typename Impl>
 *          class DrawModel
 *              : public DrawConcept // publicly derived from the Concept type.
 *          {
 *          public:
 *              // The Model type must be constructable from Impl.
 *              explicit DrawModel(Impl impl)
 *                  : DrawConcept{ }, // default construct the base.
 *                    m_impl{ std::move(impl) }
 *              {
 *              }
 *
 *              virtual std::unique_ptr<DrawConcept> clone() const override
 *              {
 *                  // Impl must be copy-constructable.
 *                  return std::make_unique<DrawModel>(m_impl);
 *              }
 *
 *              virtual void draw(std::ostream &os, std::size_t position) const override
 *              {
 *                  // Implementation code...
 *                  // Do whatever 'draw'ing should do with an 'Impl'.
 *                  // You may want to specialize the DrawModel template type.
 *                  drawIt(m_impl, os, position);
 *              }
 *
 *          private:
 *              Impl m_impl;
 *          };
 *
 *          int main()
 *          {
 *              // Convenience type alias.
 *              using Drawable = pl::ConceptPoly<DrawConcept, DrawModel>;
 *
 *              // Use with a dynamic type of 'Implementation' that conforms to the interface.
 *              Drawable drawable{ Implementation{ "My String" } };
 *              drawable->draw(std::cout, 5U);
 *
 *              // Switch to int, which also happens to conform to the interface.
 *              drawable = Drawable{ 7 };
 *              drawable->draw(std::cout, 10U);
 *          }
 *
 * The 'Concept' type must be a pure abstract base class that serves as the
 * type that defines the interface. All the member functions, excluding
 * the destructor, of the 'Concept' type must be pure virtual.
 * The destructor of the 'Concept' type must be declared virtual.
 * The 'Concept' type must define a pure virtual 'clone' member function
 * that used for cloning (virtual copy constructor). The return type of
 * that 'clone' pure virtual member function must be std::unique_ptr<Concept>.
 * The 'Model' type must be a template type that has one template type
 * parameter, that template type parameter may be any type wrapped by the
 * 'Model' template type. The 'Model' template type must be derived from
 * 'Concept' and implement all the virtual member functions of 'Concept'.
 * The 'clone' virtual member function of 'Model' shall return a copy
 * of itself as std::unique_ptr<Concept>.
 * Can be used to 'put' types into a 'type-hierarchy' that cannot derive
 * from any type. Allows putting types that fulfill the Concept through
 * the Model into the corresponding ConceptPoly without the implementation
 * type needing to be derived from any type, resulting in looser coupling
 * and allowing the type to be used outside of any type-hierarchy, completely
 * avoiding virtual function call overhead. Provides value semantics rather
 * than reference semantics.
**/
template <typename Concept, template <typename> class Model>
class ConceptPoly
{
public:
    /*!
     * \brief An alias of this type.
    **/
    using this_type = ConceptPoly;

    /*!
     * \brief Type alias of the 'Concept' type.
     *        Used to be able to query the 'Concept' type.
    **/
    using concept_type = Concept;

    /*!
     * \brief Alias of the 'Model<???>' type.
     *        Used to be able to query the 'Model' type.
     * \note You can check the dynamic type by comparing the std::type_info
     *       objects of different instantiations of the 'Model' template type
     *       with the std::type_info object for the object returned by
     *       one of the accessor functions.
    **/
    template <typename Type>
    using model_type = Model<Type>;

    /*!
     * \brief The pointer type used by the underlying std::unique_ptr.
     *        An alias for Concept *.
    **/
    using pointer = typename std::unique_ptr<Concept>::pointer;

    /*!
     * \brief The element_type used by the underlying std::unique_ptr.
     *        An alias for Concept.
    **/
    using element_type = typename std::unique_ptr<Concept>::element_type;

    /*!
     * \brief The deletery_type used by the underlying std::unique_ptr.
    **/
    using deleter_type = typename std::unique_ptr<Concept>::deleter_type;

    /*!
     * \brief Constructs a ConceptPoly object from the object passed in.
     * \param impl The implementation object to use.
     * \note This constructor will only be enabled if 'Impl' is not
     *       of type ConceptPoly<Concept, Model> and 'Concept' is a base of
     *       Model<Impl>.
     * \warning Do not replace the second template type parameter of this
     *          constructor!
    **/
    template <typename Impl,
              typename = std::enable_if_t<
                  not std::is_same<meta::remove_cvref_t<Impl>, this_type>::value
                  and std::is_base_of<Concept, Model<meta::remove_cvref_t<Impl>>>::value,
                  void>>
    explicit ConceptPoly(PL_IN Impl &&impl)
        : m_ptr{ std::make_unique<Model<meta::remove_cvref_t<Impl>>>(std::forward<Impl>(impl)) }
    {
    }

    /*!
     * \brief Copy constructs a ConceptPoly object from another one.
     * \param other The other ConceptPoly object to create a copy of.
     * \note Uses the 'clone' virtual member function of 'Concept',
     *       which must return std::unique_ptr<Concept> and clone the
     *       underlying Model<???> type.
     * \warning Precondition: other is not in the moved-from state.
    **/
    ConceptPoly(PL_IN const this_type &other)
        : m_ptr{ nullptr }
    {
        PL_DBG_CHECK_PRE(static_cast<bool>(other));
        m_ptr = other.m_ptr->clone();
    }

    /*!
     * \brief Defaulted move constructor.
     * \warning The object passed into the parameter is left in the
     *          moved-from state. The operator bool() member function
     *          of the ConceptPoly type can be used to determine whether
     *          the object is valid, that is, it is not in the moved from
     *          state.
     *
     * Move constructs a ConceptPoly object from another one.
     * Performs a member by member move.
    **/
    ConceptPoly(PL_IN this_type &&) noexcept = default;

    /*!
     * \brief Copy assignment operator. Copy assigns this object with 'other'.
     * \param other The other ConceptPoly object to become a copy of.
     * \return A reference to this object.
     * \note Destroys the current implementation object and replaces it
     *       with a copy of the parameter's.
     *       Uses the 'clone' virtual member function of the 'Concept' type
     *       which must be correctly implemented by the derived Model<???>
     *       type and return a clone as std::unique_ptr<Concept>.
     * \warning Precondition: other is not in the moved-from state.
    **/
    this_type &operator=(PL_IN const this_type &other)
    {
        PL_DBG_CHECK_PRE(static_cast<bool>(other));
        m_ptr = other.m_ptr->clone();
    }

    /*!
     * \brief Move assigns this object with the one passed into the parameter.
     * \return A reference to this object.
     * \note Performs a member by member move.
     * \warning The object passed into the parameter is left in the moved-from
     *          state. The operator bool() member function can be used
     *          to check if a ConceptPoly object is valid, that is, it isn't
     *          in the moved-from state.
    **/
    this_type &operator=(PL_IN this_type &&) noexcept = default;

    /*!
     * \brief Swaps this object with the one passed into the parameter.
     * \param other The other object to swap with.
     * \note Just swaps the underlying std::unique_ptrs.
    **/
    void swap(PL_INOUT this_type &other) noexcept
    {
        std::swap(m_ptr, other.m_ptr);
    }

    /*!
     * \brief Accessor function to get to the object managed by this ConceptPoly.
     * \return A raw pointer of type Concept * to the object managed by
     *         this ConceptPoly.
     * \note Can be used to access the object directly.
    **/
    Concept *get() noexcept
    {
        return m_ptr.get();
    }

    /*!
     * \brief Accessor function to get to the object managed by this ConceptPoly.
     * \return A raw pointer of type const Concept * to the object managed by
     *         this ConceptPoly.
     * \note Can be used to access the object directly.
    **/
    const Concept *get() const noexcept
    {
        return const_cast<this_type *>(this)->get();
    }

    /*!
     * \brief Returns a Concept & to the object managed.
     * \return A Concept & to the object managed.
     * \warning Precondition: this object is not in the moved-from state.
    **/
    Concept &operator*()
    {
        PL_DBG_CHECK_PRE(this->operator bool());
        return *m_ptr;
    }

    /*!
     * \brief Returns a const Concept & to the object managed.
     * \return A const Concept & to the object managed.
     * \warning Precondition: this object is not in the moved-from state.
    **/
    const Concept &operator*() const
    {
        return const_cast<this_type *>(this)->operator*();
    }

    /*!
     * \brief Operator to call member functions on the object managed
     *        that are defined by the 'Concept' interface type.
     * \return A Concept *.
     * \warning Precondition: this object is not in the moved-from state.
    **/
    Concept *operator->()
    {
        PL_DBG_CHECK_PRE(this->operator bool());
        return m_ptr.operator->();
    }

    /*!
     * \brief Operator to call const member functions on the object managed
     *        that are defined by the 'Concept' interface type.
     * \return A const Concept *.
     * \warning Precondition: this object is not in the moved-from state.
    **/
    const Concept *operator->() const
    {
        return const_cast<this_type *>(this)->operator->();
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
 * \brief Non member swap function for the ConceptPoly template type.
 *        Swaps the two parameters passed in with each other.
 * \param lhs The first parameter.
 * \param rhs The second parameter.
 * \note This function can be found by ADL (argument dependent lookup),
 *       unlike the .swap member function.
**/
template <typename Concept, template <typename> class Model>
void swap(
    PL_INOUT ConceptPoly<Concept, Model> &lhs,
    PL_INOUT ConceptPoly<Concept, Model> &rhs) noexcept
{
    lhs.swap(rhs);
}
} // namespace pl
#endif // INCG_PL_CONCEPT_POLY_HPP
