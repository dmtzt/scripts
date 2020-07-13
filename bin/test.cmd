@echo off
if [%1]==[] (
    call :usage
    exit /b %errorlevel%
)
if [%2]==[] (
    call :usage
    exit /b %errorlevel%
)
exit /b %errorlevel%

:usage
echo Command line arguments are missing.
exit /B 1