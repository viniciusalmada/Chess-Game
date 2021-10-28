#!/usr/bin/env bash
mkdir -p cmake-build-debug
mkdir -p bin
cd cmake-build-debug
cmake -S .. -B .
make -j `nproc` && \
  mv Chess-Game ../bin
