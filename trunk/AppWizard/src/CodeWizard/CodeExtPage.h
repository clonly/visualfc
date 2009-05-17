// CodeExtPage.h: interface for the CCodeExtPage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CODEEXTPAGE_H__C91EDD2D_FA1C_4C86_BC24_B6135025D54D__INCLUDED_)
#define AFX_CODEEXTPAGE_H__C91EDD2D_FA1C_4C86_BC24_B6135025D54D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include "WizardInfo.h"

class CCodeExtPage : public CWizardPageImpl<CCodeExtPage, CWizardInfo>
{
public:
	CCheckListViewCtrl	m_extList;
	enum {IDD = IDD_CODEEXT_PAGE};

	BEGIN_DDX_MAP(CCodeExtPage)
		DDX_CONTROL(IDC_CODEEXT_LIST, m_extList)
		if (bSaveAndValidate == DDX_SAVE)
		{
			for (int i = 0; i < m_extList.GetItemCount(); i++)
			{
				info->ar_ext[i].bsel = m_extList.GetCheckState(i) == TRUE;
			}
		}
	END_DDX_MAP();
	
	void OnInit();
	typedef CWizardPageImpl<CCodeExtPage, CWizardInfo> baseClass;

	CCodeExtPage();
	virtual ~CCodeExtPage();
};

#endif // !defined(AFX_CODEEXTPAGE_H__C91EDD2D_FA1C_4C86_BC24_B6135025D54D__INCLUDED_)
