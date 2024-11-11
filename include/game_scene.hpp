/*
 * Silvergun Engine Demo
 * By:  Matthew Evans
 * File:  game_scene.hpp
 *
 * See LICENSE.md for copyright information
 */

#ifndef DEMO_GAME_SCENE_HPP
#define DEMO_GAME_SCENE_HPP

#include <silvergun/silvergun.hpp>

#include <allegro5/allegro_physfs.h>

class game_scene final : public slv::scene {
  public:
    game_scene() : slv::scene("game_scene", slv::SCOPE_B) {};
    ~game_scene() = default;

    void load(void) override {
      //  Spawn starting entities
      slv::mgr::spawner::spawn("starfield", {});
      slv::mgr::spawner::spawn("score_overlay", {});
      slv::mgr::spawner::spawn("player_info_overlay", {});
      slv::mgr::spawner::spawn("game_over_overlay", {});
      slv::mgr::spawner::spawn("player", {});
      slv::mgr::spawner::spawn("main_cannon", {});
      slv::mgr::spawner::spawn("shield", {});

      //  Reset score.
      slv::mgr::variables::set("score", (int64_t)0);

      //  Set number of lives.
      if (slv::mgr::variables::get<int64_t>("max_lives") > 5 || slv::mgr::variables::get<int64_t>("max_lives") < 3)
        slv::mgr::variables::set("max_lives", (int64_t)3);
      slv::mgr::variables::set("lives", slv::mgr::variables::get<int64_t>("max_lives"));

      //slv::mgr::audio::music::a::play(slv::mgr::assets::get<ALLEGRO_AUDIO_STREAM>("music"));

      slv::mgr::messages::load_script("game.sdf");
      slv::config::flags::engine_paused = false;
    };

    void unload(void) override {
      if (slv::mgr::variables::get<int64_t>("score") > slv::mgr::variables::get<int64_t>("hiscore"))
        slv::mgr::variables::set("hiscore", slv::mgr::variables::get<int64_t>("score"));
    };

    void loop(void) override {};
};

#endif
