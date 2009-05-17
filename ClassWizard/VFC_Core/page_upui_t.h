#ifndef _PAGE_UPUI_T_H_
#define _PAGE_UPUI_T_H_

class dlg_add_upui : public ui_simple_dialog_t<dlg_add_upui,IDD_ADD_UPUI_DIALOG>,
					 public CWinDataExchange<dlg_add_upui>
{
public:
	CButton	m_btnSB;
	CButton	m_btnTB;
	CButton	m_btnCW;
	CButton	m_btnMB;
	CButton	m_btnMP;
	CString	m_objectid;
	CString	m_restype;
	CString		m_upui;
	ResBase	*	m_res;

	BEGIN_DDX_MAP(dlg_add_upui)
		DDX_CONTROL_HANDLE(IDC_MENUPOPUP_CHECK, m_btnMP)
		DDX_CONTROL_HANDLE(IDC_MENUBAR_CHECK, m_btnMB)
		DDX_CONTROL_HANDLE(IDC_CHILDWINDOW_CHECK, m_btnCW)
		DDX_CONTROL_HANDLE(IDC_TOOLBAR_CHECK, m_btnTB)
		DDX_CONTROL_HANDLE(IDC_STATUSBAR_CHECK, m_btnSB)
		DDX_TEXT(IDC_RESTYPE_EDIT, m_restype)
		DDX_TEXT(IDC_OBJECTID_EDIT, m_objectid)
	END_DDX_MAP();
	
public:
	void OnInit()
	{
		if (m_res->GetResType() == RES_CONTROL)
		{
			m_restype = ((ResControl*)m_res)->m_Type;
		}
		else if (m_res->GetResType() == RES_MENUITEM)
		{
			m_restype = _T("MENUITEM");
		}
		DoDataExchange(FALSE);
		if (m_res->GetResType() == RES_CONTROL)
		{
			m_btnSB.EnableWindow(FALSE);
			m_btnTB.EnableWindow(FALSE);
			m_btnCW.EnableWindow(TRUE);
			m_btnCW.SetCheck(TRUE);
			m_btnMB.EnableWindow(FALSE);
			m_btnMP.EnableWindow(FALSE);
		}
		else if (m_res->GetResType() == RES_MENUITEM)
		{
			m_btnSB.EnableWindow(FALSE);
			m_btnTB.EnableWindow(TRUE);
			m_btnCW.EnableWindow(FALSE);
			m_btnMB.EnableWindow(FALSE);
			m_btnMP.EnableWindow(TRUE);
			m_btnMP.SetCheck(TRUE);
		}
	}
	bool MakeUPUI(CButton & btn)
	{
		if (btn.GetCheck() == FALSE)
			return false;
		TCHAR text[41] = {0};
		btn.GetWindowText(text,40);
		if (!m_upui.IsEmpty())
			m_upui += _T(" | ");
		m_upui += _T("UPDUI_");
		m_upui += text;
		return true;
	}
	BOOL OnClose()
	{
		DoDataExchange(TRUE);
		MakeUPUI(m_btnMP);
		MakeUPUI(m_btnSB);
		MakeUPUI(m_btnTB);
		MakeUPUI(m_btnCW);
		MakeUPUI(m_btnMB);
		return TRUE;
	}
};

struct page_upui_peer
{
	virtual ~page_upui_peer(){}
	virtual void init_tag(tag_token & tag) = 0;
	virtual bool find_token(Token * tk) = 0;
	virtual Token * add_token_dlg(codeparser * pcode, Token * tkcls, ResBase * res) = 0;
};

class page_upui_template : public ui_page_dialog_t<page_upui_template, IDD_PAGE_UPUI>,
						  public page_base_t<page_upui_template>
{
public:
	tag_token	m_tag;
	page_upui_peer	* m_peer;
	Token					* m_tkcls;
	CResDialog				* m_pResDlg;
	CResMenu				* m_pResMenu;
	page_upui_template() : m_peer(NULL), m_pResDlg(NULL), m_pResMenu(NULL)
	{
	}
	virtual ~page_upui_template()
	{
		if (m_peer)
		{
			delete m_peer;
			m_peer = NULL;
		}
	}
public:
	enum { IDD = IDD_PAGE_UPUI };
	
	BEGIN_DLGRESIZE_MAP(page_upui_template)
		DLGRESIZE_CONTROL(IDC_RESOURCE_LIST,DLSZ_SIZE_X)
		DLGRESIZE_CONTROL(IDC_TOKEN_LIST,DLSZ_SIZE_X | DLSZ_SIZE_Y)
		DLGRESIZE_CONTROL(IDC_ADDUPUI_BTN,DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(IDC_DELUPUI_BTN,DLSZ_MOVE_X)
	END_DLGRESIZE_MAP()
	
	CDataListT<ResBase>  m_resList;
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
		CAtlArray<CString> array;
		StringToArray(args,array,_T(","));
		if (array.GetSize() >= 2)
		{
			//array[0] - id
			//array[1] - var
			CString text;
			ArrayToStringEx(array,text,_T(","),1);
			return m_tkList.AddStringData(array[0]+_T(";")+text,tk);
		}
		return m_tkList.AddStringData(name+_T(";")+args,tk);
		return -1;
	}
public: //event
	void OnCloseProject(WORD wID)
	{
		m_tkcls = NULL;
		m_pResDlg = NULL;
		m_pResMenu = NULL;
		m_tkList.ResetContent();
		m_resList.ResetContent();
	}
	void OnClassChange(Token * tkcls)
	{	
		m_tkList.ResetContent();
		m_tkcls = tkcls;
		if (tkcls == NULL)
			return;

		for (size_t i = 0; i < tkcls->m_Children.GetCount(); i++)
		{
			Token * tk = tkcls->m_Children[i]; 
			if (m_peer->find_token(tk) == true)
			{
				AddTokenList(tk);
			}
		}	
		UpdateUI();
	}
	
	void AddResMenuItem(const ResMenuItem * menu)
	{
		CString type;
		if (menu->GetResType() == RES_MENUITEM)
		{
			type = _T("MENUITEM");
		}
		else if (menu->GetResType() == RES_MENUBAR)
		{
			type = _T("MENUBAR");
		}
		m_resList.AddStringData(menu->m_ID+_T(";")+type,(ResBase*)menu);
	}
	void AddResControl(const ResControl * ctrl)
	{
		m_resList.AddStringData(ctrl->m_ID+_T(";")+ctrl->m_Type,(ResBase*)ctrl);
	}

	void ResetResourceList()
	{
		m_resList.ResetContent();
		if (m_pResDlg != NULL)
		{
			pcode->EnumResDialogControl(m_pResDlg,QLib::Event<void,const ResControl*>(this,&page_upui_template::AddResControl));
		}	

		if (m_pResMenu != NULL)
		{
			pcode->EnumResMenuItem(m_pResMenu,QLib::Event<void,const ResMenuItem*>(this,&page_upui_template::AddResMenuItem));
		}		
	}

	void OnResDialogChange(CResDialog * dlg)
	{
		m_pResDlg = dlg;

		ResetResourceList();		
	}
	void OnResMenuChange(CResMenu * menu)
	{
		m_pResMenu = menu;
		ResetResourceList();
	}
public:
	void OnInit()
	{
		m_resList.SubclassWindow(GetDlgItem(IDC_RESOURCE_LIST));

		m_tkList.SubclassWindow(GetDlgItem(IDC_TOKEN_LIST));
	}

	BEGIN_MSG_MAP(page_upui_template)
		COMMAND_HANDLER(IDC_RESOURCE_LIST, LBN_SELCHANGE, OnSelchangeResourceList)
		COMMAND_HANDLER(IDC_TOKEN_LIST, LBN_SELCHANGE, OnSelchangeTokenList)
		COMMAND_ID_HANDLER(IDC_ADDUPUI_BTN, OnAddUpuiBtn)
		COMMAND_ID_HANDLER(IDC_DELUPUI_BTN, OnDelUpuiBtn)
		CHAIN_MSG_MAP(ui_page_dialog_base)
	END_MSG_MAP()

	LRESULT OnAddUpuiBtn(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		ResBase * res = m_resList.GetCurSelData();
		if (res == NULL)
			return 0;

		if (m_peer)
		{
			Token * tk = m_peer->add_token_dlg(pcode,m_tkcls,res);
			if (tk != NULL)
			{
				int index = AddTokenList(tk);
				m_tkList.SetCurSel(index);
				UpdateUI();
			}
		}
		return 0;
	}

	LRESULT OnDelUpuiBtn(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
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

	LRESULT OnSelchangeResourceList(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		// TODO : Add Code for control notification handler.
		ResBase * res = m_resList.GetCurSelData();

		m_tkList.SetCurSel(FindToken(res));
		UpdateUI();
		return 0;
	}

	LRESULT OnSelchangeTokenList(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		// TODO : Add Code for control notification handler.
		Token * tk = m_tkList.GetCurSelData();
		if (tk == NULL)
			return 0;
		m_resList.SetCurSel(FindControl(tk));
		UpdateUI();
		return 0;
	}

protected:
	int FindToken(ResBase * res)
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
				if (ar[0] == res->m_ID)
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
			for (int i = 0; i < m_resList.GetCount(); i++)
			{
				ResBase * res = (ResBase*)m_resList.GetItemData(i);
				if (res->m_ID == ar[0])
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
		::EnableWindow(GetDlgItem(IDC_DELUPUI_BTN),icur == -1 ? FALSE : TRUE );
		::EnableWindow(GetDlgItem(IDC_ADDUPUI_BTN),icur == -1 ? TRUE : FALSE );
	}
};


#endif