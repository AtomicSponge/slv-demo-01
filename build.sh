#!/bin/sh

set -e

mkdir -p build
cd build
cmake ..
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
