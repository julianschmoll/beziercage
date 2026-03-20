#!/bin/bash

find ./src -iname '*.hpp' -o -iname '*.cpp' | clang-format --style=file -i --files=/dev/stdin
