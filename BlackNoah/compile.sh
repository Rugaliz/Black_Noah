#!/bin/sh
[  -d build ] && chmod -R 777 build;
rm -r build;
mkdir build;
cmake -S . -B build;
cd build;
make

