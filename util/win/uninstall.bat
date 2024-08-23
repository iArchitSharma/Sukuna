@echo off
echo Uninstalling Sukuna...

REM Define the installation path
set "INSTALL_DIR=C:\Program Files\Sukuna"

echo Removing files...
REM Delete the Sukuna installation directory
rd /s /q "%INSTALL_DIR%"

echo Sukuna has been successfully uninstalled.
pause
