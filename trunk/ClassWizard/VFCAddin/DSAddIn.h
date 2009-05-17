// DSAddIn.h : header file
//

#if !defined(AFX_DSADDIN_H__8BDC175F_7AA8_4B31_BDF7_6CA4E48B34C8__INCLUDED_)
#define AFX_DSADDIN_H__8BDC175F_7AA8_4B31_BDF7_6CA4E48B34C8__INCLUDED_

#include "commands.h"

#ifdef EVC4
// {FE72BFC6-2B67-4BC0-8BAE-74C5CE293D66}
DEFINE_GUID(CLSID_DSAddIn,
0xfe72bfc6, 0x2b67, 0x4bc0, 0x8b, 0xae, 0x74, 0xc5, 0xce, 0x29, 0x3d, 0x66);
#else
// {FE72BFC6-2B67-4BC0-8BAE-74C5CE293D66}
DEFINE_GUID(CLSID_DSAddIn,
0xfe72bfc6, 0x2b67, 0x4bc0, 0x8b, 0xae, 0x74, 0xc5, 0xce, 0x29, 0x3d, 0x65);
#endif

/////////////////////////////////////////////////////////////////////////////
// CDSAddIn

class CDSAddIn : 
	public IDSAddIn,
	public CComObjectRoot,
	public CComCoClass<CDSAddIn, &CLSID_DSAddIn>
{
public:
#ifdef EVC4
		DECLARE_REGISTRY(CDSAddIn, "VFCAddinEVC.DSAddIn.1",
		"VFCADDIN Developer Studio Add-in", IDS_VFCADDIN_LONGNAME_EVC,
		THREADFLAGS_BOTH)
#else
	DECLARE_REGISTRY(CDSAddIn, "VFCAddin.DSAddIn.1",
		"VFCADDIN Developer Studio Add-in", IDS_VFCADDIN_LONGNAME,
		THREADFLAGS_BOTH)
#endif

	CDSAddIn() {}
	BEGIN_COM_MAP(CDSAddIn)
		COM_INTERFACE_ENTRY(IDSAddIn)
	END_COM_MAP()
	DECLARE_NOT_AGGREGATABLE(CDSAddIn)

// IDSAddIns
public:
	STDMETHOD(OnConnection)(THIS_ IApplication* pApp, VARIANT_BOOL bFirstTime,
		long dwCookie, VARIANT_BOOL* OnConnection);
	STDMETHOD(OnDisconnection)(THIS_ VARIANT_BOOL bLastTime);

protected:
	CCommandsObj* m_pCommands;
	DWORD m_dwCookie;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DSADDIN_H__8BDC175F_7AA8_4B31_BDF7_6CA4E48B34C8__INCLUDED)
