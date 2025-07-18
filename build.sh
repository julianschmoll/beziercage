#!/bin/bash

# Usage:
#   ./build.sh <MayaVersion> [LOG_LEVEL]
#   LOG_LEVEL can be ERROR, INFO, DEBUG (case-insensitive)
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

LOG_LEVEL_VALUE=1 # Default to ERROR
if [ -n "$2" ]; then
  case "${2^^}" in
    INFO)  LOG_LEVEL_VALUE=2 ;;
    DEBUG) LOG_LEVEL_VALUE=3 ;;
  esac
fi

CMAKE_FLAGS="-DLOG_LEVEL=$LOG_LEVEL_VALUE -DCMAKE_CXX_STANDARD=${CMAKE_CXX_STANDARD:-17}"
echo "Setting LOG_LEVEL to $LOG_LEVEL_VALUE"

cmake -DMAYA_VERSION="$1" $CMAKE_FLAGS -DCMAKE_TOOLCHAIN_FILE="$root_folder/vcpkg/scripts/buildsystems/vcpkg.cmake" "$root_folder"
cmake --build . --target install --config Release
cmake --build . --target clean

echo "Cleaning up build files"

for item in "$builddir"/*; do
  if [ "$(basename "$item")" != "cage" ] && [ "$(basename "$item")" != "USAGE.md" ]; then
    rm -rf "$item"
  fi
done

cd "$root_folder"
