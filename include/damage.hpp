/*
 * Silvergun Engine Demo
 * By:  Matthew Evans
 * File:  damage.hpp
 *
 * See LICENSE.txt for copyright information
 *
 * Damage component.
 */

#ifndef DEMO_CMP_DAMAGE_HPP
#define DEMO_CMP_DAMAGE_HPP

#include <silvergun/silvergun.hpp>

/*
 * Store the amount of damage an entity can do
 */
class damage final : public slv::cmp::component {
    public:
        /*!
         * Damage constructor.
         * \param d Damage amount.
         * \return void
         */
        inline damage(const int& d) : dmg(d) {};

        int dmg;
};

#endif
