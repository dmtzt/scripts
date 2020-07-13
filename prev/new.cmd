@echo off
if [%1]==[] goto :usage
if [%2]==[] goto :usage

set filetype=%1
set filename=%2

call :header_comment
call :directives
call :main
echo %filename%.%filetype% fue creado exitosamente.
exit /B 0

:header_comment
( 
echo /* 
echo. * %filename%.%filetype%
echo. * 
echo. * Description
echo. *
echo. * David Alejandro Martinez Tristan
echo. * %DATE%
echo */
echo.
) > %filename%.%filetype%
goto :eof

:directives
if "%filetype%"=="cpp" (
(
echo #include ^<iostream^>
echo.
echo using namespace std^;
echo.
) >> %filename%.%filetype%
goto :eof
)
if "%filetype%"=="c" (
(
echo #include ^<stdio.h^>
echo.
) >> %filename%.%filetype%
goto :eof
)

:main
(
echo int main^(void^)
echo ^{
echo.
echo.    return 0^;
echo ^}
) >> %filename%.%filetype%
goto :eof

:usage
echo Uso: %0 ^<Filetype^> ^<Filename^>
exit /B 1