#!/bin/sh

wget --no-cache https://hg.libsdl.org/SDL/archive/2088cd828335.tar.gz
wget --no-cache https://hg.libsdl.org/SDL_image/archive/c28eb37178a1.tar.gz
wget --no-cache https://hg.libsdl.org/SDL_ttf/archive/62fc3433538d.tar.gz
wget --no-cache https://hg.libsdl.org/SDL_mixer/archive/c593f8bf25c3.tar.gz
tar -xf 2088cd828335.tar.gz
tar -xf c28eb37178a1.tar.gz
tar -xf 62fc3433538d.tar.gz
tar -xf c593f8bf25c3.tar.gz
cd SDL-2088cd828335/
./configure && make && make install
cd -
cd SDL_image-c28eb37178a1/
./configure && make && make install
cd -
cd SDL_ttf-62fc3433538d/
./configure && make && make install
cd -
cd SDL_mixer-c593f8bf25c3/
./configure && make && make install
cd -
