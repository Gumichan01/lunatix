#!/bin/sh

#
# This script will help you to launch some tests on the engine
#
# It only works on Linux system.
#


make test -r -j -f Makefile;
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
make clean-test -f Makefile;

