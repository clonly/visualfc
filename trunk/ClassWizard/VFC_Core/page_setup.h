// page_setup.h : interface of the page_setup class
//
/////////////////////////////////////////////////////////////////////////////
#if !defined(VFC_PAGE_SETUP_H__0D9043F8_7E5B_411b_BCAA_A744B08CF5C2__INCLUDED_)
#define VFC_PAGE_SETUP_H__0D9043F8_7E5B_411b_BCAA_A744B08CF5C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class page_setup : public ui_page_dialog_t<page_setup,IDD_PAGE_SETUP>,
				   public page_base_t<page_setup>, 
				   public CWinDataExchange<page_setup>
{
public:
	vfc_config	cfg;

	BEGIN_MSG_MAP(page_setup)
		CHAIN_MSG_MAP(ui_page_dialog_base)
	END_MSG_MAP()
	
	BEGIN_DDX_MAP(page_setup)
		DDX_CHECK(IDC_ENABLE_WTL, cfg.bWTL)
		DDX_CHECK(IDC_ENABLE_WINX, cfg.bWinx)
		DDX_CHECK(IDC_ENABLE_APPWIZARD, cfg.bAppWizard)
		DDX_CHECK(IDC_ENABLE_CODEWIZARD, cfg.bCodeWizard)
	END_DDX_MAP();
	
	void OnInit()
	{
		cfg.load();
		DoDataExchange(false);
	}

	void OnProjectChange(project_dsp *)
	{
		cfg.load();
		DoDataExchange(false);
	}

	void OnCloseProject(WORD wID)
	{
		if (wID == IDOK)
		{
			DoDataExchange(true);
			cfg.save();
		}
	}
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// VisualFC AppWizard will insert additional declarations immediately before the previous line.
#endif // !defined(VFC_PAGE_SETUP_H__0D9043F8_7E5B_411b_BCAA_A744B08CF5C2__INCLUDED_)
