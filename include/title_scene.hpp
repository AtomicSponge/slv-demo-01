/*
 * WTEngine Demo
 * By:  Matthew Evans
 * File:  title_scene.cpp
 *
 * See LICENSE.md for copyright information
 */

#include <wtengine/wtengine.hpp>

#include <allegro5/allegro_physfs.h>

#include <damage.hpp>
#include <energy.hpp>
#include <health.hpp>
#include <size.hpp>
#include <stars.hpp>

class title_scene final : public wte::scene {
  public:
    void load(void) override {};

    void unload(void) override {};

    void loop(void) override {};
};
