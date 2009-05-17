// AppTypePage.h: interface for the CAppTypePage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_APPTYPEPAGE_H__9BFAAD00_243E_4A26_8A69_0E798FFAF609__INCLUDED_)
#define AFX_APPTYPEPAGE_H__9BFAAD00_243E_4A26_8A69_0E798FFAF609__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include "wizardinfo.h"

class CAppTypePage : public CWizardPageImpl<CAppTypePage, CWizardInfo>
{
public:
	BEGIN_DDX_MAP(CAppTypePage)
		DDX_CHECK(IDC_USE_FULLSCREEN, info->m_bFullScreen)
		DDX_CHECK(IDC_USE_ORIENTAWARE, info->m_bOrientAware)
		DDX_CHECK(IDC_USE_CSTRING, info->m_bUseString)
		DDX_RADIO(IDC_USE_ATLSTR, info->m_nStringType)
		DDX_RADIO(IDC_USE_RESIZING, info->m_nOrientType)
		DDX_CHECK(IDC_USE_EVCCOMPA, info->m_bEVCCompa)
		CComboBox cmb = GetDlgItem(IDC_LANG_COMBO);
		if (cmb.GetCount() == 0)
		{
			for (int i = 0; i < info->ar_lang.size(); i++)
			{
				int lang = ::_ttol(info->ar_lang[i]);
				TCHAR buf[100] = {0};
				::GetLocaleInfo(lang,4,buf,100);
				if (lstrlen(buf) != 0)
				{
					cmb.AddString(buf);
				}
			}
			cmb.SetCurSel(info->nAppLang);
		}
		DDX_CHECK(IDC_ACTIVEX, info->bEnableActiveX)
		//DDX_CHECK(IDC_COMSERVER, info->bComServer)
		DDX_CHECK(IDC_CPPFILES, info->bCppFiles)
		//DDX_CHECK(IDC_MODALDIALOG_CHECK, info->bModalDialog)
		DDX_RADIO(IDC_APPTYPE_SDI, info->nAppType)
		//bSaveAndValidate;
		//nCtlID;
		if (bSaveAndValidate == DDX_SAVE)
		{
			if (cmb.GetCurSel() != -1)
			{
				info->nAppLang = cmb.GetCurSel();
			}

			info->bUseView = info->nAppType != 5;
			info->bStatusBar = info->nAppType != 5;
		}
	END_DDX_MAP();

	BEGIN_UPDATE_UI_MAP(CAppTypePage)
		UPDATE_ELEMENT(IDC_MODALDIALOG_CHECK, UPDUI_CHILDWINDOW)
	END_UPDATE_UI_MAP();
	
	void DoUpdateUI(UINT id)
	{
		DoDataExchange(true);
		UIEnable(IDC_MODALDIALOG_CHECK,info->nAppType == 5);
	}
	
	enum { IDD = IDD_APPTYPE_PAGE };

	CAppTypePage();
	virtual ~CAppTypePage();
};

#endif // !defined(AFX_APPTYPEPAGE_H__9BFAAD00_243E_4A26_8A69_0E798FFAF609__INCLUDED_)

