rem todo : create makefile

set PATH=C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\bin;C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Bin;%PATH%
set INCLUDE=C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\include;C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Include
set LIB=C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\lib;C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Lib


if not exist Debug md Debug
cl.exe /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_VC80_UPGRADE=0x0710" /Gm /EHsc /RTC1 /MTd /Fo"Debug\\" /Fd"Debug\vc80.pdb" /W3 /nologo /c /Wp64 /ZI /TP /errorReport:prompt ruslat.c
rc.exe /d "_VC80_UPGRADE=0x0710" /fo"Debug/ruslat.res" .\ruslat.rc