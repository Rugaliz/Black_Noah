#!/bin/sh
set -e
rm -rf build
mingw64-cmake -S . -B build
cmake --build build -j"$(nproc)"
