#!/bin/sh
rm -rf build/ && mkdir build && cd build && (cmake .. && cmake --build . && ./PiUi/PiUi && cd ..) || cd ..
