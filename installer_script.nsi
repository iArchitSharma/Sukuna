; NSIS script for Sukuna Compiler installer

; Name of the installer
OutFile "sukuna_installer.exe"

; General Information
Name "Sukuna Compiler"
Version "1.0"
InstallDir "$PROGRAMFILES\Sukuna"
InstallDirRegKey HKLM "Software\Sukuna Compiler" "Install_Dir"

; Default group name for the Start Menu shortcut
!define MUI_STARTMENUPAGE_DEFAULTFOLDER "Sukuna"

; Compression
SetCompressor /SOLID lzma

; Include Modern UI
!include "MUI2.nsh"

; Pages
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_STARTMENU Application $MUI_STARTMENUPAGE_DEFAULTFOLDER
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_LANGUAGE "English"

Section "MainSection" SEC01
    ; Set output path to the installation directory
    SetOutPath "$INSTDIR"

    ; Install the executable
    File "build\sukuna.exe"

    ; Create a Start Menu shortcut
    CreateShortcut "$SMPROGRAMS\$MUI_STARTMENUPAGE_DEFAULTFOLDER\Sukuna Compiler.lnk" "$INSTDIR\sukuna.exe"

    ; Add the install directory to the system PATH
    nsExec::ExecToLog '"$SYSDIR\cmd.exe" /C setx /M PATH "$INSTDIR;%PATH%"'
    
    ; Write the installation path to the registry for uninstallation
    WriteRegStr HKLM "Software\Sukuna Compiler" "Install_Dir" "$INSTDIR"
    WriteUninstaller "$INSTDIR\uninstall.exe"
SectionEnd

Section "Uninstall"
    ; Remove the installed directory from the PATH
    nsExec::ExecToLog '"$SYSDIR\cmd.exe" /C setx /M PATH "$PATH%"'

    ; Delete installed files and shortcuts
    Delete "$SMPROGRAMS\$MUI_STARTMENUPAGE_DEFAULTFOLDER\Sukuna Compiler.lnk"
    Delete "$INSTDIR\sukuna.exe"
    Delete "$INSTDIR\uninstall.exe"
    RMDir "$INSTDIR"

    ; Remove the registry key
    DeleteRegKey HKLM "Software\Sukuna Compiler"
SectionEnd
