# Microsoft Developer Studio Project File - Name="GothicStarter" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=GothicStarter - Win32 Release
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "GothicStarter.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "GothicStarter.mak" CFG="GothicStarter - Win32 Release"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "GothicStarter - Win32 Release" (basierend auf  "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe
# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "tmp"
# PROP BASE Intermediate_Dir "tmp"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "tmp"
# PROP Intermediate_Dir "tmp"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G6 /W4 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /FD /c
# ADD CPP /nologo /G6 /Gr /Zp1 /W4 /O1 /Ob0 /I ".\res" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# SUBTRACT MTL /mktyplib203
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib advapi32.lib shell32.lib comctl32.lib /nologo /entry:"WinMain" /subsystem:windows /pdb:none /machine:I386 /nodefaultlib /out:"./GothicStarter.exe" /OPT:NOWIN98 /FIXED /RELEASE
# ADD LINK32 kernel32.lib user32.lib gdi32.lib advapi32.lib shell32.lib comctl32.lib /nologo /subsystem:windows /pdb:none /machine:I386 /out:"GothicStarter.exe" /libpath:".\lib" /OPT:NOWIN98 /FIXED /RELEASE
# SUBTRACT LINK32 /nodefaultlib
# Begin Target

# Name "GothicStarter - Win32 Release"
# Begin Group "res"

# PROP Default_Filter "*.rc;*.rh"
# Begin Source File

SOURCE=.\res\resource.rc
# End Source File
# Begin Source File

SOURCE=.\res\resource.rh
# End Source File
# End Group
# Begin Source File

SOURCE=.\GothicStarter.c
# End Source File
# Begin Source File

SOURCE=.\GothicStarter.h
# End Source File
# End Target
# End Project
