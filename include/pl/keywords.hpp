/*!
 * \file keywords.hpp
 * \brief Exports keyword like macros.
 *        Define PL_NO_KEYWORDS to disable the keyword-like variants.
**/
#ifndef INCG_PL_KEYWORDS_HPP
#define INCG_PL_KEYWORDS_HPP
#include <ciso646> // not

/*!
 * \def PL_UNLESS(condition)
 * \brief Control flow statement that will execute its body unless the condition
 *        is true.
 * \note Behaves the same as if (not condition)
**/

/*!
 * \def PL_REPEAT
 * \brief Introduces a repeat until loop.
 * \warning Must be ended with PL_UNTIL
 * \note The repeat until loop behaves like do { } while (not condition)
**/

/*!
 * \def PL_UNTIL(condition)
 * \brief The until part of the repeat until loop. The loop will run until
 *        the condition is true, that is the loop will repeat its body as long
 *        as the condition is false.
 * \warning Must be introduced with PL_UNTIL
 * \note The repeat until loop behaves like do { } while (not condition)
**/

/*!
 * \def unless(condition)
 * \brief Keyword like alias for PL_UNLESS.
 * \see PL_UNLESS.
 * \note Define PL_NO_KEYWORDS globally (in the compiler options)
 *       to not have this macro defined.
**/

/*!
 * \def repeat
 * \brief Keyword like alias for PL_REPEAT.
 * \see PL_REPEAT.
 * \note Define PL_NO_KEYWORDS globally (in the compiler options)
 *       to not have this macro defined.
**/

/*!
 * \def until(condition)
 * \brief Keyword like alias for PL_UNTIL.
 * \see PL_UNTIL.
 * \note Define PL_NO_KEYWORDS globally (in the compiler options)
 *       to not have this macro defined.
**/

#define PL_UNLESS(condition) if (not (condition))

#define PL_REPEAT do

#define PL_UNTIL(condition) while (not (condition))

#ifndef PL_NO_KEYWORDS
#define unless(condition) PL_UNLESS(condition)

#define repeat PL_REPEAT

#define until(condition) PL_UNTIL(condition)
#endif // PL_NO_KEYWORDS
#endif // INCG_PL_KEYWORDS_HPP
