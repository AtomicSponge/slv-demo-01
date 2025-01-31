/*
 * Silvergun Engine Demo
 * By:  Matthew Evans
 * File:  stars.hpp
 *
 * See LICENSE.txt for copyright information
 *
 * Header file for the stars component
 */

#ifndef DEMO_CMP_STARS_HPP
#define DEMO_CMP_STARS_HPP

#include <silvergun/silvergun.hpp>

#define MAX_STARS 64

class stars : public slv::cmp::component {
  public:
    inline stars() : speed_mult(1.0) {
      for(int i = 0; i < MAX_STARS; i++) {
        x[i] = std::rand() % slv::config::gfx::viewport_w + 1;
        y[i] = std::rand() % slv::config::gfx::viewport_h + 1;
        speed[i] = (std::rand() % 3 + 1) * 3;
        color[i] = std::rand() % 4 + 1;
      }
    }

    float x[MAX_STARS];
    float y[MAX_STARS];
    float speed[MAX_STARS];
    float color[MAX_STARS];

    float speed_mult;
};

#endif
