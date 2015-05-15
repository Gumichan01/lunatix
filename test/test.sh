#!/bin/sh

make test -r -j -f Makefile;
./test-init;
./test-config;
./test-device;
./test-physics;
./test-window;
./test-system;
make clean-test -f Makefile;

