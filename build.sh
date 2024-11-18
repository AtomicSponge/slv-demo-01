#!/bin/sh

set -e

mkdir -p build
cd build
cmake ..
cmake --build . -t slvdemo

#  Copy assets
ASSETS_DIR=assets
BUILD_DIR=build
cd ..
cp -r ${ASSETS_DIR}/asteroid.png ${BUILD_DIR}
cp -r ${ASSETS_DIR}/background_control.sdf ${BUILD_DIR}
cp -r ${ASSETS_DIR}/cannon.png ${BUILD_DIR}
cp -r ${ASSETS_DIR}/explosion.wav ${BUILD_DIR}
cp -r ${ASSETS_DIR}/game_over.png ${BUILD_DIR}
cp -r ${ASSETS_DIR}/game.sdf ${BUILD_DIR}
cp -r ${ASSETS_DIR}/icon.bmp ${BUILD_DIR}
cp -r ${ASSETS_DIR}/laser.wav ${BUILD_DIR}
cp -r ${ASSETS_DIR}/music.ogg ${BUILD_DIR}
cp -r ${ASSETS_DIR}/shield.png ${BUILD_DIR}
cp -r ${ASSETS_DIR}/shield.wav ${BUILD_DIR}
cp -r ${ASSETS_DIR}/ship.png ${BUILD_DIR}
cp -r ${ASSETS_DIR}/spawn_asteroids.sdf ${BUILD_DIR}
cp -r ${ASSETS_DIR}/title.bmp ${BUILD_DIR}
