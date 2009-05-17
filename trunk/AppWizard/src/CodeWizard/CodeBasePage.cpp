// CodeBasePage.cpp: implementation of the CCodeBasePage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "CodeBasePage.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCodeBasePage::CCodeBasePage()
{
	SetTitle("Code Wizard 8.0 - Step 1 of 2");
	SetHeaderTitle("Application Type");
	SetHeaderSubTitle("Selection Application Type");
	m_dwButton = PSWIZB_NEXT;
}

CCodeBasePage::~CCodeBasePage()
{

}

LRESULT CCodeBasePage::OnEnChangeClassnameEdit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	TCHAR sz[256] = {0};
	m_edClassName.GetWindowText(sz,255);
	if (sz[0] != _T('C'))
	{
		m_edFileName.SetWindowText(sz);
	}
	else
	{
		m_edFileName.SetWindowText(&sz[1]);
	}
	return 0;
}

LRESULT CCodeBasePage::OnProjectpathBtn(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CFolderDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		SetDlgItemText(IDC_PROJECTPATH_EDIT,dlg.m_szFolderPath);
	}

	return 0;
}

void CCodeBasePage::OnInit()
{
	int i = 0;
	for (i = 0; i < info->ar_id.size(); i++)
	{
		m_cmbDialogID.AddString(info->ar_id[i]);
	}
	for (i = 0; i < info->ar_baseclass.size(); i++)
	{
		m_cmbBaseClass.AddString(info->ar_baseclass[i].baseclass);
	}

	UIEnable(IDC_DIALOGID_COMBO,info->cfg.bEnableIDD);
	UIEnable(IDC_BASECLASS_COMBO, info->ar_baseclass.size() > 0);
	UIEnable(IDC_USE_CPPFILES,info->cfg.bEnableCPP);
	UIEnable(IDC_USE_RESOURCE,info->cfg.bEnableCPP);
	UIEnable(IDC_USE_STDAFX,info->cfg.bEnableCPP);
}
