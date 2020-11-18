REM this needs to be run inside Visual Studio Developer Command Prompt

@echo off
mc -U EventLogMessages.mc
rc -r EventLogMessages.rc
link -dll -noentry /MACHINE:X64 -out:EventLogMessages.dll EventLogMessages.res
copy EventLogMessages.h ..\src
pause
