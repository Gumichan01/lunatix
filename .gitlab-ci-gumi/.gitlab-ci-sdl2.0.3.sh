#!/bin/sh

wget --no-cache https://hg.libsdl.org/SDL/archive/704a0bfecf75.tar.gz
wget --no-cache https://hg.libsdl.org/SDL_image/archive/05ed5cf4143d.tar.gz
wget --no-cache https://hg.libsdl.org/SDL_ttf/archive/df9d0e8ef4db.tar.gz
git clone https://gitlab.com/gumi-contrib/SDL_mixer-2.0.0.git
tar -xf 704a0bfecf75.tar.gz
tar -xf 05ed5cf4143d.tar.gz
tar -xf df9d0e8ef4db.tar.gz
cd SDL-704a0bfecf75/
./configure && make && make install
cd -
cd SDL_image-05ed5cf4143d/
./configure && make && make install
cd -
cd SDL_ttf-df9d0e8ef4db/
./configure && make && make install
cd -
cd SDL_mixer-2.0.0/
git checkout gumi
./configure && make && make install
cd -
