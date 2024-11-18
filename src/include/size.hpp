/*
 * Silvergun Engine Demo
 * By:  Matthew Evans
 * File:  damage.hpp
 *
 * See LICENSE.txt for copyright information
 *
 * Size component.
 */

#ifndef DEMO_CMP_SIZE_HPP
#define DEMO_CMP_SIZE_HPP

#include <silvergun/silvergun.hpp>

/*
 * Save the asteroid size
 */
class size final : public slv::cmp::component {
    public:
        /*!
         * Size constructor.
         * \param s Size.
         * \return void
         */
        inline size(const int& s) : the_size(s) {};

        int the_size;
};

#endif
