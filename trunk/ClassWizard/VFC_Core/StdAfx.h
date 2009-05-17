// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__E7A5FABE_A62A_4245_AB8B_DDA722C36FA6__INCLUDED_)
#define AFX_STDAFX_H__E7A5FABE_A62A_4245_AB8B_DDA722C36FA6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif
#define _ATL_APARTMENT_THREADED

//#define WINVER		0x0400
//#define _WIN32_WINNT	0x0400
#define _WIN32_IE	0x0400
#define _RICHEDIT_VER	0x0100

#include <atlbase.h>
#include <atlapp.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CAppModule _Module;
#include <atlcom.h>

#include <ShlGuid.h>
#include <atlapp.h>
#include <atlwin.h>
#include <atlmisc.h>
#include <atlframe.h>
#include <atlctrls.h>
#include <atlctrlx.h>
#include <atlsplit.h>
#include <atlddx.h>

#include "vfcframe.h"
#include "vfcpanel.h"
#include "vfcsplit.h"
#include "vfcpanes.h"

#include <map>

#include "../public/atltabex.h"
#include "../public/foxlib.h"
#include "../public/foxuilib.h"
#include "../public/qevent.h"
#include "../public/vfcfonts.h"
#include "../public/vfcsplit.h"
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__E7A5FABE_A62A_4245_AB8B_DDA722C36FA6__INCLUDED)
