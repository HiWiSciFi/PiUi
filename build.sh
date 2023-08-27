#!/bin/sh
mkdir build
cd build
cmake ..
cmake --build .
cd PiUi
./PiUi
cd ../..
