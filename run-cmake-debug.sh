#!/usr/bin/env bash
mkdir -p tmp
mkdir -p bin
cd tmp
cmake -S .. -B . -DCMAKE_BUILD_TYPE=Debug
make -j `nproc` && \
  mv Chess-Game ../bin
