#!/bin/sh

mkdir build
cd build
cmake -D CMAKE_C_COMPILER=/opt/local/bin/clang-mp-15 -D CMAKE_CXX_COMPILER=/opt/local/bin/clang++-mp-15 -D CMAKE_C_FLAGS="-march=core2" -D CMAKE_CXX_FLAGS="-march=core2" ..
cmake --build . --config Release
