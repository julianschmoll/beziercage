@echo off

set maya=Maya%1
set thisDir=%~dp0
set testfile="%thisDir%%packageName%\tests\run_tests.py"
set mayapy="C:\Program Files\Autodesk\%maya%\bin\mayapy.exe"

echo Running tests for Maya %1.
echo ----------------------------------------------------------

%mayapy% %testfile% %thisDir% %1
