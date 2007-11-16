#ifndef _PAGE_FONT_T_H_
#define _PAGE_FONT_T_H_

struct page_font_peer
{
	virtual ~page_font_peer() {}
	virtual init_tag(tag_token & tag) = 0;
	virtual Token * add_font_dlg(codeparser * pcode, Token * tkcls, ResControl * ctrl, bool bdlg) = 0;

	virtual LPCTSTR get_token_id(Token * tk)
	{
		CString name;
		CString args;
		HelperGetTokenTag(tk,name,args);
		CString temp;
		if (name.Find(_T("DIALOG")) != -1)
		{
			return _T("*DIALOG*");
		}
		else
		{
			CAtlArray<CString> array;
			StringToArray(args,array,_T(","),true);
			if (array.GetSize() >= 2)
			{
				return array[0];
			}
		}
		return NULL;
	}

	virtual bool get_token_font(Token * tk, CString & id, CString & font)
	{
		CString name;
		CString args;
		HelperGetTokenTag(tk,name,args);
		CString temp;
		if (name.Find(_T("DIALOG")) != -1)
		{
			id = _T("*DIALOG*");
			font = args;
			return true;
		}
		else
		{
			CAtlArray<CString> array;
			StringToArray(args,array,_T(","),true);
			if (array.GetSize() >= 2)
			{
				id = array[0];
				ArrayToStringEx(array,font,_T(","),1,-1);
				return true;
			}
		}
		return false;
	}
};

class page_font_template : public ui_page_dialog_t<page_font_template, IDD_PAGE_FONT>,
						   public page_base_t<page_font_template>
{
public:
	tag_token	m_tag;
	page_font_peer *	m_peer;
public:
	const char * page_name()
	{
		return "Page Font Template";
	}
	page_font_template()
	{
		m_peer = NULL;
	}
	virtual ~page_font_template()
	{
		if (m_peer)
		{
			m_peer = NULL;
			delete m_peer;
		}
	}
	Token	   * m_tkcls;
	CDataListT<ResControl>	 m_ctrlList;
	CDataListT<Token>		 m_tkList;
public:
	BEGIN_DLGRESIZE_MAP(page_font_template)
		DLGRESIZE_CONTROL(IDC_CONTROL_LIST, DLSZ_SIZE_X)
		DLGRESIZE_CONTROL(IDC_TOKEN_LIST, DLSZ_SIZE_Y | DLSZ_SIZE_X)
		DLGRESIZE_CONTROL(IDC_ADDFONT_BTN, DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(IDC_DELFONT_BTN, DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(IDC_ADDDLGFONT_BTN, DLSZ_MOVE_X)
	END_DLGRESIZE_MAP()

	void OnInit()
	{
		m_ctrlList.SubclassWindow(GetDlgItem(IDC_CONTROL_LIST));
		m_tkList.SubclassWindow(GetDlgItem(IDC_TOKEN_LIST));
	}
	
	int AddTokenList(Token * tk)
	{
		int index = -1;
		if (m_peer)
		{
			CString id, font;
			if (m_peer->get_token_font(tk,id,font))
			{
				index = m_tkList.AddStringData(id+_T(";")+font,tk);
			}
		}

		return index;
	}

	void AddResControl(const ResControl * ctl)
	{
		int index = m_ctrlList.AddString(ctl->m_ID);
		m_ctrlList.SetItemData(index,(DWORD)ctl);
	}
	void OnClassChange(Token * tkcls)
	{
		m_tkcls = tkcls;
		m_tkList.ResetContent();
		if (tkcls)
		{
			for (size_t i = 0; i < tkcls->m_Children.GetCount(); i++)
			{
				Token * tk = tkcls->m_Children[i]; 
				if (m_tag.find_body(tk->m_Name) == true)
				{
					AddTokenList(tk);
				}
			}	
		}
		UpdateUI();
	}
	void OnResDialogChange(CResDialog * dlg)
	{
		m_ctrlList.ResetContent();

		if (dlg == NULL)
			return;

		for (size_t i = 0; i < dlg->GetCount(); i++)
		{	
			ResControl * ctrl = (ResControl*)&dlg->GetAt(i);
			if (ctrl->m_ID != _T("IDC_STATIC"))
			{
				m_ctrlList.AddStringData(ctrl->m_ID+_T(";")+ctrl->m_Type,ctrl);
			}
		}
	}
public:
	BEGIN_MSG_MAP(page_font_template)
		COMMAND_ID_HANDLER(IDC_ADDDLGFONT_BTN, OnAddDlgFontBtn)
		COMMAND_ID_HANDLER(IDC_ADDFONT_BTN, OnAddFontBtn)
		COMMAND_ID_HANDLER(IDC_DELFONT_BTN, OnDelFontBtn)
		COMMAND_HANDLER(IDC_CONTROL_LIST, LBN_SELCHANGE, OnSelchangeControlList)
		COMMAND_HANDLER(IDC_TOKEN_LIST, LBN_SELCHANGE, OnSelchangeTokenList)
		CHAIN_MSG_MAP(ui_page_dialog_base)
	END_MSG_MAP()	

	LRESULT OnAddFontBtn(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		ResControl * ctrl = m_ctrlList.GetCurSelData();
		if (ctrl == NULL)
			return 0;
		if (m_peer != NULL)
		{
			Token * tk = m_peer->add_font_dlg(pcode,m_tkcls,ctrl,false);
			if (tk != NULL)
			{
				int index = AddTokenList(tk);
				m_tkList.SetCurSel(index);
				UpdateUI();
			}
		}
		return 0;
	}

	LRESULT OnAddDlgFontBtn(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if (m_peer != NULL)
		{
			Token * tk = m_peer->add_font_dlg(pcode,m_tkcls,NULL,true);
			if (tk != NULL)
			{
				int index = AddTokenList(tk);
				m_tkList.SetCurSel(index);
				UpdateUI();
			}
		}
		return 0;
	}

	LRESULT OnDelFontBtn(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		int icur = m_tkList.GetCurSel();
		Token * tk = m_tkList.GetCurSelData();
		if (tk == NULL)
			return 0;
		if (pcode->RemoveToken(tk) == true)
		{
			m_tkList.DeleteStringData(icur);
			UpdateUI();
		}
		return 0;
	}

	int FindToken(ResControl * ctrl)
	{
		for (int i = 0; i < m_tkList.GetCount(); i++)
		{
			Token * tk = (Token*)m_tkList.GetItemData(i);
			if (m_peer != NULL && m_peer->get_token_id(tk) == ctrl->m_ID)
			{
				return i;
			}
		}
		return -1;
	}

	int FindControl(Token * tk)
	{
		CString id;

		if(m_peer)
		{
			id = m_peer->get_token_id(tk);
		}
		for (int i = 0; i < m_ctrlList.GetCount(); i++)
		{
			ResControl * ctl = (ResControl*)m_ctrlList.GetItemData(i);
			if (ctl->m_ID == id)
				return i;
		}
		return -1;
	}
	
	LRESULT OnSelchangeControlList(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		ResControl * ctrl = m_ctrlList.GetCurSelData();
		if (ctrl == NULL)
			return 0;
		int icur = FindToken(ctrl);
		m_tkList.SetCurSel(icur);
		UpdateUI();
		return 0;
	}

	void UpdateUI()
	{
		int icur = m_tkList.GetCurSel();
		::EnableWindow(GetDlgItem(IDC_DELFONT_BTN),icur == -1 ? FALSE : TRUE );
		::EnableWindow(GetDlgItem(IDC_ADDFONT_BTN),icur == -1 ? TRUE : FALSE );
	}

	LRESULT OnSelchangeTokenList(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		Token * tk = (Token*)m_tkList.GetCurSelData();
		if (tk == NULL)
			return 0;
		int icur = FindControl(tk);
		m_ctrlList.SetCurSel(icur);
		UpdateUI();
		return 0;
	}
};


#endif