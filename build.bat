@echo off

set "root_folder=%cd%"

set builddir="%root_folder%/build/%1-Windows"
del %builddir% /S /Q
mkdir %builddir%

cd %builddir%

echo Building cage for Maya%1

set "LOG_LEVEL_VALUE=1"
if /I "%2"=="INFO" set "LOG_LEVEL_VALUE=2"
if /I "%2"=="DEBUG" set "LOG_LEVEL_VALUE=3"

set "CMAKE_FLAGS=-DLOG_LEVEL=%LOG_LEVEL_VALUE% -DCMAKE_CXX_STANDARD=%CMAKE_CXX_STANDARD:17%"
echo Setting LOG_LEVEL to %LOG_LEVEL_VALUE%

cmake -A x64 -T v143 -DMAYA_VERSION=%1 %CMAKE_FLAGS% -DCMAKE_TOOLCHAIN_FILE=%root_folder%/vcpkg/scripts/buildsystems/vcpkg.cmake %root_folder%
cmake --build . --target install --config Release
cmake --build . --target clean

echo Cleaning up build files

for %%F in ("%builddir%\*") do (
    if /I not "%%~nxF"=="cage" if /I not "%%~nxF"=="USAGE.md" if /I not "%%~nxF"=="cage.mod" (
        del /q /f "%%F"
    )
)

for /d %%D in ("%builddir%\*") do (
    if /I not "%%~nxD"=="cage" (
        rd /s /q "%%D"
    )
)

cd %root_folder%
