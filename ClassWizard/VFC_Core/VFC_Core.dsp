# Microsoft Developer Studio Project File - Name="VFC_Core" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=VFC_Core - Win32 AnsiDebug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VFC_Core.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VFC_Core.mak" CFG="VFC_Core - Win32 AnsiDebug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VFC_Core - Win32 AnsiRelease" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "VFC_Core - Win32 AnsiDebug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "VFC_Core - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "VFC_Core - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "VFC_Core - Win32 AnsiRelease"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "AnsiDebug"
# PROP BASE Intermediate_Dir "AnsiDebug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "AnsiRelease"
# PROP Intermediate_Dir "AnsiRelease"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /O1 /I "..\include" /I "..\public" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_MBCS" /Yu"stdafx.h" /FD /Zm128 /c
# ADD CPP /nologo /MD /W3 /O1 /I "..\include" /I "..\public" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_MBCS" /Yu"stdafx.h" /FD /Zm256 /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386 /out:"../bin/VFC_Core.dll"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wxbase28.lib /nologo /subsystem:windows /dll /machine:I386 /out:"../bin/VFC_Core.dll"

!ELSEIF  "$(CFG)" == "VFC_Core - Win32 AnsiDebug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "AnsiDebug"
# PROP BASE Intermediate_Dir "AnsiDebug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "AnsiDebug"
# PROP Intermediate_Dir "AnsiDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /ZI /Od /I "..\include" /I "..\public" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_MBCS" /Fp"Debug/VFC_Core.pch" /Yu"stdafx.h" /FD /Zm256 /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /ZI /Od /I "..\include" /I "..\public" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_MBCS" /Fp"Debug/VFC_Core.pch" /Yu"stdafx.h" /FD /Zm256 /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"../bin/VFC_Core.dll" /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"../bin/VFC_Core.dll" /pdbtype:sept

!ELSEIF  "$(CFG)" == "VFC_Core - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /O1 /I "..\include" /I "..\public" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /FR /Yu"stdafx.h" /FD /Zm128 /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386 /out:"../bin/VFC_Core.dll"

!ELSEIF  "$(CFG)" == "VFC_Core - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /ZI /Od /I "..\include" /I "..\public" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /Zm256 /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"../bin/VFC_Core.dll" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "VFC_Core - Win32 AnsiRelease"
# Name "VFC_Core - Win32 AnsiDebug"
# Name "VFC_Core - Win32 Release"
# Name "VFC_Core - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\FCWizard.cpp
# End Source File
# Begin Source File

SOURCE=.\FCWizard.def
# End Source File
# Begin Source File

SOURCE=.\FCWizard.idl
# ADD MTL /tlb ".\FCWizard.tlb" /h "FCWizard.h" /iid "FCWizard_i.c" /Oicf
# End Source File
# Begin Source File

SOURCE=.\FCWizard.rc
# End Source File
# Begin Source File

SOURCE=.\cbparser\parserthread.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\resources\ResAccelerators.cpp
# End Source File
# Begin Source File

SOURCE=.\resources\ResDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\resources\ResMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\resources\Resources.cpp
# End Source File
# Begin Source File

SOURCE=.\resources\ResToolbar.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\cbparser\token.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\cbparser\tokenizer.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\public\atltabex.h
# End Source File
# Begin Source File

SOURCE=.\codeparser.h
# End Source File
# Begin Source File

SOURCE=.\codeupdate.h
# End Source File
# Begin Source File

SOURCE=.\datalist_t.h
# End Source File
# Begin Source File

SOURCE=.\dspparser.h
# End Source File
# Begin Source File

SOURCE=.\page_appwizard.h
# End Source File
# Begin Source File

SOURCE=.\page_base_t.h
# End Source File
# Begin Source File

SOURCE=.\page_class_info.h
# End Source File
# Begin Source File

SOURCE=.\page_ddx_t.h
# End Source File
# Begin Source File

SOURCE=.\page_ddx_template.h
# End Source File
# Begin Source File

SOURCE=.\page_dlsz_t.h
# End Source File
# Begin Source File

SOURCE=.\page_event_t.h
# End Source File
# Begin Source File

SOURCE=.\page_font_t.h
# End Source File
# Begin Source File

SOURCE=.\page_notify_t.h
# End Source File
# Begin Source File

SOURCE=.\page_setup.h
# End Source File
# Begin Source File

SOURCE=.\page_tools.h
# End Source File
# Begin Source File

SOURCE=.\page_upui_t.h
# End Source File
# Begin Source File

SOURCE=.\page_winx_ddx.h
# End Source File
# Begin Source File

SOURCE=.\page_winx_dlsz.h
# End Source File
# Begin Source File

SOURCE=.\page_winx_event.h
# End Source File
# Begin Source File

SOURCE=.\page_winx_font.h
# End Source File
# Begin Source File

SOURCE=.\page_winx_notify.h
# End Source File
# Begin Source File

SOURCE=.\page_winx_upui.h
# End Source File
# Begin Source File

SOURCE=.\page_wtl_ddx.h
# End Source File
# Begin Source File

SOURCE=.\page_wtl_dlsz.h
# End Source File
# Begin Source File

SOURCE=.\page_wtl_event.h
# End Source File
# Begin Source File

SOURCE=.\page_wtl_font.h
# End Source File
# Begin Source File

SOURCE=.\page_wtl_notify.h
# End Source File
# Begin Source File

SOURCE=.\page_wtl_upui.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\vfc_config.h
# End Source File
# Begin Source File

SOURCE=.\win32_notify.h
# End Source File
# Begin Source File

SOURCE=.\winx_event.h
# End Source File
# Begin Source File

SOURCE=.\wizardui.h
# End Source File
# Begin Source File

SOURCE=.\wtl_event.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\image.bmp
# End Source File
# Begin Source File

SOURCE=.\prop_too.bmp
# End Source File
# End Group
# End Target
# End Project
