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
  -D CMAKE_EXE_LINKER_FLAGS="${USE_FLAGS[*]} --preload-file assets@" \
  -D CMAKE_EXECUTABLE_SUFFIX_CXX=".html"

cmake --build . -t slvdemo
