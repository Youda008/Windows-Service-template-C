@echo off
reg add "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\EventLog\Application\TemperatureService" /v "EventMessageFile" /t REG_SZ /d "%~dp0\EventLogMessages.dll"
reg add "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\EventLog\Application\TemperatureService" /v "TypesSupported" /t REG_DWORD /d 7
sc create "TemperatureService" binPath= "%~dp0\TemperatureService.exe"
sc start "TemperatureService"
pause
