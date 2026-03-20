#!/bin/bash

ARGS=("-D" "CMAKE_EXPORT_COMPILE_COMMANDS=ON" "-D" "CMAKE_BUILD_TYPE=Debug")
ROOT=$(pwd)

mkdir -p "clang-tidy-build"
cd "clang-tidy-build"

CC=clang CXX=clang++ cmake "${ARGS[@]}" $ROOT || (echo "cmake failed!"; false) || exit 1
cmake --build .

run-clang-tidy -header-filter "$(pwd)/src/.*" -p . -quiet -j 2 > output.txt

grep -E '(warning|error): ' output.txt | sort | uniq > clang-tidy.log
if [ -s clang-tidy.log ]; then
    cat clang-tidy.log
    exit 1
fi

echo "All passed"
exit 0
