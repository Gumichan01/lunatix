#!/bin/sh

apt-get update -qq
apt-get install -y apt-utils
apt-get install -y curl wget software-properties-common
apt-get install -y build-essential mercurial make cmake autoconf automake
apt-get install -y libtool libasound2-dev libpulse-dev libaudio-dev libx11-dev libxext-dev
apt-get install -y libxrandr-dev libxcursor-dev libxi-dev libxinerama-dev libxxf86vm-dev
apt-get install -y libxss-dev libgl1-mesa-dev libesd0-dev libdbus-1-dev libudev-dev
apt-get install -y libgles1-mesa-dev libgles2-mesa-dev libegl1-mesa-dev
apt-get install -y libjpeg-dev libpng-dev libwebp-dev libtiff5-dev libtiff-opengl
apt-get install -y libfreetype6-dev
apt-get install -y libflac-dev libflac++-dev libogg0 libogg-dev libvorbis-dev liboggz2-dev libmodplug1
apt-get install -y libmodplug-dev fluidsynth libfluidsynth* libsmpeg*
