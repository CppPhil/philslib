/*!
 * \file forever.hpp
 * \brief Exports a macro that can be used to declare a never ending loop.
**/
#ifndef INCG_PL_FOREVER_HPP
#define INCG_PL_FOREVER_HPP

/*!
 * \def PL_FOREVER
 * \brief Expands to for (;;). Macro to create a never ending loop.
 * \note Using for (;;) rather than while (true) avoids pedantic warnings
 *       regarding constant expressions being evaluated.
 * \warning Be careful not to create a never ending loop that has no
 *          observable behavior.
 * \see http://en.cppreference.com/w/cpp/language/memory_model#Forward_progress
**/

#define PL_FOREVER for (;;)
#endif // INCG_PL_FOREVER_HPP
