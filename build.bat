@echo off

set "root_folder=%cd%"

set builddir="%root_folder%/build/%1"
del %builddir% /S /Q
mkdir %builddir%

cd %builddir%

echo Building jSmear for Maya%1

cmake -A x64 -T v143 -DMAYA_VERSION=%1 %root_folder%
cmake --build . --target install --config Release
cmake --build . --target clean

echo Cleaning up build files

for %%F in ("%builddir%\*") do (
    if /I not "%%~nxF"=="jSmear" if /I not "%%~nxF"=="README.md" (
        del /q /f "%%F"
    )
)

for /d %%D in ("%builddir%\*") do (
    if /I not "%%~nxD"=="jSmear" (
        rd /s /q "%%D"
    )
)

cd %root_folder%
