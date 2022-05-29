Do you want to create a Windows service without having to use C#, Visual Studio IDE and weird enterprise frameworks?
Download this template that uses only Win32 API and get started in no time.

## How to build

1. Build the message DLL using the `messages/CompileMessages.bat`.
   You need Visual Studio Developer Tools for that, but not the IDE. Run this bat in Visual Studio Developer Command Prompt.
2. Build the service executable from the source files in `src` using your favourite build system and IDE
   Simpliest example would be `g++ -o MyNewService.exe src/*`

## How to install

1. Create a directory in Program Files
2. Copy the service executable + the messages DLL + (Un)InstallService.bat into that directory
3. Edit the (Un)InstallService.bat to contain correct service name
4. Run InstallService.bat as administrator


These instruction were taken from https://docs.microsoft.com/en-us/windows/win32/services/the-complete-service-sample
