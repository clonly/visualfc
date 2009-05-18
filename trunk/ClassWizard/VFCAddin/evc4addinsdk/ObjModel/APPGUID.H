// Microsoft Visual Studio Object Model
// Copyright (C) 1996-1997 Microsoft Corporation
// All rights reserved.

/////////////////////////////////////////////////////////////////////////////
// appguid.h

// Declaration of GUIDs used for objects found in the type library
//  VISUAL STUDIO 97 SHARED OBJECTS (SharedIDE\bin\devshl.dll)

// NOTE!!!  This file uses the DEFINE_GUID macro.  If you #include
//  this file in your project, then you must also #include it in
//  exactly one of your project's other files with a 
//  "#include <initguid.h>" beforehand: i.e.,
//		#include <initguid.h>
//		#include <appguid.h>
//  If you fail to do this, you will get UNRESOLVED EXTERNAL linker errors.
//  The Developer Studio add-in wizard automatically does this for you.

#ifndef __APPGUID_H__
#define __APPGUID_H__

/////////////////////////////////////////////////////////////////////////
// Application Object IDs

// {EC1D73A1-8CC4-11cf-9BE9-00A0C90A632C}
struct __declspec(uuid("{EC1D73A1-8CC4-11cf-9BE9-00A0C90A632C}")) IApplication;
DEFINE_GUID(IID_IApplication,
0xEC1D73A1L,0x8CC4,0x11CF,0x9B,0xE9,0x00,0xA0,0xC9,0x0A,0x63,0x2C);

// {8EA3F900-4A9F-11cf-8E4E-00AA004254C4}
struct __declspec(uuid("{8EA3F900-4A9F-11cf-8E4E-00AA004254C4}")) IApplicationEvents;
DEFINE_GUID(IID_IApplicationEvents, 
0x8ea3f900, 0x4a9f, 0x11cf, 0x8e, 0x4e, 0x0, 0xaa, 0x0, 0x42, 0x54, 0xc4);

#ifdef EVC4
// {FB08B405-EB5F-442e-887C-20135428DD68}
DEFINE_GUID(CLSID_Application, 
0xFB08B405, 0xEB5F, 0x442e, 0x88, 0x7C, 0x20, 0x13, 0x54, 0x28, 0xDD, 0x68);
#else
// {0110cbb5-3d58-4d22-b108-2b33234fcf65}
DEFINE_GUID(CLSID_Application, 
0x0110cbb5, 0x3d58, 0x4d22, 0xb1, 0x08, 0x2b, 0x33, 0x23, 0x4f, 0xcf, 0x65);
#endif //EVC4

/////////////////////////////////////////////////////////////////////////
// Document Object IID

#ifdef EVC4
// {28B45BBB-666C-4950-9F2D-9F271F30AB47}
struct __declspec(uuid("{28B45BBB-666C-4950-9F2D-9F271F30AB47}")) IGenericDocument;
DEFINE_GUID(IID_IGenericDocument, 
0x28B45BBB, 0x666C, 0x4950, 0x9F, 0x2D, 0x9F, 0x27, 0x1F, 0x30, 0xAB, 0x47);
#else
// {c41998bd-f7b1-49bf-874b-b48d6ce99f12}
struct __declspec(uuid("{c41998bd-f7b1-49bf-874b-b48d6ce99f12}")) IGenericDocument;
DEFINE_GUID(IID_IGenericDocument, 
0xc41998bd, 0xf7b1, 0x49bf, 0x87, 0x4b, 0xb4, 0x8d, 0x6c, 0xe9, 0x9f, 0x12);
#endif //EVC4

/////////////////////////////////////////////////////////////////////////
// Documents Collection Object IID

#ifdef EVC4
// {C3E4138A-0F5E-4cbf-A6B8-65D710B34BEA}
struct __declspec(uuid("{C3E4138A-0F5E-4cbf-A6B8-65D710B34BEA}")) IDocuments;
DEFINE_GUID(IID_IDocuments,
0xC3E4138AL,0x0F5E,0x4cbf,0xA6,0xB8,0x65,0xD7,0x10,0xB3,0x4B,0xEA);
#else
// {9093b40f-e2db-44a0-9caa-ed14c73ffdc5}
struct __declspec(uuid("{9093b40f-e2db-44a0-9caa-ed14c73ffdc5}")) IDocuments;
DEFINE_GUID(IID_IDocuments,
0x9093b40fL,0xe2db,0x44a0,0x9c,0xaa,0xed,0x14,0xc7,0x3f,0xfd,0xc5);
#endif //EVC4

/////////////////////////////////////////////////////////////////////////
// Window Object IID

// {FD20FC80-A9D2-11cf-9C13-00A0C90A632C}
struct __declspec(uuid("{FD20FC80-A9D2-11cf-9C13-00A0C90A632C}")) IGenericWindow;
DEFINE_GUID(IID_IGenericWindow,
0xFD20FC80L,0xA9D2,0x11CF,0x9C,0x13,0x00,0xA0,0xC9,0x0A,0x63,0x2C);


/////////////////////////////////////////////////////////////////////////
// Windows Collection Object IID

// {3928F551-96E6-11cf-9C00-00A0C90A632C}
struct __declspec(uuid("{3928F551-96E6-11cf-9C00-00A0C90A632C}")) IWindows;
DEFINE_GUID(IID_IWindows, 
0x3928f551L, 0x96e6, 0x11cf, 0x9c, 0x00, 0x00, 0xa0, 0xc9, 0xa, 0x63, 0x2c);


/////////////////////////////////////////////////////////////////////////
// Project Object IID

// {8CA5A960-FC7D-11cf-927D-00A0C9138C45}
struct __declspec(uuid("{8CA5A960-FC7D-11cf-927D-00A0C9138C45}")) IGenericProject;
DEFINE_GUID(IID_IGenericProject, 
0x8ca5a960, 0xfc7d, 0x11cf, 0x92, 0x7d, 0x0, 0xa0, 0xc9, 0x13, 0x8c, 0x45);


/////////////////////////////////////////////////////////////////////////
// Projects Collection Object IID

// {13BF7741-A7E8-11cf-AD07-00A0C9034965}
struct __declspec(uuid("{13BF7741-A7E8-11cf-AD07-00A0C9034965}")) IProjects;
DEFINE_GUID(IID_IProjects,
0x13BF7741L,0xA7E8,0x11CF,0xAD,0x07,0x00,0xA0,0xC9,0x03,0x49,0x65);


#endif //__APPGUID_H__

