#ifndef _PAGE_WINX_UPUI_H_
#define _PAGE_WINX_UPUI_H_

struct page_winx_upui_peer : page_upui_peer
{
	virtual void init_tag(tag_token & tag)
	{
		tag.kind = tkMapping;
		tag.bext = false;
		tag.add_body(_T("WINX_UPDATEUI"));
		tag.add_head(_T("WINX_UPDATEUI_BEGIN"));
		tag.tag.begin = _T("WINX_UPDATEUI_BEGIN()");
		tag.tag.end = _T("WINX_UPDATEUI_END();");
	}
	virtual bool find_token(Token * tk)
	{
		if (tk->m_TokenKind == tkMapping &&
			tk->m_Name == _T("WINX_UPDATEUI"))
		{
			return true;
		}
		return false;
	}

	virtual Token * add_token_dlg(codeparser * pcode, Token * tkcls, ResBase * res)
	{
		dlg_add_upui dlg;
		dlg.m_objectid = res->m_ID;
		dlg.m_res = res;
		if (dlg.DoModal() == IDOK && !dlg.m_upui.IsEmpty())
		{
			Token * tk = pcode->AddTokenMappingArgs2(tkcls,_T("WINX_UPDATEUI"),res->m_ID,dlg.m_upui);
			return tk;
		}
		return NULL;
	}
};

class page_winx_upui : public page_upui_template
{
public:
	page_winx_upui()
	{
		m_peer = new page_winx_upui_peer();
		m_peer->init_tag(m_tag);
	}
	const char * page_name()
	{
		return "Winx UpdateUI";
	}
};

#endif