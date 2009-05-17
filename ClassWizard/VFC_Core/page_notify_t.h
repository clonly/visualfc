#ifndef _PAGE_NOTIFY_T_H_
#define _PAGE_NOTIFY_T_H_

class dlg_add_notify : public ui_simple_dialog_t<dlg_add_notify,IDD_ADD_NOTIFY_DIALOG>
{
public:
	CString		m_notify;
	CString		m_function;
	CString		m_objectid;
public:
	void OnInit()
	{
		SetDlgItemText(IDC_NOTIFY_STATIC,m_notify);
		SetDlgItemText(IDC_OBJECTID_STATIC,m_objectid);
		SetDlgItemText(IDC_FUNCTIONNAME_EDIT,m_function);
		CEdit ed = GetDlgItem(IDC_FUNCTIONNAME_EDIT);
		ed.SetFocus();
		ed.SetSel(2,-1);
	}
	BOOL OnClose()
	{
		CEdit ed = GetDlgItem(IDC_FUNCTIONNAME_EDIT);
		TCHAR sz[256] = {0};
		ed.GetWindowText(sz,255);
		m_function = sz;
		if (m_function.IsEmpty())
			return FALSE;
		return TRUE;
	}
};


struct page_notify_peer
{
	virtual ~page_notify_peer() {}
	virtual void init_tag(tag_token & tag) = 0;
	virtual Token * add_notify_dlg(codeparser * pcode, Token * tkcls, win32_notify_code * wnc, LPCTSTR id, bool bMenu) = 0;
	virtual CString GetIDFunctionName(LPCTSTR id)
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
};

class page_notify_template : public ui_page_dialog_t<page_notify_template,IDD_PAGE_NOTIFY>,
						 public page_base_t<page_notify_template>
{
protected:
	page_notify_peer	* m_peer;
public:
	tag_token	m_tag;
	page_notify_template()
	{
		m_peer = NULL;
	}
	~page_notify_template()
	{
		if (m_peer)
		{
			delete m_peer;
			m_peer = NULL;
		}
	}
public:
	const char * page_name()
	{
		return "Page Notify Template";
	}
	Token	   * m_tkcls;
	CDevListBoxImpl	 m_ctrlList;
	CListBox     m_menuList;
	CListBox	 m_notifyList;
	CDevListBoxImpl	 m_tokenList;
	win32_notify	* m_wn;
public:
	BEGIN_DLGRESIZE_MAP(page_notify_template)
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
		m_ctrlList.SubclassWindow(GetDlgItem(IDC_CONTROL_LIST));
		m_ctrlList.m_nDivider = 150;
		m_menuList = GetDlgItem(IDC_MENU_LIST);
		m_notifyList = GetDlgItem(IDC_NOTIFY_LIST);
		m_tokenList.SubclassWindow(GetDlgItem(IDC_NOTIFY_TOKEN_LIST));
	}

	int AddTokenList(Token * tk)
	{
		int index = m_tokenList.AddString(tk->m_Name+_T(";")+tk->m_Args);
		m_tokenList.SetItemData(index,(DWORD)tk);
		return index;
	}

	void AddResControl(const ResControl * ctrl)
	{
		int index = m_ctrlList.AddString(ctrl->m_ID+_T(";")+ctrl->m_Type);
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
			//pcode->EnumWinxMessageToken(tkcls,QLib::Event<void,Token*>(this,&page_winx_notify::AddWinxNotifyToken));
			for (size_t i = 0; i < tkcls->m_Children.GetCount(); i++)
			{
				Token * tk = tkcls->m_Children[i]; 
				if (m_tag.find_body(tk->m_Name) == true)
				{
					AddTokenList(tk);
				}
			}	
		}
	}

	void OnResDialogChange(CResDialog * dlg)
	{
		m_ctrlList.ResetContent();
		if (dlg)
		{
			pcode->EnumResDialogControl(dlg,QLib::Event<void,const ResControl*>(this,&page_notify_template::AddResControl));
		}
	}
	
	void OnResMenuChange(CResMenu * menu)
	{
		m_menuList.ResetContent();
		if (menu)
		{
			pcode->EnumResMenuItem(menu,QLib::Event<void,const ResMenuItem*>(this,&page_notify_template::AddResMenuItem));
		}
	}
public:
	BEGIN_MSG_MAP(page_notify_template)
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

	bool OnAddNotify(win32_notify_code * wnc, LPCTSTR id, bool bMenu)
	{
		if (m_peer)
		{
			Token * tk = m_peer->add_notify_dlg(pcode,m_tkcls,wnc,id,bMenu);
			if (tk)
			{
				int index = AddTokenList(tk);
				m_tokenList.SetCurSel(index);
				return true;
			}
		}
		return false;
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
		UINT id = ::MessageBox(m_hWnd,text,_T("Delete Notify"),MB_YESNOCANCEL | MB_ICONQUESTION);
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
		bool bRet = pcode->WinxRemoveNotifyToken(tk,QLib::Event<bool,Token*>(this,&page_notify_template::AskRemoveToken));
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
		pcode->EnumControlNofity(m_wn,QLib::Event<void,win32_notify_code*>(this,&page_notify_template::AddControlNotify));
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
		pcode->EnumControlNofity(m_wn,QLib::Event<void,win32_notify_code*>(this,&page_notify_template::AddControlNotify));
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