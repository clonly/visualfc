#ifndef _PAGE_DLSZ_H_
#define _PAGE_DLSZ_H_

struct page_dlsz_peer
{
	virtual ~page_dlsz_peer(){}
	virtual void init_tag(tag_token & tag) = 0;
	virtual Token * add_token_dlg(codeparser * pcode, Token * tkcls, ResControl * ctrl) = 0;
};

class page_dlsz_template : public ui_page_dialog_t<page_dlsz_template, IDD_PAGE_DLSZ>,
					  public page_base_t<page_dlsz_template>
{
public:
	tag_token	m_tag;
	page_dlsz_peer	* m_peer;
	page_dlsz_template() : m_peer(NULL)
	{
	}
	virtual ~page_dlsz_template()
	{
		if (m_peer)
		{
			delete m_peer;
			m_peer = NULL;
		}
	}
public:
	enum { IDD = IDD_PAGE_DLSZ };
	
	BEGIN_DLGRESIZE_MAP(page_dlsz_template)
		DLGRESIZE_CONTROL(IDC_CONTROL_LIST,DLSZ_SIZE_X)
		DLGRESIZE_CONTROL(IDC_TOKEN_LIST,DLSZ_SIZE_X | DLSZ_SIZE_Y)
		DLGRESIZE_CONTROL(IDC_ADDDLSZ_BTN,DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(IDC_DELDLSZ_BTN,DLSZ_MOVE_X)
	END_DLGRESIZE_MAP()
	
	Token					* m_tkcls;
	CDataListT<ResControl>  m_ctrlList;
	CDataListT<Token>		m_tkList;
public:
	const char * page_name() 
	{ 
		return _T("Page Resize Template"); 
	}
	int AddTokenList(Token * tk)
	{
		CString name, args;
		CAtlArray<CString> ar;
		HelperGetTokenTag(tk,name,args);
		StringToArray(args,ar,_T(","),true);
		if (ar.GetSize() == 2)
		{
			return m_tkList.AddStringData(ar[0]+_T(";") + ar[1],tk);
			//return m_tkList.AddStringData(ar[0],ar[1],tk);
		}
		else
		{
			return m_tkList.AddStringData(name,tk);
		}
		return -1;
	}
public: //event
	void OnClassChange(Token * tkcls)
	{
		m_tkList.ResetContent();
		m_tkcls = tkcls;
		if (tkcls == NULL)
			return;

		for (size_t i = 0; i < tkcls->m_Children.GetCount(); i++)
		{
			Token * tk = tkcls->m_Children[i]; 
			if (m_tag.find_body(tk->m_Name) == true)
			{
				AddTokenList(tk);
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
	void OnInit()
	{
		m_ctrlList.SubclassWindow(GetDlgItem(IDC_CONTROL_LIST));

		m_tkList.SubclassWindow(GetDlgItem(IDC_TOKEN_LIST));
	}

	BEGIN_MSG_MAP(page_dlsz_template)
		COMMAND_HANDLER(IDC_CONTROL_LIST, LBN_SELCHANGE, OnSelchangeControlList)
		COMMAND_HANDLER(IDC_TOKEN_LIST, LBN_SELCHANGE, OnSelchangeTokenList)
		COMMAND_ID_HANDLER(IDC_ADDDLSZ_BTN, OnAddDlszBtn)
		COMMAND_ID_HANDLER(IDC_DELDLSZ_BTN, OnDelDlszBtn)
		CHAIN_MSG_MAP(ui_page_dialog_base)
	END_MSG_MAP()

	LRESULT OnAddDlszBtn(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		ResControl * ctrl = m_ctrlList.GetCurSelData();
		if (ctrl == NULL)
			return 0;

		if (m_peer)
		{
			Token * tk = m_peer->add_token_dlg(pcode,m_tkcls,ctrl);
			if (tk != NULL)
			{
				int index = AddTokenList(tk);
				m_tkList.SetCurSel(index);
				UpdateUI();
			}
		}
		return 0;
	}

	LRESULT OnDelDlszBtn(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
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

	LRESULT OnSelchangeControlList(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		// TODO : Add Code for control notification handler.
		ResControl * ctrl = m_ctrlList.GetCurSelData();
		if (ctrl == NULL)
			return 0;

		m_tkList.SetCurSel(FindToken(ctrl));
		UpdateUI();
		return 0;
	}

	LRESULT OnSelchangeTokenList(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		// TODO : Add Code for control notification handler.
		Token * tk = m_tkList.GetCurSelData();
		if (tk == NULL)
			return 0;
		m_ctrlList.SetCurSel(FindControl(tk));
		UpdateUI();
		return 0;
	}

protected:
	int FindToken(ResControl * ctrl)
	{
		for (int i = 0; i < m_tkList.GetCount(); i++)
		{
			Token * tk = (Token*)m_tkList.GetItemData(i);
			CString name, args;
			CAtlArray<CString> ar;
			HelperGetTokenTag(tk,name,args);
			StringToArray(args,ar,_T(","),true);
			if (ar.GetSize() == 2)
			{
				if (ar[0] == ctrl->m_ID)
				{
					return i;
				}
			}
		}
		return -1;
	}
	
	int FindControl(Token * tk)
	{
		CString name, args;
		CAtlArray<CString> ar;
		HelperGetTokenTag(tk,name,args);
		StringToArray(args,ar,_T(","),true);
		if (ar.GetSize() == 2)
		{
			for (int i = 0; i < m_ctrlList.GetCount(); i++)
			{
				ResControl * ctrl = (ResControl*)m_ctrlList.GetItemData(i);
				if (ctrl->m_ID == ar[0])
				{
					return i;
				}
			}
		}
		return -1;
	}
	void UpdateUI()
	{
		int icur = m_tkList.GetCurSel();
		::EnableWindow(GetDlgItem(IDC_DELDLSZ_BTN),icur == -1 ? FALSE : TRUE );
		::EnableWindow(GetDlgItem(IDC_ADDDLSZ_BTN),icur == -1 ? TRUE : FALSE );
	}
};

#endif