# Microsoft Developer Studio Project File - Name="imaging" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=imaging - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE
!MESSAGE NMAKE /f "imaging.mak".
!MESSAGE
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE
!MESSAGE NMAKE /f "imaging.mak" CFG="imaging - Win32 Debug"
!MESSAGE
!MESSAGE Possible choices for configuration are:
!MESSAGE
!MESSAGE "imaging - Win32 DLL Universal Unicode Release" (based on "Win32 (x86) Application")
!MESSAGE "imaging - Win32 DLL Universal Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE "imaging - Win32 DLL Universal Release" (based on "Win32 (x86) Application")
!MESSAGE "imaging - Win32 DLL Universal Debug" (based on "Win32 (x86) Application")
!MESSAGE "imaging - Win32 DLL Unicode Release" (based on "Win32 (x86) Application")
!MESSAGE "imaging - Win32 DLL Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE "imaging - Win32 DLL Release" (based on "Win32 (x86) Application")
!MESSAGE "imaging - Win32 DLL Debug" (based on "Win32 (x86) Application")
!MESSAGE "imaging - Win32 Universal Unicode Release" (based on "Win32 (x86) Application")
!MESSAGE "imaging - Win32 Universal Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE "imaging - Win32 Universal Release" (based on "Win32 (x86) Application")
!MESSAGE "imaging - Win32 Universal Debug" (based on "Win32 (x86) Application")
!MESSAGE "imaging - Win32 Unicode Release" (based on "Win32 (x86) Application")
!MESSAGE "imaging - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE "imaging - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "imaging - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "imaging - Win32 DLL Universal Unicode Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vc_mswunivudll"
# PROP BASE Intermediate_Dir "vc_mswunivudll\imaging"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "vc_mswunivudll"
# PROP Intermediate_Dir "vc_mswunivudll\imaging"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /Fdvc_mswunivudll\imaging.pdb /O2 /GR /EHsc /I "c:\program files\wxwidgets-2.8.10\lib\vc_dll\mswunivu" /I "c:\program files\wxwidgets-2.8.10\include" /W4 /I "." /I "c:\program files\wxwidgets-2.8.10\samples" /D "WIN32" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_UNICODE" /D "WXUSINGDLL" /D "_WINDOWS" /D "NOPCH" /c
# ADD CPP /nologo /FD /MD /Fdvc_mswunivudll\imaging.pdb /O2 /GR /EHsc /I "c:\program files\wxwidgets-2.8.10\lib\vc_dll\mswunivu" /I "c:\program files\wxwidgets-2.8.10\include" /W4 /I "." /I "c:\program files\wxwidgets-2.8.10\samples" /D "WIN32" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_UNICODE" /D "WXUSINGDLL" /D "_WINDOWS" /D "NOPCH" /c
# ADD BASE MTL /nologo /D "WIN32" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_UNICODE" /D "WXUSINGDLL" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_UNICODE" /D "WXUSINGDLL" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "_UNICODE" /i "c:\program files\wxwidgets-2.8.10\lib\vc_dll\mswunivu" /i "c:\program files\wxwidgets-2.8.10\include" /i "." /d "WXUSINGDLL" /d "_WINDOWS" /i "c:\program files\wxwidgets-2.8.10\samples" /d NOPCH
# ADD RSC /l 0x409 /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "_UNICODE" /i "c:\program files\wxwidgets-2.8.10\lib\vc_dll\mswunivu" /i "c:\program files\wxwidgets-2.8.10\include" /i "." /d "WXUSINGDLL" /d "_WINDOWS" /i "c:\program files\wxwidgets-2.8.10\samples" /d NOPCH
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxmswuniv28u_core.lib wxbase28u.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregexu.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswunivudll\imaging.exe" /pdb:"vc_mswunivudll\imaging.pdb" /libpath:"c:\program files\wxwidgets-2.8.10\lib\vc_dll" /subsystem:windows
# ADD LINK32 wxmswuniv28u_core.lib wxbase28u.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregexu.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswunivudll\imaging.exe" /pdb:"vc_mswunivudll\imaging.pdb" /libpath:"c:\program files\wxwidgets-2.8.10\lib\vc_dll" /subsystem:windows

!ELSEIF  "$(CFG)" == "imaging - Win32 DLL Universal Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "vc_mswunivuddll"
# PROP BASE Intermediate_Dir "vc_mswunivuddll\imaging"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "vc_mswunivuddll"
# PROP Intermediate_Dir "vc_mswunivuddll\imaging"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Zi /Fdvc_mswunivuddll\imaging.pdb /Od /Gm /GR /EHsc /I "c:\program files\wxwidgets-2.8.10\lib\vc_dll\mswunivud" /I "c:\program files\wxwidgets-2.8.10\include" /W4 /I "." /I "c:\program files\wxwidgets-2.8.10\samples" /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_UNICODE" /D "WXUSINGDLL" /D "_WINDOWS" /D "NOPCH" /c
# ADD CPP /nologo /FD /MDd /Zi /Fdvc_mswunivuddll\imaging.pdb /Od /Gm /GR /EHsc /I "c:\program files\wxwidgets-2.8.10\lib\vc_dll\mswunivud" /I "c:\program files\wxwidgets-2.8.10\include" /W4 /I "." /I "c:\program files\wxwidgets-2.8.10\samples" /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_UNICODE" /D "WXUSINGDLL" /D "_WINDOWS" /D "NOPCH" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_UNICODE" /D "WXUSINGDLL" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_UNICODE" /D "WXUSINGDLL" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "__WXDEBUG__" /d "_UNICODE" /i "c:\program files\wxwidgets-2.8.10\lib\vc_dll\mswunivud" /i "c:\program files\wxwidgets-2.8.10\include" /i "." /d "WXUSINGDLL" /d "_WINDOWS" /i "c:\program files\wxwidgets-2.8.10\samples" /d NOPCH
# ADD RSC /l 0x409 /d "_DEBUG" /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "__WXDEBUG__" /d "_UNICODE" /i "c:\program files\wxwidgets-2.8.10\lib\vc_dll\mswunivud" /i "c:\program files\wxwidgets-2.8.10\include" /i "." /d "WXUSINGDLL" /d "_WINDOWS" /i "c:\program files\wxwidgets-2.8.10\samples" /d NOPCH
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxmswuniv28ud_core.lib wxbase28ud.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexud.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswunivuddll\imaging.exe" /debug /pdb:"vc_mswunivuddll\imaging.pdb" /libpath:"c:\program files\wxwidgets-2.8.10\lib\vc_dll" /subsystem:windows
# ADD LINK32 wxmswuniv28ud_core.lib wxbase28ud.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexud.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswunivuddll\imaging.exe" /debug /pdb:"vc_mswunivuddll\imaging.pdb" /libpath:"c:\program files\wxwidgets-2.8.10\lib\vc_dll" /subsystem:windows

!ELSEIF  "$(CFG)" == "imaging - Win32 DLL Universal Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vc_mswunivdll"
# PROP BASE Intermediate_Dir "vc_mswunivdll\imaging"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "vc_mswunivdll"
# PROP Intermediate_Dir "vc_mswunivdll\imaging"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /Fdvc_mswunivdll\imaging.pdb /O2 /GR /EHsc /I "c:\program files\wxwidgets-2.8.10\lib\vc_dll\mswuniv" /I "c:\program files\wxwidgets-2.8.10\include" /W4 /I "." /I "c:\program files\wxwidgets-2.8.10\samples" /D "WIN32" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "WXUSINGDLL" /D "_WINDOWS" /D "NOPCH" /c
# ADD CPP /nologo /FD /MD /Fdvc_mswunivdll\imaging.pdb /O2 /GR /EHsc /I "c:\program files\wxwidgets-2.8.10\lib\vc_dll\mswuniv" /I "c:\program files\wxwidgets-2.8.10\include" /W4 /I "." /I "c:\program files\wxwidgets-2.8.10\samples" /D "WIN32" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "WXUSINGDLL" /D "_WINDOWS" /D "NOPCH" /c
# ADD BASE MTL /nologo /D "WIN32" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "WXUSINGDLL" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "WXUSINGDLL" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "__WXMSW__" /d "__WXUNIVERSAL__" /i "c:\program files\wxwidgets-2.8.10\lib\vc_dll\mswuniv" /i "c:\program files\wxwidgets-2.8.10\include" /i "." /d "WXUSINGDLL" /d "_WINDOWS" /i "c:\program files\wxwidgets-2.8.10\samples" /d NOPCH
# ADD RSC /l 0x409 /d "__WXMSW__" /d "__WXUNIVERSAL__" /i "c:\program files\wxwidgets-2.8.10\lib\vc_dll\mswuniv" /i "c:\program files\wxwidgets-2.8.10\include" /i "." /d "WXUSINGDLL" /d "_WINDOWS" /i "c:\program files\wxwidgets-2.8.10\samples" /d NOPCH
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxmswuniv28_core.lib wxbase28.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregex.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswunivdll\imaging.exe" /pdb:"vc_mswunivdll\imaging.pdb" /libpath:"c:\program files\wxwidgets-2.8.10\lib\vc_dll" /subsystem:windows
# ADD LINK32 wxmswuniv28_core.lib wxbase28.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregex.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswunivdll\imaging.exe" /pdb:"vc_mswunivdll\imaging.pdb" /libpath:"c:\program files\wxwidgets-2.8.10\lib\vc_dll" /subsystem:windows

!ELSEIF  "$(CFG)" == "imaging - Win32 DLL Universal Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "vc_mswunivddll"
# PROP BASE Intermediate_Dir "vc_mswunivddll\imaging"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "vc_mswunivddll"
# PROP Intermediate_Dir "vc_mswunivddll\imaging"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Zi /Fdvc_mswunivddll\imaging.pdb /Od /Gm /GR /EHsc /I "c:\program files\wxwidgets-2.8.10\lib\vc_dll\mswunivd" /I "c:\program files\wxwidgets-2.8.10\include" /W4 /I "." /I "c:\program files\wxwidgets-2.8.10\samples" /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "_WINDOWS" /D "NOPCH" /c
# ADD CPP /nologo /FD /MDd /Zi /Fdvc_mswunivddll\imaging.pdb /Od /Gm /GR /EHsc /I "c:\program files\wxwidgets-2.8.10\lib\vc_dll\mswunivd" /I "c:\program files\wxwidgets-2.8.10\include" /W4 /I "." /I "c:\program files\wxwidgets-2.8.10\samples" /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "_WINDOWS" /D "NOPCH" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "__WXDEBUG__" /i "c:\program files\wxwidgets-2.8.10\lib\vc_dll\mswunivd" /i "c:\program files\wxwidgets-2.8.10\include" /i "." /d "WXUSINGDLL" /d "_WINDOWS" /i "c:\program files\wxwidgets-2.8.10\samples" /d NOPCH
# ADD RSC /l 0x409 /d "_DEBUG" /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "__WXDEBUG__" /i "c:\program files\wxwidgets-2.8.10\lib\vc_dll\mswunivd" /i "c:\program files\wxwidgets-2.8.10\include" /i "." /d "WXUSINGDLL" /d "_WINDOWS" /i "c:\program files\wxwidgets-2.8.10\samples" /d NOPCH
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxmswuniv28d_core.lib wxbase28d.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexd.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswunivddll\imaging.exe" /debug /pdb:"vc_mswunivddll\imaging.pdb" /libpath:"c:\program files\wxwidgets-2.8.10\lib\vc_dll" /subsystem:windows
# ADD LINK32 wxmswuniv28d_core.lib wxbase28d.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexd.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswunivddll\imaging.exe" /debug /pdb:"vc_mswunivddll\imaging.pdb" /libpath:"c:\program files\wxwidgets-2.8.10\lib\vc_dll" /subsystem:windows

!ELSEIF  "$(CFG)" == "imaging - Win32 DLL Unicode Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vc_mswudll"
# PROP BASE Intermediate_Dir "vc_mswudll\imaging"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "vc_mswudll"
# PROP Intermediate_Dir "vc_mswudll\imaging"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /Fdvc_mswudll\imaging.pdb /O2 /GR /EHsc /I "c:\program files\wxwidgets-2.8.10\lib\vc_dll\mswu" /I "c:\program files\wxwidgets-2.8.10\include" /W4 /I "." /I "c:\program files\wxwidgets-2.8.10\samples" /D "WIN32" /D "__WXMSW__" /D "_UNICODE" /D "WXUSINGDLL" /D "_WINDOWS" /D "NOPCH" /c
# ADD CPP /nologo /FD /MD /Fdvc_mswudll\imaging.pdb /O2 /GR /EHsc /I "c:\program files\wxwidgets-2.8.10\lib\vc_dll\mswu" /I "c:\program files\wxwidgets-2.8.10\include" /W4 /I "." /I "c:\program files\wxwidgets-2.8.10\samples" /D "WIN32" /D "__WXMSW__" /D "_UNICODE" /D "WXUSINGDLL" /D "_WINDOWS" /D "NOPCH" /c
# ADD BASE MTL /nologo /D "WIN32" /D "__WXMSW__" /D "_UNICODE" /D "WXUSINGDLL" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "__WXMSW__" /D "_UNICODE" /D "WXUSINGDLL" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "__WXMSW__" /d "_UNICODE" /i "c:\program files\wxwidgets-2.8.10\lib\vc_dll\mswu" /i "c:\program files\wxwidgets-2.8.10\include" /i "." /d "WXUSINGDLL" /d "_WINDOWS" /i "c:\program files\wxwidgets-2.8.10\samples" /d NOPCH
# ADD RSC /l 0x409 /d "__WXMSW__" /d "_UNICODE" /i "c:\program files\wxwidgets-2.8.10\lib\vc_dll\mswu" /i "c:\program files\wxwidgets-2.8.10\include" /i "." /d "WXUSINGDLL" /d "_WINDOWS" /i "c:\program files\wxwidgets-2.8.10\samples" /d NOPCH
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxmsw28u_core.lib wxbase28u.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregexu.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswudll\imaging.exe" /pdb:"vc_mswudll\imaging.pdb" /libpath:"c:\program files\wxwidgets-2.8.10\lib\vc_dll" /subsystem:windows
# ADD LINK32 wxmsw28u_core.lib wxbase28u.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregexu.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswudll\imaging.exe" /pdb:"vc_mswudll\imaging.pdb" /libpath:"c:\program files\wxwidgets-2.8.10\lib\vc_dll" /subsystem:windows

!ELSEIF  "$(CFG)" == "imaging - Win32 DLL Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "vc_mswuddll"
# PROP BASE Intermediate_Dir "vc_mswuddll\imaging"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "vc_mswuddll"
# PROP Intermediate_Dir "vc_mswuddll\imaging"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Zi /Fdvc_mswuddll\imaging.pdb /Od /Gm /GR /EHsc /I "c:\program files\wxwidgets-2.8.10\lib\vc_dll\mswud" /I "c:\program files\wxwidgets-2.8.10\include" /W4 /I "." /I "c:\program files\wxwidgets-2.8.10\samples" /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_UNICODE" /D "WXUSINGDLL" /D "_WINDOWS" /D "NOPCH" /c
# ADD CPP /nologo /FD /MDd /Zi /Fdvc_mswuddll\imaging.pdb /Od /Gm /GR /EHsc /I "c:\program files\wxwidgets-2.8.10\lib\vc_dll\mswud" /I "c:\program files\wxwidgets-2.8.10\include" /W4 /I "." /I "c:\program files\wxwidgets-2.8.10\samples" /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_UNICODE" /D "WXUSINGDLL" /D "_WINDOWS" /D "NOPCH" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_UNICODE" /D "WXUSINGDLL" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_UNICODE" /D "WXUSINGDLL" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "__WXMSW__" /d "__WXDEBUG__" /d "_UNICODE" /i "c:\program files\wxwidgets-2.8.10\lib\vc_dll\mswud" /i "c:\program files\wxwidgets-2.8.10\include" /i "." /d "WXUSINGDLL" /d "_WINDOWS" /i "c:\program files\wxwidgets-2.8.10\samples" /d NOPCH
# ADD RSC /l 0x409 /d "_DEBUG" /d "__WXMSW__" /d "__WXDEBUG__" /d "_UNICODE" /i "c:\program files\wxwidgets-2.8.10\lib\vc_dll\mswud" /i "c:\program files\wxwidgets-2.8.10\include" /i "." /d "WXUSINGDLL" /d "_WINDOWS" /i "c:\program files\wxwidgets-2.8.10\samples" /d NOPCH
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxmsw28ud_core.lib wxbase28ud.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexud.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswuddll\imaging.exe" /debug /pdb:"vc_mswuddll\imaging.pdb" /libpath:"c:\program files\wxwidgets-2.8.10\lib\vc_dll" /subsystem:windows
# ADD LINK32 wxmsw28ud_core.lib wxbase28ud.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexud.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswuddll\imaging.exe" /debug /pdb:"vc_mswuddll\imaging.pdb" /libpath:"c:\program files\wxwidgets-2.8.10\lib\vc_dll" /subsystem:windows

!ELSEIF  "$(CFG)" == "imaging - Win32 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vc_mswdll"
# PROP BASE Intermediate_Dir "vc_mswdll\imaging"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "vc_mswdll"
# PROP Intermediate_Dir "vc_mswdll\imaging"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /Fdvc_mswdll\imaging.pdb /O2 /GR /EHsc /I "c:\program files\wxwidgets-2.8.10\lib\vc_dll\msw" /I "c:\program files\wxwidgets-2.8.10\include" /W4 /I "." /I "c:\program files\wxwidgets-2.8.10\samples" /D "WIN32" /D "__WXMSW__" /D "WXUSINGDLL" /D "_WINDOWS" /D "NOPCH" /c
# ADD CPP /nologo /FD /MD /Fdvc_mswdll\imaging.pdb /O2 /GR /EHsc /I "c:\program files\wxwidgets-2.8.10\lib\vc_dll\msw" /I "c:\program files\wxwidgets-2.8.10\include" /W4 /I "." /I "c:\program files\wxwidgets-2.8.10\samples" /D "WIN32" /D "__WXMSW__" /D "WXUSINGDLL" /D "_WINDOWS" /D "NOPCH" /c
# ADD BASE MTL /nologo /D "WIN32" /D "__WXMSW__" /D "WXUSINGDLL" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "__WXMSW__" /D "WXUSINGDLL" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "__WXMSW__" /i "c:\program files\wxwidgets-2.8.10\lib\vc_dll\msw" /i "c:\program files\wxwidgets-2.8.10\include" /i "." /d "WXUSINGDLL" /d "_WINDOWS" /i "c:\program files\wxwidgets-2.8.10\samples" /d NOPCH
# ADD RSC /l 0x409 /d "__WXMSW__" /i "c:\program files\wxwidgets-2.8.10\lib\vc_dll\msw" /i "c:\program files\wxwidgets-2.8.10\include" /i "." /d "WXUSINGDLL" /d "_WINDOWS" /i "c:\program files\wxwidgets-2.8.10\samples" /d NOPCH
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxmsw28_core.lib wxbase28.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregex.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswdll\imaging.exe" /pdb:"vc_mswdll\imaging.pdb" /libpath:"c:\program files\wxwidgets-2.8.10\lib\vc_dll" /subsystem:windows
# ADD LINK32 wxmsw28_core.lib wxbase28.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregex.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswdll\imaging.exe" /pdb:"vc_mswdll\imaging.pdb" /libpath:"c:\program files\wxwidgets-2.8.10\lib\vc_dll" /subsystem:windows

!ELSEIF  "$(CFG)" == "imaging - Win32 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "vc_mswddll"
# PROP BASE Intermediate_Dir "vc_mswddll\imaging"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "vc_mswddll"
# PROP Intermediate_Dir "vc_mswddll\imaging"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Zi /Fdvc_mswddll\imaging.pdb /Od /Gm /GR /EHsc /I "c:\program files\wxwidgets-2.8.10\lib\vc_dll\mswd" /I "c:\program files\wxwidgets-2.8.10\include" /W4 /I "." /I "c:\program files\wxwidgets-2.8.10\samples" /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "_WINDOWS" /D "NOPCH" /c
# ADD CPP /nologo /FD /MDd /Zi /Fdvc_mswddll\imaging.pdb /Od /Gm /GR /EHsc /I "c:\program files\wxwidgets-2.8.10\lib\vc_dll\mswd" /I "c:\program files\wxwidgets-2.8.10\include" /W4 /I "." /I "c:\program files\wxwidgets-2.8.10\samples" /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "_WINDOWS" /D "NOPCH" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "__WXMSW__" /d "__WXDEBUG__" /i "c:\program files\wxwidgets-2.8.10\lib\vc_dll\mswd" /i "c:\program files\wxwidgets-2.8.10\include" /i "." /d "WXUSINGDLL" /d "_WINDOWS" /i "c:\program files\wxwidgets-2.8.10\samples" /d NOPCH
# ADD RSC /l 0x409 /d "_DEBUG" /d "__WXMSW__" /d "__WXDEBUG__" /i "c:\program files\wxwidgets-2.8.10\lib\vc_dll\mswd" /i "c:\program files\wxwidgets-2.8.10\include" /i "." /d "WXUSINGDLL" /d "_WINDOWS" /i "c:\program files\wxwidgets-2.8.10\samples" /d NOPCH
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxmsw28d_core.lib wxbase28d.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexd.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswddll\imaging.exe" /debug /pdb:"vc_mswddll\imaging.pdb" /libpath:"c:\program files\wxwidgets-2.8.10\lib\vc_dll" /subsystem:windows
# ADD LINK32 wxmsw28d_core.lib wxbase28d.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexd.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswddll\imaging.exe" /debug /pdb:"vc_mswddll\imaging.pdb" /libpath:"c:\program files\wxwidgets-2.8.10\lib\vc_dll" /subsystem:windows

!ELSEIF  "$(CFG)" == "imaging - Win32 Universal Unicode Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vc_mswunivu"
# PROP BASE Intermediate_Dir "vc_mswunivu\imaging"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "vc_mswunivu"
# PROP Intermediate_Dir "vc_mswunivu\imaging"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /Fdvc_mswunivu\imaging.pdb /O2 /GR /EHsc /I "c:\program files\wxwidgets-2.8.10\lib\vc_lib\mswunivu" /I "c:\program files\wxwidgets-2.8.10\include" /W4 /I "." /I "c:\program files\wxwidgets-2.8.10\samples" /D "WIN32" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_UNICODE" /D "_WINDOWS" /D "NOPCH" /c
# ADD CPP /nologo /FD /MD /Fdvc_mswunivu\imaging.pdb /O2 /GR /EHsc /I "c:\program files\wxwidgets-2.8.10\lib\vc_lib\mswunivu" /I "c:\program files\wxwidgets-2.8.10\include" /W4 /I "." /I "c:\program files\wxwidgets-2.8.10\samples" /D "WIN32" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_UNICODE" /D "_WINDOWS" /D "NOPCH" /c
# ADD BASE MTL /nologo /D "WIN32" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_UNICODE" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_UNICODE" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "_UNICODE" /i "c:\program files\wxwidgets-2.8.10\lib\vc_lib\mswunivu" /i "c:\program files\wxwidgets-2.8.10\include" /i "." /d "_WINDOWS" /i "c:\program files\wxwidgets-2.8.10\samples" /d NOPCH
# ADD RSC /l 0x409 /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "_UNICODE" /i "c:\program files\wxwidgets-2.8.10\lib\vc_lib\mswunivu" /i "c:\program files\wxwidgets-2.8.10\include" /i "." /d "_WINDOWS" /i "c:\program files\wxwidgets-2.8.10\samples" /d NOPCH
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxmswuniv28u_core.lib wxbase28u.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregexu.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswunivu\imaging.exe" /pdb:"vc_mswunivu\imaging.pdb" /libpath:"c:\program files\wxwidgets-2.8.10\lib\vc_lib" /subsystem:windows
# ADD LINK32 wxmswuniv28u_core.lib wxbase28u.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregexu.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswunivu\imaging.exe" /pdb:"vc_mswunivu\imaging.pdb" /libpath:"c:\program files\wxwidgets-2.8.10\lib\vc_lib" /subsystem:windows

!ELSEIF  "$(CFG)" == "imaging - Win32 Universal Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "vc_mswunivud"
# PROP BASE Intermediate_Dir "vc_mswunivud\imaging"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "vc_mswunivud"
# PROP Intermediate_Dir "vc_mswunivud\imaging"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Zi /Fdvc_mswunivud\imaging.pdb /Od /Gm /GR /EHsc /I "c:\program files\wxwidgets-2.8.10\lib\vc_lib\mswunivud" /I "c:\program files\wxwidgets-2.8.10\include" /W4 /I "." /I "c:\program files\wxwidgets-2.8.10\samples" /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_UNICODE" /D "_WINDOWS" /D "NOPCH" /c
# ADD CPP /nologo /FD /MDd /Zi /Fdvc_mswunivud\imaging.pdb /Od /Gm /GR /EHsc /I "c:\program files\wxwidgets-2.8.10\lib\vc_lib\mswunivud" /I "c:\program files\wxwidgets-2.8.10\include" /W4 /I "." /I "c:\program files\wxwidgets-2.8.10\samples" /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_UNICODE" /D "_WINDOWS" /D "NOPCH" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_UNICODE" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_UNICODE" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "__WXDEBUG__" /d "_UNICODE" /i "c:\program files\wxwidgets-2.8.10\lib\vc_lib\mswunivud" /i "c:\program files\wxwidgets-2.8.10\include" /i "." /d "_WINDOWS" /i "c:\program files\wxwidgets-2.8.10\samples" /d NOPCH
# ADD RSC /l 0x409 /d "_DEBUG" /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "__WXDEBUG__" /d "_UNICODE" /i "c:\program files\wxwidgets-2.8.10\lib\vc_lib\mswunivud" /i "c:\program files\wxwidgets-2.8.10\include" /i "." /d "_WINDOWS" /i "c:\program files\wxwidgets-2.8.10\samples" /d NOPCH
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxmswuniv28ud_core.lib wxbase28ud.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexud.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswunivud\imaging.exe" /debug /pdb:"vc_mswunivud\imaging.pdb" /libpath:"c:\program files\wxwidgets-2.8.10\lib\vc_lib" /subsystem:windows
# ADD LINK32 wxmswuniv28ud_core.lib wxbase28ud.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexud.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswunivud\imaging.exe" /debug /pdb:"vc_mswunivud\imaging.pdb" /libpath:"c:\program files\wxwidgets-2.8.10\lib\vc_lib" /subsystem:windows

!ELSEIF  "$(CFG)" == "imaging - Win32 Universal Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vc_mswuniv"
# PROP BASE Intermediate_Dir "vc_mswuniv\imaging"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "vc_mswuniv"
# PROP Intermediate_Dir "vc_mswuniv\imaging"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /Fdvc_mswuniv\imaging.pdb /O2 /GR /EHsc /I "c:\program files\wxwidgets-2.8.10\lib\vc_lib\mswuniv" /I "c:\program files\wxwidgets-2.8.10\include" /W4 /I "." /I "c:\program files\wxwidgets-2.8.10\samples" /D "WIN32" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_WINDOWS" /D "NOPCH" /c
# ADD CPP /nologo /FD /MD /Fdvc_mswuniv\imaging.pdb /O2 /GR /EHsc /I "c:\program files\wxwidgets-2.8.10\lib\vc_lib\mswuniv" /I "c:\program files\wxwidgets-2.8.10\include" /W4 /I "." /I "c:\program files\wxwidgets-2.8.10\samples" /D "WIN32" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_WINDOWS" /D "NOPCH" /c
# ADD BASE MTL /nologo /D "WIN32" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "__WXMSW__" /d "__WXUNIVERSAL__" /i "c:\program files\wxwidgets-2.8.10\lib\vc_lib\mswuniv" /i "c:\program files\wxwidgets-2.8.10\include" /i "." /d "_WINDOWS" /i "c:\program files\wxwidgets-2.8.10\samples" /d NOPCH
# ADD RSC /l 0x409 /d "__WXMSW__" /d "__WXUNIVERSAL__" /i "c:\program files\wxwidgets-2.8.10\lib\vc_lib\mswuniv" /i "c:\program files\wxwidgets-2.8.10\include" /i "." /d "_WINDOWS" /i "c:\program files\wxwidgets-2.8.10\samples" /d NOPCH
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxmswuniv28_core.lib wxbase28.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregex.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswuniv\imaging.exe" /pdb:"vc_mswuniv\imaging.pdb" /libpath:"c:\program files\wxwidgets-2.8.10\lib\vc_lib" /subsystem:windows
# ADD LINK32 wxmswuniv28_core.lib wxbase28.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregex.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswuniv\imaging.exe" /pdb:"vc_mswuniv\imaging.pdb" /libpath:"c:\program files\wxwidgets-2.8.10\lib\vc_lib" /subsystem:windows

!ELSEIF  "$(CFG)" == "imaging - Win32 Universal Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "vc_mswunivd"
# PROP BASE Intermediate_Dir "vc_mswunivd\imaging"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "vc_mswunivd"
# PROP Intermediate_Dir "vc_mswunivd\imaging"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Zi /Fdvc_mswunivd\imaging.pdb /Od /Gm /GR /EHsc /I "c:\program files\wxwidgets-2.8.10\lib\vc_lib\mswunivd" /I "c:\program files\wxwidgets-2.8.10\include" /W4 /I "." /I "c:\program files\wxwidgets-2.8.10\samples" /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_WINDOWS" /D "NOPCH" /c
# ADD CPP /nologo /FD /MDd /Zi /Fdvc_mswunivd\imaging.pdb /Od /Gm /GR /EHsc /I "c:\program files\wxwidgets-2.8.10\lib\vc_lib\mswunivd" /I "c:\program files\wxwidgets-2.8.10\include" /W4 /I "." /I "c:\program files\wxwidgets-2.8.10\samples" /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_WINDOWS" /D "NOPCH" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "__WXDEBUG__" /i "c:\program files\wxwidgets-2.8.10\lib\vc_lib\mswunivd" /i "c:\program files\wxwidgets-2.8.10\include" /i "." /d "_WINDOWS" /i "c:\program files\wxwidgets-2.8.10\samples" /d NOPCH
# ADD RSC /l 0x409 /d "_DEBUG" /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "__WXDEBUG__" /i "c:\program files\wxwidgets-2.8.10\lib\vc_lib\mswunivd" /i "c:\program files\wxwidgets-2.8.10\include" /i "." /d "_WINDOWS" /i "c:\program files\wxwidgets-2.8.10\samples" /d NOPCH
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxmswuniv28d_core.lib wxbase28d.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexd.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswunivd\imaging.exe" /debug /pdb:"vc_mswunivd\imaging.pdb" /libpath:"c:\program files\wxwidgets-2.8.10\lib\vc_lib" /subsystem:windows
# ADD LINK32 wxmswuniv28d_core.lib wxbase28d.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexd.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswunivd\imaging.exe" /debug /pdb:"vc_mswunivd\imaging.pdb" /libpath:"c:\program files\wxwidgets-2.8.10\lib\vc_lib" /subsystem:windows

!ELSEIF  "$(CFG)" == "imaging - Win32 Unicode Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vc_mswu"
# PROP BASE Intermediate_Dir "vc_mswu\imaging"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "vc_mswu"
# PROP Intermediate_Dir "vc_mswu\imaging"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /Fdvc_mswu\imaging.pdb /O2 /GR /EHsc /I "c:\program files\wxwidgets-2.8.10\lib\vc_lib\mswu" /I "c:\program files\wxwidgets-2.8.10\include" /W4 /I "." /I "c:\program files\wxwidgets-2.8.10\samples" /D "WIN32" /D "__WXMSW__" /D "_UNICODE" /D "_WINDOWS" /D "NOPCH" /c
# ADD CPP /nologo /FD /MD /Fdvc_mswu\imaging.pdb /O2 /GR /EHsc /I "c:\program files\wxwidgets-2.8.10\lib\vc_lib\mswu" /I "c:\program files\wxwidgets-2.8.10\include" /W4 /I "." /I "c:\program files\wxwidgets-2.8.10\samples" /D "WIN32" /D "__WXMSW__" /D "_UNICODE" /D "_WINDOWS" /D "NOPCH" /c
# ADD BASE MTL /nologo /D "WIN32" /D "__WXMSW__" /D "_UNICODE" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "__WXMSW__" /D "_UNICODE" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "__WXMSW__" /d "_UNICODE" /i "c:\program files\wxwidgets-2.8.10\lib\vc_lib\mswu" /i "c:\program files\wxwidgets-2.8.10\include" /i "." /d "_WINDOWS" /i "c:\program files\wxwidgets-2.8.10\samples" /d NOPCH
# ADD RSC /l 0x409 /d "__WXMSW__" /d "_UNICODE" /i "c:\program files\wxwidgets-2.8.10\lib\vc_lib\mswu" /i "c:\program files\wxwidgets-2.8.10\include" /i "." /d "_WINDOWS" /i "c:\program files\wxwidgets-2.8.10\samples" /d NOPCH
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxmsw28u_core.lib wxbase28u.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregexu.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswu\imaging.exe" /pdb:"vc_mswu\imaging.pdb" /libpath:"c:\program files\wxwidgets-2.8.10\lib\vc_lib" /subsystem:windows
# ADD LINK32 wxmsw28u_core.lib wxbase28u.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregexu.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswu\imaging.exe" /pdb:"vc_mswu\imaging.pdb" /libpath:"c:\program files\wxwidgets-2.8.10\lib\vc_lib" /subsystem:windows

!ELSEIF  "$(CFG)" == "imaging - Win32 Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "vc_mswud"
# PROP BASE Intermediate_Dir "vc_mswud\imaging"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "vc_mswud"
# PROP Intermediate_Dir "vc_mswud\imaging"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Zi /Fdvc_mswud\imaging.pdb /Od /Gm /GR /EHsc /I "c:\program files\wxwidgets-2.8.10\lib\vc_lib\mswud" /I "c:\program files\wxwidgets-2.8.10\include" /W4 /I "." /I "c:\program files\wxwidgets-2.8.10\samples" /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_UNICODE" /D "_WINDOWS" /D "NOPCH" /c
# ADD CPP /nologo /FD /MDd /Zi /Fdvc_mswud\imaging.pdb /Od /Gm /GR /EHsc /I "c:\program files\wxwidgets-2.8.10\lib\vc_lib\mswud" /I "c:\program files\wxwidgets-2.8.10\include" /W4 /I "." /I "c:\program files\wxwidgets-2.8.10\samples" /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_UNICODE" /D "_WINDOWS" /D "NOPCH" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_UNICODE" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_UNICODE" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "__WXMSW__" /d "__WXDEBUG__" /d "_UNICODE" /i "c:\program files\wxwidgets-2.8.10\lib\vc_lib\mswud" /i "c:\program files\wxwidgets-2.8.10\include" /i "." /d "_WINDOWS" /i "c:\program files\wxwidgets-2.8.10\samples" /d NOPCH
# ADD RSC /l 0x409 /d "_DEBUG" /d "__WXMSW__" /d "__WXDEBUG__" /d "_UNICODE" /i "c:\program files\wxwidgets-2.8.10\lib\vc_lib\mswud" /i "c:\program files\wxwidgets-2.8.10\include" /i "." /d "_WINDOWS" /i "c:\program files\wxwidgets-2.8.10\samples" /d NOPCH
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxmsw28ud_core.lib wxbase28ud.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexud.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswud\imaging.exe" /debug /pdb:"vc_mswud\imaging.pdb" /libpath:"c:\program files\wxwidgets-2.8.10\lib\vc_lib" /subsystem:windows
# ADD LINK32 wxmsw28ud_core.lib wxbase28ud.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexud.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswud\imaging.exe" /debug /pdb:"vc_mswud\imaging.pdb" /libpath:"c:\program files\wxwidgets-2.8.10\lib\vc_lib" /subsystem:windows

!ELSEIF  "$(CFG)" == "imaging - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vc_msw"
# PROP BASE Intermediate_Dir "vc_msw\imaging"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "vc_msw"
# PROP Intermediate_Dir "vc_msw\imaging"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /Fdvc_msw\imaging.pdb /O2 /GR /EHsc /I "c:\program files\wxwidgets-2.8.10\lib\vc_lib\msw" /I "c:\program files\wxwidgets-2.8.10\include" /W4 /I "." /I "c:\program files\wxwidgets-2.8.10\samples" /D "WIN32" /D "__WXMSW__" /D "_WINDOWS" /D "NOPCH" /c
# ADD CPP /nologo /FD /MD /Fdvc_msw\imaging.pdb /O2 /GR /EHsc /I "c:\program files\wxwidgets-2.8.10\lib\vc_lib\msw" /I "c:\program files\wxwidgets-2.8.10\include" /W4 /I "." /I "c:\program files\wxwidgets-2.8.10\samples" /D "WIN32" /D "__WXMSW__" /D "_WINDOWS" /D "NOPCH" /c
# ADD BASE MTL /nologo /D "WIN32" /D "__WXMSW__" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "__WXMSW__" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "__WXMSW__" /i "c:\program files\wxwidgets-2.8.10\lib\vc_lib\msw" /i "c:\program files\wxwidgets-2.8.10\include" /i "." /d "_WINDOWS" /i "c:\program files\wxwidgets-2.8.10\samples" /d NOPCH
# ADD RSC /l 0x409 /d "__WXMSW__" /i "c:\program files\wxwidgets-2.8.10\lib\vc_lib\msw" /i "c:\program files\wxwidgets-2.8.10\include" /i "." /d "_WINDOWS" /i "c:\program files\wxwidgets-2.8.10\samples" /d NOPCH
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxmsw28_core.lib wxbase28.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregex.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /machine:i386 /out:"vc_msw\imaging.exe" /pdb:"vc_msw\imaging.pdb" /libpath:"c:\program files\wxwidgets-2.8.10\lib\vc_lib" /subsystem:windows
# ADD LINK32 wxmsw28_core.lib wxbase28.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregex.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /machine:i386 /out:"vc_msw\imaging.exe" /pdb:"vc_msw\imaging.pdb" /libpath:"c:\program files\wxwidgets-2.8.10\lib\vc_lib" /subsystem:windows

!ELSEIF  "$(CFG)" == "imaging - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "vc_mswd"
# PROP BASE Intermediate_Dir "vc_mswd\imaging"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "vc_mswd"
# PROP Intermediate_Dir "vc_mswd\imaging"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Zi /Fdvc_mswd\imaging.pdb /Od /Gm /GR /EHsc /I "c:\program files\wxwidgets-2.8.10\lib\vc_lib\mswd" /I "c:\program files\wxwidgets-2.8.10\include" /W4 /I "." /I "c:\program files\wxwidgets-2.8.10\samples" /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_WINDOWS" /D "NOPCH" /c
# ADD CPP /nologo /FD /MDd /Zi /Fdvc_mswd\imaging.pdb /Od /Gm /GR /EHsc /I "c:\program files\wxwidgets-2.8.10\lib\vc_lib\mswd" /I "c:\program files\wxwidgets-2.8.10\include" /W4 /I "." /I "c:\program files\wxwidgets-2.8.10\samples" /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_WINDOWS" /D "NOPCH" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_WINDOWS" /D "NOPCH" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "__WXMSW__" /d "__WXDEBUG__" /i "c:\program files\wxwidgets-2.8.10\lib\vc_lib\mswd" /i "c:\program files\wxwidgets-2.8.10\include" /i "." /d "_WINDOWS" /i "c:\program files\wxwidgets-2.8.10\samples" /d NOPCH
# ADD RSC /l 0x409 /d "_DEBUG" /d "__WXMSW__" /d "__WXDEBUG__" /i "c:\program files\wxwidgets-2.8.10\lib\vc_lib\mswd" /i "c:\program files\wxwidgets-2.8.10\include" /i "." /d "_WINDOWS" /i "c:\program files\wxwidgets-2.8.10\samples" /d NOPCH
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxmsw28d_core.lib wxbase28d.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexd.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswd\imaging.exe" /debug /pdb:"vc_mswd\imaging.pdb" /libpath:"c:\program files\wxwidgets-2.8.10\lib\vc_lib" /subsystem:windows
# ADD LINK32 wxmsw28d_core.lib wxbase28d.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexd.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib /nologo /machine:i386 /out:"vc_mswd\imaging.exe" /debug /pdb:"vc_mswd\imaging.pdb" /libpath:"c:\program files\wxwidgets-2.8.10\lib\vc_lib" /subsystem:windows

!ENDIF

# Begin Target

# Name "imaging - Win32 DLL Universal Unicode Release"
# Name "imaging - Win32 DLL Universal Unicode Debug"
# Name "imaging - Win32 DLL Universal Release"
# Name "imaging - Win32 DLL Universal Debug"
# Name "imaging - Win32 DLL Unicode Release"
# Name "imaging - Win32 DLL Unicode Debug"
# Name "imaging - Win32 DLL Release"
# Name "imaging - Win32 DLL Debug"
# Name "imaging - Win32 Universal Unicode Release"
# Name "imaging - Win32 Universal Unicode Debug"
# Name "imaging - Win32 Universal Release"
# Name "imaging - Win32 Universal Debug"
# Name "imaging - Win32 Unicode Release"
# Name "imaging - Win32 Unicode Debug"
# Name "imaging - Win32 Release"
# Name "imaging - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\main.cc
# End Source File

# End Group
# End Target
# End Project

