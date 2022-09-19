#!/bin/sh

cd build
cmake ..
make all
./Kaleidoscope-googletest
