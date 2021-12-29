#!/usr/bin/bash
cd build
cmake ..
cmake --build .
mv GameOfLife ..
cd ..
./GameOfLife

