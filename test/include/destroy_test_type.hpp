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

#ifndef INCG_PL_TEST_DESTROY_TEST_TYPE_HPP
#define INCG_PL_TEST_DESTROY_TEST_TYPE_HPP

namespace pl {
namespace test {
/*!
 * \brief Type to test destroying algorithms that call destructors.
**/
class destroy_test_type {
public:
    using this_type = destroy_test_type;

    /*!
     * \brief Creates a destroy_test_type object.
     * \param p A pointer to a bool that should be set to false.
     * \warning Causes undefined behaviour if 'p' does not point to a bool.
     * \note Initializes the 'm_p' data member with 'p'.
    **/
    explicit destroy_test_type(bool* p);

    /*!
     * \brief Defaulted copy constructor.
    **/
    destroy_test_type(const this_type&);

    /*!
     * \brief Defaulted copy assignment operator.
    **/
    this_type& operator=(const this_type&);

    /*!
     * \brief Sets the bool pointed to by 'm_p' to true.
    **/
    ~destroy_test_type();

private:
    bool* m_p; /*!< Pointer to the bool passed into the constructor */
};
} // namespace test
} // namespace pl
#endif // INCG_PL_TEST_DESTROY_TEST_TYPE_HPP
