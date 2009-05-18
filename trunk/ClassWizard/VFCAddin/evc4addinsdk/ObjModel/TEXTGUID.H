// Microsoft Visual Studio Object Model
// Copyright (C) 1996-1997 Microsoft Corporation
// All rights reserved.

/////////////////////////////////////////////////////////////////////////////
// textguid.h

// Declaration of GUIDs used for objects found in the type library
//  VISUAL STUDIO 97 TEXT EDITOR (SharedIDE\bin\devedit.pkg)

// NOTE!!!  This file uses the DEFINE_GUID macro.  If you #include
//  this file in your project, then you must also #include it in
//  exactly one of your project's other files with a 
//  "#include <initguid.h>" beforehand: i.e.,
//		#include <initguid.h>
//		#include <textguid.h>
//  If you fail to do this, you will get UNRESOLVED EXTERNAL linker errors.
//  The Developer Studio add-in wizard automatically does this for you.

#ifndef __TEXTGUID_H__
#define __TEXTGUID_H__


/////////////////////////////////////////////////////////////////////////
// TextDocument Object IID

#ifdef EVC4
// {A2B45641-9F45-4247-ADEC-B35668B52514}
struct __declspec(uuid("{A2B45641-9F45-4247-ADEC-B35668B52514}")) ITextDocument;
DEFINE_GUID(IID_ITextDocument,
0xA2B45641L,0x9F45,0x4247,0xAD,0xEC,0xB3,0x56,0x68,0xB5,0x25,0x14);
#else
// {ae0914db-ac28-4834-9361-6dead7a1adad}
struct __declspec(uuid("{ae0914db-ac28-4834-9361-6dead7a1adad}")) ITextDocument;
DEFINE_GUID(IID_ITextDocument,
0xae0914dbL,0xac28,0x4834,0x93,0x61,0x6d,0xea,0xd7,0xa1,0xad,0xad);
#endif //EVC4

/////////////////////////////////////////////////////////////////////////
// TextSelection Object IID

// {05092F20-833F-11CF-AB59-00AA00C091A1}
struct __declspec(uuid("{05092F20-833F-11CF-AB59-00AA00C091A1}")) ITextSelection;
DEFINE_GUID(IID_ITextSelection,
0x05092F20L,0x833F,0x11CF,0xAB,0x59,0x00,0xAA,0x00,0xC0,0x91,0xA1);


/////////////////////////////////////////////////////////////////////////
// TextWindow Object IID

// {08541520-83D3-11CF-AB59-00AA00C091A1}
struct __declspec(uuid("{08541520-83D3-11CF-AB59-00AA00C091A1}")) ITextWindow;
DEFINE_GUID(IID_ITextWindow,
0x08541520L,0x83D3,0x11CF,0xAB,0x59,0x00,0xAA,0x00,0xC0,0x91,0xA1);


/////////////////////////////////////////////////////////////////////////
// TextEditor Object IID

// {0DE5B3A0-A420-11cf-AB59-00AA00C091A1}
struct __declspec(uuid("{0DE5B3A0-A420-11cf-AB59-00AA00C091A1}")) ITextEditor;
DEFINE_GUID(IID_ITextEditor,
0x0DE5B3A0L,0xA420,0x11CF,0xAB,0x59,0x00,0xAA,0x00,0xC0,0x91,0xA1);


#endif // __TEXTGUID_H__

