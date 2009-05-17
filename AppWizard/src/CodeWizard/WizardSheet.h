// WizardSheet.h: interface for the CWizardSheet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WIZARDSHEET_H__B5CE6101_D0C0_44BF_B03C_144B2DC5435A__INCLUDED_)
#define AFX_WIZARDSHEET_H__B5CE6101_D0C0_44BF_B03C_144B2DC5435A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WizardInfo.h"
#include "CodeBasePage.h"
#include "CodeExtPage.h"

class CWizardSheet : public CWizard97SheetImpl<CWizardSheet>
{
public:
	typedef CWizard97SheetImpl<CWizardSheet> baseClass;

	CWizardSheet(CWizardInfo * info, UINT uStartPage, HWND hWndParent);
	virtual ~CWizardSheet();

	BEGIN_MSG_MAP(CWizardSheet)
		CHAIN_MSG_MAP(baseClass)
	END_MSG_MAP()

	CCodeBasePage	m_pageBase;
	CCodeExtPage	m_pageExt;
};

#endif // !defined(AFX_WIZARDSHEET_H__B5CE6101_D0C0_44BF_B03C_144B2DC5435A__INCLUDED_)
