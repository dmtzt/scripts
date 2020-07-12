@echo off
set extension=%1
set name=%2
set extensions=cpp py
set author=David Alejandro Martinez Tristan
for %%a in (%extensions%) do (
    if %extension% == %%a (
        call :%extension%
        exit /b %errorlevel%
    )
)     
echo Extension not compatible with generator.
exit /b %errorlevel%

:: C++ template generator
:cpp
if exist %name%.%extension% (
    call :file_exists
    exit /b 0
)
(
    echo /*
    echo  * %name%.%extension%
    echo  * Description
    echo  * %author%
    echo  * %date%
    echo */
    echo #include ^<iostream^>
    echo.
    echo using namespace std^;
    echo.
    echo int main^(^)
    echo {}
) > %name%.%extension%
call :file_created
exit /b 0

:: Python template generator
:py
if exist %name%.%extension% (
    call :file_exists
    exit /b 0
)
(
    echo  # %name%.%extension%
    echo  # Description
    echo  # %author%
    echo  # %date%
    echo def main^(^):
    echo     pass
    echo.
    echo.
    echo if __name__ == ^"__main__^":
    echo     main^(^)
) > %name%.%extension%
call :file_created
exit /b 0

:file_exists
echo %name%.%extension% already exists.
exit /b 0

:file_created
if exist %name%.%extension% (
    echo %date% %time%: %name%.%extension% was created.
) else (
    echo >> Error creating file.
)
exit /b 0