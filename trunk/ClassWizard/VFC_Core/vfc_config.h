// vfc_config.h : interface of the vfc_config class
//
/////////////////////////////////////////////////////////////////////////////
#ifndef __VFC_CONFIG_H__
#define __VFC_CONFIG_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class vfc_config
{
public:
	vfc_config()
	{
		cfgApp = _T("SETUP");
		cfgPath = GetModulePath(_Module.m_hInst)+_T("\\visualfc.ini");
	}
	virtual ~vfc_config()
	{
	}
	void load()
	{
		bWTL = load_cfg_bool(_T("ENABLE_WTL"),true);
		bWinx = load_cfg_bool(_T("ENABLE_WINXGUI"),true);
		bAppWizard = load_cfg_bool(_T("ENABLE_APPWIZARD"),true);
		bCodeWizard = load_cfg_bool(_T("ENABLE_CODEWIZARD"),true);
	}
	void save()
	{
		save_cfg_bool(_T("ENABLE_WTL"),bWTL);
		save_cfg_bool(_T("ENABLE_WINXGUI"),bWinx);
		save_cfg_bool(_T("ENABLE_APPWIZARD"),bAppWizard);
		save_cfg_bool(_T("ENABLE_CODEWIZARD"),bCodeWizard);
	}
	bool load_cfg_bool(LPCTSTR lpszKey, bool bdef)
	{
		return ::GetPrivateProfileInt(cfgApp,lpszKey,bdef ? 1 : 0,cfgPath) != 0;
	}
	void save_cfg_bool(LPCTSTR lpszKey, bool bval)
	{
		::WritePrivateProfileString(cfgApp,lpszKey,bval ? _T("1") : _T("0"),cfgPath);
	}

	CString cfgApp;
	CString cfgPath;

	bool	bWTL;
	bool	bWinx;
	bool	bAppWizard;
	bool	bCodeWizard;

	bool operator == (vfc_config & cfg)
	{
		return bWTL == cfg.bWTL && 
			   bWinx == cfg.bWinx && 
			   bAppWizard == cfg.bAppWizard &&
			   bCodeWizard == cfg.bCodeWizard;
	}
	bool operator != (vfc_config & cfg)
	{
		return !(*this == cfg);
	}
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// VisualFC AppWizard will insert additional declarations immediately before the previous line.
#endif // __VFC_CONFIG_H__
