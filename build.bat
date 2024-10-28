@echo off

set builddir=build%1
del %builddir% /S /Q
mkdir %builddir%
cd %builddir%
cmake -A x64 -T v143 -DMAYA_VERSION=%1 ../
cmake --build . --target install --config Release
cd ..
