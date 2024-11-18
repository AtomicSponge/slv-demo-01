#!/bin/bash

set -e

mkdir -p build_emscripten
cd build_emscripten

USE_FLAGS=(
  -s USE_FREETYPE=1
  -s USE_VORBIS=1
  -s USE_OGG=1
  -s USE_LIBJPEG=1
  -s USE_SDL=2
  -s USE_LIBPNG=1
  -s FULL_ES2=1
  -s ASYNCIFY
  -O3
)

# Wish I knew how to remove this.
SDL2_INCLUDE_DIR=$(dirname $(which emcc))/cache/sysroot/include

emcmake cmake .. \
  -D CMAKE_BUILD_TYPE=Release \
  -D ALLEGRO_SDL=ON \
  -D WANT_ALLOW_SSE=OFF \
  -D WANT_OPENAL=OFF \
  -D ALLEGRO_WAIT_EVENT_SLEEP=ON \
  -D SDL2_INCLUDE_DIR="$SDL2_INCLUDE_DIR" \
  -D CMAKE_C_FLAGS="${USE_FLAGS[*]}" \
  -D CMAKE_CXX_FLAGS="${USE_FLAGS[*]}" \
  -D CMAKE_EXE_LINKER_FLAGS="${USE_FLAGS[*]}" \
  -D CMAKE_EXECUTABLE_SUFFIX_CXX=".html"

cmake --build . -t slvdemo

#  Copy assets
cd ..
cp -r assets/asteroid.png build
cp -r assets/background_control.sdf build
cp -r assets/cannon.png build
cp -r assets/explosion.wav build
cp -r assets/game_over.png build
cp -r assets/game.sdf build
cp -r assets/icon.bmp build
cp -r assets/laser.wav build
cp -r assets/music.ogg build
cp -r assets/shield.png build
cp -r assets/shield.wav build
cp -r assets/ship.png build
cp -r assets/spawn_asteroids.sdf build
cp -r assets/title.bmp build
