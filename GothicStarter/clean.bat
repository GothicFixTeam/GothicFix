@echo off
if "%PROJECT%" == "" set PROJECT=GothicStarter

attrib -s -h -r /S
if exist ".\%PROJECT%.layout" erase ".\%PROJECT%.layout"
if exist ".\%PROJECT%.ncb" erase ".\%PROJECT%.ncb"
if exist ".\%PROJECT%.opt" erase ".\%PROJECT%.opt"
if exist ".\%PROJECT%.plg" erase ".\%PROJECT%.plg"
if exist ".\%PROJECT%.suo" erase ".\%PROJECT%.suo"
if exist ".\%PROJECT%.tds" erase ".\%PROJECT%.tds"
if exist .\Makefile.win erase .\Makefile.win
for %%i in (.\tmp\*.*) do erase %%i
