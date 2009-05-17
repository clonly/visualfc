#ifndef _PAGE_DDX_T_H_
#define _PAGE_DDX_T_H_

class dlg_add_ddx : public ui_simple_dialog_t<dlg_add_ddx,IDD_ADD_DDX_DIALOG>,
					public CWinDataExchange<dlg_add_ddx>
{
public:
	CString	m_len;
	CString	m_min;
	CString	m_max;
	CString	m_var;

	BEGIN_MSG_MAP(dlg_add_ddx)
		COMMAND_HANDLER(IDC_DDXTYPE_COMBO, CBN_SELCHANGE, OnCbnSelchangeDdxtypeCombo)
		CHAIN_MSG_MAP(ui_simple_dialog_base)
	END_MSG_MAP()
		
	BEGIN_DDX_MAP(dlg_add_ddx)
		DDX_TEXT(IDC_LEN_EDIT, m_len)
		DDX_TEXT(IDC_MIN_EDIT, m_min)
		DDX_TEXT(IDC_MAX_EDIT, m_max)
		DDX_TEXT(IDC_VAR_EDIT, m_var)
	END_DDX_MAP();
	
	CString m_id;
	CString m_ddxtype;
	CString m_vartype;
	bool	m_blen;
	bool	m_brange;
	CEdit	  m_editVar;
	CComboBox m_cmbDDXType;
	CComboBox m_cmbVarType;

	win32_notify	* m_wn;
	ResControl		* m_res;
	QLib::Event<void, win32_notify *, ResControl * , std::vector<CString> &> get_ddx_type;
	QLib::Event<void, win32_notify *, const CString & , std::vector<CString> & > get_var_type;

	void UpdateUI(const CString & ddx_type)
	{
		m_blen = FALSE;
		m_brange = FALSE;
		if (ddx_type.Find(_T("LEN")) != -1)
		{
			m_blen = TRUE;			
		}
		if (ddx_type.Find(_T("RANGE")) != -1)
		{
			m_brange = TRUE;
		}
		::EnableWindow(GetDlgItem(IDC_LEN_EDIT),m_blen);
		::EnableWindow(GetDlgItem(IDC_MIN_EDIT),m_brange);
		::EnableWindow(GetDlgItem(IDC_MAX_EDIT),m_brange);
	}

	void OnInit()
	{
		
		m_editVar = GetDlgItem(IDC_VAR_EDIT);
		m_cmbDDXType = GetDlgItem(IDC_DDXTYPE_COMBO);
		m_cmbVarType = GetDlgItem(IDC_VARTYPE_COMBO);


		CComboBox box = GetDlgItem(IDC_OBJECTID_COMBO);
		if (!m_id.IsEmpty())
		{
			box.AddString(m_id);
			box.SetCurSel(0);
		}

		SetDlgItemText(IDC_VAR_EDIT,m_var);
		std::vector<CString> array;
		get_ddx_type(m_wn,m_res,array);
		size_t i = 0;
		for (i = 0; i < array.size(); i++)
		{
			m_cmbDDXType.AddString(array[i]);
		}
		if (array.size() == 0)
		{
			EndDialog(IDCANCEL);
			return;
		}
		m_cmbDDXType.SetCurSel(0);
		//m_cmbVarType.SetCurSel(0);	
		DDXTypeSelChange(0);

		DoDataExchange(FALSE);

		m_editVar.SetFocus();
		m_editVar.AppendText(_T("m_"));
	}

	BOOL OnClose()
	{
		TCHAR buf[128] = {0};
		m_cmbDDXType.GetWindowText(buf,127);
		m_ddxtype = buf;
		m_cmbVarType.GetWindowText(buf,127);
		m_vartype = buf;

		DoDataExchange(TRUE);
		if (m_blen)
		{
			if (m_len.IsEmpty())
			{
				MessageBox(_T("Please input text len"));
				return FALSE;
			}
		}
		if (m_brange)
		{
			if (m_min.IsEmpty() || m_max.IsEmpty())
			{
				MessageBox(_T("Please input number min and max"));
				return FALSE;
			}
		}
		return TRUE;
	}

	void DDXTypeSelChange(int index)
	{
		TCHAR ddx_type[128] = {0};
		m_cmbDDXType.GetWindowText(ddx_type,127);
		m_cmbVarType.ResetContent();
		std::vector<CString>	array;
		get_var_type(m_wn,ddx_type,array);
		for (size_t i = 0; i < array.size(); i++)
		{
			m_cmbVarType.AddString(array[i]);
		}
		m_cmbVarType.SetCurSel(0);
		UpdateUI(ddx_type);
	}

	LRESULT OnCbnSelchangeDdxtypeCombo(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		int index = m_cmbDDXType.GetCurSel();
		if (index != -1)
		{
			DDXTypeSelChange(index);
		}
		return 0;
	}
};


struct page_ddx_peer
{
	virtual ~page_ddx_peer(){}
	virtual void init_tag(tag_token & tag) = 0;
	virtual Token * add_token_dlg(codeparser * pcode, Token * tkcls, ResControl * ctrl) = 0;
};

class page_ddx_template : public ui_page_dialog_t<page_ddx_template, IDD_PAGE_DDX>,
						  public page_base_t<page_ddx_template>
{
public:
	tag_token	m_tag;
	page_ddx_peer	* m_peer;
	page_ddx_template() : m_peer(NULL)
	{
	}
	virtual ~page_ddx_template()
	{
		if (m_peer)
		{
			delete m_peer;
			m_peer = NULL;
		}
	}
public:
	enum { IDD = IDD_PAGE_DDX };
	
	BEGIN_DLGRESIZE_MAP(page_ddx_template)
		DLGRESIZE_CONTROL(IDC_CONTROL_LIST,DLSZ_SIZE_X)
		DLGRESIZE_CONTROL(IDC_TOKEN_LIST,DLSZ_SIZE_X | DLSZ_SIZE_Y)
		DLGRESIZE_CONTROL(IDC_ADDDDX_BTN,DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(IDC_DELDDX_BTN,DLSZ_MOVE_X)
	END_DLGRESIZE_MAP()
	
	Token					* m_tkcls;
	CDataListT<ResControl>  m_ctrlList;
	CDataListT<Token>		m_tkList;
public:
	const char * page_name() 
	{ 
		return _T("Page DDX Template"); 
	}
	int AddTokenList(Token * tk)
	{
		CString name, args;
		CAtlArray<CString> ar;
		HelperGetTokenTag(tk,name,args);
		CSimpleArray<CString> array;
		StringToArray(args,array,_T(","));
		if (array.GetSize() >= 2)
		{
			//array[0] - id
			//array[1] - var
			Token * tkvar = pcode->FindTokenVarible(m_tkcls,array[1]);
			if (tkvar != NULL)
			{
				tk->m_Data = tkvar;
				return m_tkList.AddStringData(name+_T(";")+args+_T(";")+(CString)tkvar->m_Type+_T(";")+(CString)tkvar->m_Name,tk);
			}
		}
		return m_tkList.AddStringData(name+_T(";")+args,tk);
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

	BEGIN_MSG_MAP(page_ddx_template)
		COMMAND_HANDLER(IDC_CONTROL_LIST, LBN_SELCHANGE, OnSelchangeControlList)
		COMMAND_HANDLER(IDC_TOKEN_LIST, LBN_SELCHANGE, OnSelchangeTokenList)
		COMMAND_ID_HANDLER(IDC_ADDDDX_BTN, OnAddDDXBtn)
		COMMAND_ID_HANDLER(IDC_DELDDX_BTN, OnDelDDXBtn)
		CHAIN_MSG_MAP(ui_page_dialog_base)
	END_MSG_MAP()

	LRESULT OnAddDDXBtn(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
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

	LRESULT OnDelDDXBtn(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		int icur = m_tkList.GetCurSel();
		Token * tk = m_tkList.GetCurSelData();
		if (tk == NULL)
			return 0;
		Token * tkvar = (Token*)tk->m_Data;
		if (pcode->RemoveToken(tk) == true)
		{
			if (tkvar != NULL)
			{
				pcode->RemoveToken(tkvar);
			}
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
			if (ar.GetSize() >= 1)
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
		if (ar.GetSize() >= 1)
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
		::EnableWindow(GetDlgItem(IDC_DELDDX_BTN),icur == -1 ? FALSE : TRUE );
	//	::EnableWindow(GetDlgItem(IDC_ADDDDX_BTN),icur == -1 ? TRUE : FALSE );
	}
};

#endif //_PAGE_DDX_T_H_