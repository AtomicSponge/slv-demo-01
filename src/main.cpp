/*
 * Silvergun Engine Demo
 * By:  Matthew Evans
 * File:  main.cpp
 *
 * See LICENSE.md for copyright information
 */

#include <ctime>

#include <silvergun/silvergun.hpp>

#include "include/damage.hpp"
#include "include/energy.hpp"
#include "include/health.hpp"
#include "include/size.hpp"
#include "include/stars.hpp"

#include "include/title_scene.hpp"
#include "include/game_scene.hpp"

namespace layer {
  static const std::size_t background = 0;
  static const std::size_t enemy = 1;
  static const std::size_t player = 2;
  static const std::size_t overlay = 0;
}

namespace player_pols {
  static float x = 0.0f;
  static float y = 0.0f;
  static void reset(void) { x = y = 0.0f; };
}

int main(int argc, char **argv) {
  std::srand(std::time(nullptr));  //  Seed random, using time.

  slv::engine::load_systems = [](){
    slv::mgr::systems::add<slv::sys::movement>();
    slv::mgr::systems::add<slv::sys::colision>();
    slv::mgr::systems::add<slv::sys::logic>();
    slv::mgr::systems::add<slv::sys::gfx::animate>();
  };

  slv::engine::on_engine_pause = [](){
    slv::mgr::audio::music::a::pause();
    slv::mgr::audio::ambiance::pause();
  };

  slv::engine::on_engine_unpause = [](){
    slv::mgr::audio::music::a::unpause();
    slv::mgr::audio::ambiance::unpause();
  };

  //  Initialize game object
  slv::display::set_window_title("Silvergun Engine Demo");
  slv::engine::initialize(768, 1024);

  slv::engine::add_scene<title_scene>();
  slv::engine::add_scene<game_scene>();

  /* ********************************* */
  /* *** Input handling ************** */
  /* ********************************* */
  /* Title screen handler - ESC exits demo - any other key starts game */
  slv::add_handler<slv::SCOPE_A, slv::EVENT_KEY_DOWN, slv::handler::key>([](const int& key, ALLEGRO_DISPLAY* display) {
    if (key == ALLEGRO_KEY_ESCAPE) {
      slv::stop_game();  //  Stop the game loop.
      return;
    }

    slv::engine::load_scene("game_scene");
  });

  /* Game handlers - key down */
  slv::add_handler<slv::SCOPE_B, slv::EVENT_KEY_DOWN, slv::handler::key>([](const int& key, ALLEGRO_DISPLAY* display) {
    if (key == ALLEGRO_KEY_SPACE) {
      if (slv::config::flags::engine_paused) {
        slv::config::flags::engine_paused = false;
      } else {
        slv::config::flags::engine_paused = true;
      }
    }

    if (key == ALLEGRO_KEY_ESCAPE) {
      slv::engine::load_scene("title_scene");
    }

    if (slv::config::flags::engine_paused) return;  //  Stop key down processing if engine is paused.

    if (key == ALLEGRO_KEY_W) {
      slv::entity_id player_id = slv::mgr::world::get_id("player");
      player_pols::y = -1.0f;
      const float rad = std::atan2(player_pols::y, player_pols::x);
      slv::mgr::world::set_component<slv::cmp::motion>(player_id)->direction = rad;
      slv::mgr::world::set_component<slv::cmp::motion>(player_id)->x_vel = 5.0f;
      slv::mgr::world::set_component<slv::cmp::motion>(player_id)->y_vel = 5.0f;
    }
    if (key == ALLEGRO_KEY_S) {
      slv::entity_id player_id = slv::mgr::world::get_id("player");
      player_pols::y = 1.0f;
      const float rad = std::atan2(player_pols::y, player_pols::x);
      slv::mgr::world::set_component<slv::cmp::motion>(player_id)->direction = rad;
      slv::mgr::world::set_component<slv::cmp::motion>(player_id)->x_vel = 5.0f;
      slv::mgr::world::set_component<slv::cmp::motion>(player_id)->y_vel = 5.0f;
    }
    if (key == ALLEGRO_KEY_A) {
      slv::entity_id player_id = slv::mgr::world::get_id("player");
      player_pols::x = -1.0f;
      const float rad = std::atan2(player_pols::y, player_pols::x);
      slv::mgr::world::set_component<slv::cmp::motion>(player_id)->direction = rad;
      slv::mgr::world::set_component<slv::cmp::motion>(player_id)->x_vel = 5.0f;
      slv::mgr::world::set_component<slv::cmp::motion>(player_id)->y_vel = 5.0f;
    }
    if (key == ALLEGRO_KEY_D) {
      slv::entity_id player_id = slv::mgr::world::get_id("player");
      player_pols::x = 1.0f;
      const float rad = std::atan2(player_pols::y, player_pols::x);
      slv::mgr::world::set_component<slv::cmp::motion>(player_id)->direction = rad;
      slv::mgr::world::set_component<slv::cmp::motion>(player_id)->x_vel = 5.0f;
      slv::mgr::world::set_component<slv::cmp::motion>(player_id)->y_vel = 5.0f;
    }
    if (key == ALLEGRO_KEY_RCTRL) {
      slv::entity_id player_id = slv::mgr::world::get_id("player");
      slv::entity_id can_id = slv::mgr::world::get_id("main_cannon");
      //  Set the cannon's location to match the player.
      slv::mgr::world::set_component<slv::cmp::location>(can_id)->pos_x = 
        slv::mgr::world::get_component<slv::cmp::location>(player_id)->pos_x;
      slv::mgr::world::set_component<slv::cmp::location>(can_id)->pos_y = 
        slv::mgr::world::get_component<slv::cmp::location>(player_id)->pos_y -
        slv::mgr::world::get_component<slv::cmp::hitbox>(can_id)->height;

      //  Turn the cannon on.
      slv::mgr::world::set_component<slv::cmp::gfx::sprite>(can_id)->visible = true;
      slv::mgr::world::set_component<slv::cmp::ai>(can_id)->enabled = true;
      slv::mgr::world::set_component<slv::cmp::hitbox>(can_id)->solid = true;
      //  Play sound effect.
      slv::mgr::audio::sample::play(slv::mgr::assets::get<ALLEGRO_SAMPLE>("laser"), "cannon_fire");
    }
    if (key == ALLEGRO_KEY_ALTGR) {
      slv::entity_id player_id = slv::mgr::world::get_id("player");
      slv::entity_id shd_id = slv::mgr::world::get_id("shield");
      //  Set the shield's location to match the player
      slv::mgr::world::set_component<slv::cmp::location>(shd_id)->pos_x =
        slv::mgr::world::get_component<slv::cmp::location>(player_id)->pos_x - 28.0f;
      slv::mgr::world::set_component<slv::cmp::location>(shd_id)->pos_y =
        slv::mgr::world::get_component<slv::cmp::location>(player_id)->pos_y - 16.0f;

      if (slv::mgr::world::set_component<energy>(shd_id)->amt > 0) {
        //  Enable the shield.
        slv::mgr::world::set_component<slv::cmp::gfx::sprite>(shd_id)->visible = true;
        slv::mgr::world::set_component<slv::cmp::ai>(shd_id)->enabled = true;
        slv::mgr::world::set_component<slv::cmp::hitbox>(shd_id)->solid = true;
        slv::mgr::world::set_component<slv::cmp::hitbox>(player_id)->solid = false;
        //  Play sound effect.
        slv::mgr::audio::sample::play(slv::mgr::assets::get<ALLEGRO_SAMPLE>("shield"), "shield_sound");
      }
    }
  });

  /* Game handlers - key up */
  slv::add_handler<slv::SCOPE_B, slv::EVENT_KEY_UP, slv::handler::key>([](const int& key, ALLEGRO_DISPLAY* display) {
    if (key == ALLEGRO_KEY_W) {
      slv::entity_id player_id = slv::mgr::world::get_id("player");
      if (player_pols::y < 0.0f) player_pols::y = 0.0f;
      if (player_pols::x == 0.0f && player_pols::y == 0.0f) {
        slv::mgr::world::set_component<slv::cmp::motion>(player_id)->x_vel = 0.0f;
        slv::mgr::world::set_component<slv::cmp::motion>(player_id)->y_vel = 0.0f;
      }
    }
    if (key == ALLEGRO_KEY_S) {
      slv::entity_id player_id = slv::mgr::world::get_id("player");
      if (player_pols::y > 0.0f) player_pols::y = 0.0f;
      if (player_pols::x == 0.0f && player_pols::y == 0.0f) {
        slv::mgr::world::set_component<slv::cmp::motion>(player_id)->x_vel = 0.0f;
        slv::mgr::world::set_component<slv::cmp::motion>(player_id)->y_vel = 0.0f;
      }
    }
    if (key == ALLEGRO_KEY_A) {
      slv::entity_id player_id = slv::mgr::world::get_id("player");
      if (player_pols::x < 0.0f) player_pols::x = 0.0f;
      if (player_pols::x == 0.0f && player_pols::y == 0.0f) {
        slv::mgr::world::set_component<slv::cmp::motion>(player_id)->x_vel = 0.0f;
        slv::mgr::world::set_component<slv::cmp::motion>(player_id)->y_vel = 0.0f;
      }
    }
    if (key == ALLEGRO_KEY_D) {
      slv::entity_id player_id = slv::mgr::world::get_id("player");
      if (player_pols::x > 0.0f) player_pols::x = 0.0f;
      if (player_pols::x == 0.0f && player_pols::y == 0.0f) {
        slv::mgr::world::set_component<slv::cmp::motion>(player_id)->x_vel = 0.0f;
        slv::mgr::world::set_component<slv::cmp::motion>(player_id)->y_vel = 0.0f;
      }
    }
    if (key == ALLEGRO_KEY_RCTRL) {
      //  Turn the cannon off.
      slv::entity_id can_id = slv::mgr::world::get_id("main_cannon");
      slv::mgr::world::set_component<slv::cmp::gfx::sprite>(can_id)->visible = false;
      slv::mgr::world::set_component<slv::cmp::ai>(can_id)->enabled = false;
      slv::mgr::world::set_component<slv::cmp::hitbox>(can_id)->solid = false;
      //  Stop sound effect.
      slv::mgr::audio::sample::stop("cannon_fire");
    }
    if (key == ALLEGRO_KEY_ALTGR) {
      slv::entity_id player_id = slv::mgr::world::get_id("player");
      slv::entity_id shd_id = slv::mgr::world::get_id("shield");
      //  Disable shield.
      slv::mgr::world::set_component<slv::cmp::gfx::sprite>(shd_id)->visible = false;
      slv::mgr::world::set_component<slv::cmp::ai>(shd_id)->enabled = false;
      slv::mgr::world::set_component<slv::cmp::hitbox>(shd_id)->solid = false;
      slv::mgr::world::set_component<slv::cmp::hitbox>(player_id)->solid = true;
      //  Stop sound effect.
      slv::mgr::audio::sample::stop("shield_sound");
    }
  });

  /* ********************************* */
  /* *** Game variables ************** */
  /* ********************************* */
  slv::mgr::variables::reg<int64_t>("score", 0);
  slv::mgr::variables::reg<int64_t>("hiscore", 0);
  slv::mgr::variables::reg<int64_t>("max_lives", 3);
  slv::mgr::variables::reg<int64_t>("lives", 3);

  slv::mgr::variables::set_data_file("game.cfg");
  slv::mgr::variables::load<int64_t>("max_lives");
  slv::mgr::variables::load<int64_t>("hiscore");


  /* ********************************* */
  /* *** Asset loading *************** */
  /* ********************************* */
  slv::mgr::assets::load<ALLEGRO_BITMAP>(
    "starfield",
    slv::make_asset<ALLEGRO_BITMAP>(slv::config::gfx::viewport_w, slv::config::gfx::viewport_h)
  );
  slv::mgr::assets::load<ALLEGRO_BITMAP>("score_overlay", slv::make_asset<ALLEGRO_BITMAP>(200, 20));
  slv::mgr::assets::load<ALLEGRO_BITMAP>("player_info_overlay", slv::make_asset<ALLEGRO_BITMAP>(200, 20));
  slv::mgr::assets::load<ALLEGRO_BITMAP>("title_screen", slv::make_asset<ALLEGRO_BITMAP>("title.bmp"));
  slv::mgr::assets::load<ALLEGRO_BITMAP>("game_over_overlay", slv::make_asset<ALLEGRO_BITMAP>("game_over.png"));
  slv::mgr::assets::load<ALLEGRO_BITMAP>("ship", slv::make_asset<ALLEGRO_BITMAP>("ship.png"));
  slv::mgr::assets::load<ALLEGRO_BITMAP>("cannon", slv::make_asset<ALLEGRO_BITMAP>("cannon.png"));
  slv::mgr::assets::load<ALLEGRO_BITMAP>("shield", slv::make_asset<ALLEGRO_BITMAP>("shield.png"));
  slv::mgr::assets::load<ALLEGRO_BITMAP>("asteroid", slv::make_asset<ALLEGRO_BITMAP>("asteroid.png"));

  //  Load music for the demo into the asset manager.
  slv::mgr::assets::load<ALLEGRO_AUDIO_STREAM>("music", slv::make_asset<ALLEGRO_AUDIO_STREAM>("music.ogg"));
  //  Load some samples in the asset manager.
  slv::mgr::assets::load<ALLEGRO_SAMPLE>("laser", slv::make_asset<ALLEGRO_SAMPLE>("laser.wav"));
  slv::mgr::assets::load<ALLEGRO_SAMPLE>("shield", slv::make_asset<ALLEGRO_SAMPLE>("shield.wav"));
  slv::mgr::assets::load<ALLEGRO_SAMPLE>("explosion", slv::make_asset<ALLEGRO_SAMPLE>("explosion.wav"));

  /* **************************************************** */
  /* *** ENTITY CREATION ******************************** */
  /* **************************************************** */
  /* ************************************ */
  /* *** Title Screen overlay entity **** */
  /* ************************************ */
  slv::mgr::spawner::add("title_screen", 0,
    [](const slv::entity_id& e_id, const slv::msg_args& args) {
      slv::mgr::world::set_name(e_id, "title_screen");
      slv::mgr::world::add_component<slv::cmp::gfx::overlay>(e_id,
        slv::mgr::assets::get<ALLEGRO_BITMAP>("title_screen"),
        slv::mgr::assets::get<ALLEGRO_FONT>("slv_default_font"),
        layer::background, 0, 0,
        [](const slv::entity_id& e_id) {}
      );
    }
  );

  /* ********************************* */
  /* *** Background entity *********** */
  /* ********************************* */
  slv::mgr::spawner::add("starfield", 0,
    [](const slv::entity_id& e_id, const slv::msg_args& args) {
      slv::mgr::world::set_name(e_id, "starfield");
      slv::mgr::world::add_component<stars>(e_id);
      slv::mgr::world::add_component<slv::cmp::gfx::background>(e_id,
        slv::mgr::assets::get<ALLEGRO_BITMAP>("starfield"), layer::background, 0, 0,
        [](const slv::entity_id& bkg_id) {
          //  Define the animation process for the starfield.
          slv::mgr::world::set_component<slv::cmp::gfx::background>(bkg_id)->set_drawing();
          al_clear_to_color(al_map_rgb(0,0,0));

          //  Move the stars.
          for (std::size_t i = 0; i < MAX_STARS; i++) {
            slv::mgr::world::set_component<stars>(bkg_id)->y[i] +=
              slv::mgr::world::get_component<stars>(bkg_id)->speed[i] * slv::mgr::world::get_component<stars>(bkg_id)->speed_mult;
            if (slv::mgr::world::get_component<stars>(bkg_id)->y[i] > slv::config::gfx::viewport_h) {
              //  Make a new star.
              slv::mgr::world::set_component<stars>(bkg_id)->x[i] =
                std::rand() % slv::config::gfx::viewport_w + 1;
              slv::mgr::world::set_component<stars>(bkg_id)->y[i] = 0;
              slv::mgr::world::set_component<stars>(bkg_id)->speed[i] = (std::rand() % 3 + 1) * 3;
              slv::mgr::world::set_component<stars>(bkg_id)->color[i] = std::rand() % 4 + 1;
            }
          }

          //  Draw the stars.
          for (std::size_t i = 0; i < MAX_STARS; i++) {
            if (slv::mgr::world::get_component<stars>(bkg_id)->color[i] == 1 ||
            slv::mgr::world::get_component<stars>(bkg_id)->color[i] == 4)
              al_draw_pixel(slv::mgr::world::get_component<stars>(bkg_id)->x[i],
                            slv::mgr::world::get_component<stars>(bkg_id)->y[i], al_map_rgb(255,255,255));
            if (slv::mgr::world::get_component<stars>(bkg_id)->color[i] == 2)
              al_draw_pixel(slv::mgr::world::get_component<stars>(bkg_id)->x[i],
                            slv::mgr::world::get_component<stars>(bkg_id)->y[i], al_map_rgb(255,255,0));
            if (slv::mgr::world::get_component<stars>(bkg_id)->color[i] == 3)
              al_draw_pixel(slv::mgr::world::get_component<stars>(bkg_id)->x[i],
                            slv::mgr::world::get_component<stars>(bkg_id)->y[i], al_map_rgb(255,0,0));
          }
        });  //  End background rendering.

        slv::mgr::world::add_component<slv::cmp::dispatcher>(e_id,
          [](const slv::entity_id& bkg_id, const slv::message& msg) {
            //  Define message processing for the starfield.
            if (msg.get_cmd() == "default") slv::mgr::world::set_component<stars>(bkg_id)->speed_mult = 1;
            if (msg.get_cmd() == "up") slv::mgr::world::set_component<stars>(bkg_id)->speed_mult *= 2;
            if (msg.get_cmd() == "down") slv::mgr::world::set_component<stars>(bkg_id)->speed_mult /= 2;
            if (msg.get_cmd() == "reset") {
              slv::mgr::world::set_component<stars>(bkg_id)->speed_mult = 1;

              for (std::size_t i = 0; i < MAX_STARS; i++) {
                slv::mgr::world::set_component<stars>(bkg_id)->x[i] =
                  std::rand() % slv::config::gfx::viewport_w + 1;
                slv::mgr::world::set_component<stars>(bkg_id)->y[i] =
                  std::rand() % slv::config::gfx::viewport_h + 1;
                slv::mgr::world::set_component<stars>(bkg_id)->speed[i] = (std::rand() % 3 + 1) * 3;
                slv::mgr::world::set_component<stars>(bkg_id)->color[i] = std::rand() % 4 + 1;
              }
            }
          }  //  End starfield message processing.
        );  //  End dispatcher component.
    }
  );

  /* ********************************* */
  /* *** Score overlay entity ******** */
  /* ********************************* */
  slv::mgr::spawner::add("score_overlay", 0,
    [](const slv::entity_id& e_id, const slv::msg_args& args) {
      slv::mgr::world::set_name(e_id, "score_overlay");
      slv::mgr::world::add_component<slv::cmp::gfx::overlay>(e_id,
        slv::mgr::assets::get<ALLEGRO_BITMAP>("score_overlay"),
        slv::mgr::assets::get<ALLEGRO_FONT>("slv_default_font"),
        layer::overlay, 0, slv::config::gfx::viewport_h - 20,
        [](const slv::entity_id& ovr_id) {
          //  Define what gets displayed on the overlay.
          slv::mgr::world::set_component<slv::cmp::gfx::overlay>(ovr_id)->set_drawing();
          al_clear_to_color(al_map_rgba(0,0,0,0));
          slv::mgr::world::set_component<slv::cmp::gfx::overlay>(ovr_id)->draw_text("Score:  ", al_map_rgb(255,255,255), 110, 0, ALLEGRO_ALIGN_RIGHT);
          slv::mgr::world::set_component<slv::cmp::gfx::overlay>(ovr_id)->draw_text(std::to_string(slv::mgr::variables::get<int64_t>("score")), al_map_rgb(255,255,255), 110, 0, ALLEGRO_ALIGN_LEFT);
          slv::mgr::world::set_component<slv::cmp::gfx::overlay>(ovr_id)->draw_text("High Score:  ", al_map_rgb(255,255,255), 110, 10, ALLEGRO_ALIGN_RIGHT);
          slv::mgr::world::set_component<slv::cmp::gfx::overlay>(ovr_id)->draw_text(std::to_string(slv::mgr::variables::get<int64_t>("hiscore")), al_map_rgb(255,255,255), 110, 10, ALLEGRO_ALIGN_LEFT);
        }
      );  //  End score overlay drawing.
    }
  );

  /* ********************************* */
  /* *** Player Info overlay entity ** */
  /* ********************************* */
  slv::mgr::spawner::add("player_info_overlay", 0,
    [](const slv::entity_id& e_id, const slv::msg_args& args) {
      slv::mgr::world::set_name(e_id, "player_info_overlay");
      slv::mgr::world::add_component<slv::cmp::gfx::overlay>(e_id,
        slv::mgr::assets::get<ALLEGRO_BITMAP>("player_info_overlay"),
        slv::mgr::assets::get<ALLEGRO_FONT>("slv_default_font"), layer::overlay,
        slv::config::gfx::viewport_w - 200, slv::config::gfx::viewport_h - 20,
        [](const slv::entity_id& ovr_id) {
          //  Define what gets displayed on the overlay.
          slv::entity_id shd_id = slv::mgr::world::get_id("shield");
          slv::mgr::world::set_component<slv::cmp::gfx::overlay>(ovr_id)->set_drawing();
          al_clear_to_color(al_map_rgba(0,0,0,0));
          al_draw_filled_rectangle((float)(120 - slv::mgr::world::get_component<energy>(shd_id)->amt), 0, 120, 10, al_map_rgb(255,255,0));
          slv::mgr::world::set_component<slv::cmp::gfx::overlay>(ovr_id)->draw_text("Shield", al_map_rgb(255,255,255), 200, 0, ALLEGRO_ALIGN_RIGHT);
          slv::mgr::world::set_component<slv::cmp::gfx::overlay>(ovr_id)->draw_text("Lives:  " + std::to_string(slv::mgr::variables::get<int64_t>("lives")), al_map_rgb(255,255,255), 200, 10, ALLEGRO_ALIGN_RIGHT);
        }
      );  //  End info overlay drawing.
    }
  );

  /* ********************************* */
  /* *** Game Over overlay entity **** */
  /* ********************************* */
  slv::mgr::spawner::add("game_over_overlay", 0,
    [](const slv::entity_id& e_id, const slv::msg_args& args) {
      slv::mgr::world::set_name(e_id, "game_over_overlay");
      slv::mgr::world::add_component<slv::cmp::gfx::overlay>(e_id,
        slv::mgr::assets::get<ALLEGRO_BITMAP>("game_over_overlay"),
        slv::mgr::assets::get<ALLEGRO_FONT>("slv_default_font"),
        layer::overlay, (slv::config::gfx::viewport_w / 2) - 240, (slv::config::gfx::viewport_h / 2) - 66,
        [](const slv::entity_id& ovr_id) {}
      );
      slv::mgr::world::set_component<slv::cmp::gfx::overlay>(e_id)->visible = false;
    }
  );

  /* ********************************* */
  /* *** Player entity *************** */
  /* ********************************* */
  slv::mgr::spawner::add("player", 0,
    [](const slv::entity_id& e_id, const slv::msg_args& args) {
      slv::mgr::world::set_name(e_id, "player");
      slv::mgr::world::add_component<slv::cmp::location>(e_id,
        (slv::config::gfx::viewport_w / 2) - 5,
         slv::config::gfx::viewport_h - 40);
      slv::mgr::world::add_component<slv::cmp::hitbox>(e_id, 10, 10, 0);
      slv::mgr::world::add_component<slv::cmp::bounding_box>(e_id, 12.0f, 0.0f,
        (float)(slv::config::gfx::viewport_w - 21),
        (float)(slv::config::gfx::viewport_h - 32));
      slv::mgr::world::add_component<health>(e_id, 1, 1);
      slv::mgr::world::add_component<slv::cmp::motion>(e_id, 0.0f, 0.0f, 0.0f);
      slv::mgr::world::add_component<slv::cmp::gfx::sprite>(e_id, slv::mgr::assets::get<ALLEGRO_BITMAP>("ship"),
                                     layer::player, 32.0f, 32.0f, -11.0f, 0.0f, 1);
      slv::mgr::world::set_component<slv::cmp::gfx::sprite>(e_id)->add_cycle("main", 0, 3);
      slv::mgr::world::set_component<slv::cmp::gfx::sprite>(e_id)->add_cycle("death", 4, 7);
      slv::mgr::world::set_component<slv::cmp::gfx::sprite>(e_id)->set_cycle("main");

      //  Player logic.
      slv::mgr::world::add_component<slv::cmp::ai>(e_id,
        [](const slv::entity_id& plr_id) {
          if (slv::mgr::world::get_component<health>(plr_id)->hp <= 0) {  //  Check player health.
            slv::mgr::world::set_component<slv::cmp::ai>(plr_id)->enabled = false;
            slv::mgr::world::set_component<health>(plr_id)->hp = slv::mgr::world::get_component<health>(plr_id)->hp_max;
            std::string player_name = slv::mgr::world::get_name(plr_id);
            slv::mgr::messages::add(slv::message("entities", player_name, player_name, "death", ""));
          }
        }
      );  //  End player logic.

      //  Player message handling.
      slv::mgr::world::add_component<slv::cmp::dispatcher>(e_id,
        [](const slv::entity_id& plr_id, const slv::message& msg) {
          //  Process player death.
          if (msg.get_cmd() == "death") {
            slv::config::flags::input_enabled = false;
            //  Make sure cannon stops firing
            slv::entity_id cannon_id = slv::mgr::world::get_id("main_cannon");
            slv::mgr::world::set_component<slv::cmp::gfx::sprite>(cannon_id)->visible = false;
            slv::mgr::world::set_component<slv::cmp::ai>(cannon_id)->enabled = false;
            slv::mgr::world::set_component<slv::cmp::hitbox>(cannon_id)->solid = false;
            slv::mgr::audio::sample::stop("cannon_fire");

            //  Just to make sure... turn shield off
            slv::entity_id shield_id = slv::mgr::world::get_id("shield");
            slv::mgr::world::set_component<slv::cmp::gfx::sprite>(shield_id)->visible = false;
            slv::mgr::world::set_component<slv::cmp::ai>(shield_id)->enabled = false;
            slv::mgr::world::set_component<slv::cmp::hitbox>(shield_id)->solid = false;
            slv::mgr::audio::sample::stop("shield_sound");

            slv::mgr::world::set_component<slv::cmp::hitbox>(plr_id)->solid = false;

            slv::mgr::audio::sample::play(slv::mgr::assets::get<ALLEGRO_SAMPLE>("explosion"), "once");
            slv::mgr::variables::set<int64_t>("lives", slv::mgr::variables::get<int64_t>("lives") - 1);
            slv::mgr::world::set_component<slv::cmp::motion>(plr_id)->x_vel = 0.0f;
            slv::mgr::world::set_component<slv::cmp::motion>(plr_id)->y_vel = 0.0f;
            slv::mgr::world::set_component<slv::cmp::gfx::sprite>(plr_id)->set_cycle("death");
            if (slv::mgr::variables::get<int64_t>("lives") == 0) {
              slv::mgr::audio::music::a::stop();
              //  Game over!  Show the overlay.
              slv::entity_id go_id = slv::mgr::world::get_id("game_over_overlay");
              slv::mgr::world::set_component<slv::cmp::gfx::overlay>(go_id)->visible = true;
              //  Wait a bit then end the game.
              slv::mgr::messages::add(slv::message(slv::engine_time::check() + 180, "system", "enable-input", ""));
              slv::mgr::messages::add(slv::message(slv::engine_time::check() + 180, "system", "load-scene", "title_scene"));
            } else {
              std::string player_name = slv::mgr::world::get_name(plr_id);
              slv::mgr::messages::add(
                slv::message(slv::engine_time::check() + 120, "entities", player_name, player_name, "reset", "")
              );
            }
          }

          //  Reset player.
          if (msg.get_cmd() == "reset") {
            slv::config::flags::input_enabled = true;
            player_pols::reset();
            slv::mgr::world::set_component<slv::cmp::motion>(plr_id)->x_vel = 0.0f;
            slv::mgr::world::set_component<slv::cmp::motion>(plr_id)->y_vel = 0.0f;
            slv::mgr::world::set_component<slv::cmp::location>(plr_id)->pos_x = (float)((slv::config::gfx::viewport_w / 2) - 5);
            slv::mgr::world::set_component<slv::cmp::location>(plr_id)->pos_y = (float)(slv::config::gfx::viewport_h - 40);
            slv::mgr::world::set_component<health>(plr_id)->hp = slv::mgr::world::get_component<health>(plr_id)->hp_max;
            slv::mgr::world::set_component<slv::cmp::ai>(plr_id)->enabled = true;
            slv::mgr::world::set_component<slv::cmp::gfx::sprite>(plr_id)->set_cycle("main");
            slv::mgr::world::set_component<slv::cmp::hitbox>(plr_id)->solid = true;
          }

          //  Take damage.
          if (msg.get_cmd() == "damage") {
            slv::mgr::world::set_component<health>(plr_id)->hp -= std::stoi(msg.get_arg(0));
          }
        }
      );  //  End player message processing.
    }
  );

  /* ********************************* */
  /* *** Main cannon entity ********** */
  /* ********************************* */
  slv::mgr::spawner::add("main_cannon", 0,
    [](const slv::entity_id& e_id, const slv::msg_args& args) {
      slv::mgr::world::set_name(e_id, "main_cannon");
      slv::mgr::world::add_component<slv::cmp::location>(e_id, 0, 0);
      slv::mgr::world::add_component<slv::cmp::hitbox>(e_id, 10, 200, 0, false);
      slv::mgr::world::set_component<slv::cmp::hitbox>(e_id)->solid = false;
      slv::mgr::world::add_component<damage>(e_id, 3);
      slv::mgr::world::add_component<slv::cmp::gfx::sprite>(e_id, slv::mgr::assets::get<ALLEGRO_BITMAP>("cannon"),
                                          layer::player, 10.0f, 200.0f, 0.0f, 0.0f, 2);
      slv::mgr::world::set_component<slv::cmp::gfx::sprite>(e_id)->add_cycle("main", 0, 3);
      slv::mgr::world::set_component<slv::cmp::gfx::sprite>(e_id)->set_cycle("main");
      slv::mgr::world::set_component<slv::cmp::gfx::sprite>(e_id)->visible = false;

      //  Cannon logic.
      slv::mgr::world::add_component<slv::cmp::ai>(e_id,
        [](const slv::entity_id& can_id) {
          slv::entity_id player_entity = slv::mgr::world::get_id("player");
          //  Set the cannon's location to match the player.
          slv::mgr::world::set_component<slv::cmp::location>(can_id)->pos_x =
            slv::mgr::world::get_component<slv::cmp::location>(player_entity)->pos_x;
          slv::mgr::world::set_component<slv::cmp::location>(can_id)->pos_y =
            slv::mgr::world::get_component<slv::cmp::location>(player_entity)->pos_y -
            slv::mgr::world::get_component<slv::cmp::hitbox>(can_id)->height;
        }
      );  //  End cannon logic.
      slv::mgr::world::set_component<slv::cmp::ai>(e_id)->enabled = false;

      //  Cannon message processing.
      slv::mgr::world::add_component<slv::cmp::dispatcher>(e_id,
        [](const slv::entity_id& can_id, const slv::message& msg) {
          if (msg.get_cmd() == "colision") {
            //  Deal damage
            slv::mgr::messages::add(slv::message("entities", msg.get_from(), msg.get_to(),
              "damage", std::to_string(slv::mgr::world::get_component<damage>(can_id)->dmg)));
          }
        }
      );  //  End cannon message processing.
    }
  );

  /* ********************************* */
  /* *** Shield entity *************** */
  /* ********************************* */
  slv::mgr::spawner::add("shield", 0,
    [](const slv::entity_id& e_id, const slv::msg_args& args) {
      slv::mgr::world::set_name(e_id, "shield");
      slv::mgr::world::add_component<slv::cmp::location>(e_id, 0, 0);
      slv::mgr::world::add_component<slv::cmp::hitbox>(e_id, 64, 64, 0, false);
      slv::mgr::world::set_component<slv::cmp::hitbox>(e_id)->solid = false;
      slv::mgr::world::add_component<energy>(e_id, 50, 100);
      slv::mgr::world::add_component<damage>(e_id, 100);
      slv::mgr::world::add_component<slv::cmp::gfx::sprite>(e_id, slv::mgr::assets::get<ALLEGRO_BITMAP>("shield"),
                                          layer::player, 64.0f, 64.0f, 0.0f, 0.0f, 6);
      slv::mgr::world::set_component<slv::cmp::gfx::sprite>(e_id)->add_cycle("main", 0, 5);
      slv::mgr::world::set_component<slv::cmp::gfx::sprite>(e_id)->set_cycle("main");
      slv::mgr::world::set_component<slv::cmp::gfx::sprite>(e_id)->visible = false;

      //  Shield logic.
      slv::mgr::world::add_component<slv::cmp::ai>(e_id,
        //  Enabeled AI.
        [](const slv::entity_id& shd_id) {
          slv::entity_id player_entity = slv::mgr::world::get_id("player");
          //  Set the shield's location to match the player.
          slv::mgr::world::set_component<slv::cmp::location>(shd_id)->pos_x =
            slv::mgr::world::get_component<slv::cmp::location>(player_entity)->pos_x - 28.0f;
          slv::mgr::world::set_component<slv::cmp::location>(shd_id)->pos_y =
            slv::mgr::world::get_component<slv::cmp::location>(player_entity)->pos_y - 16.0f;

          //  Drain the shield.
          if (slv::mgr::world::set_component<energy>(shd_id)->amt > 0)
            slv::mgr::world::set_component<energy>(shd_id)->amt -= 1;

          if (slv::mgr::world::get_component<energy>(shd_id)->amt <= 0) {
            //  Disable shield.
            slv::mgr::world::set_component<slv::cmp::gfx::sprite>(shd_id)->visible = false;
            slv::mgr::world::set_component<slv::cmp::ai>(shd_id)->enabled = false;
            slv::mgr::world::set_component<slv::cmp::hitbox>(player_entity)->solid = true;
            //  Stop sound effect.
            slv::mgr::audio::sample::stop("shield_sound");
          }
        },
        //  Disabeled AI.
        [](const slv::entity_id& shd_id) {
          //  Recharge the shield.
          if (slv::mgr::world::set_component<energy>(shd_id)->amt < slv::mgr::world::set_component<energy>(shd_id)->amt_max)
            slv::mgr::world::set_component<energy>(shd_id)->amt += 1;
        }
      );  //  End shield logic.
      slv::mgr::world::set_component<slv::cmp::ai>(e_id)->enabled = false;

      //  Shield message processing.
      slv::mgr::world::add_component<slv::cmp::dispatcher>(e_id,
        [](const slv::entity_id& shd_id, const slv::message& msg) {
          if (msg.get_cmd() == "colision") {
            //  Deal damage
            slv::mgr::messages::add(slv::message("entities", msg.get_from(), msg.get_to(),
              "damage", std::to_string(slv::mgr::world::get_component<damage>(shd_id)->dmg)));
          }
        }
      );  //  End shield message processing.
    }
  );

  /* ************************************** */
  /* Add the asteroid entity to the spawner */
  /* Arguments:                             */
  /*  (1) X location                        */
  /*  (2) Y location                        */
  /*  (3) Direction in degrees              */
  /*  (4) Velocity                          */
  /*  (5) Size                              */
  /* ************************************** */
  slv::mgr::spawner::add("asteroid", 5,
    [](const slv::entity_id& e_id, const slv::msg_args& args) {
      int temp_size = std::stoi(args[5]);
      if (temp_size < 1) temp_size = 1;
      if (temp_size > 8) temp_size = 8;

      slv::mgr::world::set_name(e_id, "asteroid" + std::to_string(e_id));
      slv::mgr::world::add_component<slv::cmp::location>(e_id, std::stof(args[1]), std::stof(args[2]));
      slv::mgr::world::add_component<slv::cmp::hitbox>(e_id, (float)(temp_size * 16), (float)(temp_size * 16), 1);
      slv::mgr::world::add_component<health>(e_id, temp_size * 10, temp_size * 10);
      slv::mgr::world::add_component<damage>(e_id, 10);
      slv::mgr::world::add_component<size>(e_id, temp_size);
      slv::mgr::world::add_component<slv::cmp::motion>(e_id, 0.0f, 0.0f, 0.0f);
      slv::mgr::world::set_component<slv::cmp::motion>(e_id)->direction = std::stof(args[3]) * (M_PI / 180);
      slv::mgr::world::set_component<slv::cmp::motion>(e_id)->x_vel = std::stof(args[4]);
      slv::mgr::world::set_component<slv::cmp::motion>(e_id)->y_vel = std::stof(args[4]);

      slv::mgr::world::add_component<slv::cmp::gfx::sprite>(e_id, slv::mgr::assets::get<ALLEGRO_BITMAP>("asteroid"),
        layer::enemy, 16.0f, 16.0f, 0.0f, 0.0f, (int)(30 / std::stof(args[4])));
      slv::mgr::world::set_component<slv::cmp::gfx::sprite>(e_id)->add_cycle("main", 0, 5);
      slv::mgr::world::set_component<slv::cmp::gfx::sprite>(e_id)->set_cycle("main");
      slv::mgr::world::set_component<slv::cmp::gfx::sprite>(e_id)->scale_factor_x = (float)temp_size;
      slv::mgr::world::set_component<slv::cmp::gfx::sprite>(e_id)->scale_factor_y = (float)temp_size;
      slv::mgr::world::set_component<slv::cmp::gfx::sprite>(e_id)->rotated = true;
      slv::mgr::world::set_component<slv::cmp::gfx::sprite>(e_id)->direction = std::stof(args[3]) * (M_PI / 180);

      //  Asteroid logic.
      slv::mgr::world::add_component<slv::cmp::ai>(e_id,
        [](const slv::entity_id& ast_id) {
          //  AI for asteroids defined here.
          //  Perform OOB check.
          if (slv::mgr::world::get_component<slv::cmp::location>(ast_id)->pos_y > (float)(slv::config::gfx::viewport_h + 100)) {
            slv::mgr::messages::add(slv::message("spawner", "delete", slv::mgr::world::get_name(ast_id)));
          }

          //  Health check.  If asteroid's HP is <= 0, reward player with points and delete the entity.
          if (slv::mgr::world::get_component<health>(ast_id)->hp <= 0) {
            slv::mgr::messages::add(slv::message("spawner", "delete", slv::mgr::world::get_name(ast_id)));
            slv::mgr::audio::sample::play(slv::mgr::assets::get<ALLEGRO_SAMPLE>("explosion"), "once", 1.0f, ALLEGRO_AUDIO_PAN_NONE, 1.8f);

            //  Increase the score.
            slv::mgr::variables::set("score",
              (slv::mgr::variables::get<int64_t>("score") +
              (10 * slv::mgr::world::get_component<size>(ast_id)->the_size)));

            //  If the current score is the new hiscore, update.
            if (slv::mgr::variables::get<int64_t>("score") > slv::mgr::variables::get<int64_t>("hiscore")) {
              slv::mgr::variables::set("hiscore", slv::mgr::variables::get<int64_t>("score"));
            }

            //  If the asteroid was size >= 4, split into two.
            if (slv::mgr::world::get_component<size>(ast_id)->the_size >= 4) {
              const int new_size = slv::mgr::world::get_component<size>(ast_id)->the_size / 2;
              float dir_a = slv::mgr::world::get_component<slv::cmp::motion>(ast_id)->direction - 90.0f;
              if (dir_a < 0.0f) dir_a = 0.0f;
              float dir_b = slv::mgr::world::get_component<slv::cmp::motion>(ast_id)->direction + 90.0f;
              if (dir_b > 360.0f) dir_b = 360.0f;
              const float new_x = slv::mgr::world::get_component<slv::cmp::location>(ast_id)->pos_x;
              const float new_y = slv::mgr::world::get_component<slv::cmp::location>(ast_id)->pos_y;
              const float new_vel = slv::mgr::world::get_component<slv::cmp::motion>(ast_id)->x_vel / 2;
              std::string new_spawner_a = "asteroid;" + std::to_string(new_x) + ";" +
                std::to_string(new_y) + ";" + std::to_string(dir_a) + ";" +
                std::to_string(new_vel) + ";" + std::to_string(new_size);
              std::string new_spawner_b = "asteroid;" + std::to_string(new_x) + ";" +
                std::to_string(new_y) + ";" + std::to_string(dir_b) + ";" +
                std::to_string(new_vel) + ";" + std::to_string(new_size);
              slv::mgr::messages::add(slv::message("spawner", "new", new_spawner_a));
              slv::mgr::messages::add(slv::message("spawner", "new", new_spawner_b));
            }
          }
        }
      );  //  End asteroid AI

      //  Asteroid message processing.
      slv::mgr::world::add_component<slv::cmp::dispatcher>(e_id,
        [](const slv::entity_id& ast_id, const slv::message& msg) {
          if (msg.get_cmd() == "colision") {
            //  Deal damage
            slv::mgr::messages::add(slv::message("entities", msg.get_from(), msg.get_to(),
              "damage", std::to_string(slv::mgr::world::get_component<damage>(ast_id)->dmg)));
          }

          if (msg.get_cmd() == "damage") {
            slv::mgr::world::set_component<health>(ast_id)->hp -= std::stoi(msg.get_arg(0));
          }
        }
      );  //  End asteroid message dispatching.
    }  //  End asteroid spawner function.
  );
  /* **************************************************** */
  /* *** END ENTITY CREATION **************************** */
  /* **************************************************** */

  slv::mgr::audio::set_level(0.5f);  //  Set main audio level.
  slv::engine::load_scene("title_scene");  //  Load a scene.
  slv::start_game();  //  Run the game loop.

  slv::engine::deinitialize();
  return 0;
}
