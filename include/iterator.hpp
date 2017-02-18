/*! \file iterator.hpp
 *  \brief This file defines various utilities for working with iterators.
**/

#ifndef INCG_PL_ITERATOR_HPP
#define INCG_PL_ITERATOR_HPP

/*!
 * \def PL_BEGIN_END(cont)
 * \brief Macro that can be used to call a function that expects begin and
 *        end iterators to cont.
**/

/*!
 * \def PL_CBEGIN_CEND(cont)
 * \brief Macro that can be used to call a function that expects cbegin and
 *        cend iterators to cont.
**/

/*!
 * \def PL_RBEGIN_REND(cont)
 * \brief Macro that can be used to call a function that expects rbegin and
 *        rend iterators to cont.
**/

/*!
 * \def PL_CRBEGIN_CREND(cont)
 * \brief Macro that can be used to call a function that expects crbegin and
 *        crend iterators to cont.
**/

namespace pl
{

#warning "IMPLEMENT pl::begin, pl::end etc"

} // namespace pl
#define PL_BEGIN_END(cont) pl::begin(cont), pl::end(cont)
#define PL_CBEGIN_CEND(cont) pl::cbegin(cont), pl::cend(cont)
#define PL_RBEGIN_REND(cont) pl::rbegin(cont), pl::rend(cont)
#define PL_CRBEGIN_CREND(cont) pl::crbegin(cont), pl::crend(cont)
#endif // INCG_PL_ITERATOR_HPP
