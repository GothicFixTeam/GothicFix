@echo off
if "%PROJECT%" == "" set PROJECT=GothicStarter
if not exist "%PROJECT%.exe" goto done

REM --- http://rpi.net.au/~ajohnson/resourcehacker --- 
if not exist .\bin\ResHacker.exe goto trim
echo.
.\bin\ResHacker.exe -delete "%PROJECT%.exe", "%PROJECT%.exe", RCDATA,DVCLAL,0
type .\bin\ResHacker.log
erase .\bin\ResHacker.ini
erase .\bin\ResHacker.log
echo.

:trim
REM --- http://www.collakesoftware.com --- 
if not exist .\bin\PETrim.exe goto pack
echo.
.\bin\PETrim.exe "%PROJECT%.exe"
echo.

:pack
REM --- http://upx.sourceforge.net --- 
if not exist .\bin\upx.exe goto csum
echo.
.\bin\upx.exe --brute --overlay=strip --color "%PROJECT%.exe"
if errorlevel 1 .\bin\upx.exe --best --overlay=strip "%PROJECT%.exe"
echo.

:csum
REM --- http://www.collakesoftware.com --- 
if not exist .\bin\PEChksum.exe goto done
echo.
.\bin\PEChksum.exe "%PROJECT%.exe"
echo.

:done
pause