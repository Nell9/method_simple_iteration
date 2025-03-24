@echo off
cd..
set example=Wait file is compiling...
set example2=Files ready!
echo %example%
@echo off
start /wait py main.py
echo %example2%
TIMEOUT [/T] 2 [/NOBREAK]
exit 1