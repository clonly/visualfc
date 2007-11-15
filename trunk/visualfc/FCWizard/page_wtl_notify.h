#ifndef _PAGE_WTL_NOTIFY_H_
#define _PAGE_WTL_NOTIFY_H_

struct page_wtl_notify_peer : page_notify_peer
{
	virtual void init_tag(tag_token & tag)
	{
		tag.kind = tkMapping;
		tag.bext = true;
		tag.data_kind = tkFunction;
		tag.add_body(_T("COMMAND_HANDLER"));
		tag.add_body(_T("COMMAND_ID_HANDLER"));
		tag.add_body(_T("COMMAND_CODE_HANDLER"));
		tag.add_body(_T("COMMAND_RANGE_HANDLER"));
		tag.add_body(_T("NOTIFY_HANDLER"));
		tag.add_body(_T("NOTIFY_ID_HANDLER"));
		tag.add_body(_T("NOTIFY_CODE_HANDLER"));
		tag.add_body(_T("NOTIFY_HANDLER"));
		tag.add_body(_T("NOTIFY_RANGE_HANDLER"));
		tag.add_head(_T("BEGIN_MSG_MAP"));
		tag.add_head(_T("BEGIN_MSG_MAP_EX"));
		tag.tag.begin = _T("BEGIN_MSG_MAP($CLS)");
		tag.tag.end = _T("END_MSG_MAP()");
		tag.get_function.bind(this,&page_wtl_notify_peer::get_function);
	}
	void get_function(Token * tkcls, Token * tk, insert_point * pt, insert_point * ptimpl)
	{
		CString ret;
		CString func;
		CString param;
		CString body;
		if (tk->m_Name == _T("COMMAND_ID_HANDLER") ||
			tk->m_Name == _T("COMMAND_HANDLER") )
		{
			ret = _T("LRESULT ");
			func = tk->m_String;
			param = _T("(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)");
			body = _T("return 0;");
		}
		else if (tk->m_Name == _T("NOTIFY_HANDLER") ||
			tk->m_Name == _T("NOTIFY_ID_HANDLER"))
		{
			ret = _T("LRESULT ");
			func = tk->m_String;
			param = _T("(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)");
			body = _T("return 0");
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

	virtual Token * add_notify_dlg(codeparser * pcode, Token * tkcls, win32_notify_code * wnc, LPCTSTR id, bool bMenu)
	{
		dlg_add_notify dlg;
		dlg.m_notify = _T("Message: ")+wnc->code;
		dlg.m_objectid = _T("Object ID: ")+(CString)id;
		dlg.m_function = wnc->func+GetIDFunctionName(id);
		if (dlg.DoModal() == IDOK)
		{
			Token * tk = NULL;
			if (wnc->code == _T("COMMAND"))
			{
				tk = pcode->AddTokenArgs2(tkcls,_T("COMMAND_ID_HANDLER"),id,dlg.m_function);
			}
			else if (wnc->kind == wkCOMMAND)
			{
				tk = pcode->AddTokenArgs2(tkcls,_T("COMMAND_HANDLER"),id,wnc->code,dlg.m_function);
			}
			else if (wnc->kind == wkNOTIFY)
			{
				tk = pcode->AddTokenArgs2(tkcls,_T("NOTIFY_HANDLER"),id,wnc->code,dlg.m_function);
			}
			if (tk)
			{
				tk->m_String = dlg.m_function;
			}
			return tk;
		}
		return NULL;
	}
};

class page_wtl_notify : public page_notify_template
{
public:
	const char * page_name()
	{
		return "WTL Notify";
	}
public:
	page_wtl_notify()
	{
		m_peer = new page_wtl_notify_peer();
		m_peer->init_tag(m_tag);
	}
};

#endif