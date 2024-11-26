/*
 * Silvergun Engine Demo
 * By:  Matthew Evans
 * File:  energy.hpp
 *
 * See LICENSE.txt for copyright information
 *
 * Health component.
 */

#ifndef DEMO_CMP_ENERGY_HPP
#define DEMO_CMP_ENERGY_HPP

#include <silvergun/silvergun.hpp>

/*
 * Store the amount of energy an entity has
 */
class energy final : public slv::cmp::component {
  public:
    /*!
     * Energy constructor.
     * \param h Health value.
     * \param hm Max health value.
     * \return void
     */
    inline energy(const int& e, const int& em) :
    amt(e), amt_max(em) {};

    int amt, amt_max;
};

#endif
