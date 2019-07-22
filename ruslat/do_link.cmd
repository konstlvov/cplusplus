rem todo : create makefile

set PATH=C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\bin;C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Bin;%PATH%
set INCLUDE=C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\include;C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Include
set LIB=C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\lib;C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Lib

if not exist Debug md Debug
cd Debug
link /VERBOSE:LIB /OUT:"ruslat.exe" /INCREMENTAL /RELEASE /SUBSYSTEM:WINDOWS /DYNAMICBASE:NO /MACHINE:X86 /ERRORREPORT:PROMPT kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ruslat.obj ruslat.res
