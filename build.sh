#!/bin/bash

# Usage:
#   ./build.sh <MayaVersion> [LOG_LEVEL]
#   LOG_LEVEL can be ERROR, INFO, DEBUG (case-insensitive)
#

set -e

root_folder="$(pwd)"
vcpkg_dir="$root_folder/external/vcpkg"

echo Updating submodules...
git submodule update --init --recursive

echo "Bootstrapping vcpkg if necessary..."
if [ ! -f "$vcpkg_dir/vcpkg" ]; then
    "$vcpkg_dir/bootstrap-vcpkg.sh" -disableMetrics
fi

echo "Installing dependencies with vcpkg..."
"$vcpkg_dir/vcpkg" install

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

LOG_LEVEL_VALUE=0  # no logging by default
if [ -n "$2" ]; then
  case "${2^^}" in
    ERROR)  LOG_LEVEL_VALUE=1 ;;
    INFO)  LOG_LEVEL_VALUE=2 ;;
    DEBUG) LOG_LEVEL_VALUE=3 ;;
  esac
fi

echo "Setting LOG_LEVEL to $LOG_LEVEL_VALUE"

toolchain_file="$vcpkg_dir/scripts/buildsystems/vcpkg.cmake"

cmake -DCMAKE_TOOLCHAIN_FILE="$toolchain_file" \
      -DMAYA_VERSION="$1" \
      -DLOG_LEVEL="$LOG_LEVEL_VALUE" \
      -DCMAKE_CXX_STANDARD=17 \
      "$root_folder"
      # -DCMAKE_CXX_FLAGS_RELEASE="-O3 -march=native -flto -DNDEBUG" \
      # -DCMAKE_C_FLAGS_RELEASE="-O3 -march=native -flto -DNDEBUG" \


cmake --build . --target install --config Release
cmake --build . --target clean

echo "Cleaning up build files"

for item in "$builddir"/*; do
  if [ "$(basename "$item")" != "cage" ] && [ "$(basename "$item")" != "USAGE.md" ] &&  [ "$(basename "$item")" != "cage.mod" ]; then
    rm -rf "$item"
  fi
done

cd "$root_folder"
