#ifndef _PAGE_WINX_DDX_H_
#define _PAGE_WINX_DDX_H_

struct page_winx_ddx_peer : public page_ddx_peer
{
	virtual void init_tag(tag_token & tag)
	{
		tag.kind = tkMapping;
		tag.bext = true;
	//	tag.add_body(_T("DDX_CONTROL"));
	//	tag.add_body(_T("DDX_CONTROL_HANDLE"));
		tag.add_body(_T("WINX_DDX_TEXT"));
		tag.add_body(_T("WINX_DDX_TEXT_LEN"));
		tag.add_body(_T("WINX_DDX_INT"));
		tag.add_body(_T("WINX_DDX_INT_RANGE"));
		tag.add_body(_T("WINX_DDX_UINT"));
		tag.add_body(_T("WINX_DDX_UINT_RANGE"));
		tag.add_body(_T("WINX_DDX_FLOAT"));
		tag.add_body(_T("WINX_DDX_FLOAT_RANGE"));
		tag.add_body(_T("WINX_DDX_FLOAT_P"));
		tag.add_body(_T("WINX_DDX_FLOAT_P_RANGE"));	
		tag.add_body(_T("WINX_DDX_CHECK"));	
		tag.add_body(_T("WINX_DDX_RADIO"));	
		tag.add_head(_T("WINX_DDX_BEGIN"));
		tag.tag.begin = _T("WINX_DDX_BEGIN()");
		tag.tag.end = _T("WINX_DDX_END();");
	}
	virtual Token * add_token_dlg(codeparser * pcode, Token * tkcls, ResControl * ctrl)
	{
		
		dlg_add_ddx dlg;
		
		dlg.m_id = ctrl->m_ID;
		dlg.m_wn = pcode->m_notify.get_notify_by_res(ctrl->m_Type);
		dlg.m_res = ctrl;
		dlg.get_var_type.bind(this,&page_winx_ddx_peer::get_var_type);
		dlg.get_ddx_type.bind(this,&page_winx_ddx_peer::get_ddx_type);
		if (dlg.m_wn && dlg.DoModal() == IDOK && !dlg.m_var.IsEmpty())
		{
			Token * tk = NULL;
			if (dlg.m_blen)
				tk = pcode->AddTokenMappingArgs3(tkcls,dlg.m_ddxtype,dlg.m_id,dlg.m_var,dlg.m_len);
			else if (dlg.m_brange)
				tk = pcode->AddTokenMappingArgs4(tkcls,dlg.m_ddxtype,dlg.m_id,dlg.m_var,dlg.m_min,dlg.m_max);
			else
				tk = pcode->AddTokenMappingArgs2(tkcls,dlg.m_ddxtype,dlg.m_id,dlg.m_var);
			//add type var
			if (tk)
			{
				Token * tkvar = pcode->AddTokenVarible(tkcls,dlg.m_vartype,dlg.m_var);
			}
			return tk;
		}
		return NULL;
	}
protected:
	void get_ddx_type(win32_notify * wn, ResControl * res, std::vector<CString> & array)
	{
	//	array.push_back(_T("DDX_CONTROL_HANDLE"));
	//	array.push_back(_T("DDX_CONTROL"));


		if (wn->name.CompareNoCase(_T("Edit")) == 0 || 
			wn->name.CompareNoCase(_T("Static")) == 0)
		{
			array.push_back(_T("WINX_DDX_TEXT"));
			array.push_back(_T("WINX_DDX_TEXT_LEN"));
			array.push_back(_T("WINX_DDX_INT"));
			array.push_back(_T("WINX_DDX_INT_RANGE"));
			array.push_back(_T("WINX_DDX_UINT"));
			array.push_back(_T("WINX_DDX_UINT_RANGE"));
			array.push_back(_T("WINX_DDX_FLOAT"));
			array.push_back(_T("WINX_DDX_FLOAT_RANGE"));
			array.push_back(_T("WINX_DDX_FLOAT_P"));
			array.push_back(_T("WINX_DDX_FLOAT_P_RANGE"));
		}
		else if (res->m_Create.Find(_T("BS_AUTOCHECKBOX")) != -1 || 
			res->m_Create.Find(_T("BS_CHECKBOX")) != -1 ||
			res->m_Create.Find(_T("BS_3STATE")) != -1 || 
			res->m_Create.Find(_T("BS_AUTO3STATE")) != -1)
		{
			array.push_back(_T("WINX_DDX_CHECK"));
		}
		else if (res->m_Create.Find(_T("BS_AUTORADIOBUTTON")) != -1 || 
			res->m_Create.Find(_T("BS_RADIOBUTTON")) != -1)
		{
			array.push_back(_T("WINX_DDX_CHECK"));
			array.push_back(_T("WINX_DDX_RADIO"));
		}	
	}

	void get_var_type(win32_notify * wn, const CString & ddx_type, std::vector<CString> & array)
	{
		if (ddx_type.Find(_T("CONTROL")) != -1)
		{
			for (int i = 0; i < wn->ddxwords.GetCount(); i++)
			{
				array.push_back(wn->ddxwords[i]);
			}
		}
		else if (ddx_type.Find(_T("TEXT")) != -1)
		{
			array.push_back(_T("winx::CString"));
			array.push_back(_T("CComBSTR"));
			array.push_back(_T("BSTR"));
			array.push_back(_T("LPTSTR"));
		}
		else if (ddx_type.Find(_T("INT")) != -1)
		{
			array.push_back(_T("int"));
			array.push_back(_T("short"));
			array.push_back(_T("long"));
		}
		else if (ddx_type.Find(_T("UINT")) != -1)
		{
			array.push_back(_T("UINT"));
			array.push_back(_T("DWORD"));
			array.push_back(_T("WORD"));
			array.push_back(_T("ULONG"));
		}
		else if (ddx_type.Find(_T("FLOAT")) != -1)
		{
			array.push_back(_T("float"));
			array.push_back(_T("double"));
		}
		else if (ddx_type.Find(_T("CHECK")) != -1)
		{
			array.push_back(_T("BOOL"));
			array.push_back(_T("bool"));
			array.push_back(_T("int"));
		}
		else if (ddx_type.Find(_T("RADIO")) != -1)
		{
			array.push_back(_T("int"));
		}	
	}
};

class page_winx_ddx : public page_ddx_template
{
public:
	page_winx_ddx()
	{
		m_peer = new page_winx_ddx_peer();
		m_peer->init_tag(m_tag);
	}
	const char * page_name() 
	{ 
		return _T("Winx DDX"); 
	}
};


#endif