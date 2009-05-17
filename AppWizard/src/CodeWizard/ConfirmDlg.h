// aboutdlg.h : interface of the CAboutDlg class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(VFC_CONFIRMDLG_H__DC8F7426_3AB6_4d85_AAC1_F11EFD5C8EB5__INCLUDED_)
#define VFC_CONFIRMDLG_H__DC8F7426_3AB6_4d85_AAC1_F11EFD5C8EB5__INCLUDED_
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CConfirmDlg : public CDialogImpl<CConfirmDlg>, public CWinDataExchange<CConfirmDlg>
{
public:
	CString	m_projectPath;
	CString	m_info;

	enum { IDD = IDD_CONFIRM_DLG };

	BEGIN_MSG_MAP(CConfirmDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
	END_MSG_MAP()

	BEGIN_DDX_MAP(CConfirmDlg)
		DDX_TEXT(IDC_PROJECT_PATH, m_projectPath)
		DDX_TEXT(IDC_INFO_EDIT, m_info)
	END_DDX_MAP();
// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// [!output INSERT_LOCATION_COMMENT]

#endif // !defined(VFC_CONFIRMDLG_H__DC8F7426_3AB6_4d85_AAC1_F11EFD5C8EB5__INCLUDED_)
