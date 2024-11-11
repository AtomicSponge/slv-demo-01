/*
 * WTEngine Demo
 * By:  Matthew Evans
 * File:  game_scene.hpp
 *
 * See LICENSE.md for copyright information
 */

#include <wtengine/wtengine.hpp>

#include <allegro5/allegro_physfs.h>

class game_scene final : public wte::scene {
  public:
    game_scene() : wte::scene("game_scene", wte::SCOPE_B) {};
    ~game_scene() = default;

    void load(void) override {
      //  Spawn starting entities
      wte::mgr::spawner::spawn("starfield", {});
      wte::mgr::spawner::spawn("score_overlay", {});
      wte::mgr::spawner::spawn("player_info_overlay", {});
      wte::mgr::spawner::spawn("game_over_overlay", {});
      wte::mgr::spawner::spawn("player", {});
      wte::mgr::spawner::spawn("main_cannon", {});
      wte::mgr::spawner::spawn("shield", {});

      //  Reset score.
      wte::mgr::variables::set("score", (int64_t)0);

      //  Set number of lives.
      if (wte::mgr::variables::get<int64_t>("max_lives") > 5 || wte::mgr::variables::get<int64_t>("max_lives") < 3)
        wte::mgr::variables::set("max_lives", (int64_t)3);
      wte::mgr::variables::set("lives", wte::mgr::variables::get<int64_t>("max_lives"));

      //wte::mgr::audio::music::a::play(wte::mgr::assets::get<ALLEGRO_AUDIO_STREAM>("music"));

      wte::mgr::messages::load_script("game.sdf");
    };

    void unload(void) override {
      if (wte::mgr::variables::get<int64_t>("score") > wte::mgr::variables::get<int64_t>("hiscore"))
        wte::mgr::variables::set("hiscore", wte::mgr::variables::get<int64_t>("score"));
    };

    void loop(void) override {};
};
