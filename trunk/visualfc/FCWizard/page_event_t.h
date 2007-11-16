#ifndef _PAGE_EVENT_T_H_
#define _PAGE_EVENT_T_H_

struct wtl_event;

struct page_event_peer
{
	virtual ~page_event_peer(){}
	virtual init_tag(tag_token & tag) = 0;
	virtual bool find_token(Token * tk) = 0;	
	virtual bool init_event(HWND hWndList) = 0;
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

	CDevListBoxImpl		m_tkList;
	CDevListBoxImpl		m_evList;

	BEGIN_DLGRESIZE_MAP(page_event_template)
		DLGRESIZE_CONTROL(IDC_ADDEVENT_BTN, DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(IDC_DELEVENT_BTN, DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(IDC_TOKEN_LIST, DLSZ_SIZE_X | DLSZ_MOVE_Y)
		DLGRESIZE_CONTROL(IDC_EVENT_LIST, DLSZ_SIZE_X | DLSZ_SIZE_Y)
	END_DLGRESIZE_MAP()
	
	BEGIN_MSG_MAP(page_event_template)
		COMMAND_ID_HANDLER(IDC_ADDEVENT_BTN, OnAddeventBtn)
		COMMAND_ID_HANDLER(IDC_DELEVENT_BTN, OnDeleventBtn)
		COMMAND_HANDLER(IDC_EVENT_LIST, LBN_SELCHANGE, OnLbnSelchangeEventList)
		COMMAND_HANDLER(IDC_TOKEN_LIST, LBN_SELCHANGE, OnLbnSelchangeTokenList)
		CHAIN_MSG_MAP(ui_page_dialog_base)
	END_MSG_MAP()
	
	BEGIN_DDX_MAP(page_event_template)
		DDX_CONTROL(IDC_TOKEN_LIST, m_tkList)
		DDX_CONTROL(IDC_EVENT_LIST, m_evList)
	END_DDX_MAP();
	
	void OnInit()
	{
		DoDataExchange(FALSE);
		if (m_peer)
		{
			if (!m_peer->init_event(m_evList))
			{
				MessageBox(_T("Load wtlevent.h false!!"));
			}
		}
		m_tkList.m_level.Add(250);
		m_tkList.m_level.Add(80);
		m_tkList.m_level.Add(200);
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

	void OnCloseProject()
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

};

#endif  