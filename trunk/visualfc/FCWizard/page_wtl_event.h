#ifndef _PAGE_WTL_EVENT_H_
#define _PAGE_WTL_EVENT_H_

#include "wtl_event.h"

class dlg_wtl_event_dialog  : public ui_simple_dialog_t<dlg_wtl_event_dialog, IDD_ADD_WTLEVENT_DIALOG>,
							  public CWinDataExchange<dlg_wtl_event_dialog>
{
protected:
	BEGIN_MSG_MAP(dlg_wtl_event_dialog)
		COMMAND_HANDLER(IDC_WTLNEW_CHECK, BN_CLICKED, OnBnClickedWtlnewCheck)
		CHAIN_MSG_MAP(ui_simple_dialog_base)
	END_MSG_MAP()
	
	wtl_event	* m_ev;
public:
	BOOL	m_bNew;
	CButton	m_newCheck;
	CString	m_func;
	CString	m_name;
	CString	m_msg;

	BEGIN_DDX_MAP(dlg_wtl_event_dialog)
		DDX_CHECK(IDC_WTLNEW_CHECK, m_bNew)
		DDX_CONTROL_HANDLE(IDC_WTLNEW_CHECK, m_newCheck)
		DDX_TEXT(IDC_MSG_EDIT, m_msg)
		DDX_TEXT(IDC_FUNCNAME_EDIT, m_name)
		DDX_TEXT(IDC_FUNC_EDIT, m_func)
	END_DDX_MAP();

	void GetFunction(BOOL bNew)
	{
		m_msg = m_ev->msg;
		m_name = m_ev->func;
		if (bNew)
		{
			m_func = m_ev->func;
		}
		else
		{
			m_func =  _T("LRESULT ");
			m_func += m_ev->func;
			m_func += _T("(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)");
			m_bNew = FALSE;
		}
	}
	
	void OnInit()
	{
		m_bNew = FALSE;
		GetFunction(m_bNew);
		DoDataExchange(FALSE);
	}
	BOOL OnClose()	
	{
		DoDataExchange(TRUE);
		return TRUE;
	}
	LRESULT OnBnClickedWtlnewCheck(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		DoDataExchange(TRUE);
		GetFunction(m_bNew);
		DoDataExchange(FALSE);
		return 0;
	}
	
};

struct page_wtl_event_peer : page_event_peer
{
	wtl_event_config	m_wev;
	virtual init_tag(tag_token & tag)
	{
		tag.kind = tkMapping;
		tag.bext = true;
		tag.add_head(_T("BEGIN_MSG_MAP"));
		tag.add_head(_T("BEGIN_MSG_MAP_EX"));
		tag.tag.begin = _T("BEGIN_MSG_MAP($CLS)");
		tag.tag.end = _T("END_MSG_MAP();");
		tag.data_kind = tkFunction;
		tag.get_function.bind(this,&page_wtl_event_peer::get_fucntion);
		tag.find_token.bind(this,&page_wtl_event_peer::find_token);
	}
	
	void get_fucntion(Token * tkcls, Token* tk, insert_point* pt, insert_point * ptimpl)
	{
		wtl_event * ev = (wtl_event*)tk->m_Data;
		CString ret;
		CString func;
		CString param;
		CString body;
		if (tk->m_Name == _T("MESSAGE_HANDLER"))
		{
			ret = _T("LRESULT ");
			func = ev->func;
			param =  _T("(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)");
			body = _T("return 0;");
		}
		else if (tk->m_Name.Find(_T("MSG_WM")) == 0)
		{
			ret = ev->ret+_T(" ");
			func = ev->func;
			param = ev->param;
			body = ev->body;
		}
		if (ptimpl == NULL)
		{
			pt->AddLine(ret+func+param);
			pt->AddLine(_T("{"));
			pt->AddLine(body,1);
			pt->AddLine(_T("}"));
		}
		else
		{
			CString	cls = tkcls->m_Name+_T("::");
			pt->AddLine(ret+func+param+_T(";"));
			ptimpl->AddLine(ret+cls+func+param);
			ptimpl->AddLine(_T("{"));
			ptimpl->AddLine(_T("return 0;"),1);
			ptimpl->AddLine(_T("}"));
		}
	}

	virtual bool find_token(Token * tk)
	{
		if (tk->m_Name == _T("MESSAGE_HANDLER") ||
			tk->m_Name == _T("MESSAGE_HANDLER_EX") ||
			tk->m_Name == _T("MESSAGE_RANGE_HANDLER") ||
			tk->m_Name == _T("MESSAGE_RANGE_HANDLER_EX") )
		{
			return true;
		}
		else if (tk->m_Name.Find(_T("MSG_WM")) == 0)
		{
			return true;
		}
		return false;
	}
	virtual Token * add_token_dlg(codeparser * pcode, Token * tkcls, wtl_event * ev)
	{
		dlg_wtl_event_dialog dlg;
		dlg.m_ev = ev;
		if (dlg.DoModal() == IDOK)
		{
			Token * tk = NULL;
			if (!dlg.m_bNew)
			{
				tk = pcode->AddTokenMappingArgs2(tkcls,_T("MESSAGE_HANDLER"),ev->msg,ev->func);
			}
			else
			{
				tk = pcode->AddTokenMappingArgs1(tkcls,ev->ext,ev->func);
			}
			if (tk)
			{
				tk->m_Data = ev;
			}
			return tk;
		}
		return NULL;
	}

	virtual int	add_tklist(HWND hWndList, Token * tk)
	{
		CListBox list(hWndList);
		CString name, args;
		HelperGetTokenTag(tk,name,args);
		int index = -1;
		if (name.Find(_T("MSG_WM")) == 0)
		{
			name = name.Right(name.GetLength()-4);
			index = list.AddString(name+_T(";<WTL>;")+args);
		}
		else
		{
			CAtlArray<CString> array;
			StringToArray(args,array,_T(","));
			if (array.GetCount() == 2)
			{
				index = list.AddString(array[0]+_T(";<ATL>;")+array[1]);
			}
		}
		if (index != -1)
		{
			list.SetItemData(index,(DWORD)tk);
		}
		return index;
	}
	virtual bool init_event(HWND hWndList)
	{
		if (!m_wev.loadex(GetModulePath(_Module.m_hInst)+_T("\\wtlevent.ini")))
		{
			return false;
		}
		CListBox list(hWndList);
		for (size_t i = 0; i < m_wev.m_items.GetCount(); i++)
		{
			wtl_event & ev = m_wev.m_items[i];
			int index = list.AddString(ev.msg);
			list.SetItemData(index,(DWORD)&ev);
		}
		return true;
	}
};

class page_wtl_event : public page_event_template
{
public:
	tag_token	m_tag;
public:
	page_wtl_event()
	{
		m_peer = new page_wtl_event_peer();
		m_peer->init_tag(m_tag);
	}
	const char * page_name()
	{
		return "WTL Event";
	}
};

#endif