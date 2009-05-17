// WizardSheet.cpp: implementation of the CWizardSheet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "WizardSheet.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWizardSheet::CWizardSheet(CWizardInfo * info, UINT uStartPage, HWND hWndParent) : 
	baseClass(_T("ATL/WTL Application Wizard"), IDB_HEADER, IDB_WTL,uStartPage, hWndParent)
{
	m_psh.dwFlags |= PSH_WIZARDHASFINISH;
	m_psh.dwFlags &= ~PSH_HASHELP;
	//	m_psh.dwFlags &= ~(PSH_NOCONTEXTHELP);
	//	m_psh.dwFlags &= ~(PSH_WIZARD | PSH_WIZARD_LITE | PSH_HASHELP | PSH_WIZARDCONTEXTHELP);

	//	m_psh.dwFlags |= (PSH_HASHELP | PSH_WIZARDCONTEXTHELP);
	//	m_psh.dwFlags |= PSH_WIZARD97;
	m_pageBase.info = info;
	m_pageBase.SetHeaderTitle(info->strCodeWizName);
	m_pageBase.SetHeaderSubTitle(info->strCodeWizInfo);

	if (info->ar_ext.size() > 0)
	{
		m_pageBase.SetTitle("Code Wizard 8.0 - Step 1 of 2");
		m_pageBase.m_dwButton = PSWIZB_NEXT;
	}
	else
	{
		m_pageBase.SetTitle("Code Wizard 8.0 - Step 1 of 1");
		m_pageBase.m_dwButton = PSWIZB_BACK | PSWIZB_FINISH;
	}
	AddPage(m_pageBase);

	if (info->ar_ext.size() > 0 )
	{
		m_pageExt.info = info;
		m_pageExt.SetHeaderTitle(info->strCodeWizName);
		m_pageExt.SetHeaderSubTitle("Code Wizard Extern");
		AddPage(m_pageExt);
	}
}


CWizardSheet::~CWizardSheet()
{

}
