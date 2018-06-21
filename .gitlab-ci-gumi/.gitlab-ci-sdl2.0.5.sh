#!/bin/sh

wget --no-cache https://hg.libsdl.org/SDL/archive/007dfe83abf8.tar.gz
wget --no-cache https://hg.libsdl.org/SDL_image/archive/20954174d833.tar.gz
wget --no-cache https://hg.libsdl.org/SDL_ttf/archive/62fc3433538d.tar.gz
wget --no-cache https://hg.libsdl.org/SDL_mixer/archive/7e59d684b070.tar.gz
tar -xf 007dfe83abf8.tar.gz
tar -xf 20954174d833.tar.gz
tar -xf 62fc3433538d.tar.gz
tar -xf 7e59d684b070.tar.gz
cd SDL-007dfe83abf8/
./configure && make && make install
cd -
cd SDL_image-20954174d833/
./configure && make && make install
cd -
cd SDL_ttf-62fc3433538d/
./configure && make && make install
cd -
cd SDL_mixer-7e59d684b070/
./configure && make && make install
cd -
