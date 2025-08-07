@echo off
setlocal

set "root_folder=%cd%"
set "vcpkg_dir=%root_folder%/external/vcpkg"

echo Bootstrapping vcpkg if necessary...
if not exist "%vcpkg_dir%/vcpkg.exe" (
    call "%vcpkg_dir%/bootstrap-vcpkg.bat" -disableMetrics
)

echo Installing dependencies with vcpkg...
"%vcpkg_dir%/vcpkg" install

set "builddir=%root_folder%/build/%1-Windows"
if exist "%builddir%" (
    rmdir /S /Q "%builddir%"
)
mkdir "%builddir%"
cd "%builddir%"

echo Building cage for Maya%1

set "LOG_LEVEL_VALUE=1"
if /I "%2"=="INFO" set "LOG_LEVEL_VALUE=2"
if /I "%2"=="DEBUG" set "LOG_LEVEL_VALUE=3"

set "CMAKE_FLAGS=-DLOG_LEVEL=%LOG_LEVEL_VALUE% -DCMAKE_CXX_STANDARD=17"
echo Setting LOG_LEVEL to %LOG_LEVEL_VALUE%

set "toolchain_file=%vcpkg_dir%/scripts/buildsystems/vcpkg.cmake"

cmake -A x64 -T v143 -DCMAKE_TOOLCHAIN_FILE="%toolchain_file%" -DMAYA_VERSION=%1 %CMAKE_FLAGS% "%root_folder%"
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

cd "%root_folder%"
endlocal
