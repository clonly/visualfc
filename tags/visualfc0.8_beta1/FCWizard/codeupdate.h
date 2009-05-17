#ifndef _CODEUPDATE_H__
#define _CODEUPDATE_H__

#include "./codeparser.h"
#include "../public/foxlib.h"

struct insert_point;
class Token;

//token tag 
struct tag_token
{
	struct _s_tag
	{
		CString begin;
		CString end;
	};
	TokenKind					kind;		//Token kind
	TokenKind					data_kind;		//custom data kind
	_s_tag						tag;		//insert tag
	CAtlArray<CString>			heads;		//find tag heads
	CAtlArray<CString>			bodys;		//tag body
	bool						bext;		//WTL style
	QLib::Event<void, Token*, insert_point*>	 get_tkdata;
	QLib::Event<void, Token *, Token*, insert_point*, insert_point*>	 get_function;
	QLib::Event<bool, Token*>	find_token;
//	CAtlArray<Token*>			tks;		//tag token
	tag_token() : bext(false), data_kind(tkUndefined)
	{
	}
	
	void set_tag(LPCTSTR begin, LPCTSTR end)
	{
		tag.begin = begin;
		tag.end = end;
	}
	// add body
	void add_body(LPCTSTR body)
	{
		bodys.Add((CString)body);
	}
	// add find head
	void add_head(LPCTSTR head)
	{
		heads.Add((CString)head);
	}
	bool find(CAtlArray<CString> & array, LPCTSTR str)
	{
		for (int i = 0; i < array.GetSize(); i++)
		{
			if (array[i] == str)
				return true;
		}
		return false;
	}
	// find tag head
	bool find_head(LPCTSTR head)
	{
		return find(heads,head);
	}
	// find tag body
	bool find_body(LPCTSTR body)
	{
		return find(bodys,body);
	}
};

template <typename ArrayT>
inline void StringToArray(LPCTSTR text, ArrayT & array, LPCTSTR separator = _T(""), bool trimSpaces = true)
{
    CString search = text;
    int seplen = CString(separator).GetLength();
    while (true)
    {
        int idx = search.Find(separator);
        if (idx == -1)
        {
            if (trimSpaces)
            {
                search.TrimLeft();
                search.TrimRight();
            }
            if (!search.IsEmpty())
                array.Add(search);
            break;
        }
        CString part = search.Left(idx);
        search.Delete(0, idx + seplen);
        if (trimSpaces)
        {
            part.TrimLeft();
            part.TrimRight();
        }
        if (!part.IsEmpty())
            array.Add(part);
    }
}

template <typename ArrayT>
void ArrayToString(ArrayT & array, CString & text, LPCTSTR separator = _T(""))
{
	for (int i = 0, j = array.GetCount(); ; i++)
	{
		text += array[i];
		if (i > j)
			break;
		text += separator;
	}
}

template <typename ArrayT>
void ArrayToStringEx(ArrayT & array, CString & text, LPCTSTR separator = _T(""), int begin = 0, int end = -1)
{
	if (end == -1)
		end = array.GetCount();

	for (int i = begin; ; i++)
	{
		text += array[i];
		if (i >= end-1)
			break;
		text += separator;
	}
}


void HelperGetTokenTag(const Token * tk, CString & name, CString & args)
{
	name = tk->m_Name;
	args = tk->m_Args;

	args.TrimLeft();
	args.TrimRight();
	if (args.GetLength() > 2)
		args = args.Mid(1,args.GetLength()-2);
}

/*
struct parser_tag
{
	tag_token	tag;

	// process class tag
	void GetUpdateClassTag(Token * tkcls, tag_token & tag)
	{
		for (size_t i = 0; i < tkcls->m_Children.GetCount(); i++)
		{
			Token * tk = tkcls->m_Children[i];

			if (tk->m_TokenKind == tag.kind)
			{
				if (tk->m_TokenUpdate == tuAddnew)
				{
					if (tag.find_body(tk->m_Name))
					{
						tag.tks.Add(tk);
					}
				}
			}
		}
	}// process token tag
	void GetClassTokenTag(Token * tkcls, tag_token & tag)
	{
		for (size_t i = 0; i < tkcls->m_Children.GetCount(); i++)
		{
			Token * tk = tkcls->m_Children[i];

			if (tk->m_TokenKind == tag.kind)
			{
				if (tk->m_TokenUpdate != tuRemove)
				{
					if (tag.find_body(tk->m_Name))
					{
						tag.tks.Add(tk);
					}
				}
			}
		}
	}
};
*/
//code update class
class codeupdate
{
	typedef std::map<CString,CSimpleArray<insert_point*> > INSERTPT_MAP;
public:
	fox::vs_addin  *  pVSAddin;
	codeparser		 * pcode;
	CAtlArray<tag_token*> *	ptags;
public:
	codeupdate() : pVSAddin(NULL), pcode(NULL), ptags(NULL)
	{
	}
	void ProcessUpdateTokenVarible(Token * tkcls, Token * tk, INSERTPT_MAP & ptmap)
	{
		if (tk->m_TokenUpdate == tuRemove)
		{
			if (!tk->m_Filename.IsEmpty() && pVSAddin)
			{
				pVSAddin->replace_text(tk->m_Filename,tk->m_Line,tk->m_Type,"//"+tk->m_Type);
			}
		}
		else if (tk->m_TokenUpdate == tuAddnew)
		{
			int line = 0;
			Token * head = NULL;
			head = pcode->GetFirstTokenByScope(tkcls,tsPublic);//pcode->GetLastTokenByScope(tkcls,tsPublic);
			
			if (head)
				line = head->m_Line-1;
			else
				line = GetFirstInsertLine(tkcls);
			
			insert_point * pt = new insert_point();
			pt->line = line;
			pt->AddLine(tk->m_Type+_T("\t")+tk->m_Name+_T(";"));
			ptmap[(CString)tkcls->m_Filename].Add(pt);
		}
	}
	void ProcessUpdateTokenFunction(Token * tkcls, Token * tk, INSERTPT_MAP & ptmap)
	{
		if (tk->m_TokenUpdate == tuRemove)
		{
			if (!tk->m_Filename.IsEmpty() && pVSAddin)
			{
				pVSAddin->replace_text(tk->m_Filename,tk->m_Line,tk->m_Name,"_winxDEL_"+tk->m_Name);
			}
			if (!tk->m_ImplFilename.IsEmpty() && pVSAddin)
			{
				pVSAddin->replace_text(tk->m_ImplFilename,tk->m_ImplLine,tk->m_Name,"_winxDEL_"+tk->m_Name);
			}
		}
		else if (tk->m_TokenUpdate == tuAddnew)
		{
			Token * last = pcode->GetLastTokenByScope(tkcls,tk->m_Scope);
			int line = 0;
			if (last == NULL)
			{
				line = tkcls->m_EndLine-1;
			}
			else
			{
				if (last->m_TokenKind == tkFunction)
				{
					if (last->m_ImplFilename.IsEmpty())
						line = last->m_EndLine;
					else
						line = last->m_Line;
				}
				else 
					line = last->m_Line;
			}
			insert_point * pt = new insert_point();
			pt->line = line;
			winx_event * ev = (winx_event*)tk->m_Data;
			if (last == NULL)
				pt->AddLine(tk->GetTokenScopeString()+_T(":"));
			pt->AddNewLine();
			pt->AddLine(ev->func);
			pt->AddLine(_T("{"));
			if (!ev->body.IsEmpty())
				pt->AddLine(ev->body,1);
			pt->AddLine(_T("}"));
			ptmap[(CString)tkcls->m_Filename].Add(pt);
		}
	}
	void ProcessUpdateNotifyTokenFunction(Token * tkcls, const CString & func, const CString & body,INSERTPT_MAP & ptmap)
	{
		Token * last = pcode->GetLastTokenByScope(tkcls,tsPublic);
		int line = 0;
		if (last == NULL)
		{
			line = tkcls->m_EndLine-1;
		}
		else
		{
			if (last->m_TokenKind == tkFunction)
			{
				if (last->m_ImplFilename.IsEmpty())
					line = last->m_EndLine;
				else
					line = last->m_Line;
			}
			else 
				line = last->m_Line;
		}
		insert_point * pt = new insert_point();
		pt->line = line;
		//if (last == NULL)
		//	pt->AddLine(_T("public:"),0);
		pt->AddNewLine();
		pt->AddLine(func);
		pt->AddLine(_T("{"));
		if (!body.IsEmpty())
			pt->AddLine(body,1);
		pt->AddLine(_T("}"));
		ptmap[(CString)tkcls->m_Filename].Add(pt);
	}

	int GetFirstInsertLine(Token * tkcls)
	{
		for (size_t i = 0; i < tkcls->m_Children.GetCount(); i++)
		{
			Token * tk = tkcls->m_Children[i];
			if (tk->m_TokenUpdate == tuNormal && 
				( tk->m_TokenKind == tkFunction || 
				  tk->m_TokenKind == tkVariable) )
			{
				return tk->m_Line-1;
			}
		}
		return tkcls->m_EndLine-1;
	}
	bool GetClassImplFile(Token * tkcls, CString & implFile, int & line)
	{
		for (size_t i = 0; i < tkcls->m_Children.GetCount(); i++)
		{
			Token * tk = tkcls->m_Children[i];
			if (!tk->m_ImplFilename.IsEmpty())
			{
				implFile = (LPCTSTR)tk->m_ImplFilename;
				line = tk->m_ImplLine-1;
				return true;
			}
		}
		return false;
	}
	bool GetClassLastImplFile(Token * tkcls, CString & implFile, int & line)
	{	
		for (size_t i = tkcls->m_Children.GetCount()-1; i-- ; i >= 0)
		{
			Token * tk = tkcls->m_Children[i];
			if (tk->m_TokenUpdate != tuAddnew && 
				(tk->m_TokenKind == tkFunction || tk->m_TokenKind == tkConstructor || tk->m_TokenKind == tkDestructor) && 
				!tk->m_ImplFilename.IsEmpty() )
			{
				implFile = (LPCTSTR)tk->m_ImplFilename;
				line = tk->m_EndLine;
				return true;
			}
		}
		return false;
	}
	void ProcessUpdateTokenCmd(Token * tkcls, CSimpleArray<Token*> & cmd, INSERTPT_MAP & ptmap)
	{
		if (cmd.GetSize() == 0)
			return;
		int line = 0;
		Token * head = pcode->GetFirstTokenByName(tkcls,_T("WINX_CMDS_BEGIN_EX"));
		if (!head)
			head = pcode->GetFirstTokenByName(tkcls,_T("WINX_CMDS_BEGIN"));
		if (head)
			line = head->m_Line;
		else
			line = GetFirstInsertLine(tkcls);
		insert_point * pt = new insert_point();
		pt->line = line;
		int i = 0;
		if (head == NULL)
		{
			pt->AddLine(_T(""));
			pt->AddLine(_T("WINX_CMDS_BEGIN_EX()"));
		}
		for (i = 0; i < cmd.GetSize(); i++)
		{
			Token * tk = cmd[i];
			pt->AddLine(tk->m_Name+tk->m_Args,1);
		}
		if (head == NULL)
		{
			pt->AddLine(_T("WINX_CMDS_END_EX();"));
			pt->AddLine(_T(""));
		}

		ptmap[(CString)tkcls->m_Filename].Add(pt);	

		for (i = 0; i < cmd.GetSize(); i++)
		{
			Token * tk = cmd[i];
			ProcessUpdateNotifyTokenFunction(tkcls,(LPCTSTR)tk->m_String,_T(""),ptmap);
		}
	}
	void ProcessUpdateTokenNotify(Token * tkcls, CSimpleArray<Token*> & cmd, INSERTPT_MAP & ptmap)
	{
		if (cmd.GetSize() == 0)
			return;
		int line = 0;
		Token * head = pcode->GetFirstTokenByName(tkcls,_T("WINX_NOTIFY_BEGIN"));
		if (head)
			line = head->m_Line;
		else
			line = GetFirstInsertLine(tkcls);
		insert_point * pt = new insert_point();
		pt->line = line;
		int i = 0;
		if (head == NULL)
			pt->AddLine(_T("WINX_NOTIFY_BEGIN()"));
		for (i = 0; i < cmd.GetSize(); i++)
		{
			Token * tk = cmd[i];
			pt->AddLine(tk->m_Name+tk->m_Args,1);
		}
		if (head == NULL)
		{
			pt->AddLine(_T("WINX_NOTIFY_END();"));
			pt->AddLine(_T(""));
		}

		ptmap[(CString)tkcls->m_Filename].Add(pt);	

		for (i = 0; i < cmd.GetSize(); i++)
		{
			Token * tk = cmd[i];
			ProcessUpdateNotifyTokenFunction(tkcls,(LPCTSTR)tk->m_String,_T(""),ptmap);
		}
	}

	void ProcessUpdateTokenDlsz(Token * tkcls, CSimpleArray<Token*> & tks, INSERTPT_MAP & ptmap)
	{
		if (tks.GetSize() == 0)
			return;
		int line = 0;
		Token * head = pcode->GetFirstTokenByName(tkcls,_T("WINX_DLGRESIZE_BEGIN"));
		if (head)
			line = head->m_Line;
		else
			line = GetFirstInsertLine(tkcls);
		insert_point * pt = new insert_point();
		pt->line = line;
		int i = 0;
		if (head == NULL)
			pt->AddLine(_T("WINX_DLGRESIZE_BEGIN(TRUE)"));
		for (i = 0; i < tks.GetSize(); i++)
		{
			Token * tk = tks[i];
			pt->AddLine(tk->m_Name+tk->m_Args,1);
		}
		if (head == NULL)
			pt->AddLine(_T("WINX_DLGRESIZE_END();\r\n"));

		ptmap[(CString)tkcls->m_Filename].Add(pt);
	}
	void ProcessUpdateTokenFont(Token * tkcls, CSimpleArray<Token*> & tks, INSERTPT_MAP & ptmap)
	{
		if (tks.GetSize() == 0)
			return;
		int line = 0;
		Token * head = pcode->GetFirstTokenByName(tkcls,_T("WINX_DLGFONT_BEGIN"));
		if (head)
			line = head->m_Line;
		else
			line = GetFirstInsertLine(tkcls);
		insert_point * pt = new insert_point();
		pt->line = line;
		int i = 0;
		if (head == NULL)
			pt->AddLine(_T("WINX_DLGFONT_BEGIN()"));
		for (i = 0; i < tks.GetSize(); i++)
		{
			Token * tk = tks[i];
			pt->AddLine(tk->m_Name+tk->m_Args,1);
		}
		if (head == NULL)
			pt->AddLine(_T("WINX_DLGFONT_END();\r\n"));

		ptmap[(CString)tkcls->m_Filename].Add(pt);
	}
	// process class tag
	void GetUpdateClassTag(Token * tkcls, tag_token & tag, CSimpleArray<Token*> & tks)
	{
		for (size_t i = 0; i < tkcls->m_Children.GetCount(); i++)
		{
			Token * tk = tkcls->m_Children[i];

			if (tk->m_TokenKind == tag.kind)
			{
				if (tk->m_TokenUpdate == tuAddnew)
				{
					if (!tag.find_token.empty() && tag.find_token(tk) )
					{
						tks.Add(tk);
					}
					else if (tag.find_body(tk->m_Name))
					{
						tks.Add(tk);
					}
				}
			}
		}
	}// process token tag
	bool ProcessUpdateTokenTagMapping(Token * tkcls, INSERTPT_MAP & ptmap, tag_token & tag, CSimpleArray<Token*> & tks)
	{
		if (tks.GetSize() == 0)
			return false;
		int line = 0;
		Token * head = NULL;
		int i = 0;
		for (i = 0; i < tag.heads.GetSize(); i++)
		{
			head = pcode->GetFirstTokenByName(tkcls,tag.heads[i]);
			if (head != NULL)
				break;
		}
		if (head)
			line = head->m_Line;
		else
			line = GetFirstInsertLine(tkcls);
		insert_point * pt = new insert_point();
		pt->line = line;
		if (head == NULL)
		{
			if (tag.bext == true)
			{
				CString text = tag.tag.begin;
				text.Replace(_T("$CLS"),tkcls->m_Name);
				pt->AddLine(text);
			}
			else
				pt->AddLine(tag.tag.begin);
		}

		for (i = 0; i < tks.GetSize(); i++)
		{
			Token * tk = tks[i];
			pt->AddLine(tk->m_Name+tk->m_Args,1);
		}
		if (head == NULL)
		{
			pt->AddLine(tag.tag.end);
			pt->AddLine(_T(""));
		}

		ptmap[(CString)tkcls->m_Filename].Add(pt);
	}
	bool ProcessUpdateTokenTagFunction(Token * tkcls, INSERTPT_MAP & ptmap, tag_token & tag, CSimpleArray<Token*> & tks)
	{
		if (tks.GetSize() == 0)
			return false;
		int line = 0;
		Token * head = NULL;
		head = pcode->GetLastTokenByScope(tkcls,tsPublic);//pcode->GetLastTokenByScope(tkcls,tsPublic);

		if (head)
		{
			if (head->m_ImplFilename.IsEmpty())
				line = head->m_EndLine;
			else
				line = head->m_Line;
		}
		else
			line = GetFirstInsertLine(tkcls);

		insert_point * pt = new insert_point();
		pt->line = line;
		//test is find impl file
		
		CString implFile;
		int implLine;
		if (GetClassLastImplFile(tkcls,implFile,implLine))
		{
			insert_point * pt2 = new insert_point(true);
			pt2->line = implLine;
			for (int i = 0; i < tks.GetSize(); i++)
			{
				Token * tk = tks[i];
				tag.get_function(tkcls,tk,pt,pt2);
			}
			ptmap[(LPCTSTR)tkcls->m_Filename].Add(pt);
			ptmap[implFile].Add(pt2);
			return true;
		}
		else
		{
			
			for (int i = 0; i < tks.GetSize(); i++)
			{
				Token * tk = tks[i];
				tag.get_function(tkcls,tk,pt,NULL);
			}
			
			ptmap[(CString)tkcls->m_Filename].Add(pt);
			return true;
		}
		return false;
	}

	bool ProcessUpdateTokenTagVarible(Token * tkcls, INSERTPT_MAP & ptmap, tag_token & tag, CSimpleArray<Token*> & tks)
	{
		if (tks.GetSize() == 0)
			return false;
		int line = 0;
		Token * head = NULL;
		head = pcode->GetFirstTokenByScope(tkcls,tsPublic);//pcode->GetLastTokenByScope(tkcls,tsPublic);

		if (head)
			line = head->m_Line-1;
		else
			line = GetFirstInsertLine(tkcls);

		insert_point * pt = new insert_point();
		pt->line = line;

		for (int i = 0; i < tks.GetSize(); i++)
		{
			Token * tk = tks[i];
			tag.get_tkdata(tk,pt);
		}

		ptmap[(CString)tkcls->m_Filename].Add(pt);
	}

	void ProcessUpdateClass(Token * tkcls, INSERTPT_MAP & ptmap)
	{
		//pre process mapping
		CSimpleArray<Token*>  cmd;		//WINX_CMD
		CSimpleArray<Token*>  notify;	//WINX_NOTIFY
	//	CSimpleArray<Token*>  dlsz;		//WINX_DLGRESIZE
	//	CSimpleArray<Token*>  font;		//WINX_DLGFONT

		size_t i = 0;
		for (i = 0; i < tkcls->m_Children.GetCount(); i++)
		{
			Token * tk = tkcls->m_Children[i];
			if (tk->m_TokenKind == tkMapping)
			{
				//ProcessUpdateTokenMapping(tkcls,tk,ptmap);
				if (tk->m_TokenUpdate == tuRemove)
				{
					if (!tk->m_Filename.IsEmpty() && pVSAddin)
					{
						pVSAddin->replace_text(tk->m_Filename,tk->m_Line,tk->m_Name,"//"+tk->m_Name);
					}
				}
				else if (tk->m_TokenUpdate == tuAddnew)
				{
					if (tk->m_Name == _T("WINX_CMD") ||
						tk->m_Name == _T("WINX_CMD_EX"))
					{
						cmd.Add(tk);
					}
					else if (tk->m_Name == _T("WINX_NOTIFY"))
					{
						notify.Add(tk);
					}
					else if (tk->m_Name == _T("WINX_DLGRESIZE"))
					{
				//		dlsz.Add(tk);
					}
					else if (tk->m_Name == _T("WINX_DLGFONT") ||
						tk->m_Name == _T("WINX_DLGFONT_EX") ||
						tk->m_Name == _T("WINX_DLGFONT_DIALOG") ||
						tk->m_Name == _T("WINX_DLGFONT_DIALOG_EX") ) 
					{
					//	font.Add(tk);
					}
				}
			}
		}
		ProcessUpdateTokenCmd(tkcls,cmd,ptmap);
		ProcessUpdateTokenNotify(tkcls,notify,ptmap);
	//	ProcessUpdateTokenDlsz(tkcls,dlsz,ptmap);

//		GetUpdateClassTag(tkcls,tag_font, font);
//		ProcessUpdateTokenTag(tkcls,ptmap,tag_font, font);
	//	ProcessUpdateTokenFont(tkcls,font,ptmap);
		for (i = 0; i < ptags->GetCount(); i++)
		{
			CSimpleArray<Token*>	tag_tks;
			tag_token * tag = ptags->GetAt(i);
			GetUpdateClassTag(tkcls,*tag,tag_tks);
			ProcessUpdateTokenTagMapping(tkcls,ptmap,*tag,tag_tks);
			if (tag->data_kind == tkFunction)
			{
				ProcessUpdateTokenTagFunction(tkcls,ptmap,*tag,tag_tks);
			}
			else if (tag->data_kind == tkVariable)
			{
				ProcessUpdateTokenTagVarible(tkcls,ptmap,*tag,tag_tks);
			}
		}
		
		// process funciton
		// process varible
		for (i = 0; i < tkcls->m_Children.GetCount(); i++)
		{
			Token * tk = tkcls->m_Children[i];
			if (tk->m_TokenKind == tkVariable)
			{
				ProcessUpdateTokenVarible(tkcls,tk,ptmap);
			}
			else if (tk->m_TokenKind == tkFunction)
			{
				ProcessUpdateTokenFunction(tkcls,tk,ptmap);
			}
		}
	}
	void ProcessInsertPoint(INSERTPT_MAP & ptmap)
	{
		for (INSERTPT_MAP::iterator it = ptmap.begin(); it != ptmap.end(); it++)
		{
			const CString & filename = it->first;
			CSimpleArray<insert_point*> & ar = it->second;
			typedef std::multimap<int,insert_point*,std::greater<int> > MM_MAP;
			MM_MAP mm;
			for (int i = 0; i < ar.GetSize(); i++)
			{
				insert_point * pt = ar[i];
				mm.insert(MM_MAP::value_type(pt->line,pt));
			}
			int line = 0;
			for (MM_MAP::iterator it = mm.begin(); it != mm.end(); it++)
			{
				insert_point * pt = it->second;
				if (pVSAddin)
				{
					if (pt->bcpp == false)
						pVSAddin->insert_block(filename,pt->line,0,pt->GetText(1));
					else
						pVSAddin->insert_block(filename,pt->line,0,pt->GetText(0));
				}	
			}
		}
	}
	//进行更新
	void ProcessUpdate()
	{
		//插入点
		INSERTPT_MAP ptmap;
	
		for (size_t i = 0; i < pcode->m_Tokens.GetCount(); i++)
		{
			Token * tk = pcode->m_Tokens[i];
			if (tk->m_TokenKind == tkClass)
			{
				ProcessUpdateClass(tk,ptmap);
			}
		}
		//处理插入点
		ProcessInsertPoint(ptmap);
		//clear all
		for (INSERTPT_MAP::iterator it = ptmap.begin(); it != ptmap.end(); it++)
		{
			CSimpleArray<insert_point*> & ar = it->second;
			for (int i = 0; i < ar.GetSize(); i++)
				delete ar[i];
			ar.RemoveAll();
		}
	}
	bool GotoLine(Token * tk)
	{
		if (tk == NULL)
			return false;
		if (tk->m_TokenUpdate != tuNormal)
			return false;

		if (pcode->WinxIsMessageToken(tk) == true)
		{
			Token * tkcls = tk->m_pParent;
			if (tkcls == NULL)
				return false;
			CString name = pcode->WinxGetNotifyTokenFuncitonName(tk);
			if (name.IsEmpty())
				return false;
			for (size_t i = 0; i < tkcls->m_Children.GetCount(); i++)
			{
				Token * tks = tkcls->m_Children[i];
				if (tks->m_TokenKind == tkFunction &&
					name.Compare(tks->m_Name) == 0)
				{
					tk = tks;
					goto process;								
				}
			}
			return false;
		}
process:
		if (pVSAddin)
		{
			ProcessUpdate();

			if (!tk->m_ImplFilename.IsEmpty())
			{
				pVSAddin->goto_line(tk->m_ImplFilename,tk->m_ImplLine);
			}
			else if (!tk->m_Filename.IsEmpty())
			{
				pVSAddin->goto_line(tk->m_Filename,tk->m_Line);
			}
			return true;
		}
		return false;
	}
};

#endif	//_CODEUPDATE_H__