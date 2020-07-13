@echo off
if [%1]==[] goto usage

set filename=%1
g++ -Werror -o %filename% %filename%.cpp
exit /B 0

:usage
echo Usage: %0 ^<Filename.cpp^>
exit /B 1