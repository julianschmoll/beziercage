@echo off

set builddir=build%1
del %builddir% /S /Q
mkdir %builddir%
cd %builddir%
cmake -A x64 -T v143 -DMAYA_VERSION=%1 ../
cmake --build . --target install --config Release

set "target_folder=%cd%"

for %%F in ("%target_folder%\*") do (
    if /I not "%%~nxF"=="jSmear" (
        echo Deleting file %%F
        del /q "%%F"
    )
)

for /d %%D in ("%target_folder%\*") do (
    if /I not "%%~nxD"=="jSmear" (
        echo Deleting directory %%D
        rmdir /s /q "%%D"
    )
)

cd ..
