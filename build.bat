@echo off

set "root_folder=%cd%"

set builddir="%root_folder%/build/%1-Windows"
del %builddir% /S /Q
mkdir %builddir%

cd %builddir%

echo Building cage for Maya%1

set "CMAKE_FLAGS="
if /I "%2"=="debug" (
    set "CMAKE_FLAGS=-DCMAKE_CXX_FLAGS=/DDEBUG/EHsc"
    echo Building in debug mode
)

cmake -A x64 -T v143 -DMAYA_VERSION=%1 %CMAKE_FLAGS% %root_folder%
cmake --build . --target install --config Release
cmake --build . --target clean

echo Cleaning up build files

for %%F in ("%builddir%\*") do (
    if /I not "%%~nxF"=="cage" if /I not "%%~nxF"=="USAGE.md" (
        del /q /f "%%F"
    )
)

for /d %%D in ("%builddir%\*") do (
    if /I not "%%~nxD"=="cage" (
        rd /s /q "%%D"
    )
)

cd %root_folder%
