// maindlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINDLG_H__EC6F42D4_F9AB_4A8E_84E7_D97E2A1E8FAF__INCLUDED_)
#define AFX_MAINDLG_H__EC6F42D4_F9AB_4A8E_84E7_D97E2A1E8FAF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <atlddx.h>
#include <atlmisc.h>

#include "../public/wtlfileex.h"
#include "../FCWizard/wtl_event.h"

template <typename ArrayT>
inline void StringToArray(LPCTSTR text, ArrayT & array, LPCTSTR separator = _T(""), bool trimSpaces = true)
{
    CString search = text;
    int seplen = CString(separator).GetLength();
    while (true)
    {
        int idx = search.Find(separator);
        if (idx == -1)
        {
            if (trimSpaces)
            {
                search.TrimLeft();
                search.TrimRight();
            }
            if (!search.IsEmpty())
                array.Add(search);
            break;
        }
        CString part = search.Left(idx);
        search.Delete(0, idx + seplen);
        if (trimSpaces)
        {
            part.TrimLeft();
            part.TrimRight();
        }
        if (!part.IsEmpty())
            array.Add(part);
    }
}

class CMainDlg : public CDialogImpl<CMainDlg>, public CUpdateUI<CMainDlg>,
		public CMessageFilter, public CIdleHandler, public CWinDataExchange<CMainDlg>,
		public CDialogResize<CMainDlg>
{
public:
	BEGIN_DLGRESIZE_MAP(CMainDlg)
		DLGRESIZE_CONTROL(IDC_OPENMSG_BTN, DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(IDC_CFG_EDIT, DLSZ_SIZE_X | DLSZ_SIZE_Y)
		DLGRESIZE_CONTROL(IDOK, DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(IDCANCEL, DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(ID_APP_ABOUT, DLSZ_MOVE_X | DLSZ_MOVE_Y)
	END_DLGRESIZE_MAP()
	
	CRichEditCtrl	m_cfgEdit;
	enum { IDD = IDD_MAINDLG };

	BEGIN_DDX_MAP(CMainDlg)
		DDX_CONTROL_HANDLE(IDC_CFG_EDIT, m_cfgEdit)
	END_DDX_MAP();
	
	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		return IsDialogMessage(pMsg);
	}

	virtual BOOL OnIdle()
	{
		return FALSE;
	}

	BEGIN_UPDATE_UI_MAP(CMainDlg)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CMainDlg)
		COMMAND_ID_HANDLER(IDC_OPENMSG_BTN, OnOpenmsgBtn)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		CHAIN_MSG_MAP(CDialogResize<CMainDlg>)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		// center the dialog on the screen
		CenterWindow();

		// set icons
		HICON hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
			IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
		SetIcon(hIcon, TRUE);
		HICON hIconSmall = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
			IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
		SetIcon(hIconSmall, FALSE);

		// register object for message filtering and idle updates
		CMessageLoop* pLoop = _Module.GetMessageLoop();
		ATLASSERT(pLoop != NULL);
		pLoop->AddMessageFilter(this);
		pLoop->AddIdleHandler(this);

		UIAddChildWindowContainer(m_hWnd);

		DoDataExchange(FALSE);

		DlgResize_Init();

		return TRUE;
	}

	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CAboutDlg dlg;
		dlg.DoModal();
		return 0;
	}

	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		// TODO: Add validation code 
		CloseDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CloseDialog(wID);
		return 0;
	}

	void CloseDialog(int nVal)
	{
		DestroyWindow();
		::PostQuitMessage(nVal);
	}
	LRESULT OnOpenmsgBtn(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		CFileDialog dlg(TRUE);
		dlg.m_ofn.lpstrFilter = _T("atlcrack.h\0*.h\0");
		if (dlg.DoModal() == IDOK)
		{
			CSimpleArray<CString> ar;
			OpenMsg(dlg.m_ofn.lpstrFile,ar);
			m_cfgEdit.SetWindowText("");
		//	m_cfgEdit.SetRedraw(FALSE);
			for (int i = 0; i < ar.GetSize(); i++)
			{
				m_cfgEdit.AppendText(ar[i]+_T("\r\n"));
			}
		//	m_cfgEdit.SetRedraw(TRUE);
		}
		return 0;
	}

	BOOL OpenMsg(LPCTSTR lpszFileName, CSimpleArray<CString> & ar)
	{
/*	
// int OnCreate(LPCREATESTRUCT lpCreateStruct)
#define MSG_WM_CREATE(func) \
	if (uMsg == WM_CREATE) \
	{ \
		SetMsgHandled(TRUE); \
		lResult = (LRESULT)func((LPCREATESTRUCT)lParam); \
		if(IsMsgHandled()) \
			return TRUE; \
	}
*/		
		CTextFile file;
		if (!file.Open(lpszFileName,CFile::modeRead))
			return FALSE;
		CString line;
		CString func;
		CString name;
		CString msg;
		CString body;
		CString ret;
		CString param;
		CString conv; //lResult = (LRESULT)func((HWND)wParam, (PCOPYDATASTRUCT)lParam);
		while (file.ReadLine(line))
		{
			int pos = -1;
			int right = -1;
			if (line.Find(_T("#define")) != -1 &&  
				( pos = line.Find(_T("MSG_WM")) , pos != -1) &&
				( right = line.Find(_T("(")), right != -1) )
			{
				func.TrimLeft(_T("/"));
				func.TrimLeft();
				int l = func.Find(_T(' '));
				int r = func.Find(_T("("));
				name = func.Mid(l,r-l);
				ret = func.Left(l);
				param = func.Right(func.GetLength()-r);
				if (ret == _T("void"))
					body = _T("");
				else
					body = _T("return 0;");
				name.TrimLeft();
				name.TrimRight();
				msg = line.Mid(pos+4,right-pos-4);
				
				ar.Add(_T("<")+msg+_T(">"));
				ar.Add(_T("ext=")+line.Mid(pos,right-pos));
				ar.Add(_T("func=")+name);
				ar.Add(_T("ret=")+ret);
				ar.Add(_T("param=")+param);
				ar.Add(_T("body=")+body);

				while(file.ReadLine(line))
				{
					if (line.Left(2) == _T("//"))
						break;
					if ( (pos = line.Find(_T("func")), pos != -1) && 
						(right = line.Find(_T(";")), right != -1) )
					{
						conv = line.Mid(pos+4,right-pos-4);
						conv.TrimLeft();
						conv.TrimRight();
						//ar.Add(_T("conv=")+conv);
						ar.Add(_T("crack=")+make_crack(param,conv));
						break;
					}
				}
				ar.Add(_T("</")+msg+_T(">"));
				ar.Add((CString)_T(""));
			}
			if (line.Left(2) == _T("//"))
			{
				func = line;
			}
		}
		file.Close();
		return TRUE;
	}

	CString make_crack(const CString & _param, const CString & _conv)
	{
		CString param = _param.Mid(1,_param.GetLength()-2);
		CString conv = _conv.Mid(1,_conv.GetLength()-2);
		CSimpleArray<CString> ar1, ar2;
		::StringToArray(param,ar1,_T(","));
		::StringToArray(conv,ar2,_T(","));
		if (ar1.GetSize() == 0 )
		{
			return _T("");
		}
		CString text;
		//fix CPoint CSize ->lParam last param
		if (ar1.GetSize() != ar2.GetSize())
		{
			ar2[ar2.GetSize()-2] = ar2[ar2.GetSize()-2]+_T(",")+ar2[ar2.GetSize()-1];
			ar2.RemoveAt(ar2.GetSize()-1);
		}
		if (ar2.GetSize() != ar2.GetSize())
		{
			return _T("error");
		}
		for (int i = 0; i < ar1.GetSize(); i++)
		{
			text += ar1[i];
			text += _T(" = ");
			text += ar2[i];
			text += _T(";");
			text += _T("  ");
		}
		return text;
	}
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINDLG_H__EC6F42D4_F9AB_4A8E_84E7_D97E2A1E8FAF__INCLUDED_)
