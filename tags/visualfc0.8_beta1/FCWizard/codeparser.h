#ifndef _CODEPARSER_H__
#define _CODEPARSER_H__

//Code::Blocks Common
#include "./cbparser/parserthread.h"
//WTLHelper Common
#include "./resources/reshelper.h"
#include "./resources/Resources.h"
//
#include "./winx_event.h"
#include "./win32_notify.h"

inline CString get_file_name(const CString & filename)
{
	int i = filename.ReverseFind(_T('\\'));
	if (i != -1) 
	{
		return filename.Right(filename.GetLength()-i-1);
	}
	return _T("");
}

inline CString get_file_ext(const CString & filename)
{
	int i = filename.ReverseFind(_T('.'));
	if (i != -1) 
	{
		return filename.Right(filename.GetLength()-i);
	}
	return _T("");
}

//type: void process(CResDialog*)
template <typename Array, typename FUNC>
bool HelperEnumArray(Array & ar, FUNC & Process)
{
	for (size_t i = 0; i < ar.GetCount(); i++)
	{
		Process(&ar[i]);
	}
	return true;
}

struct parser_win32res
{
	CResources m_Res;
	// parser enum { IDD = IDD_MAINDLG };
	CString GetClassEnumIDD(Token * tkcls)
	{
		for (size_t i = 0; i < tkcls->m_Children.GetCount(); i++)
		{
			Token * tk = tkcls->m_Children[i];
			if (tk->m_TokenKind == tkEnum && 
				tk->m_Children.GetCount() ==1) 
			{
				Token * tkidd = tk->m_Children[0];
				if (tkidd->m_Name == _T("IDD")) 
				{
					return (LPCTSTR)(tkidd->m_Args);
				}
			}
		}
		return _T("");
	}

	// 1. enum { IDD = IDD_MAINDLG };
	// 2. CMainDlg : public winx::ModelDialog<CMainDlg, IDD_MAINDLG>
	CResDialog * GetResDialog(Token * tkcls)
	{
		CString id = GetClassEnumIDD(tkcls);
		for (size_t i = 0; i < m_Res.m_Dialogs.GetCount(); i++)
		{
			CResDialog & dlg = m_Res.m_Dialogs[i];
			if ((!id.IsEmpty() && id == dlg.m_ID) ||
				(tkcls->m_AncestorsString.Find(dlg.m_ID) != -1) )
			{
				return &dlg;
			}
		}
		return NULL;
	}

	//
	CResMenu * GetResDialogMenu(LPCTSTR menuID)
	{
		for (size_t i = 0; i < m_Res.m_Menus.GetCount(); i++)
		{
			const CResMenu & menu = m_Res.m_Menus.GetAt(i);
			if (menu.m_ID == menuID)
			{
				return (CResMenu*)&menu;
			}
		}
		return NULL;
	}
	//type: void process(CResDialog*)
	template <typename FUNC>
	bool EnumResDialog(FUNC & Process)
	{
		Helper::EnumArray(m_Res.m_Dialogs,Process);
		return true;
	}
	//type: void process(CResMenu*)
	template <typename FUNC>
	bool EnumResMenu(FUNC & Process)
	{
		for (size_t i = 0; i < m_Res.m_Menus.GetCount(); i++)
		{
			Process(&m_Res.m_Menus[i]);
		}
		return true;
	}

	//type void process(const ResControl*)
	template <typename FUNC>
	bool EnumResDialogControl(const CResDialog * dlg, FUNC & Process)
	{
		for (size_t i = 0; i < dlg->GetCount(); i++)
		{	
			if (dlg->GetAt(i).m_ID != _T("IDC_STATIC"))
				Process(&dlg->GetAt(i));
		}
		return true;
	}
	//type void process(const CResMenu*)
	template <typename FUNC>
	bool EnumResMenuItem(const CResMenu * menu, FUNC & Process)
	{
		for (size_t i = 0; i < menu->GetCount(); i++)
		{
			if (!menu->m_ID.IsEmpty())
				Process(&menu->GetAt(i));
		}
		for (size_t j = 0; j < menu->m_SubMenus.GetCount(); j++)
		{
			const CResMenu & subMenu = menu->m_SubMenus.GetAt(j);
			for (size_t k = 0; k < subMenu.GetCount(); k++)
			{
				if (!subMenu.GetAt(k).m_ID.IsEmpty())
					Process(&subMenu.GetAt(k));
			}
		}
		return true;
	}

	bool LoadRes(LPCTSTR lpszResource,bool bAppend = false)
	{
		return m_Res.Load(lpszResource,bAppend);
	}
};

struct insert_point
{
	CSimpleArray<CString> array;
	int     line;
	bool	bcpp;
	insert_point(bool _bcpp = false) : bcpp(_bcpp)
	{
	}
	void AddNewLine()
	{
		array.Add((CString)_T(""));
	}
	void AddLine(LPCTSTR lpszLine = _T(""), int ntab = 0)
	{
		CString tab;
		for (int i = 0; i < ntab; i++)
			tab += _T("\t");
		array.Add(tab+(CString)lpszLine);
	}
	CString GetText(int ntab = 0)
	{
		CString tab;
		for (int i = 0; i < ntab; i++)
			tab += _T("\t");
		CString text;
		for (int i = 0; i < array.GetSize(); i++)
		{
			text += _T("\r\n");
			text += tab;
			text += array[i];
		}
		return text;
	}
};

class codeparser
{
public:
	CResources m_Res;
	TokensArray m_Tokens;
	winx_event_config	m_winxev;
	win32_notify_config m_notify;
	~codeparser()
	{
		WX_CLEAR_ARRAY(m_Tokens);
		m_Tokens.Clear();
		m_Res.Clear();
	}
public:
	Token * AddTokenMappingArgs1(Token * tkcls, LPCTSTR name, LPCTSTR args1)
	{
		Token * tk = new Token();
		tk->m_Name = name;
		tk->m_TokenKind = tkMapping;
		tk->m_TokenUpdate = tuAddnew;
		tk->m_Args = _T("(");
		tk->m_Args += args1;
		tk->m_Args += _T(")");
		if (tkcls)
		{
			tk->m_pParent = tkcls;
			tkcls->AddChild(tk);
		}
		m_Tokens.Add(tk);
		return tk;
	}
	Token * AddTokenMappingArgs2(Token * tkcls, LPCTSTR name, LPCTSTR args1, LPCTSTR args2)
	{
		Token * tk = new Token();
		tk->m_Name = name;
		tk->m_TokenKind = tkMapping;
		tk->m_TokenUpdate = tuAddnew;
		tk->m_Args = _T("(");
		tk->m_Args += args1;
		tk->m_Args += _T(", ");
		tk->m_Args += args2;
		tk->m_Args += _T(")");
		if (tkcls)
		{
			tk->m_pParent = tkcls;
			tkcls->AddChild(tk);
		}
		m_Tokens.Add(tk);
		return tk;
	}

	Token * AddTokenMappingArgs3(Token * tkcls, LPCTSTR name, LPCTSTR args1, LPCTSTR args2, LPCTSTR args3)
	{
		Token * tk = new Token();
		tk->m_Name = name;
		tk->m_TokenKind = tkMapping;
		tk->m_TokenUpdate = tuAddnew;
		tk->m_Args = _T("(");
		tk->m_Args += args1;
		tk->m_Args += _T(", ");
		tk->m_Args += args2;
		tk->m_Args += _T(", ");
		tk->m_Args += args3;
		tk->m_Args += _T(")");
		if (tkcls)
		{
			tk->m_pParent = tkcls;
			tkcls->AddChild(tk);
		}
		m_Tokens.Add(tk);
		return tk;
	}
	Token * AddTokenMappingArgs4(Token * tkcls, LPCTSTR name, LPCTSTR args1, LPCTSTR args2, LPCTSTR args3, LPCTSTR args4)
	{
		Token * tk = new Token();
		tk->m_Name = name;
		tk->m_TokenKind = tkMapping;
		tk->m_TokenUpdate = tuAddnew;
		tk->m_Args = _T("(");
		tk->m_Args += args1;
		tk->m_Args += _T(", ");
		tk->m_Args += args2;
		tk->m_Args += _T(", ");
		tk->m_Args += args3;
		tk->m_Args += _T(", ");
		tk->m_Args += args4;
		tk->m_Args += _T(")");
		if (tkcls)
		{
			tk->m_pParent = tkcls;
			tkcls->AddChild(tk);
		}
		m_Tokens.Add(tk);
		return tk;
	}


	Token * AddTokenArgs2(Token * tkcls, LPCTSTR name, LPCTSTR args1, LPCTSTR args2 = NULL, LPCTSTR args3 = NULL, TokenKind = tkMapping)
	{
		Token * tk = new Token();
		tk->m_Name = name;
		tk->m_TokenKind = tkMapping;
		tk->m_TokenUpdate = tuAddnew;
		tk->m_Args = _T("(");
		tk->m_Args += args1;
		if (lstrlen(args2) != 0)
		{
			tk->m_Args += _T(", ");
			tk->m_Args += args2;
		}
		if (lstrlen(args3) != 0)
		{
			tk->m_Args += _T(", ");
			tk->m_Args += args3;
		}
		tk->m_Args += _T(")");
		if (tkcls)
		{
			tk->m_pParent = tkcls;
			tkcls->AddChild(tk);
		}
		m_Tokens.Add(tk);
		return tk;
	}

	Token * AddTokenVarible(Token * tkcls, LPCTSTR type, LPCTSTR var)
	{
		Token * tk = new Token();
		tk->m_Name = var;
		tk->m_Type = type;
		tk->m_TokenKind = tkVariable;
		tk->m_TokenUpdate = tuAddnew;
		if (tkcls)
		{
			tk->m_pParent = tkcls;
			tkcls->AddChild(tk);
		}
		m_Tokens.Add(tk);
		return tk;
	}

	Token * FindTokenVarible(Token * tkcls, LPCTSTR var)
	{
		for (size_t i = 0; i < tkcls->m_Children.GetCount(); i++) {
			Token * tk = tkcls->m_Children[i];
			if (tk->m_TokenKind == tkVariable &&
				(CString)tk->m_Name == (CString)var) 
			{
				return tk;
			}
		}
		return NULL;
	}

	bool RemoveToken(Token * tk)
	{
		Token * tkcls = tk->m_pParent;
		if (tk->m_TokenUpdate == tuAddnew)
		{
			if (tkcls)
				tkcls->RemoveChild(tk);
			m_Tokens.Remove(tk);
			return true;
		}
		else if (tk->m_TokenUpdate == tuNormal)
		{
			tk->m_TokenUpdate = tuRemove;
			return true;
		}
		return false;
	}

	//type bool ask(Token*)
	template <typename FUNC>
	bool WinxRemoveNotifyToken(Token * tk, FUNC & AskRemove)
	{
		//is addnew token remove it
		if (tk->m_TokenUpdate == tuAddnew)
		{
			if (tk->m_pParent != NULL)
			{
				tk->m_pParent->RemoveChild(tk);
			}
			m_Tokens.Remove(tk);
			return true;
		}
		//is extern token set flag remove
		else if (tk->m_TokenUpdate == tuNormal)
		{
			if (AskRemove(tk) == true)
			{
				tk->m_TokenUpdate = tuRemove;
				return true;
			}
		}
		return false;
	}

	bool WinxRemoveDialogResizeToken(Token * tk)
	{
		Token * tkcls = tk->m_pParent;
		if (tk->m_TokenUpdate == tuAddnew)
		{
			if (tkcls)
				tkcls->RemoveChild(tk);
			m_Tokens.Remove(tk);
			return true;
		}
		else if (tk->m_TokenUpdate == tuNormal)
		{
			tk->m_TokenUpdate = tuRemove;
			return true;
		}
		return false;
	}

	Token * WinxAddDialogResizeToken(Token * tkcls, LPCTSTR id, LPCTSTR dlsz)
	{
		Token * tk = new Token();
		tk->m_Name = _T("WINX_DLGRESIZE");
		tk->m_TokenKind = tkMapping;
		tk->m_TokenUpdate = tuAddnew;
		tk->m_Args = _T("(");
		tk->m_Args += id;
		tk->m_Args += _T(",");
		tk->m_Args += dlsz;
		tk->m_Args += _T(")");
		if (tkcls)
		{
			tk->m_pParent = tkcls;
			tkcls->AddChild(tk);
		}
		m_Tokens.Add(tk);
		return tk;
	}
	Token * AddDialogFontToken(Token * tkcls, LPCTSTR name, LPCTSTR id, LOGFONT & lf, bool bdlg)
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
		Token * tk = new Token();
		tk->m_Name = name;
		tk->m_TokenKind = tkMapping;
		tk->m_TokenUpdate = tuAddnew;
		tk->m_Args = _T("(");
		if (bdlg == false)
		{
			tk->m_Args += id;
			tk->m_Args += _T(",");
		}
		tk->m_Args += font;
		tk->m_Args += _T(")");
		if (tkcls)
		{
			tk->m_pParent = tkcls;
			tkcls->AddChild(tk);
		}
		m_Tokens.Add(tk);
		return tk;
	}

	Token * WinxAddDialogFontToken(Token * tkcls, LPCTSTR id, LOGFONT & lf, int flag)
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
		Token * tk = new Token();
		if (flag == 0)
			tk->m_Name = _T("WINX_DLGFONT_EX");
		else
			tk->m_Name = _T("WINX_DLGFONT_DIALOG_EX");
		tk->m_TokenKind = tkMapping;
		tk->m_TokenUpdate = tuAddnew;
		tk->m_Args = _T("(");
		if (flag == 0)
		{
			tk->m_Args += id;
			tk->m_Args += _T(",");
		}
		tk->m_Args += font;
		tk->m_Args += _T(")");
		if (tkcls)
		{
			tk->m_pParent = tkcls;
			tkcls->AddChild(tk);
		}
		m_Tokens.Add(tk);
		return tk;
	}
	bool WinxRemoveDialogFontToken(Token * tk)
	{
		Token * tkcls = tk->m_pParent;
		if (tk->m_TokenUpdate == tuAddnew)
		{
			if (tkcls)
				tkcls->RemoveChild(tk);
			m_Tokens.Remove(tk);
			return true;
		}
		else if (tk->m_TokenUpdate == tuNormal)
		{
			tk->m_TokenUpdate = tuRemove;
			return true;
		}
		return false;
	}
	Token * WinxAddNotifyToken(win32_notify_code * wnc, Token * tkcls, LPCSTR id, LPCTSTR func, bool bMenu)
	{
		Token * tk = new Token();

		if (wnc->code == _T("COMMAND"))
		{
			tk->m_Name = _T("WINX_CMD");
			tk->m_TokenKind = tkMapping;
			tk->m_TokenUpdate = tuAddnew;
			tk->m_Args = _T("(");
			tk->m_Args += id;
			tk->m_Args += _T(",");
			tk->m_Args += func;
			tk->m_Args += _T(")");

			tk->m_String = _T("void ");
			tk->m_String += func;
			tk->m_String += _T("(HWND hWnd)");
		}
		else if (wnc->kind == wkCOMMAND)
		{
			tk->m_Name = _T("WINX_CMD_EX");
			tk->m_Args = _T("(");
			tk->m_Args += id;
			tk->m_Args += _T(",");
			tk->m_Args += wnc->code;
			tk->m_Args += _T(",");
			tk->m_Args += func;
			tk->m_Args += _T(")");

			tk->m_String = _T("void ");
			tk->m_String += func;
			tk->m_String += _T("(HWND hWnd)");
		}
		else if (wnc->kind == wkNOTIFY)
		{
			tk->m_Name = _T("WINX_NOTIFY");
			tk->m_Args = _T("(");
			tk->m_Args += id;
			tk->m_Args += _T(",");
			tk->m_Args += wnc->code;
			tk->m_Args += _T(",");
			tk->m_Args += func;
			tk->m_Args += _T(")");

			tk->m_String = _T("void ");
			tk->m_String += func;
			tk->m_String += _T("(HWND hWnd, LPNMHDR pnmh, LRESULT* pResult)");
		}

		tk->m_TokenKind = tkMapping;
		tk->m_TokenUpdate = tuAddnew;
		//save m_String is func name
		if (tkcls)
		{
			tk->m_pParent = tkcls;
			tkcls->AddChild(tk);
		}
		m_Tokens.Add(tk);
		return tk;
	}

	Token * WinxAddEventToken(winx_event * ev, Token * tkcls)
	{
		//is remove reset flag normal
		for (size_t i = 0; i < tkcls->m_Children.GetCount(); i++) {
			Token * tk = tkcls->m_Children[i];
			if (tk->m_TokenKind == tkFunction &&
				(CString)tk->m_Name == ev->name) {
				if (tk->m_TokenUpdate == tuRemove) {
					tk->m_TokenUpdate = tuNormal;
				}
				return tk;
			}
		}
		//add new token
		Token * tk = new Token();
		tk->m_Name = ev->name;
		if (tkcls)
		{
			tk->m_pParent = tkcls;
			tkcls->AddChild(tk);
		}
		tk->m_TokenKind = tkFunction;
		tk->m_Scope = tsPublic;
		tk->m_TokenUpdate = tuAddnew;
		tk->m_Data = (void*)ev;
		m_Tokens.Add(tk);
		return tk;
	}
	//type bool ask(Token*)
	template <typename FUNC> 
	bool WinxRemoveEventToken(Token * tk_ev, FUNC & AskRemove)
	{
		Token * tkcls = tk_ev->m_pParent;
		for (size_t i = 0; i < tkcls->m_Children.GetCount(); i++) 
		{
			Token * tk = tkcls->m_Children[i];
			if (tk->m_TokenKind == tkFunction &&
				tk->m_Name == tk_ev->m_Name ) 
			{
				if (tk->m_TokenUpdate == tuAddnew) 
				{
					if (tk->m_pParent != NULL) {
						tk->m_pParent->RemoveChild(tk);
					}
					m_Tokens.Remove(tk);
					return true;
				}
				else if (tk->m_TokenUpdate == tuNormal) 
				{
					if (AskRemove(tk) == true)
					{
						tk->m_TokenUpdate = tuRemove;
						return true;
					}
				}
			}
		}
		return false;
	}

	bool WinxIsEventToken(Token * tk)
	{
		for (int i = 0; i < m_winxev.m_items.GetSize(); i++)
		{
			winx_event & ev = m_winxev.m_items[i];
			if (ev.name == CString(tk->m_Name))
			{
				return true;
			}
		}
		return false;
	}
	bool WinxIsCmdToken(Token * tk)
	{
	}
	bool WinxIsNotifyToken(Token * tk)
	{
	}
	bool WinxIsDlszToken(Token * tk)
	{

	}
	bool WinxIsMessageToken(Token * tk)
	{
		if (tk->m_TokenKind != tkMapping)
			return false;
		if ( tk->m_Name == _T("WINX_CMD") ||
			tk->m_Name == _T("WINX_CMD_EX") ||
			tk->m_Name == _T("WINX_CMD_NOARG") ||
			tk->m_Name == _T("WINX_CMD_RANGE") ||
			tk->m_Name == _T("WINX_CMD_NOTIFY") ||
			tk->m_Name == _T("WINX_SYSCMD") ||
			tk->m_Name == _T("WINX_NOTIFY") ||
			tk->m_Name == _T("WINX_NOTIFY_RANGE") )	
		{
			return true;
		}
		return false;
	}
	CString WinxGetNotifyTokenFuncitonName(Token * tk)
	{
		CString tmp = tk->m_Args;
		tmp.TrimLeft(_T("("));
		tmp.TrimRight(_T(")"));
		CAtlArray<CString> array;
		CutString(tmp,array,_T(","));
		if (array.GetCount() == 0)
			return _T("");
		for (int i = array.GetCount()-1; i >= 0; i++)
		{
			CString text = array[i];
			text.TrimLeft();
			text.TrimRight();
			if (!text.IsEmpty())
				return text;
		}
		return _T("");
	}
	//type: void process(Token*)
	template <typename FUNC>
	bool EnumWinxEventToken(Token * tkcls, FUNC & Process)
	{
		for (size_t i = 0; i < tkcls->m_Children.GetCount(); i++)
		{
			Token * tk = tkcls->m_Children[i]; 
			if (tk->m_TokenKind == tkFunction && WinxIsEventToken(tk))
			{
				Process(tk);
			}
		}	
		return true;
	}
	//type: void process(Token*)
	template <typename FUNC>
	bool EnumWinxDialogResizeToken(Token * tkcls, FUNC & Process)
	{
		for (size_t i = 0; i < tkcls->m_Children.GetCount(); i++)
		{
			Token * tk = tkcls->m_Children[i]; 
			if (tk->m_TokenKind == tkMapping && 
				tk->m_TokenUpdate != tuRemove &&
				tk->m_Name == _T("WINX_DLGRESIZE"))
			{
				Process(tk);
			}
		}	
		return true;
	}
	//type: void process(Token*, int flag)
	template <typename FUNC>
	bool EnumWinxDialogFontToken(Token * tkcls, FUNC & Process)
	{
		for (size_t i = 0; i < tkcls->m_Children.GetCount(); i++)
		{
			Token * tk = tkcls->m_Children[i]; 
			if (tk->m_TokenKind == tkMapping && 
				tk->m_TokenUpdate != tuRemove &&
				( tk->m_Name == _T("WINX_DLGFONT") ||
				  tk->m_Name == _T("WINX_DLGFONT_EX")) )
				//  tk->m_Name == _T("WINX_DLGFONT_DIALOG") ||
				//  tk->m_Name == _T("WINX_DLGFONT_DIALOG_EX") )
			{
				Process(tk, 0);
			}
			else if (tk->m_TokenKind == tkMapping && 
					tk->m_TokenUpdate != tuRemove &&
				( tk->m_Name == _T("WINX_DLGFONT_DIALOG") ||
				  tk->m_Name == _T("WINX_DLGFONT_DIALOG_EX")) )
			{
				Process(tk,1);
			}

		}	
		return true;
	}
	//type: void process(Token*)
	template <typename FUNC>
	bool EnumProjectClass(FUNC & Process)
	{
		for (size_t i = 0; i < m_Tokens.GetCount(); i++)
		{
			Token * tk = m_Tokens[i];
			if (tk->m_TokenKind == tkClass)
			{
				Process(tk);
			}
		}
		return true;
	}
	//type: void process(Token*)
	template <typename FUNC>
	bool EnumWinxMessageToken(Token * tkcls, FUNC & Process)
	{
		for (size_t i = 0; i < tkcls->m_Children.GetCount(); i++)
		{
			Token * tk = tkcls->m_Children[i]; 
			if (tk->m_TokenKind ==  tkMapping)
			{
				if (tk->m_Name == _T("WINX_CMD") ||
					tk->m_Name == _T("WINX_CMD_EX") ||
					tk->m_Name == _T("WINX_CMD_NOARG") ||
					tk->m_Name == _T("WINX_CMD_RANGE") ||
					tk->m_Name == _T("WINX_CMD_NOTIFY") ||
					tk->m_Name == _T("WINX_SYSCMD") ||
					tk->m_Name == _T("WINX_NOTIFY") ||
					tk->m_Name == _T("WINX_NOTIFY_RANGE") )			
				{
					Process(tk);
				}
			}
		}
		return true;
	}
	//type: void process(Token*)
	template <typename FUNC>
	bool EnumWinxProperty(Token * tkcls, FUNC & Process)
	{
		for (size_t i = 0; i < tkcls->m_Children.GetCount(); i++)
		{
			Token * tk = tkcls->m_Children[i]; 
			if (tk->m_TokenKind ==  tkMapping)
			{
				if (tk->m_Name == _T("WINX_CMD") ||
					tk->m_Name == _T("WINX_CMD_EX") ||
					tk->m_Name == _T("WINX_CMD_NOARG") ||
					tk->m_Name == _T("WINX_CMD_RANGE") ||
					tk->m_Name == _T("WINX_CMD_NOTIFY") ||
					tk->m_Name == _T("WINX_SYSCMD") ||
					tk->m_Name == _T("WINX_NOTIFY") ||
					tk->m_Name == _T("WINX_NOTIFY_RANGE") ||
					tk->m_Name == _T("WINX_UPDATEUI"))
				{
					continue;
				}
				else
				{
					Process(tk);
				}
			}
		}
		return true;
	}
/*
	bool EnumControlNofity(win32_notify * wn, QLib::Event<void,win32_notify_code*> & Process)
	{
		if (wn == NULL) {
			return false;
		}
		for (int i = 0; i < wn->codes.GetSize(); i++)
		{
			Process(&wn->codes[i]);
		}
		return true;
	}
*/
	template <typename FUNC>
	bool EnumControlNofity(win32_notify * wn, FUNC & Process)
	{
		if (wn == NULL) {
			return false;
		}
		for (int i = 0; i < wn->codes.GetSize(); i++)
		{
			Process(&wn->codes[i]);
		}
		return true;
	}

	CString GetClassEnumIDD(Token * tkcls)
	{
		for (size_t i = 0; i < tkcls->m_Children.GetCount(); i++)
		{
			Token * tk = tkcls->m_Children[i];
			if (tk->m_TokenKind == tkEnum && 
				tk->m_Children.GetCount() ==1) 
			{
				Token * tkidd = tk->m_Children[0];
				if (tkidd->m_Name == _T("IDD")) 
				{
					return (LPCTSTR)(tkidd->m_Args);
				}
			}
		}
		return _T("");
	}
	CResDialog * GetResDialog(Token * tkcls)
	{
		CString id = GetClassEnumIDD(tkcls);
		for (size_t i = 0; i < m_Res.m_Dialogs.GetCount(); i++)
		{
			CResDialog & dlg = m_Res.m_Dialogs[i];
			if ((!id.IsEmpty() && id == dlg.m_ID) ||
				(tkcls->m_AncestorsString.Find(dlg.m_ID) != -1) )
			{
				return &dlg;
			}
		}
		return NULL;
	}

	CResMenu * GetResDialogMenu(LPCTSTR menuID)
	{
		for (size_t i = 0; i < m_Res.m_Menus.GetCount(); i++)
		{
			const CResMenu & menu = m_Res.m_Menus.GetAt(i);
			if (menu.m_ID == menuID)
			{
				return (CResMenu*)&menu;
			}
		}
		return NULL;
	}

	win32_notify * GetResControlNotify(ResControl * ctrl)
	{
		return m_notify.get_notify_by_res(ctrl->m_Type);
	}
	win32_notify * GetResMenuNotify()
	{
		return m_notify.get_notify_by_name(_T("menu"));
	}

	Token * GetFirstTokenByName(Token * tkcls, LPCTSTR head, TokenKind kind = tkMapping)
	{
		for (size_t i = 0; i < tkcls->m_Children.GetCount(); i++)
		{
			Token * tk = tkcls->m_Children[i];
			if (tk->m_TokenKind == kind && tk->m_TokenUpdate == tuNormal)
			{
				if (tk->m_Name == head)
				{
					return tk;
				}
			}
		}
		return NULL;
	}
	//type: void process(CResDialog*)
	template <typename FUNC>
	bool EnumResDialog(FUNC & Process)
	{
		for (size_t i = 0; i < m_Res.m_Dialogs.GetCount(); i++)
		{
			Process(&m_Res.m_Dialogs[i]);
		}
	
	//	HelperEnumArray(m_Res.m_Dialogs,Process);
		return true;
	}
	//type: void process(CResMenu*)
	template <typename FUNC>
	bool EnumResMenu(FUNC & Process)
	{
		for (size_t i = 0; i < m_Res.m_Menus.GetCount(); i++)
		{
			Process(&m_Res.m_Menus[i]);
		}
		return true;
	}
	//type void process(const ResContron*)
	template <typename FUNC>
	bool EnumResDialogControl(const CResDialog * dlg, FUNC & Process)
	{
		for (size_t i = 0; i < dlg->GetCount(); i++)
		{	
			if (dlg->GetAt(i).m_ID != _T("IDC_STATIC"))
				Process(&dlg->GetAt(i));
		}
		return true;
	}
	//type void process(const CResMenu*)
	template <typename FUNC>
	bool EnumResMenuItem(const CResMenu * menu, FUNC & Process)
	{
		for (size_t i = 0; i < menu->GetCount(); i++)
		{
			if (!menu->m_ID.IsEmpty())
			{
				Process(&menu->GetAt(i));
			}
		}
		for (size_t j = 0; j < menu->m_SubMenus.GetCount(); j++)
		{
			const CResMenu & subMenu = menu->m_SubMenus.GetAt(j);
			for (size_t k = 0; k < subMenu.GetCount(); k++)
			{
				if (!subMenu.GetAt(k).m_ID.IsEmpty())
					Process(&subMenu.GetAt(k));
			}
		}
		return true;
	}
	//type void process(const winx_event*)
	template <typename FUNC>
	bool EnumWinxEventList(FUNC & Process)
	{
		for (int i = 0; i < m_winxev.m_items.GetSize(); i++)
		{
			Process(&m_winxev.m_items[i]);
		}
		return true;
	}

	bool LoadRes(LPCTSTR lpszResource,bool bAppend = false)
	{
		return m_Res.Load(lpszResource,bAppend);
	}

	bool LoadCode(LPCTSTR lpszFileName, bool bAppend = false)
	{
		if (bAppend == false)
			m_Tokens.Clear();

		wxEvtHandler ev;
		ParserThreadOptions op;
		op.useBuffer = false;
		op.bufferSkipBlocks = false;
		op.wantPreprocessor = false;
		bool flag;
		bool bRet = false;
		ParserThread * th = new ParserThread(&ev,&flag,lpszFileName,true,op,&m_Tokens);
		bRet = th->Parse();
		delete th;
		return bRet;
	} 
	
	bool LoadSources(CSimpleArray<CString> & source)
	{
		m_Tokens.Clear();
		m_Res.Clear();

		CString file;
		CSimpleArray<CString> ar1,ar2;
		int i = 0;
		for (i = 0; i < source.GetSize(); i++) 
		{
			CString & tmp = source[i];
			if (tmp.Left(1) == _T("\""))
			{
				file = tmp;
				file.TrimLeft(_T("\""));
				file.TrimRight(_T("\""));
			}
			else
				file = tmp;
			CString & ext = get_file_ext(file);
			if (ext.CompareNoCase(_T(".rc")) == 0) {
				LoadRes(file,true);
			}
			else if (ext.CompareNoCase(_T(".h")) == 0 ||
				 ext.CompareNoCase(_T(".hxx")) == 0 ||
				 ext.CompareNoCase(_T(".hpp")) == 0)
			{
				ar1.Add(file);
			}
			else if ( ext.CompareNoCase(_T(".cpp")) == 0 ||
				 ext.CompareNoCase(_T(".cxx")) == 0 ||
				 ext.CompareNoCase(_T(".c")) == 0 ) 
			{
				ar2.Add(file);
			}
		}
		//frist parser .h
		for (i = 0; i < ar1.GetSize(); i++)
		{
			LoadCode(ar1[i],true);
		}
		//then parser .cpp
		for (i = 0; i < ar2.GetSize(); i++)
		{
			LoadCode(ar2[i],true);
		}
		return true;

	}
	//load vs60 dsp file and parser file
	void ClearDSP()
	{
		WX_CLEAR_ARRAY(m_Tokens);
		m_Tokens.Clear();
		m_Res.Clear();
	}
	//insert token
	Token * GetLastTokenByScope(Token * tkcls, TokenScope Scope)
	{
		for (size_t i = tkcls->m_Children.GetCount()-1; i--; i >= 0)
		{
			Token * tk = tkcls->m_Children[i];
			if (tk->m_TokenUpdate != tuAddnew &&
				tk->m_Scope == Scope ) 
			{
				return tk;
			}
		}
		return NULL;
	}
	Token * GetFirstTokenByScope(Token * tkcls, TokenScope Scope)
	{
		for (size_t i = 0; i < tkcls->m_Children.GetCount() ; i++)
		{
			Token * tk = tkcls->m_Children[i];
			if (tk->m_TokenUpdate != tuAddnew &&
				tk->m_Scope == Scope ) 
			{
				return tk;
			}
		}
		return NULL;
	}
	//parser token and process winx kind token
	void WinxParserKindToken()
	{
		for (size_t i = 0; i < m_Tokens.GetCount(); i++)
		{
			Token * tk = m_Tokens[i];
			if (tk->m_TokenKind == tkClass)
			{
				WinxParserKindTokenHelper(tk);
			}
		}		
	}
	void WinxParserKindTokenHelper(Token * tkcls)
	{
		Token * cmd = new Token();
		cmd->m_TokenKind = tkWinxCmd;
		Token * syscmd = new Token();
		syscmd->m_TokenKind = tkWinxSyscmd;
		Token * notify = new Token();
		notify->m_TokenKind = tkWinxNotify;
		Token * update = new Token();
		update->m_TokenKind = tkWinxUpdate;
		for (size_t i = 0; i < tkcls->m_Children.GetCount(); i++)
		{
			Token * tk = tkcls->m_Children[i];
			if (tk->m_TokenKind != tkMapping)
				continue;
			if (tk->m_Name == _T("WINX_CMDS_BEGIN") ||
				tk->m_Name == _T("WINX_CMDS_END") ||
				tk->m_Name == _T("WINX_CMDS_BEGIN_EX") ||
				tk->m_Name == _T("WINX_CMDS_END_EX") ||
				tk->m_Name == _T("WINX_CMD") ||
				tk->m_Name == _T("WINX_CMD_EX") ||
				tk->m_Name == _T("WINX_CMD_NOARG") ||
				tk->m_Name == _T("WINX_CMD_RANGE") ||
				tk->m_Name == _T("WINX_CMD_NOTIFY") )
			{
				tk->m_pParent = cmd;
				cmd->AddChild(tk);
			}
			else if (tk->m_Name == _T("WINX_SYSCMD_BEGIN") ||
				tk->m_Name == _T("WINX_SYSCMD_END") ||
				tk->m_Name == _T("WINX_SYSCMD") )
			{
				tk->m_pParent = syscmd;
				syscmd->AddChild(tk);
			}
			else if (tk->m_Name == _T("WINX_NOTIFY_BEGIN") ||
				tk->m_Name == _T("WINX_NOTIFY_END") ||
				tk->m_Name == _T("WINX_NOTIFY") ||
				tk->m_Name == _T("WINX_NOTIFY_RANGE") )
			{
				tk->m_pParent = notify;
				notify->AddChild(tk);
			}
			else if (tk->m_Name == _T("WINX_UPDATEUI_BEGIN") ||
				tk->m_Name == _T("WINX_UPDATEUI_END") ||
				tk->m_Name == _T("WINX_UPDATEUI") )
			{
				tk->m_pParent = update;
				update->AddChild(tk);
			}
		}
		cmd->m_pParent = tkcls;
		syscmd->m_pParent = tkcls;
		notify->m_pParent = tkcls;
		update->m_pParent = tkcls;
		tkcls->AddChild(cmd);
		tkcls->AddChild(syscmd);
		tkcls->AddChild(notify);
		tkcls->AddChild(update);
		m_Tokens.Add(cmd);
		m_Tokens.Add(syscmd);
		m_Tokens.Add(notify);
		m_Tokens.Add(update);
	}
};
/*
//member function type
enum mf_type
{
	mf_event,
	mf_virtual,	
	mf_command,
	mf_notify
};

struct MemberFunction
{
	CString	 function;
	mf_type  type;
	CString GetType()
	{
		switch(type)
		{
		case mf_event:
			return _T("EVENT");
		case mf_virtual:
			return _T("VIRTUAL");
		case mf_command:
			return _T("COMMAND");
		case mf_notify:
			return _T("NOTIFY");
		}
		return _T("");
	}
};
//元素，类，资源ID
struct cf_object
{
};
//重载消息
struct cf_message
{
};
//消息映射
struct cf_mapping
{
};
*/

#endif