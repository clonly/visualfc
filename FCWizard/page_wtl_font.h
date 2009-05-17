#ifndef _PAGE_WTL_FONT_H_
#define _PAGE_WTL_FONT_H_

struct page_wtl_font_peer : page_font_peer
{
	virtual init_tag(tag_token & tag)
	{
		tag.kind = tkMapping;
		tag.bext = true;
		tag.add_body(_T("DLGFONT_DIALOG"));
		tag.add_body(_T("DLGFONT_DIALOG_EX"));
		tag.add_body(_T("DLGFONT_CONTROL"));
		tag.add_body(_T("DLGFONT_CONTROL_EX"));
		tag.add_head(_T("BEGIN_DLGFONT_MAP"));
		tag.tag.begin = _T("BEGIN_DLGFONT_MAP($CLS)");
		tag.tag.end = _T("END_DLGFONT_MAP()");
	}
	virtual Token * add_font_dlg(codeparser * pcode, Token * tkcls, ResControl * ctrl, bool bdlg)
	{
		HFONT hf = AtlGetDefaultGuiFont();
		CLogFont lf(hf);
		CFontDialog dlg(&lf);
		if (dlg.DoModal() == IDOK)
		{
			CString font;
			font.Format(_T("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,_T(\"%s\")"),
				lf.lfHeight,
				lf.lfWidth,
				lf.lfEscapement,
				lf.lfOrientation,
				lf.lfWeight,
				lf.lfItalic,
				lf.lfUnderline,
				lf.lfStrikeOut,
				lf.lfCharSet,
				lf.lfOutPrecision,
				lf.lfClipPrecision,
				lf.lfQuality,
				lf.lfPitchAndFamily,
				lf.lfFaceName);
			Token * tk = NULL;
			if (bdlg)
			{
				tk = pcode->AddTokenArgs2(tkcls,_T("DLGFONT_DIALOG_EX"),font,_T(""));
			}
			else
			{
				tk = pcode->AddTokenArgs2(tkcls,_T("DLGFONT_CONTROL_EX"),ctrl->m_ID,font);
			}
			return tk;
		}
		return NULL;
	}
};

class page_wtl_font : public page_font_template
{
public:
	page_wtl_font()
	{
		m_peer = new page_wtl_font_peer();
		m_peer->init_tag(m_tag);
	}
	const char * page_name() 
	{ 
		return _T("WTL Font"); 
	}
};


#endif