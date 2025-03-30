#!/bin/bash

# Usage:
#   ./run_tests.sh <MayaVersion> [--mayapy /path/to/mayapy]
#

version=""
explicitMayapy=""
while [[ $# -gt 0 ]]; do
  case "$1" in
    --mayapy)
      explicitMayapy="$2"
      shift 2
      ;;
    *)
      version="$1"
      shift
      ;;
  esac
done

if [ -z "$version" ]; then
  echo "Usage: $0 <MayaVersion> [--mayapy /path/to/mayapy]"
  exit 1
fi

thisDir="$(cd "$(dirname "$0")" && pwd)"
testFile="$thisDir/tests/run_tests.py"

if [ -n "$explicitMayapy" ]; then
  mayapy="$explicitMayapy"
else
  defaultPaths=(
    "/c/Program Files/Autodesk/Maya${version}/bin/mayapy.exe"
    "/usr/autodesk/Maya${version}/bin/mayapy"
    "/Applications/Autodesk/Maya${version}/Maya.app/Contents/bin/mayapy"
  )
  for path in "${defaultPaths[@]}"; do
    if [ -f "$path" ]; then
      mayapy="$path"
      break
    fi
  done
fi

if [ -z "$mayapy" ] || [ ! -f "$mayapy" ]; then
  echo "Could not find mayapy for Maya $version please specify path with --mayapy flag!"
  exit 1
fi

case "$OSTYPE" in
  darwin*)  os="macOS" ;; 
  msys*)    os="Windows" ;;
  cygwin*)  os="Windows" ;;
  *)        os="$OSTYPE" ;;
esac

echo "Testing cage for Maya $version on $os"
echo "------------------------------------------------------"
"$mayapy" "$testFile" "$thisDir" "$version-$os"
