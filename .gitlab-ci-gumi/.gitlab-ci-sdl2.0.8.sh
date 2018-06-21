#!/bin/sh

wget --no-cache https://hg.libsdl.org/SDL/archive/f1084c419f33.tar.gz
wget --no-cache https://hg.libsdl.org/SDL_image/archive/45e1826592df.tar.gz
wget --no-cache https://hg.libsdl.org/SDL_ttf/archive/62fc3433538d.tar.gz
wget --no-cache https://hg.libsdl.org/SDL_mixer/archive/c593f8bf25c3.tar.gz
tar -xf f1084c419f33.tar.gz
tar -xf 45e1826592df.tar.gz
tar -xf 62fc3433538d.tar.gz
tar -xf c593f8bf25c3.tar.gz
cd SDL-f1084c419f33/
./configure && make && make install
cd -
cd SDL_image-45e1826592df/
./configure && make && make install
cd -
cd SDL_ttf-62fc3433538d/
./configure && make && make install
cd -
cd SDL_mixer-c593f8bf25c3/
./configure && make && make install
cd -
