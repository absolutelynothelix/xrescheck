#!/bin/sh -ex

mkdir -p build
gcc -shared -fpic -D_GNU_SOURCE -obuild/xrescheck.so src/xrescheck.c
