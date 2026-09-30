#!/bin/sh
set -e
rm -rf build
cmake -S . -B build
cmake --build build -j"$(nproc)"
