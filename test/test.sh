#!/bin/sh

#
# This script will help you to launch some tests on the engine
#
# It only works on Linux system.
#

./test-init;
./test-config;
./test-system;
./test-device;
./test-file;
./test-physics;
./test-window;
./test-ttf;
./test-particle;
rm win-*.png


