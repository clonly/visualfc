#ifndef _WTL_EVENT_H_
#define _WTL_EVENT_H_

#include "../public/wtlfileex.h"
#include "./resources/reshelper.h"
/*
<WM_CREATE>
ext=MSG_WM_CREATE
func=OnCreate
ret=int
param=(LPCREATESTRUCT lpCreateStruct)
body=return 0;
</WM_CREATE>
*/
struct wtl_event
{
	CString							  msg;	//WM_CREATE
	CString							  ext;  //MSG_WM_CREATE
	CString							  func; //OnCreate
	CString							  ret;  //int
	CString							  param;//(LPCREATESTRUCT lpCreateStruct)
	CString							  body;	//return 0;
	CString							  crack;//CWindow wndFocus = (HWND)wParam;  LPARAM lInitParam = lParam;
};

struct wtl_kind
{
	CString					kind;
	CAtlArray<CString>		msgs;
	CAtlArray<wtl_event*>   event;
};

class wtl_event_config
{
public:
	CAtlArray<wtl_event>  m_items;
	CAtlArray<wtl_kind>	  m_kinds;
public:
	enum item_kind
	{
		ikBegin = 0,
		ikEnd,
		ikItem,
		ikMsg,
		ikFunc,
		ikBody
	};
	item_kind get_item_kind(const CString & line, CString & out)
	{
		out = line;
		if (line.Left(2) == _T("</") )
		{
			out.TrimLeft(_T("</"));
			out.TrimRight(_T(">"));
			return ikEnd;
		}
		else if (line.Left(1) == _T("<") && line.Right(1) == _T(">"))
		{
			out.TrimLeft(_T("<"));
			out.TrimRight(_T(">"));
			return ikBegin;
		}

		return ikItem;
	}
	bool get_item(const CString & line, const CString & item, CString & out)
	{
		CString text = line;
		text.TrimLeft();
		text.TrimRight();
		int pos = -1;
		pos = text.Find(item);
		if (pos != 0)
			return false;
		pos = text.Find(_T("="),item.GetLength());
		if (pos == -1)
			return false;
		out = text.Right(text.GetLength()-pos-1);
		return true;
	}
	bool loadex(LPCTSTR lpszFileName)
	{
		m_items.RemoveAll();

		CTextFile file;
		if (file.Open(lpszFileName) == FALSE)
			return false;
		CString line;
		CString out;
		wtl_event * pitem = NULL;
		bool bload = false;
		while(file.ReadLine(line))
		{
			line.TrimLeft();
			line.TrimRight();
			item_kind ik = get_item_kind(line,out);
			if (ik == ikBegin)
			{
				wtl_event item;
				m_items.Add(item);
				pitem = &m_items[m_items.GetCount()-1];
				pitem->msg = out;
				bload = true;
			}
			else if (ik == ikEnd)
			{	
				bload = false;
			}
			if (bload)
			{
				get_item(line,_T("ext"),pitem->ext);
				get_item(line,_T("func"),pitem->func);
				get_item(line,_T("ret"),pitem->ret);
				get_item(line,_T("param"),pitem->param);
				get_item(line,_T("body"),pitem->body);
				get_item(line,_T("crack"),pitem->crack);
			}
		}
		file.Close();
		return true;
	}
	bool load_kind(LPCTSTR lpszFileName)
	{
		m_kinds.RemoveAll();

		CTextFile file;
		if (file.Open(lpszFileName) == FALSE)
			return false;
		CString line;
		CString out;
		wtl_kind * pitem = NULL;
		bool bload = false;
		while(file.ReadLine(line))
		{
			line.TrimLeft();
			line.TrimRight();
			item_kind ik = get_item_kind(line,out);
			if (ik == ikBegin)
			{
				wtl_kind item;
				m_kinds.Add(item);
				pitem = &m_kinds[m_kinds.GetCount()-1];
				pitem->kind = out;
				bload = true;
				continue;
			}
			else if (ik == ikEnd)
			{	
				bload = false;
			}
			if (bload && !line.IsEmpty())
			{
				pitem->msgs.Add(line);
			}
		}
		file.Close();
		return true;
	}
};


class wtl_kind_config
{
public:
	CAtlArray<wtl_kind>  m_items;
public:
	enum item_kind
	{
		ikBegin = 0,
		ikEnd,
		ikItem,
		ikMsg,
		ikFunc,
		ikBody
	};

	item_kind get_item_kind(const CString & line, CString & out)
	{
		out = line;
		if (line.Left(2) == _T("</") )
		{
			out.TrimLeft(_T("</"));
			out.TrimRight(_T(">"));
			return ikEnd;
		}
		else if (line.Left(1) == _T("<") && line.Right(1) == _T(">"))
		{
			out.TrimLeft(_T("<"));
			out.TrimRight(_T(">"));
			return ikBegin;
		}

		return ikItem;
	}
	bool loadex(LPCTSTR lpszFileName)
	{
		m_items.RemoveAll();

		CTextFile file;
		if (file.Open(lpszFileName) == FALSE)
			return false;
		CString line;
		CString out;
		wtl_kind * pitem = NULL;
		bool bload = false;
		while(file.ReadLine(line))
		{
			line.TrimLeft();
			line.TrimRight();
			item_kind ik = get_item_kind(line,out);
			if (ik == ikBegin)
			{
				wtl_kind item;
				m_items.Add(item);
				pitem = &m_items[m_items.GetCount()-1];
				pitem->kind = out;
				bload = true;
				continue;
			}
			else if (ik == ikEnd)
			{	
				bload = false;
			}
			if (bload && !line.IsEmpty())
			{
				pitem->msgs.Add(line);
			}
		}
		file.Close();
		return true;
	}
};
#endif