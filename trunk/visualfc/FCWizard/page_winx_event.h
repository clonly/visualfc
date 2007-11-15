#ifndef _PAGE_WINX_EVENT_H_
#define _PAGE_WINX_EVENT_H_



class page_winx_event : public ui_page_dialog_t<page_winx_event, IDD_PAGE_WINX_EVENT>,
						public page_base_t<page_winx_event>
{
public:
	const char * page_name()
	{
		return "Winx Event";
	}
	enum { IDD = IDD_PAGE_WINX_EVENT };
public:
//	codeparser * pcode;
	Token	   * m_tkcls;
	CTreeViewCtrl	m_eventTree;
	CAtlArray<HTREEITEM>	m_tree_items;
	CListBox     m_tokenList;
	CListBox	 m_eventList;
public:
	BEGIN_DLGRESIZE_MAP(page_winx_event)
		DLGRESIZE_CONTROL(IDC_EVENT_LIST, DLSZ_SIZE_Y)
		DLGRESIZE_CONTROL(IDC_EVENT_TREE, DLSZ_SIZE_Y)
		DLGRESIZE_CONTROL(IDC_EVENT_TOKEN_LIST, DLSZ_SIZE_Y | DLSZ_SIZE_X)
		DLGRESIZE_CONTROL(IDC_ADDEVENT_BTN, DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(IDC_DELEVENT_BTN, DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(IDC_EDITEVENT_BTN, DLSZ_MOVE_X)
	END_DLGRESIZE_MAP()
public:
	void OnInit()
	{
		m_eventList = GetDlgItem(IDC_EVENT_LIST);
		m_eventTree = GetDlgItem(IDC_EVENT_TREE);
		m_eventList.ShowWindow(SW_HIDE);

		m_tokenList = GetDlgItem(IDC_EVENT_TOKEN_LIST);
		InitEvent();
	}

	void InitEvent()
	{
		CSimpleArray<HTREEITEM> items;
		CSimpleArray<int>		kind_items;
		int i = 0;
		HTREEITEM tree_item;
		int		  list_item;
		for (i = 0; i < pcode->m_winxev.m_kinds.GetSize(); i++)
		{
			tree_item = m_eventTree.InsertItem(pcode->m_winxev.m_kinds[i].name,TVI_ROOT,NULL);
			items.Add(tree_item);
			kind_items.Add(pcode->m_winxev.m_kinds[i].kind);
		}
		
		for (i = 0; i < pcode->m_winxev.m_items.GetSize(); i++)
		{
			winx_event & ev = pcode->m_winxev.m_items[i];
			list_item = m_eventList.AddString(ev.name);
			m_eventList.SetItemData(list_item,(DWORD)&ev);
			int j = 0;
			for (j = 0; j < kind_items.GetSize(); j++)
			{
				if (kind_items[j] == pcode->m_winxev.m_items[i].kind)
				{
					tree_item = items[j];
					break;
				}
			}
			if (j == kind_items.GetSize())
			{
				continue;
			}
			tree_item = m_eventTree.InsertItem(ev.name,tree_item,NULL);
			m_eventTree.SetItemData(tree_item,(DWORD)&ev);
			m_tree_items.Add(tree_item);
		}
	}

	void OnClassChange(Token * tkcls)
	{
		m_tkcls = tkcls;
	//	m_eventList.ResetContent();
		m_tokenList.ResetContent();
		if (tkcls)
		{
	//		pcode->EnumWinxEventList(QLib::Event<void,winx_event*>(this,&page_winx_event::AddWinxEventList));
			pcode->EnumWinxEventToken(tkcls,QLib::Event<void,Token*>(this,&page_winx_event::AddWinxEventToken));
		}
	}
protected:
	//Ìí¼Óevent list
	void AddWinxEventList(winx_event * ev)
	{
		int index = m_eventList.AddString(ev->name);
		m_eventList.SetItemData(index,(DWORD)ev);
	}
	//´¦Àíevnet token 
	int AddWinxEventToken(Token * tk)
	{
		if (tk->m_TokenUpdate == tuRemove) {
			return -1;
		}
		int index = m_tokenList.AddString(tk->m_Name);
		m_tokenList.SetItemData(index,(DWORD)tk);
		return index;
	}
public:
	BEGIN_MSG_MAP(member_page)
		COMMAND_ID_HANDLER(IDC_EVENTKIND_BTN, OnEventKindBtn)
		COMMAND_ID_HANDLER(IDC_EVENTLIST_BTN, OnEventListBtn)
		COMMAND_ID_HANDLER(IDC_EDITEVENT_BTN, OnEditEventBtn)
		COMMAND_ID_HANDLER(IDC_ADDEVENT_BTN, OnAddEventBtn)
		COMMAND_ID_HANDLER(IDC_DELEVENT_BTN, OnDelEventBtn)
		COMMAND_HANDLER(IDC_EVENT_TOKEN_LIST, LBN_SELCHANGE, OnSelchangeEventTokenList)
		COMMAND_HANDLER(IDC_EVENT_LIST, LBN_SELCHANGE, OnSelchangeEventList)
		NOTIFY_HANDLER(IDC_EVENT_TREE, TVN_SELCHANGED, OnSelchangedEventTree)
		CHAIN_MSG_MAP(ui_page_dialog_base)
	END_MSG_MAP()	

	QLib::Event<void,Token*> EventGoToLine;

	LRESULT OnEventListBtn(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		::ShowWindow(GetDlgItem(IDC_EVENT_LIST),SW_SHOW);
		::ShowWindow(GetDlgItem(IDC_EVENT_TREE),SW_HIDE);
		return 0;
	}

	LRESULT OnEventKindBtn(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		::ShowWindow(GetDlgItem(IDC_EVENT_LIST),SW_HIDE);
		::ShowWindow(GetDlgItem(IDC_EVENT_TREE),SW_SHOW);
		return 0;
	}

	LRESULT OnEditEventBtn(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		int index = m_tokenList.GetCurSel();
		if (index == -1)
			return 0;
		Token * tk = (Token*)m_tokenList.GetItemData(index);
		EventGoToLine(tk);
		return 0;
	}
	LRESULT OnAddEventBtn(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		int index = m_eventList.GetCurSel();
		if (index == -1) {
			return 0;
		}
		winx_event * ev = (winx_event*)m_eventList.GetItemData(index);
		OnAddnewEvent(ev);
		return 0;
	}
	LRESULT OnDelEventBtn(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		int index = m_tokenList.GetCurSel();
		if (index == -1) {
			return 0;
		}
		Token * tk = (Token*)m_tokenList.GetItemData(index);
		if ( OnDeleteToken(tk) == true)
		{
			m_tokenList.DeleteString(index);
		}
		return 0;
	}
	LRESULT OnSelchangeEventTokenList(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		// TODO : Add Code for control notification handler.
		int index = m_tokenList.GetCurSel();
		if (index <= -1) {
			return 0;
		}
		Token * tk = (Token*)m_tokenList.GetItemData(index);
		// select list
		m_eventList.SetCurSel(FindEventWinxList(tk));
		// select tree
		m_eventTree.SelectItem(FindEventTree(tk));
		return 0;
	}
	LRESULT OnSelchangeEventList(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		// TODO : Add Code for control notification handler.
		int index = m_eventList.GetCurSel();
		if (index <= -1) {
			return 0;
		}
		winx_event * ev = (winx_event*)m_eventList.GetItemData(index);
		if (ev == NULL)
			return 0;
		//update
		m_tokenList.SetCurSel(FindEventTokenList(ev));
		//update event tree
		for (size_t i = 0; i < m_tree_items.GetCount(); i++)
		{
			winx_event * ev2 = (winx_event*)m_eventTree.GetItemData(m_tree_items[i]);
			if (ev2 != NULL && ev2 == ev)
			{
				m_eventTree.SelectItem(m_tree_items[i]);
				break;
			}
		}
		return 0;
	}

	LRESULT OnSelchangedEventTree(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
	{
		// TODO : Add Code for control notification handler.
		HTREEITEM item = m_eventTree.GetSelectedItem();
		if (item != NULL)
		{
			winx_event * ev = (winx_event*)m_eventTree.GetItemData(item);
			if (ev == NULL)
				return 0;
			//update
			m_tokenList.SetCurSel(FindEventTokenList(ev));
			// update event list
			for (size_t i = 0; i < m_eventList.GetCount(); i++) 
			{
				winx_event * ev2 = (winx_event*)m_eventList.GetItemData(i);
				if (ev2 != NULL && ev2 == ev) {
					m_eventList.SetCurSel(i);
					break;
				}
			}

		}		
		return 0;
	}

protected:
	HTREEITEM FindEventTree(Token * tk)
	{
		if (tk == NULL) {
			return NULL;
		}
		for (size_t i = 0; i < m_tree_items.GetCount(); i++)
		{
			winx_event * ev = (winx_event*)m_eventTree.GetItemData(m_tree_items[i]);
			if (ev != NULL && (ev->name == (CString)tk->m_Name))
			{
				return m_tree_items[i];
			}
		}
		return NULL;
	}
	Token * FindEventTokenListToken(winx_event * ev)
	{
		if (ev == NULL) {
			return NULL;
		}
		for (int i = 0; i < m_tokenList.GetCount(); i++) {
			Token * tk = (Token*)m_tokenList.GetItemData(i);
			if (tk && ((CString)tk->m_Name == ev->name)) {
				return tk;
			}
		}
		return NULL;
	}

	int FindEventTokenList(winx_event * ev)
	{
		if (ev == NULL) {
			return -1;
		}
		for (int i = 0; i < m_tokenList.GetCount(); i++) {
			Token * tk = (Token*)m_tokenList.GetItemData(i);
			if (tk && ((CString)tk->m_Name == ev->name)) {
				return i;
			}
		}
		return -1;
	}
	int FindEventWinxList(Token * tk)
	{
		if (tk == NULL) {
			return -1;
		}
		for (int i = 0; i < m_eventList.GetCount(); i++) {
			winx_event * ev = (winx_event*)m_eventList.GetItemData(i);
			if (ev != NULL && (ev->name == (CString)tk->m_Name) ) {
				return i;
			}
		}
		return -1;
	}

	bool OnAddnewEvent(winx_event * ev)
	{
		if (FindEventTokenList(ev) != -1) {
			return false;
		}
		Token * tk = pcode->WinxAddEventToken(ev,m_tkcls);
		int index = AddWinxEventToken(tk);
		m_tokenList.SetCurSel(index);
		return true;
	}
	bool AskRemoveToken(Token * tk)
	{
		CString text;
		text = _T("Deleting this winx event is auto rename ");
		text += tk->m_Name;
		text += _T(" to _winxDEL_");
		text += tk->m_Name;
		text += _T(". Continue?");
		UINT id = ::MessageBox(m_hWnd,text,_T("Delete Winx Event"),MB_YESNOCANCEL | MB_ICONQUESTION);
		if (id == IDYES)
			return true;
		return false;
	}
	bool OnDeleteToken(Token * tk)
	{
		return pcode->WinxRemoveEventToken(tk,QLib::Event<bool,Token*>(this,&page_winx_event::AskRemoveToken));
	}
};

#endif //_PAGE_WINX_EVENT_H_