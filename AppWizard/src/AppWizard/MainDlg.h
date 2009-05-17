// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../public/simple_plugin.h"
#include "../public/appwiz_plugin.h"
#include "../public/codewiz_plugin.h"
#include "../public/wtlfile.h"
#include "../public/wtlfileex.h"

#include <set>

class CMainDlg : public CDialogImpl<CMainDlg>, public CUpdateUI<CMainDlg>,
		public CMessageFilter, public CIdleHandler,
		public CWinDataExchange<CMainDlg>,
		public CDialogResize<CMainDlg>
{
public:
	fox::simple_plugin::manager<fox::appwiz_config>	 m_appwiz;
	fox::simple_plugin::manager<fox::codewiz_config> m_codewiz;
public:
	void ChangeTree();
	BOOL RunAppWizard(fox::appwiz_config * cfg);
	BOOL LoadCodeWiz();
	BOOL RunWizard();
	BOOL LoadAppWiz();
	BEGIN_DLGRESIZE_MAP(CMainDlg)
		DLGRESIZE_CONTROL(ID_APP_ABOUT, DLSZ_MOVE_X | DLSZ_MOVE_Y)
		DLGRESIZE_CONTROL(IDC_SPLIT_STATIC, DLSZ_SIZE_X | DLSZ_SIZE_Y)
		DLGRESIZE_CONTROL(IDC_PROJECT_TITLE_EDIT, DLSZ_SIZE_X | DLSZ_MOVE_Y)
		DLGRESIZE_CONTROL(IDC_GO_BTN, DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(IDCANCEL, DLSZ_MOVE_X)
		//DLGRESIZE_CONTROL(IDC_SPLIT_STATIC, DLSZ_SIZE_X)
	END_DLGRESIZE_MAP()
	
	CImageList		m_imageList;
	CEdit			m_projEdit;
	CListViewCtrl	m_projList;
	CTreeViewCtrl	m_projTree;
	CLayoutSplitter	m_wndSplit;

	enum { IDD = IDD_MAINDLG };

	BEGIN_DDX_MAP(CMainDlg)
		DDX_CONTROL_HANDLE(IDC_PROJECT_TITLE_EDIT, m_projEdit)
		DDX_CONTROL_HANDLE(IDC_PROJECT_TREE, m_projTree)
		DDX_CONTROL_HANDLE(IDC_PROJECT_LIST, m_projList)
		DDX_CONTROL(IDC_SPLIT_STATIC, m_wndSplit)
	END_DDX_MAP();
	
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle();

	BEGIN_UPDATE_UI_MAP(CMainDlg)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CMainDlg)
		NOTIFY_HANDLER(IDC_PROJECT_TREE, TVN_SELCHANGED, OnTvnSelchangedProjectTree)
		NOTIFY_HANDLER(IDC_PROJECT_TREE, NM_CLICK, OnNmClickProjectTree)
		NOTIFY_HANDLER(IDC_PROJECT_LIST, NM_DBLCLK, OnNmDblclkProjectList)
		NOTIFY_HANDLER(IDC_PROJECT_LIST, NM_CLICK, OnItemchangedProjectList)
		NOTIFY_HANDLER(IDC_PROJECT_LIST, LVN_ITEMCHANGED, OnItemchangedProjectList)
		COMMAND_ID_HANDLER(IDC_GO_BTN, OnGoBtn)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		CHAIN_MSG_MAP(CDialogResize<CMainDlg>)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	void CloseDialog(int nVal);
	LRESULT OnGoBtn(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnItemchangedProjectList(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
	LRESULT OnNmDblclkProjectList(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
	LRESULT OnTvnSelchangedProjectTree(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
	LRESULT OnNmClickProjectTree(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
};
