/*
 * WTEngine Demo
 * By:  Matthew Evans
 * File:  title_scene.hpp
 *
 * See LICENSE.md for copyright information
 */

#include <wtengine/wtengine.hpp>

#include <allegro5/allegro_physfs.h>

class title_scene final : public wte::scene {
  public:
    title_scene() : wte::scene("title_scene") {};
    ~title_scene() = default;
    
    void load(void) override {
      wte::mgr::spawner::spawn("title_screen", {});
    };

    void unload(void) override {};

    void loop(void) override {
      wte::engine::load_scene("game_scene");
    };
};
