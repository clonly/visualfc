#ifndef _PAGE_WTL_DLSZ_H_
#define _PAGE_WTL_DLSZ_H_


TCHAR wtl_resize[][20] = {
	_T("DLSZ_SIZE_X"),
	_T("DLSZ_SIZE_Y"),
	_T("DLSZ_MOVE_X"),
	_T("DLSZ_MOVE_Y"),
	_T("DLSZ_CENTER_X"),
	_T("DLSZ_CENTER_Y"),
	_T("DLSZ_REPAINT")
};

class dlg_wtl_edit_dlsz : public ui_simple_dialog_t<dlg_wtl_edit_dlsz,IDD_WTL_EDIT_DLSZ_DIALOG>
{
public:
	CString id;
	CString dlsz;

	void OnInit()
	{
		CComboBox box = GetDlgItem(IDC_OBJECTID_COMBO);
		if (!id.IsEmpty())
		{
			box.AddString(id);
			box.SetCurSel(0);
		}
	}

	BOOL OnClose()
	{
		for (int i = 0; i < 7; i++)
		{
			CButton btn = GetDlgItem(IDC_CHECK1+i);
			if (btn.GetCheck() == TRUE)
			{
				if (!dlsz.IsEmpty())
				{
					dlsz += _T(" | ");
				}
				dlsz += wtl_resize[i];
			}
		}
		return TRUE;
	}
};

struct page_wtl_dlsz_peer : public page_dlsz_peer
{
	virtual void init_tag(tag_token & tag)
	{
		tag.kind = tkMapping;
		tag.bext = true;
		tag.add_body(_T("DLGRESIZE_CONTROL"));
		tag.add_body(_T("BEGIN_DLGRESIZE_GROUP"));
		tag.add_body(_T("END_DLGRESIZE_GROUP"));
		tag.add_head(_T("BEGIN_DLGRESIZE_MAP"));
		tag.tag.begin = _T("BEGIN_DLGRESIZE_MAP($CLS)");
		tag.tag.end = _T("END_DLGRESIZE_MAP()");
	}
	virtual Token * add_token_dlg(codeparser * pcode, Token * tkcls, ResControl * ctrl)
	{
		dlg_wtl_edit_dlsz dlg;
		dlg.id = ctrl->m_ID;
		if (dlg.DoModal() == IDOK && !dlg.dlsz.IsEmpty())
		{
			Token * tk = pcode->AddTokenArgs2(tkcls,_T("DLGRESIZE_CONTROL"),dlg.id,dlg.dlsz);
			return tk;
		}
		return NULL;
	}
};

class page_wtl_dlsz : public page_dlsz_template
{
public:
	page_wtl_dlsz()
	{
		m_peer = new page_wtl_dlsz_peer();
		m_peer->init_tag(m_tag);
	}
	const char * page_name() 
	{ 
		return _T("WTL Resize"); 
	}
};


#endif