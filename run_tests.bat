@echo off

set maya=Maya%1
set thisDir=%~dp0
set testfile="%thisDir%%packageName%\tests\run_tests.py"
set mayapy="C:\Program Files\Autodesk\%maya%\bin\mayapy.exe"

echo Running tests in batch mode with maya.standalone (%maya%).
echo This dir: %thisDir%
echo Running in mayapy: %mayapy%
echo Executing python file: %testfile%
echo ----------------------------------------------------------

%mayapy% %testfile% %thisDir% %1
pause
