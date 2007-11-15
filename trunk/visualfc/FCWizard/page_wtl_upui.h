#ifndef _PAGE_WTL_UPUI_H_
#define _PAGE_WTL_UPUI_H_

struct page_wtl_upui_peer : page_upui_peer
{
	virtual void init_tag(tag_token & tag)
	{
		tag.kind = tkMapping;
		tag.bext = true;
		tag.add_body(_T("UPDATE_ELEMENT"));
		tag.add_head(_T("BEGIN_UPDATE_UI_MAP"));
		tag.tag.begin = _T("BEGIN_UPDATE_UI_MAP($CLS)");
		tag.tag.end = _T("END_UPDATE_UI_MAP();");
	}
	virtual bool find_token(Token * tk)
	{
		if (tk->m_TokenKind == tkMapping &&
			tk->m_Name == _T("UPDATE_ELEMENT"))
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
		//	UPDATE_ELEMENT(ID_VIEW_TOOLBAR, UPDUI_MENUPOPUP)
			Token * tk = pcode->AddTokenMappingArgs2(tkcls,_T("UPDATE_ELEMENT"),res->m_ID,dlg.m_upui);
			return tk;
		}
		return NULL;
	}
};

class page_wtl_upui : public page_upui_template
{
public:
	page_wtl_upui()
	{
		m_peer = new page_wtl_upui_peer();
		m_peer->init_tag(m_tag);
	}
	const char * page_name()
	{
		return "WTL UpdateUI";
	}
};

#endif