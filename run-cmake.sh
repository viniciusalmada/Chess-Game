#!/usr/bin/env bash
mkdir -p cmake-build
mkdir -p bin
cd cmake-build
cmake -S .. -B .
make -j `nproc` && \
  mv Chess-Game ../bin
