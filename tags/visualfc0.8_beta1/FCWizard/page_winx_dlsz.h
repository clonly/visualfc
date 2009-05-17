#ifndef _PAGE_WINX_DLSZ_H_
#define _PAGE_WINX_DLSZ_H_

TCHAR table_resize[3][20] = {
	_T("ResizeX"),
	_T("ResizeY"),
	_T("ResizeAll")
};

TCHAR table_anchor[4][20] = {
	_T("AnchorRightTop"),
	_T("AnchorLeftBottom"),
	_T("AnchorRightBottom"),
	_T("AnchorAll")
};

class dlg_winx_edit_dlsz : public ui_simple_dialog_t<dlg_winx_edit_dlsz,IDD_WINX_EDIT_DLSZ_DIALOG>
{
public:
	CString id;
	CString resize;
	CString anchor;
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
	BEGIN_MSG_MAP(dlg_winx_edit_dlsz)
		COMMAND_RANGE_HANDLER(IDC_RESIZE_X, IDC_RESIZE_ALL, OnResizeRange)
		COMMAND_RANGE_HANDLER(IDC_ANCHOR_RT, IDC_ANCHOR_ALL, OnAnchorRange)
		CHAIN_MSG_MAP(ui_simple_dialog_base)
	END_MSG_MAP()	

	LRESULT OnResizeRange(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CButton btn = GetDlgItem(wID);
		if (btn.GetCheck() == TRUE)
			CheckRadioButton(IDC_RESIZE_X,IDC_RESIZE_ALL,wID);
		resize = table_resize[wID-IDC_RESIZE_X];
		return 0;
	}
	LRESULT OnAnchorRange(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CButton btn = GetDlgItem(wID);
		if (btn.GetCheck() == TRUE)
			CheckRadioButton(IDC_ANCHOR_RT,IDC_ANCHOR_ALL,wID);
		anchor = table_anchor[wID-IDC_ANCHOR_RT];
		return 0;
	}

	BOOL OnClose()
	{
		if (!resize.IsEmpty())
			dlsz = resize;
		if (!anchor.IsEmpty()) 
		{
			if (!resize.IsEmpty())
				dlsz += _T(" | ");
			dlsz += anchor;
		}
		return TRUE;
	}
};

struct page_winx_dlsz_peer : public page_dlsz_peer
{
	virtual void init_tag(tag_token & tag)
	{
		tag.kind = tkMapping;
		tag.bext = false;
		tag.add_body(_T("WINX_DLGRESIZE"));
		tag.add_head(_T("WINX_DLGRESIZE_BEGIN"));
		tag.tag.begin = _T("WINX_DLGRESIZE_BEGIN(TRUE)");
		tag.tag.end = _T("WINX_DLGRESIZE_END();");
	}
	virtual Token * add_token_dlg(codeparser * pcode, Token * tkcls, ResControl * ctrl)
	{
		dlg_winx_edit_dlsz dlg;
		dlg.id = ctrl->m_ID;
		if (dlg.DoModal() == IDOK && !dlg.dlsz.IsEmpty())
		{
			Token * tk = pcode->AddTokenArgs2(tkcls,_T("WINX_DLGRESIZE"),dlg.id,dlg.dlsz);
			return tk;
		}
		return NULL;
	}
};

class page_winx_dlsz : public page_dlsz_template
{
public:
	page_winx_dlsz()
	{
		m_peer = new page_winx_dlsz_peer();
		m_peer->init_tag(m_tag);
	}
	const char * page_name() 
	{ 
		return _T("Winx Resize"); 
	}
};

#endif //_PAGE_WINX_DLSZ_H_