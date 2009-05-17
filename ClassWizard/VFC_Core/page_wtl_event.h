#ifndef _PAGE_WTL_EVENT_H_
#define _PAGE_WTL_EVENT_H_

#include "wtl_event.h"

class dlg_wtl_event_dialog  : public ui_simple_dialog_t<dlg_wtl_event_dialog, IDD_ADD_WTLEVENT_DIALOG>,
							  public CWinDataExchange<dlg_wtl_event_dialog>
{
protected:
	BEGIN_MSG_MAP(dlg_wtl_event_dialog)
		COMMAND_ID_HANDLER(IDC_RADIO1, OnMsgTypeRadio)
		COMMAND_ID_HANDLER(IDC_RADIO2, OnMsgTypeRadio)
		COMMAND_ID_HANDLER(IDC_RADIO3, OnMsgTypeRadio)
		CHAIN_MSG_MAP(ui_simple_dialog_base)
	END_MSG_MAP()
	
	wtl_event	* m_ev;
public:
	int	m_nMsgType;
	CString	m_func;
	CString	m_name;
	CString	m_msg;

	BEGIN_DDX_MAP(dlg_wtl_event_dialog)
		DDX_RADIO(IDC_RADIO1, m_nMsgType)
		DDX_TEXT(IDC_MSG_EDIT, m_msg)
		DDX_TEXT(IDC_FUNCNAME_EDIT, m_name)
		DDX_TEXT(IDC_FUNC_EDIT, m_func)
	END_DDX_MAP();

	void GetFunction(BOOL bNewCrack, BOOL bCrack)
	{
		m_msg = m_ev->msg;
		m_name = m_ev->func;
		if (bNewCrack)
		{
			m_func = m_ev->ret + _T(" ") + m_ev->func + m_ev->param;
			m_func += _T("\r\n{");
			if (!m_ev->body.IsEmpty())
			{
				m_func += _T("\r\n\t");
				m_func += m_ev->body;
			}
			m_func += _T("\r\n}");
		}
		else
		{
			m_func =  _T("LRESULT ");
			m_func += m_ev->func;
			m_func += _T("(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)");
			m_func += _T("\r\n{\r\n");
			if (bCrack)
			{
				CSimpleArray<CString> ar;
				StringToArray(m_ev->crack,ar,_T(";"));
				for (int i = 0; i < ar.GetSize(); i++)
				{
					m_func += _T("\t//");
					m_func += ar[i];
					m_func += _T(";\r\n");
				}
			}
			m_func += "\treturn 0;";
			m_func += _T("\r\n}");
		}
	}
	
	void OnInit()
	{
		m_nMsgType = 0;
		GetFunction(FALSE,FALSE);
		DoDataExchange(FALSE);
	}
	BOOL OnClose()	
	{
		DoDataExchange(TRUE);
		return TRUE;
	}

	LRESULT OnMsgTypeRadio(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		DoDataExchange(TRUE);
		if (m_nMsgType == 0)
			GetFunction(FALSE,FALSE);
		else if (m_nMsgType == 1)
			GetFunction(FALSE,TRUE);
		else if (m_nMsgType == 2)
			GetFunction(TRUE,FALSE);
		DoDataExchange(FALSE);
		return 0;
	}
	
};

struct page_wtl_event_peer : page_event_peer
{
	int					m_nMsgType;
	virtual init_tag(tag_token & tag)
	{
		m_nMsgType = 0;
		tag.kind = tkMapping;
		tag.bext = true;
		tag.add_head(_T("BEGIN_MSG_MAP"));
		tag.add_head(_T("BEGIN_MSG_MAP_EX"));
		tag.tag.begin = _T("BEGIN_MSG_MAP($CLS)");
		tag.tag.end = _T("END_MSG_MAP()");
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
		insert_point * p = NULL;
		if (ptimpl == NULL)
		{
			pt->AddLine();
			pt->AddLine(ret+func+param);
			p = pt;
		}
		else
		{
			CString	cls = tkcls->m_Name+_T("::");
			pt->AddLine(ret+func+param+_T(";"));
			ptimpl->AddLine();
			ptimpl->AddLine(ret+cls+func+param);
			p = ptimpl;
		}
		if (p != NULL)
		{
			p->AddLine(_T("{"));
			if (tk->m_Int == 1)
			{
				CSimpleArray<CString> ar;
				StringToArray(ev->crack,ar,_T(";"));
				CString tmp;
				for (int i = 0; i < ar.GetSize(); i++)
				{
					tmp = _T("//");
					tmp += ar[i];
					tmp += _T(";");
					p->AddLine(tmp,1);
				}
			}
			if (!body.IsEmpty())
				p->AddLine(body,1);
			p->AddLine(_T("}"));
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
		dlg.m_nMsgType = m_nMsgType;
		if (dlg.DoModal() == IDOK)
		{
			Token * tk = NULL;
			if (dlg.m_nMsgType == 0)
			{
				tk = pcode->AddTokenMappingArgs2(tkcls,_T("MESSAGE_HANDLER"),ev->msg,ev->func);
			}
			else if (dlg.m_nMsgType == 1)
			{
				tk = pcode->AddTokenMappingArgs2(tkcls,_T("MESSAGE_HANDLER"),ev->msg,ev->func);
			}
			else if (dlg.m_nMsgType == 2)
			{
				tk = pcode->AddTokenMappingArgs1(tkcls,ev->ext,ev->func);
			}
			if (tk)
			{
				//curstom int
				m_nMsgType = dlg.m_nMsgType;
				tk->m_Int = dlg.m_nMsgType;
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
	page_wtl_event_peer()
	{
	}
	virtual bool init_event(codeparser * pcode, HWND hWndTree, HWND hWndList, CAtlArray<HTREEITEM> * pItems)
	{
		CListBox list(hWndList);
		for (size_t i = 0; i < pcode->m_wtlev.m_items.GetCount(); i++)
		{
			wtl_event & ev = pcode->m_wtlev.m_items[i];
			int index = list.AddString(ev.msg);
			list.SetItemData(index,(DWORD)&ev);
		}
		CTreeViewCtrl tree(hWndTree);
		for (size_t i = 0; i < pcode->m_wtlev.m_kinds.GetCount(); i++)
		{
			wtl_kind & kind = pcode->m_wtlev.m_kinds[i];
			HTREEITEM item = tree.InsertItem(kind.kind,TVI_ROOT,NULL);
			for (int j = 0; j < kind.msgs.GetCount(); j++)
			{
				HTREEITEM it = tree.InsertItem(kind.msgs[j],item,NULL);
				for (int k = 0; k < pcode->m_wtlev.m_items.GetCount(); k++)
				{
					wtl_event & ev = pcode->m_wtlev.m_items[k];
					if (kind.msgs[j] == ev.msg)
					{
						tree.SetItemData(it,(DWORD)&ev);
						pItems->Add(it);
						break;
					}
				}
			}
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