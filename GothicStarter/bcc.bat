@echo off
if "%PROJECT%" == "" set PROJECT=GothicStarter

REM --- MAKE SURE THE TOOLS ARE THE FIRST IN PATH ---
set PATH=P:\borland\bcc55\bin;%PATH%

echo.
make.exe -r -s -B -f%PROJECT%.bcc %1 %3 %4 %5 %6 %7 %8 %9
echo.
