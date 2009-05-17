// CodeBasePage.h: interface for the CCodeBasePage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CODEBASEPAGE_H__47B4F628_D6D1_4D98_92CE_DF9FBA1DACE0__INCLUDED_)
#define AFX_CODEBASEPAGE_H__47B4F628_D6D1_4D98_92CE_DF9FBA1DACE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include "WizardInfo.h"

class CCodeBasePage : public CWizardPageImpl<CCodeBasePage, CWizardInfo>
{
public:
	CEdit	m_edFileName;
	CEdit	m_edClassName;
	void OnInit();
	typedef CWizardPageImpl<CCodeBasePage, CWizardInfo> baseClass;
	BEGIN_MSG_MAP(CCodeBasePage)
		COMMAND_ID_HANDLER(IDC_PROJECTPATH_BTN, OnProjectpathBtn)
		COMMAND_HANDLER(IDC_CLASSNAME_EDIT, EN_CHANGE, OnEnChangeClassnameEdit)
		CHAIN_MSG_MAP(baseClass)
	END_MSG_MAP()
	
	CComboBox	m_cmbDialogID;
	CComboBox	m_cmbBaseClass;
	BOOL	m_bDDX;
	enum { IDD = IDD_CODEBASE_PAGE };
	CCodeBasePage();
	virtual ~CCodeBasePage();

	BEGIN_DDX_MAP(CCodeBasePage)
		DDX_CONTROL_HANDLE(IDC_FILENAME_EDIT, m_edFileName)
		DDX_CONTROL_HANDLE(IDC_CLASSNAME_EDIT, m_edClassName)
		DDX_CONTROL_HANDLE(IDC_BASECLASS_COMBO, m_cmbBaseClass)
		DDX_CONTROL_HANDLE(IDC_DIALOGID_COMBO, m_cmbDialogID)
		DDX_CHECK(IDC_USE_RESOURCE, info->bUseResource)
		DDX_TEXT(IDC_CLASSNAME_EDIT, info->strClassName)
		DDX_TEXT(IDC_FILENAME_EDIT, info->strFileName)
		DDX_TEXT(IDC_PROJECTPATH_EDIT, info->strProjectPath)
		DDX_CHECK(IDC_USE_STDAFX, info->bUseStdAfx)
		DDX_CHECK(IDC_USE_CPPFILES,info->bUseCppFiles)
		DDX_CHECK(IDC_USE_CONSTRUCTION, info->bUseConstruction)
		DDX_CHECK(IDC_USE_DESTRUCTION, info->bUseDestruction)
		DDX_CHECK(IDC_USE_GUIDSYSBOL, info->bUseGuidSymbol)
		DDX_CBTEXT(IDC_DIALOGID_COMBO, info->strDialogID)
		DDX_CBTEXT(IDC_BASECLASS_COMBO, info->strBaseClass)
	END_DDX_MAP()

	BEGIN_UPDATE_UI_MAP(CCodeBasePage)
		UPDATE_ELEMENT(IDC_BASECLASS_COMBO, UPDUI_CHILDWINDOW)
		UPDATE_ELEMENT(IDC_USE_CONSTRUCTION, UPDUI_CHILDWINDOW)
		UPDATE_ELEMENT(IDC_USE_DESTRUCTION, UPDUI_CHILDWINDOW)
		UPDATE_ELEMENT(IDC_USE_RESOURCE, UPDUI_CHILDWINDOW)
		UPDATE_ELEMENT(IDC_USE_CPPFILES, UPDUI_CHILDWINDOW)
		UPDATE_ELEMENT(IDC_USE_STDAFX, UPDUI_CHILDWINDOW)
		UPDATE_ELEMENT(IDC_DIALOGID_COMBO, UPDUI_CHILDWINDOW)
	END_UPDATE_UI_MAP();
	
	void DoUpdateUI(UINT id)
	{
		DoDataExchange(true,id);
		
		if (info->cfg.bEnableCPP)
		{
			UISetCheck(IDC_USE_RESOURCE, info->bUseCppFiles);
			UISetCheck(IDC_USE_STDAFX,info->bUseCppFiles);
			UIEnable(IDC_USE_RESOURCE,info->bUseCppFiles);
			UIEnable(IDC_USE_STDAFX,info->bUseCppFiles);
		}
	}
	LRESULT OnEnChangeClassnameEdit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnProjectpathBtn(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
};

#endif // !defined(AFX_CODEBASEPAGE_H__47B4F628_D6D1_4D98_92CE_DF9FBA1DACE0__INCLUDED_)
