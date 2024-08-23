@echo off
setlocal

REM Set the installation directory
set "INSTALL_DIR=%ProgramFiles%\Sukuna"

REM Create the installation directory if it doesn't exist
if not exist "%INSTALL_DIR%" (
    mkdir "%INSTALL_DIR%"
)

REM Move sukuna.exe to the installation directory
echo Installing Sukuna...
copy "%~dp0sukuna.exe" "%INSTALL_DIR%\sukuna.exe"
if errorlevel 1 (
    echo ERROR: Could not copy sukuna.exe to %INSTALL_DIR%.
    pause
    exit /b
)

echo Sukuna installed successfully!
echo Please add "%INSTALL_DIR%" to your system's PATH variable manually.
echo You can do this by:
echo 1. Right-clicking on 'This PC' or 'My Computer' and selecting 'Properties'
echo 2. Clicking on 'Advanced system settings' on the left side
echo 3. Clicking on 'Environment Variables'
echo 4. Under 'System Variables', scrolling down and finding the 'Path' variable, then clicking 'Edit'
echo 5. Clicking 'New' and adding the path "%INSTALL_DIR%"
echo 6. Clicking 'OK' on all windows
echo Please restart your command prompt or open a new one to use Sukuna.
pause