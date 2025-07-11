#!/bin/bash

# Usage:
#   ./build.sh <MayaVersion> [debug]
#

root_folder="$(pwd)"

case "$OSTYPE" in
  darwin*)  os="macOS" ;;
  msys*)    os="Windows" ;;
  cygwin*)  os="Windows" ;;
  *)        os="$OSTYPE" ;;
esac


builddir="$root_folder/build/$1-$os"

rm -rf "$builddir"
mkdir -p "$builddir"
cd "$builddir"

echo "Building cage for Maya $1 on $os"

CMAKE_FLAGS=""
if [ "$2" = "debug" ]; then
  CMAKE_FLAGS="-DCMAKE_BUILD_TYPE=Debug"
  echo "Building in debug mode"
fi

cmake -DMAYA_VERSION="$1" $CMAKE_FLAGS "$root_folder"
cmake --build . --target install --config Release
cmake --build . --target clean

echo "Cleaning up build files"

for item in "$builddir"/*; do
  if [ "$(basename "$item")" != "cage" ] && [ "$(basename "$item")" != "USAGE.md" ]; then
    rm -rf "$item"
  fi
done

cd "$root_folder"
