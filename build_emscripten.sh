#!/bin/bash

set -e

ASSETS_DIR=assets
BUILD_DIR=build_emscripten

mkdir -p ${BUILD_DIR}
mkdir -p ${BUILD_DIR}/${ASSETS_DIR}

#  Copy assets
cp -r ${ASSETS_DIR}/asteroid.png ${BUILD_DIR}/${ASSETS_DIR}
cp -r ${ASSETS_DIR}/background_control.sdf ${BUILD_DIR}/${ASSETS_DIR}
cp -r ${ASSETS_DIR}/cannon.png ${BUILD_DIR}/${ASSETS_DIR}
cp -r ${ASSETS_DIR}/explosion.wav ${BUILD_DIR}/${ASSETS_DIR}
cp -r ${ASSETS_DIR}/game_over.png ${BUILD_DIR}/${ASSETS_DIR}
cp -r ${ASSETS_DIR}/game.sdf ${BUILD_DIR}/${ASSETS_DIR}
cp -r ${ASSETS_DIR}/icon.bmp ${BUILD_DIR}/${ASSETS_DIR}
cp -r ${ASSETS_DIR}/laser.wav ${BUILD_DIR}/${ASSETS_DIR}
cp -r ${ASSETS_DIR}/music.ogg ${BUILD_DIR}/${ASSETS_DIR}
cp -r ${ASSETS_DIR}/shield.png ${BUILD_DIR}/${ASSETS_DIR}
cp -r ${ASSETS_DIR}/shield.wav ${BUILD_DIR}/${ASSETS_DIR}
cp -r ${ASSETS_DIR}/ship.png ${BUILD_DIR}/${ASSETS_DIR}
cp -r ${ASSETS_DIR}/spawn_asteroids.sdf ${BUILD_DIR}/${ASSETS_DIR}
cp -r ${ASSETS_DIR}/title.png ${BUILD_DIR}/${ASSETS_DIR}

cd ${BUILD_DIR}

USE_FLAGS=(
  --use-port=freetype
  --use-port=vorbis
  --use-port=ogg
  --use-port=libjpeg
  --use-port=sdl2
  --use-port=libpng
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
  -D CMAKE_EXE_LINKER_FLAGS="${USE_FLAGS[*]} -s FULL_ES2=1 --preload-file ${ASSETS_DIR}@" \
  -D CMAKE_EXECUTABLE_SUFFIX_CXX=".html"

cmake --build . -t slvdemo
