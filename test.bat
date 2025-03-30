@echo off

setlocal enabledelayedexpansion

set "version="
set "explicitMayapy="

:parseArgs
if "%~1"=="" goto endParseArgs
if "%~1"=="--mayapy" (
    set "explicitMayapy=%~2"
    shift
    shift
    goto parseArgs
)
set "version=%~1"
shift
goto parseArgs
:endParseArgs

if "%version%"=="" (
    echo Usage: %0 ^<MayaVersion^> [--mayapy /path/to/mayapy]
    exit /b 1
)

set "thisDir=%~dp0"
set "testfile=%thisDir%tests\run_tests.py"

if not "%explicitMayapy%"=="" (
    set "mayapy=%explicitMayapy%"
) else (
    set mayapy="C:\Program Files\Autodesk\Maya%version%\bin\mayapy.exe"
)

echo Testing cage for Maya %version% on Windows.
echo ----------------------------------------------------------------------
%mayapy% %testfile% %thisDir% %version%-Windows

endlocal
