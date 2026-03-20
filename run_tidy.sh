#!/bin/bash

ARGS=("-D" "CMAKE_EXPORT_COMPILE_COMMANDS=ON" "-D" "CMAKE_BUILD_TYPE=Debug" "-D" "CMAKE_CXX_FLAGS=\"-fno-caret-diagnostics\"")
SRC=$(pwd)/src

mkdir -p "clang-tidy-build"
cd "clang-tidy-build"

CC=clang CXX=clang++ cmake "${ARGS[@]}" $SRC || (echo "cmake failed!"; false) || exit 1
cmake --build .

run-clang-tidy -header-filter . -p . -quiet -j 2 > output.txt

# grep interesting errors and make sure we remove duplicates:
grep -E '(warning|error): ' output.txt | sort | uniq > clang-tidy.log
# if we have errors, report them and set exit status to failure
if [ -s clang-tidy.log ]; then
    cat clang-tidy.log
    exit 1
fi

echo "All passed"
exit 0
