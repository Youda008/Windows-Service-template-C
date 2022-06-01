@echo off
set SERVNAME=MyNewService
reg add "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\EventLog\Application\%SERVNAME%" /v "EventMessageFile" /t REG_SZ /d "%~dp0\EventLogMessages.dll"
reg add "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\EventLog\Application\%SERVNAME%" /v "TypesSupported" /t REG_DWORD /d 7
sc create "%SERVNAME%" binPath= "%~dp0\%SERVNAME%.exe"
sc start "%SERVNAME%"
pause
