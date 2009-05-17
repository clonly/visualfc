#ifndef _PAGE_EVENT_T_H_
#define _PAGE_EVENT_T_H_

struct wtl_event;

struct page_event_peer
{
	virtual ~page_event_peer(){}
	virtual init_tag(tag_token & tag) = 0;
	virtual bool find_token(Token * tk) = 0;	
	virtual bool init_event(codeparser * pcode, HWND hWndTree, HWND hWndList, CAtlArray<HTREEITEM> * pItems) = 0;
	virtual int	add_tklist(HWND hWndList, Token * tk) = 0;
	virtual Token * add_token_dlg(codeparser * pcode, Token * tkcls, wtl_event * ev) = 0;
};

class page_event_template : public ui_page_dialog_t<page_event_template, IDD_PAGE_EVENT>,
							public page_base_t<page_event_template>,
							public CWinDataExchange<page_event_template>
{
protected:
	page_event_peer * m_peer;
	Token			* m_tkcls;
public:
	CLayoutSplitter	m_eventSplit;
	CFramePanelCtrl		m_wndFramePanel;
	CToolBarCtrl		m_wndPropToolBar;

	page_event_template() : m_peer(NULL), m_tkcls(NULL)
	{
	}
	~page_event_template()
	{
		if (m_peer)
		{
			delete m_peer;
			m_peer = NULL;
		}
	}

	CTreeViewCtrl			m_evTree;
	CAtlArray<HTREEITEM>	m_tree_items;
	CDevListBoxImpl		m_tkList;
	CDevListBoxImpl		m_evList;

	BEGIN_DLGRESIZE_MAP(page_event_template)
		DLGRESIZE_CONTROL(IDC_FRMPANEL, DLSZ_SIZE_X | DLSZ_SIZE_Y)
		DLGRESIZE_CONTROL(IDC_ADDEVENT_BTN, DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(IDC_DELEVENT_BTN, DLSZ_MOVE_X)
	//	DLGRESIZE_CONTROL(IDC_EVENT_SPLIT, DLSZ_SIZE_X | DLSZ_SIZE_Y)
	//	DLGRESIZE_CONTROL(IDC_TOKEN_LIST, DLSZ_SIZE_X | DLSZ_MOVE_Y)
	END_DLGRESIZE_MAP()
	
	BEGIN_MSG_MAP(page_event_template)
		COMMAND_ID_HANDLER(ID_PROP_KIND, OnKindBtn)
		COMMAND_ID_HANDLER(ID_PROP_LIST, OnListBtn)
		NOTIFY_HANDLER(IDC_EVENT_TREE, TVN_SELCHANGED, OnTvnSelchangedEventTree)
		NOTIFY_HANDLER(IDC_EVENT_TREE, NM_CLICK, OnNmClickEventTree)
		COMMAND_ID_HANDLER(IDC_ADDEVENT_BTN, OnAddeventBtn)
		COMMAND_ID_HANDLER(IDC_DELEVENT_BTN, OnDeleventBtn)
		COMMAND_HANDLER(IDC_EVENT_LIST, LBN_SELCHANGE, OnLbnSelchangeEventList)
		COMMAND_HANDLER(IDC_TOKEN_LIST, LBN_SELCHANGE, OnLbnSelchangeTokenList)
		CHAIN_MSG_MAP(ui_page_dialog_base)
	END_MSG_MAP()
	
	BEGIN_DDX_MAP(page_event_template)
	//	DDX_CONTROL(IDC_EVENT_SPLIT, m_eventSplit)
	//	DDX_CONTROL(IDC_FRMPANEL, m_wndFramePanel);
		DDX_CONTROL_HANDLE(IDC_EVENT_TREE, m_evTree)
		DDX_CONTROL(IDC_TOKEN_LIST, m_tkList)
		DDX_CONTROL(IDC_EVENT_LIST, m_evList)
	END_DDX_MAP();
	
	void OnQuit()
	{
		m_eventSplit.UnsubclassWindow();
		m_evTree.m_hWnd = NULL;
		m_tkList.UnsubclassWindow();
		m_evList.UnsubclassWindow();
	}

	void OnInit()
	{
		DoDataExchange(FALSE);
		m_tkList.m_level.Add(250);
		m_tkList.m_level.Add(80);
		m_tkList.m_level.Add(200);

		m_eventSplit.SubclassWindow(GetDlgItem(IDC_EVENT_SPLIT));
		m_eventSplit.SetSplitterPanes(m_evTree, m_evList);
		m_eventSplit.SetSinglePaneMode(SPLIT_PANE_LEFT);

		if (m_peer)
		{
			if (!m_peer->init_event(pcode, m_evTree, m_evList,&m_tree_items))
			{
			}
		}

		m_wndFramePanel.SubclassWindow(GetDlgItem(IDC_FRMPANEL));
		m_wndFramePanel.AddResize(IDC_EVENT_SPLIT, PANEL_SIZE_X | PANEL_SIZE_Y);
		m_wndFramePanel.AddResize(IDC_TOKEN_LIST, PANEL_SIZE_X | PANEL_MOVE_Y);
		HWND hToolBar = m_wndFramePanel.CreateToolBarCtrl(IDR_PROP_TOOLBAR);
		//m_wndFramePanel.CreateSimpleToolBar(IDR_PROP_TOOLBAR);
		m_wndFramePanel.CreateSimpleReBar();
		m_wndFramePanel.AddSimpleReBarBand(hToolBar, _T(""), TRUE);
		m_wndFramePanel.LockBands(true);
		m_wndFramePanel.RepositionDialog();

		m_wndPropToolBar = hToolBar;//m_wndFramePanel.m_hWndToolBar;
		m_wndPropToolBar.CheckButton(ID_PROP_KIND,TRUE);
	}

	void OnClassChange(Token * tkcls)
	{
		m_tkcls = tkcls;
		m_tkList.ResetContent();
		if (tkcls == NULL)
		{
			return;
		}
		for (size_t i = 0; i < tkcls->m_Children.GetCount(); i++)
		{
			Token * tk = tkcls->m_Children[i];
			if (m_peer && m_peer->find_token(tk))
			{
				m_peer->add_tklist(m_tkList,tk);
			}
		}
	}

	void OnCloseProject(WORD wID)
	{
		m_tkList.ResetContent();
		m_evList.SetCurSel(-1);
		UpdateUI();
	}

	LRESULT OnLbnSelchangeEventList(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		int index = m_evList.GetCurSel();
		if (index == -1)	
		{
			return 0;
		}
		wtl_event * ev = (wtl_event*)m_evList.GetItemData(index);
		if (ev)
		{
			int i = FindTokenList(ev->msg);
			m_tkList.SetCurSel(i);
		}
		for (size_t i = 0; i < m_tree_items.GetCount(); i++)
		{
			wtl_event * ev2 = (wtl_event*)m_evTree.GetItemData(m_tree_items[i]);
			if (ev2 != NULL && ev2 == ev)
			{
				m_evTree.SelectItem(m_tree_items[i]);
				break;
			}
		}

		UpdateUI();
		return 0;
	}

	int FindTokenList(LPCTSTR msg)
	{
		CString text;
		for (size_t i = 0; i < m_tkList.GetCount(); i++)
		{
			m_tkList.GetTextEx(i,0,text);
			if (text == msg)
			{
				return i;
			}
		}
		return -1;
	}

	int FindEventList(LPCSTR name)
	{
		CString text;
		for (size_t i = 0; i < m_evList.GetCount(); i++)
		{
			m_evList.GetTextEx(i,0,text);
			if (text == name)
			{
				return i;
			}
		}
		return -1;
	}

	HTREEITEM FindEventTree(LPCSTR name)
	{
		for (size_t i = 0; i < m_tree_items.GetCount(); i++)
		{
			wtl_event * ev = (wtl_event*)m_evTree.GetItemData(m_tree_items[i]);
			if (ev != NULL && (ev->msg == name))
			{
				return m_tree_items[i];
			}
		}
		return NULL;
	}
	
	LRESULT OnLbnSelchangeTokenList(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		int index = m_tkList.GetCurSel();
		if (index == -1)
		{
			return 0;
		}
		Token * tk = (Token*)m_tkList.GetItemData(index);
		if (tk)
		{
			CString text;
			m_tkList.GetTextEx(index,0,text);

			int i = FindEventList(text);
			m_evList.SetCurSel(i);

			HTREEITEM item = FindEventTree(text);
			m_evTree.SelectItem(item);
		}
		UpdateUI();
		return 0;
	}
	LRESULT OnAddeventBtn(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		int index = m_evList.GetCurSel();
		if (index == -1)
		{
			return 0;
		}
		wtl_event * ev = (wtl_event*)m_evList.GetItemData(index);
		if (m_peer)
		{
			Token * tk = m_peer->add_token_dlg(pcode,m_tkcls,ev);
			if (tk)
			{
				int index = m_peer->add_tklist(m_tkList,tk);
				m_tkList.SetCurSel(index);
				UpdateUI();
			}
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
		UINT id = ::MessageBox(m_hWnd,text,_T("Delete WTL Event"),MB_YESNOCANCEL | MB_ICONQUESTION);
		if (id == IDYES)
			return true;
		return false;
	}
	
	LRESULT OnDeleventBtn(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		int index = m_tkList.GetCurSel();
		if (index == -1)
			return 0;
		Token * tk = (Token*)m_tkList.GetItemData(index);
		bool bRet = pcode->WinxRemoveNotifyToken(tk,QLib::Event<bool,Token*>(this,&page_event_template::AskRemoveToken));
		if (bRet)
		{
			m_tkList.DeleteString(index);
		}
		return 0;
	}

	void UpdateUI()
	{
		int icur = m_tkList.GetCurSel();
		::EnableWindow(GetDlgItem(IDC_DELEVENT_BTN),icur == -1 ? FALSE : TRUE );
		::EnableWindow(GetDlgItem(IDC_ADDEVENT_BTN),icur == -1 ? TRUE : FALSE );
	}

	LRESULT OnTvnSelchangedEventTree(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
	{
		DoEventTreeChanged();
		return 0;
	}

	LRESULT OnNmClickEventTree(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
	{
		DoEventTreeChanged();
		return 0;
	}

	void DoEventTreeChanged()
	{
		HTREEITEM item = m_evTree.GetSelectedItem();
		wtl_event * ev = (wtl_event*)m_evTree.GetItemData(item);
		if (ev)
		{
			int i = FindTokenList(ev->msg);
			m_tkList.SetCurSel(i);
		}
		// update event list
		for (size_t i = 0; i < m_evList.GetCount(); i++) 
		{
			wtl_event * ev2 = (wtl_event*)m_evList.GetItemData(i);
			if (ev2 != NULL && ev2 == ev) {
				m_evList.SetCurSel(i);
				break;
			}
		}

		UpdateUI();
	}
	LRESULT OnKindBtn(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		m_eventSplit.SetSinglePaneMode(SPLIT_PANE_LEFT);
		m_wndPropToolBar.CheckButton(ID_PROP_KIND,TRUE);
		m_wndPropToolBar.CheckButton(ID_PROP_LIST,FALSE);
		return 0;
	}
	LRESULT OnListBtn(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		m_eventSplit.SetSinglePaneMode(SPLIT_PANE_RIGHT);
		m_wndPropToolBar.CheckButton(ID_PROP_KIND,FALSE);
		m_wndPropToolBar.CheckButton(ID_PROP_LIST,TRUE);
		return 0;
	}

};

#endif  