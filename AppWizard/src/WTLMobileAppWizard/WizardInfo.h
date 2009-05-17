// WizardInfo.h: interface for the CWizardInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WIZARDINFO_H__D023FC44_D3F7_47E1_8652_7B8222B6637B__INCLUDED_)
#define AFX_WIZARDINFO_H__D023FC44_D3F7_47E1_8652_7B8222B6637B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "wiz_file.h"
#include "../vs_wizard/vs_wizard.h"
#include <vector>
#include <algorithm>

class CWizardInfo  : public vs_wizard_info
{
public:

	CWizardInfo();
	virtual ~CWizardInfo();
	
	CString		strProjectName;
	CString		strProjectPath;
	bool	m_bEVCCompa;
	int		m_nOrientType;
	int		m_nStringType;
	bool	m_bUseString;
	bool	m_bOrientAware;
	bool	m_bFullScreen;
	bool	m_bCreateViewClass;
	int		m_nMenuType;
	bool	m_bEnableScroll;
	bool	m_bEnableZoom;
	int			nSDKType;
	int			nAppType;
	bool		bEnableActiveX;
	bool		bCppFiles;
	bool		bStatusBar;
	bool		bUseView;
	int			nViewType;
	bool		bHostActiveX;
	bool		bVCExpress;
	bool		bVS60;
	bool		bVS2002;
	bool		bVS2003;
	bool		bVS2005;
	bool		bVS2008;
	bool		bVS60STD;

	std::vector<CString>	ar_view;
	std::vector<CString>	ar_app;
};

#endif // !defined(AFX_WIZARDINFO_H__D023FC44_D3F7_47E1_8652_7B8222B6637B__INCLUDED_)
