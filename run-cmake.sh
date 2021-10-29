#!/usr/bin/env bash
mkdir -p tmp
mkdir -p bin
cd tmp
cmake -S .. -B .
make -j `nproc` && \
  mv Chess-Game ../bin
