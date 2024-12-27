#!/bin/bash

# Usage:
#   ./build.sh <MayaVersion>
#

root_folder="$(pwd)"

case "$OSTYPE" in
  solaris*) os="solaris" ;;
  darwin*)  os="darwin" ;; 
  linux*)   os="linux" ;;
  bsd*)     os="bsd" ;;
  msys*)    os="windows" ;;
  cygwin*)  os="windows" ;;
  *)        os="" ;;
esac


builddir="$root_folder/build/$1-$os"

rm -rf "$builddir"
mkdir -p "$builddir"
cd "$builddir"

echo "Building jSmear for Maya$1"

cmake -DMAYA_VERSION="$1" "$root_folder"
cmake --build . --target install --config Release
cmake --build . --target clean

echo "Cleaning up build files"

for item in "$builddir"/*; do
  if [ "$(basename "$item")" != "jSmear" ] && [ "$(basename "$item")" != "USAGE.md" ]; then
    rm -rf "$item"
  fi
done

cd "$root_folder"
