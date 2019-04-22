# Microsoft Developer Studio Generated NMAKE File, Based on DevHelper.dsp
!IF "$(CFG)" == ""
CFG=DevHelper - Win32 Debug
!MESSAGE No configuration specified. Defaulting to DevHelper - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "DevHelper - Win32 Debug" && "$(CFG)" != "DevHelper - Win32 Unicode Debug" && "$(CFG)" != "DevHelper - Win32 Release MinSize" && "$(CFG)" != "DevHelper - Win32 Release MinDependency" && "$(CFG)" != "DevHelper - Win32 Unicode Release MinSize" && "$(CFG)" != "DevHelper - Win32 Unicode Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DevHelper.mak" CFG="DevHelper - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DevHelper - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DevHelper - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DevHelper - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DevHelper - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DevHelper - Win32 Unicode Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DevHelper - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "DevHelper - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\DevHelper.dll" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\DevHelper.obj"
	-@erase "$(INTDIR)\DevHelper.pch"
	-@erase "$(INTDIR)\DevHelper.res"
	-@erase "$(INTDIR)\DeviceList.obj"
	-@erase "$(INTDIR)\DevInfoQuery.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\USBSTORHelper.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\DevHelper.dll"
	-@erase "$(OUTDIR)\DevHelper.exp"
	-@erase "$(OUTDIR)\DevHelper.ilk"
	-@erase "$(OUTDIR)\DevHelper.lib"
	-@erase "$(OUTDIR)\DevHelper.pdb"
	-@erase ".\DevHelper.h"
	-@erase ".\DevHelper.tlb"
	-@erase ".\DevHelper_i.c"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\DevHelper.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=
RSC=rc.exe
RSC_PROJ=/l 0x419 /fo"$(INTDIR)\DevHelper.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\DevHelper.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=setupapi.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\DevHelper.pdb" /debug /machine:I386 /def:".\DevHelper.def" /out:"$(OUTDIR)\DevHelper.dll" /implib:"$(OUTDIR)\DevHelper.lib" /pdbtype:sept 
DEF_FILE= \
	".\DevHelper.def"
LINK32_OBJS= \
	"$(INTDIR)\DevHelper.obj" \
	"$(INTDIR)\DeviceList.obj" \
	"$(INTDIR)\DevInfoQuery.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\USBSTORHelper.obj" \
	"$(INTDIR)\DevHelper.res"

"$(OUTDIR)\DevHelper.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\DevHelper.dll
InputPath=.\Debug\DevHelper.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "DevHelper - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\DevHelper.dll" ".\DevHelper.tlb" ".\DevHelper.h" ".\DevHelper_i.c" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\DevHelper.obj"
	-@erase "$(INTDIR)\DevHelper.pch"
	-@erase "$(INTDIR)\DevHelper.res"
	-@erase "$(INTDIR)\DeviceList.obj"
	-@erase "$(INTDIR)\DevInfoQuery.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\USBSTORHelper.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\DevHelper.dll"
	-@erase "$(OUTDIR)\DevHelper.exp"
	-@erase "$(OUTDIR)\DevHelper.ilk"
	-@erase "$(OUTDIR)\DevHelper.lib"
	-@erase "$(OUTDIR)\DevHelper.pdb"
	-@erase ".\DevHelper.h"
	-@erase ".\DevHelper.tlb"
	-@erase ".\DevHelper_i.c"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\DevHelper.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=
RSC=rc.exe
RSC_PROJ=/l 0x419 /fo"$(INTDIR)\DevHelper.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\DevHelper.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=setupapi.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\DevHelper.pdb" /debug /machine:I386 /def:".\DevHelper.def" /out:"$(OUTDIR)\DevHelper.dll" /implib:"$(OUTDIR)\DevHelper.lib" /pdbtype:sept 
DEF_FILE= \
	".\DevHelper.def"
LINK32_OBJS= \
	"$(INTDIR)\DevHelper.obj" \
	"$(INTDIR)\DeviceList.obj" \
	"$(INTDIR)\DevInfoQuery.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\USBSTORHelper.obj" \
	"$(INTDIR)\DevHelper.res"

"$(OUTDIR)\DevHelper.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\DevHelper.dll
InputPath=.\DebugU\DevHelper.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
<< 
	

!ELSEIF  "$(CFG)" == "DevHelper - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : "$(OUTDIR)\DevHelper.dll" ".\DevHelper.tlb" ".\DevHelper.h" ".\DevHelper_i.c" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\DevHelper.obj"
	-@erase "$(INTDIR)\DevHelper.pch"
	-@erase "$(INTDIR)\DevHelper.res"
	-@erase "$(INTDIR)\DeviceList.obj"
	-@erase "$(INTDIR)\DevInfoQuery.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\USBSTORHelper.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\DevHelper.dll"
	-@erase "$(OUTDIR)\DevHelper.exp"
	-@erase "$(OUTDIR)\DevHelper.lib"
	-@erase ".\DevHelper.h"
	-@erase ".\DevHelper.tlb"
	-@erase ".\DevHelper_i.c"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\DevHelper.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=
RSC=rc.exe
RSC_PROJ=/l 0x419 /fo"$(INTDIR)\DevHelper.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\DevHelper.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib setupapi.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\DevHelper.pdb" /machine:I386 /def:".\DevHelper.def" /out:"$(OUTDIR)\DevHelper.dll" /implib:"$(OUTDIR)\DevHelper.lib" 
DEF_FILE= \
	".\DevHelper.def"
LINK32_OBJS= \
	"$(INTDIR)\DevHelper.obj" \
	"$(INTDIR)\DeviceList.obj" \
	"$(INTDIR)\DevInfoQuery.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\USBSTORHelper.obj" \
	"$(INTDIR)\DevHelper.res"

"$(OUTDIR)\DevHelper.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\DevHelper.dll
InputPath=.\ReleaseMinSize\DevHelper.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "DevHelper - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\DevHelper.dll" ".\DevHelper.tlb" ".\DevHelper.h" ".\DevHelper_i.c" ".\ReleaseMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\DevHelper.obj"
	-@erase "$(INTDIR)\DevHelper.pch"
	-@erase "$(INTDIR)\DevHelper.res"
	-@erase "$(INTDIR)\DeviceList.obj"
	-@erase "$(INTDIR)\DevInfoQuery.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\USBSTORHelper.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\DevHelper.dll"
	-@erase "$(OUTDIR)\DevHelper.exp"
	-@erase "$(OUTDIR)\DevHelper.lib"
	-@erase ".\DevHelper.h"
	-@erase ".\DevHelper.tlb"
	-@erase ".\DevHelper_i.c"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\DevHelper.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=
RSC=rc.exe
RSC_PROJ=/l 0x419 /fo"$(INTDIR)\DevHelper.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\DevHelper.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib setupapi.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\DevHelper.pdb" /machine:I386 /def:".\DevHelper.def" /out:"$(OUTDIR)\DevHelper.dll" /implib:"$(OUTDIR)\DevHelper.lib" 
DEF_FILE= \
	".\DevHelper.def"
LINK32_OBJS= \
	"$(INTDIR)\DevHelper.obj" \
	"$(INTDIR)\DeviceList.obj" \
	"$(INTDIR)\DevInfoQuery.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\USBSTORHelper.obj" \
	"$(INTDIR)\DevHelper.res"

"$(OUTDIR)\DevHelper.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\DevHelper.dll
InputPath=.\ReleaseMinDependency\DevHelper.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "DevHelper - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

ALL : "$(OUTDIR)\DevHelper.dll" ".\DevHelper.tlb" ".\DevHelper.h" ".\DevHelper_i.c" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\DevHelper.obj"
	-@erase "$(INTDIR)\DevHelper.pch"
	-@erase "$(INTDIR)\DevHelper.res"
	-@erase "$(INTDIR)\DeviceList.obj"
	-@erase "$(INTDIR)\DevInfoQuery.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\USBSTORHelper.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\DevHelper.dll"
	-@erase "$(OUTDIR)\DevHelper.exp"
	-@erase "$(OUTDIR)\DevHelper.lib"
	-@erase ".\DevHelper.h"
	-@erase ".\DevHelper.tlb"
	-@erase ".\DevHelper_i.c"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\DevHelper.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=
RSC=rc.exe
RSC_PROJ=/l 0x419 /fo"$(INTDIR)\DevHelper.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\DevHelper.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib setupapi.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\DevHelper.pdb" /machine:I386 /def:".\DevHelper.def" /out:"$(OUTDIR)\DevHelper.dll" /implib:"$(OUTDIR)\DevHelper.lib" 
DEF_FILE= \
	".\DevHelper.def"
LINK32_OBJS= \
	"$(INTDIR)\DevHelper.obj" \
	"$(INTDIR)\DeviceList.obj" \
	"$(INTDIR)\DevInfoQuery.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\USBSTORHelper.obj" \
	"$(INTDIR)\DevHelper.res"

"$(OUTDIR)\DevHelper.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\DevHelper.dll
InputPath=.\ReleaseUMinSize\DevHelper.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
<< 
	

!ELSEIF  "$(CFG)" == "DevHelper - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\DevHelper.dll" ".\DevHelper.tlb" ".\DevHelper.h" ".\DevHelper_i.c" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\DevHelper.obj"
	-@erase "$(INTDIR)\DevHelper.pch"
	-@erase "$(INTDIR)\DevHelper.res"
	-@erase "$(INTDIR)\DeviceList.obj"
	-@erase "$(INTDIR)\DevInfoQuery.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\USBSTORHelper.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\DevHelper.dll"
	-@erase "$(OUTDIR)\DevHelper.exp"
	-@erase "$(OUTDIR)\DevHelper.lib"
	-@erase ".\DevHelper.h"
	-@erase ".\DevHelper.tlb"
	-@erase ".\DevHelper_i.c"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\DevHelper.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=
RSC=rc.exe
RSC_PROJ=/l 0x419 /fo"$(INTDIR)\DevHelper.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\DevHelper.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib setupapi.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\DevHelper.pdb" /machine:I386 /def:".\DevHelper.def" /out:"$(OUTDIR)\DevHelper.dll" /implib:"$(OUTDIR)\DevHelper.lib" 
DEF_FILE= \
	".\DevHelper.def"
LINK32_OBJS= \
	"$(INTDIR)\DevHelper.obj" \
	"$(INTDIR)\DeviceList.obj" \
	"$(INTDIR)\DevInfoQuery.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\USBSTORHelper.obj" \
	"$(INTDIR)\DevHelper.res"

"$(OUTDIR)\DevHelper.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\DevHelper.dll
InputPath=.\ReleaseUMinDependency\DevHelper.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("DevHelper.dep")
!INCLUDE "DevHelper.dep"
!ELSE 
!MESSAGE Warning: cannot find "DevHelper.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "DevHelper - Win32 Debug" || "$(CFG)" == "DevHelper - Win32 Unicode Debug" || "$(CFG)" == "DevHelper - Win32 Release MinSize" || "$(CFG)" == "DevHelper - Win32 Release MinDependency" || "$(CFG)" == "DevHelper - Win32 Unicode Release MinSize" || "$(CFG)" == "DevHelper - Win32 Unicode Release MinDependency"
SOURCE=.\DevHelper.cpp

"$(INTDIR)\DevHelper.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DevHelper.pch" ".\DevHelper.h" ".\DevHelper_i.c"


SOURCE=.\DevHelper.idl

!IF  "$(CFG)" == "DevHelper - Win32 Debug"

MTL_SWITCHES=/tlb ".\DevHelper.tlb" /h "DevHelper.h" /iid "DevHelper_i.c" /Oicf 

".\DevHelper.tlb"	".\DevHelper.h"	".\DevHelper_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DevHelper - Win32 Unicode Debug"

MTL_SWITCHES=/tlb ".\DevHelper.tlb" /h "DevHelper.h" /iid "DevHelper_i.c" /Oicf 

".\DevHelper.tlb"	".\DevHelper.h"	".\DevHelper_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DevHelper - Win32 Release MinSize"

MTL_SWITCHES=/tlb ".\DevHelper.tlb" /h "DevHelper.h" /iid "DevHelper_i.c" /Oicf 

".\DevHelper.tlb"	".\DevHelper.h"	".\DevHelper_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DevHelper - Win32 Release MinDependency"

MTL_SWITCHES=/tlb ".\DevHelper.tlb" /h "DevHelper.h" /iid "DevHelper_i.c" /Oicf 

".\DevHelper.tlb"	".\DevHelper.h"	".\DevHelper_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DevHelper - Win32 Unicode Release MinSize"

MTL_SWITCHES=/tlb ".\DevHelper.tlb" /h "DevHelper.h" /iid "DevHelper_i.c" /Oicf 

".\DevHelper.tlb"	".\DevHelper.h"	".\DevHelper_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DevHelper - Win32 Unicode Release MinDependency"

MTL_SWITCHES=/tlb ".\DevHelper.tlb" /h "DevHelper.h" /iid "DevHelper_i.c" /Oicf 

".\DevHelper.tlb"	".\DevHelper.h"	".\DevHelper_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\DevHelper.rc

"$(INTDIR)\DevHelper.res" : $(SOURCE) "$(INTDIR)" ".\DevHelper.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\DeviceList.cpp

"$(INTDIR)\DeviceList.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DevHelper.pch" ".\DevHelper.h"


SOURCE=.\DevInfoQuery.cpp

"$(INTDIR)\DevInfoQuery.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DevHelper.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "DevHelper - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\DevHelper.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\DevHelper.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DevHelper - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\DevHelper.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\DevHelper.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DevHelper - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\DevHelper.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\DevHelper.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DevHelper - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\DevHelper.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\DevHelper.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DevHelper - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\DevHelper.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\DevHelper.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DevHelper - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\DevHelper.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\DevHelper.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\USBSTORHelper.cpp

"$(INTDIR)\USBSTORHelper.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DevHelper.pch" ".\DevHelper.h"



!ENDIF 

