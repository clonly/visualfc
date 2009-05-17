#ifndef _PAGE_WINX_NOFITY_H_
#define _PAGE_WINX_NOFITY_H_

class page_winx_notify : public ui_page_dialog_t<page_winx_notify,IDD_PAGE_WINX_NOTIFY>,
						 public page_base_t<page_winx_notify>
{
public:
	const char * page_name()
	{
		return "Winx Notify";
	}
//	codeparser * pcode;
	Token	   * m_tkcls;
	CListBox	 m_ctrlList;
	CListBox     m_menuList;
	CListBox	 m_notifyList;
	CDevListBoxImpl	 m_tokenList;
	win32_notify	* m_wn;
public:
	BEGIN_DLGRESIZE_MAP(page_winx_notify)
		DLGRESIZE_CONTROL(IDC_CONTROL_LIST, 0)
		DLGRESIZE_CONTROL(IDC_MENU_LIST,0)
		DLGRESIZE_CONTROL(IDC_NOTIFY_LIST,DLSZ_SIZE_X)
		DLGRESIZE_CONTROL(IDC_NOTIFY_TOKEN_LIST, DLSZ_SIZE_X|DLSZ_SIZE_Y)
		DLGRESIZE_CONTROL(IDC_ADDNOTIFY_BTN,DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(IDC_DELNOTIFY_BTN, DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(IDC_EDITNOTIFY_BTN, DLSZ_MOVE_X)
	END_DLGRESIZE_MAP()

	void OnInit()
	{
		m_ctrlList = GetDlgItem(IDC_CONTROL_LIST);
		m_menuList = GetDlgItem(IDC_MENU_LIST);
		m_notifyList = GetDlgItem(IDC_NOTIFY_LIST);
		m_tokenList.SubclassWindow(GetDlgItem(IDC_NOTIFY_TOKEN_LIST));
	}

	int AddWinxNotifyToken(Token * tk)
	{
		int index = m_tokenList.AddString(tk->m_Name+_T(";")+tk->m_Args);
		m_tokenList.SetItemData(index,(DWORD)tk);
		return index;
	}
	void AddResControl(const ResControl * ctrl)
	{
		int index = m_ctrlList.AddString(ctrl->m_ID);
		m_ctrlList.SetItemData(index,(DWORD)ctrl);
	}
	void AddResMenuItem(const ResMenuItem * menu)
	{
		int index = m_menuList.AddString(menu->m_ID);
		m_menuList.SetItemData(index,(DWORD)menu);
	}
	void AddControlNotify(win32_notify_code * wnc)
	{
		int index = m_notifyList.AddString(wnc->code);
		m_notifyList.SetItemData(index,(DWORD)wnc);
	}

	void OnClassChange(Token * tkcls)
	{
		m_tkcls = tkcls;
		m_tokenList.ResetContent();
		m_notifyList.ResetContent();
		if (tkcls)	{
			pcode->EnumWinxMessageToken(tkcls,QLib::Event<void,Token*>(this,&page_winx_notify::AddWinxNotifyToken));
		}
	}

	void OnResDialogChange(CResDialog * dlg)
	{
		m_ctrlList.ResetContent();
		if (dlg) {
			pcode->EnumResDialogControl(dlg,QLib::Event<void,const ResControl*>(this,&page_winx_notify::AddResControl));
		}
	}
	
	void OnResMenuChange(CResMenu * menu)
	{
		m_menuList.ResetContent();
		if (menu) {
			pcode->EnumResMenuItem(menu,QLib::Event<void,const ResMenuItem*>(this,&page_winx_notify::AddResMenuItem));
		}
	}
public:
	BEGIN_MSG_MAP(page_winx_notify)
		COMMAND_ID_HANDLER(IDC_EDITNOTIFY_BTN, OnEditNotifyBtn)
		COMMAND_ID_HANDLER(IDC_ADDNOTIFY_BTN, OnAddNotifyBtn)
		COMMAND_ID_HANDLER(IDC_DELNOTIFY_BTN, OnDelNotifyBtn)
		COMMAND_HANDLER(IDC_CONTROL_LIST, LBN_SELCHANGE, OnSelchangeControlList)
		COMMAND_HANDLER(IDC_MENU_LIST, LBN_SELCHANGE, OnSelchangeMenuList)
		COMMAND_HANDLER(IDC_NOTIFY_LIST, LBN_SELCHANGE, OnSelchangeNotifyList)
		COMMAND_HANDLER(IDC_NOTIFY_TOKEN_LIST, LBN_SELCHANGE, OnSelchangeNotifyTokenList)
		CHAIN_MSG_MAP(ui_page_dialog_base)
	END_MSG_MAP()	

	QLib::Event<void,Token*> EventGoToLine;

	LRESULT OnEditNotifyBtn(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		int index = m_tokenList.GetCurSel();
		if (index == -1)
			return 0;
		Token * tk = (Token*)m_tokenList.GetItemData(index);
		EventGoToLine(tk);
		return 0;
	}

	CString GetIDFunctionName(LPCTSTR id)
	{
		CString name = id;
		if (name.Left(4) == _T("IDC_"))
			name = name.Right(name.GetLength()-4);
		else if (name.Left(3) == _T("ID_"))
			name = name.Right(name.GetLength()-3);
		else if (name.Left(2) == _T("ID"))
			name = name.Right(name.GetLength()-2);
		CString func;
		for (int i = 0; i < name.GetLength(); i++)
		{
			CString ch = name.GetAt(i);
			if (i == 0)
			{
				ch.MakeUpper();
				func += ch;
			}
			else if (name.GetAt(i-1) == _T('_'))
			{
				ch.MakeUpper();
				func += ch;
			}
			else if (ch != _T("_"))
			{
				ch.MakeLower();
				func += ch;
			}
		}
		return func;
	}

	bool OnAddNotify(win32_notify_code * wnc, LPCTSTR id, bool bMenu)
	{
		dlg_add_notify dlg;
		dlg.m_notify = _T("Message: ")+wnc->code;
		dlg.m_objectid = _T("Object ID: ")+(CString)id;
		dlg.m_function = wnc->func+GetIDFunctionName(id);
		if (dlg.DoModal() == IDOK)
		{
			Token * tk = pcode->WinxAddNotifyToken(wnc,m_tkcls,id,dlg.m_function,bMenu);
			int item = AddWinxNotifyToken(tk);
			m_tokenList.SetCurSel(item);
		}
		//MessageBox(wnc->func,id);
		return true;
	}

	LRESULT OnAddNotifyBtn(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		int index = m_notifyList.GetCurSel();
		if (index == -1) {
			return 0;
		}
		win32_notify_code * wnc = (win32_notify_code*)m_notifyList.GetItemData(index);
		int item = m_ctrlList.GetCurSel();
		if (item != -1)
		{
			ResControl * ctrl = (ResControl*)m_ctrlList.GetItemData(item);
			OnAddNotify(wnc,ctrl->m_ID,false);
		}
		item = m_menuList.GetCurSel();
		if (item != -1)
		{
			ResMenuItem * menu = (ResMenuItem*)m_menuList.GetItemData(item);
			OnAddNotify(wnc,menu->m_ID,true);
		}
		return 0;
	}

	bool AskRemoveToken(Token * tk)
	{
		CString text;
		text = _T("Deleting this handler requires manul removal of the implementation of\r\n");
		if (tk->m_pParent)
		{
			text += tk->m_pParent->m_Name;
			text += _T("::");
		}
		text += pcode->WinxGetNotifyTokenFuncitonName(tk);
		text += _T(". Continue?");
		UINT id = ::MessageBox(m_hWnd,text,_T("Delete Winx Notify"),MB_YESNOCANCEL | MB_ICONQUESTION);
		if (id == IDYES)
			return true;
		return false;
	}
	
	LRESULT OnDelNotifyBtn(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		int index = m_tokenList.GetCurSel();
		if (index == -1)
			return 0;
		Token * tk = (Token*)m_tokenList.GetItemData(index);
		bool bRet = pcode->WinxRemoveNotifyToken(tk,QLib::Event<bool,Token*>(this,&page_winx_notify::AskRemoveToken));
		if (bRet)
		{
			m_tokenList.DeleteString(index);
		}
		return 0;
	}

	LRESULT OnSelchangeControlList(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		int index = m_ctrlList.GetCurSel();
		if (index <= -1) { 
			return 0;
		}
		ResControl * ctrl = (ResControl*)m_ctrlList.GetItemData(index);
		m_wn = pcode->GetResControlNotify(ctrl);
		m_notifyList.ResetContent();
		pcode->EnumControlNofity(m_wn,QLib::Event<void,win32_notify_code*>(this,&page_winx_notify::AddControlNotify));
		m_menuList.SetCurSel(-1);
		if (m_wn != NULL)
			SetDlgItemText(IDC_TYPE_STATIC, _T("Message: ")+m_wn->name);
		else
			SetDlgItemText(IDC_TYPE_STATIC, _T("Message: ")+ctrl->m_Type);
		return 0;
	}

	LRESULT OnSelchangeMenuList(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		int index = m_menuList.GetCurSel();
		if (index <= -1) {
			return 0;
		}
		m_wn = pcode->GetResMenuNotify();
		m_notifyList.ResetContent();
		pcode->EnumControlNofity(m_wn,QLib::Event<void,win32_notify_code*>(this,&page_winx_notify::AddControlNotify));
		m_ctrlList.SetCurSel(-1);
		SetDlgItemText(IDC_TYPE_STATIC, _T("Message: ")+m_wn->name);
	}

	LRESULT OnSelchangeNotifyList(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		int index = m_notifyList.GetCurSel();
		if (index <= -1) {
			return 0;
		}
		return 0;
	}

	LRESULT OnSelchangeNotifyTokenList(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		return 0;
	}

};


#endif