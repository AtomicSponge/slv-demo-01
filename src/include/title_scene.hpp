/*
 * Silvergun Engine Demo
 * By:  Matthew Evans
 * File:  title_scene.hpp
 *
 * See LICENSE.md for copyright information
 */

#ifndef DEMO_TITLE_SCENE_HPP
#define DEMO_TITLE_SCENE_HPP

#include <silvergun/silvergun.hpp>

class title_scene final : public slv::scene {
  public:
    title_scene() : slv::scene("title_scene", slv::SCOPE_A) {};
    ~title_scene() = default;
    
    void load(void) override {
      slv::mgr::spawner::spawn("title_screen", {});
    };
};

#endif
