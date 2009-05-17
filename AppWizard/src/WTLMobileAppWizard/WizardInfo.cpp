// WizardInfo.cpp: implementation of the CWizardInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WizardInfo.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWizardInfo::CWizardInfo()
{
	m_bEVCCompa = false;
	m_nOrientType = 1;
	m_nStringType = 0;
	m_bUseString = true;
	m_bOrientAware = false;
	m_bFullScreen = false;
	m_bCreateViewClass = true;
	m_nMenuType = 0;
	m_bEnableScroll = false;
	m_bEnableZoom = false;

	bEnableActiveX = false;
	bCppFiles = false;
	bHostActiveX = false;
	bStatusBar = false;
	bVS2005 = false;
	bVCExpress = false;
	nAppType = 0;
	nViewType = 0;
	bVS60 = true;
	bVS2002 = false;
	bVS2003 = false;
	bVS2008 = false;
	bVS2005 = false;
	bUseView = true;
	nSDKType	= 2;

	templatePath = GetModulePath(_Module.m_hInst)+_T("\\templates");
	cfgPath = GetModulePath(NULL)+_T("\\setup.ini");
	cfgApp = _T("WTLMobileAppWizard");
//	ar_view.push_back(view_type("Generic Window","WTL_VIEWTYPE_GENERIC"));
//	ar_view.push_back(view_type("Form (Dialog Based)","WTL_VIEWTYPE_FORM","CDialogImpl"));
//	ar_view.push_back(view_type("ListBox","WTL_VIEWTYPE_LISTBOX","CListBox","WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | LBS_NOINTEGRALHEIGHT | LBS_NOTIFY | LBS_WANTKEYBOARDINPUT"));
//	ar_view.push_back(view_type("Edit","WTL_VIEWTYPE_EDIT","CEdit","WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_HSCROLL | WS_VSCROLL | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE | ES_NOHIDESEL"));

	ar_view.push_back("Generic Window");
	ar_view.push_back("Form (Dialog Based)");
	ar_view.push_back("Property Sheet");
	ar_view.push_back("ListBox");
	ar_view.push_back("Edit");
	ar_view.push_back("List View");
	ar_view.push_back("Tree View");
	ar_view.push_back("HTML Browse Control");
	ar_view.push_back("InkX Control");
	ar_view.push_back("RichInk control");

	ar_app.push_back("WTL_APPTYPE_SDI");
	ar_app.push_back("WTL_APPTYPE_DLG");

	ar_lang.push_back(_T("1033"));
	nAppLang = 0;
	load_lang();
}

CWizardInfo::~CWizardInfo()
{

}
