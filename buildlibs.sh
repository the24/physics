#!/bin/bash

mkdir -p bin/SDL
cd bin/SDL

../../SDL/configure --disable-shared --enable-static

make
mkdir -p ../../lib/
cp build/.libs/libSDL2main.a ../../lib/libSDL2main.a
cp build/.libs/libSDL2.a ../../lib/libSDL2.a

cd ../..
