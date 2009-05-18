// Windows Template Library - WTL version 8.0
// Copyright (C) Microsoft Corporation. All rights reserved.
//
// This file is a part of the Windows Template Library.
// The use and distribution terms for this software are covered by the
// Common Public License 1.0 (http://opensource.org/osi3.0/licenses/cpl1.0.php)
// which can be found in the file CPL.TXT at the root of this distribution.
// By using this software in any fashion, you are agreeing to be bound by
// the terms of this license. You must not remove this notice, or
// any other, from this software.

// Module: vfcpanel.h
// Creator: visualfc 
// Email: visualfc@gmail.com
// open source: http://sf.net/projects/visualfc
// Date: 2008-01-03

#ifndef __VFCPANEL_H__
#define __VFCPANEL_H__

#pragma once

#ifndef __cplusplus
	#error ATL requires C++ compilation (use a .cpp suffix)
#endif

#ifndef __ATLAPP_H__
	#error vfcpanel.h requires atlapp.h to be included first
#endif

#ifndef __ATLWIN_H__
	#error vfcpanel.h requires atlwin.h to be included first
#endif

#ifndef __ATLFRAME_H__
	#error vfcpanel.h requires atlframe.h to be included first
#endif

#ifndef _WIN32_WCE
#ifndef __VFCFRAME_H__
	#include <vfcframe.h>
#endif
#endif //_WIN32_WCE


///////////////////////////////////////////////////////////////////////////////
// Classes in this file:
//
//CPanelCtrlImpl
//CPanelCtrl
//CFramePanelCtrl

namespace WTL
{
#ifndef _WIN32_WCE
template <class T, class TBase = CStatic, class TWinTraits = CControlWinTraits>
#else
template <class T, class TBase = CWindow, class TWinTraits = CControlWinTraits>
#endif //_WIN32_WCE
class ATL_NO_VTABLE CPanelCtrlImpl : public CWindowImpl<T, TBase, TWinTraits>
{
public:
	bool m_bAutoAddControl;
	CPanelCtrlImpl() :  m_bAutoAddControl(true)
	{
	}
public:
	BEGIN_MSG_MAP(CPanelCtrlImpl)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
#ifdef _WIN32_WCE
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
#endif
		FORWARD_NOTIFICATIONS()
	END_MSG_MAP()
public:
	DECLARE_WND_SUPERCLASS(NULL, TBase::GetWndClassName())

	BOOL SubclassWindow(HWND hWnd)
	{

#if (_MSC_VER >= 1300)
		BOOL bRet = ATL::CWindowImpl<T, TBase, TWinTraits>::SubclassWindow(hWnd);
#else 
		typedef ATL::CWindowImpl<T, TBase, TWinTraits> _baseClass;
		BOOL bRet = _baseClass::SubclassWindow(hWnd);
#endif //(_MSC_VER >= 1300)

		if (bRet)
		{
			T * pT = static_cast<T*>(this);
			pT->Init();
		}
		return bRet;
	}

#ifdef _WIN32_WCE
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CPaintDC dc(m_hWnd);
		RECT rc = {0};
		GetClientRect(&rc);
		if ((GetExStyle() & WS_EX_DLGMODALFRAME) != 0)
			dc.DrawEdge(&rc, EDGE_ETCHED, BF_RECT | BF_ADJUST);
		else if((GetExStyle() & WS_EX_CLIENTEDGE) != 0)
			dc.DrawEdge(&rc, EDGE_SUNKEN, BF_RECT | BF_ADJUST);

		dc.FillRect(&rc, COLOR_APPWORKSPACE);
		return 0;
	}
#endif

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CWindow parent = GetParent();
		if (parent.m_hWnd)
		{
			SetFont(parent.GetFont());
		}
		T * pT = static_cast<T*>(this);

		pT->Init();
		bHandled = FALSE;
		return 1; 
	}

	void Init()
	{

#ifndef _WIN32_WCE
		const int cchBuff = 8;
		TCHAR szBuffer[cchBuff] = { 0 };
		if(::GetClassName(m_hWnd, szBuffer, cchBuff))
		{
			if(lstrcmpi(szBuffer, _T("static")) == 0)
			{
				DWORD dwStyle = GetStyle();
				if ((dwStyle & SS_BLACKFRAME) == SS_BLACKFRAME)
					ModifyStyle(SS_BLACKFRAME,0,0);
				if ((dwStyle & SS_GRAYFRAME) == SS_GRAYFRAME)
					ModifyStyle(SS_GRAYFRAME,0,0);
				if ((dwStyle & SS_WHITEFRAME) == SS_WHITEFRAME)
					ModifyStyle(SS_WHITEFRAME,0,0);
				if ((dwStyle & SS_ETCHEDFRAME) == SS_ETCHEDFRAME)
					ModifyStyle(SS_ETCHEDFRAME,0,0);
			}
			else if ( (lstrcmpi(szBuffer, _T("button")) == 0 ) && 
				( (GetStyle() & BS_GROUPBOX) == BS_GROUPBOX) )
			{
				ModifyStyle(BS_GROUPBOX,BS_TYPEMASK,0);

			}
		}
	//	ModifyStyleEx(0,WS_EX_CONTROLPARENT,0);	
#endif //_WIN32_WCE

		if (m_bAutoAddControl)
		{
			AutoAddControl(GetParent());
		}
	}
	
	void AutoAddControl(HWND hDlg)
	{
		RECT rcWindow = {0};
		GetWindowRect(&rcWindow);

		HWND wndChild = ::GetWindow(hDlg, GW_CHILD);
		wndChild = ::GetNextWindow(wndChild, GW_HWNDLAST);
		HWND wndNext = NULL;
		while (wndChild)
		{
			wndNext = ::GetNextWindow(wndChild,GW_HWNDPREV);
			if (wndChild != m_hWnd)
			{
				RECT rc = {0};
				::GetWindowRect(wndChild,&rc);
				if (rc.left >= rcWindow.left && rc.top >= rcWindow.top && 
					rc.right <= rcWindow.right && rc.bottom <= rcWindow.bottom)
				{
					::SetParent(wndChild,m_hWnd);
					rc.left -= rcWindow.left;
					rc.top -= rcWindow.top;
					rc.right -= rcWindow.left;
					rc.bottom -= rcWindow.top;
					::SetWindowPos(wndChild, NULL, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
				}
			}
			wndChild = wndNext;
		}
	}

	BOOL AddControl(HWND hWnd)
	{
		T * pT = static_cast<T*>(this);
		CWindow ctl = hWnd;
		if (ctl.GetParent() == m_hWnd)
			return TRUE;
		RECT rcWindow = {0};
		GetWindowRect(&rcWindow);
		RECT rc = {0};
		ctl.GetWindowRect(&rc);
		ctl.SetParent(m_hWnd);
		rc.left -= rcWindow.left;
		rc.top -= rcWindow.top;
		rc.right -= rcWindow.left;
		rc.bottom -= rcWindow.top;
		ctl.SetWindowPos( NULL, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
		return TRUE;
	}

	HICON GetIcon(BOOL bBigIcon = TRUE) const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return (HICON)::SendMessage(m_hWnd, WM_GETICON, bBigIcon, 0);
	}

	HICON SetIcon(HICON hIcon, BOOL bBigIcon = TRUE)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return (HICON)::SendMessage(m_hWnd, WM_SETICON, bBigIcon, (LPARAM)hIcon);
	}
};

#define PANEL_SIZE_X			0x00000001
#define PANEL_SIZE_Y			0x00000002
#define PANEL_MOVE_X			0x00000004
#define PANEL_MOVE_Y			0x00000008
#define PANEL_REPAINT			0x00000010
#define PANEL_CENTER_X			0x00000020
#define PANEL_CENTER_Y			0x00000040
#define PANEL_ANCHOR_LEFT		0
#define PANEL_ANCHOR_TOP	    0
#define PANEL_ANCHOR_RIGHT		PANEL_MOVE_X
#define PANEL_ANCHOR_BOTTOM		PANEL_MOVE_Y

template <typename T>
class CDynamicDialogResize : public CDialogResize<T>
{
protected:
	int nGroupStart;
public:

	BEGIN_DLGRESIZE_MAP(T)
	END_DLGRESIZE_MAP()

	CDynamicDialogResize() : nGroupStart(-1)
	{
	}

	void UpdateResize(int nID, DWORD dwResizeFlags)
	{
		T * pT = static_cast<T*>(this);
		CWindow ctl = pT->GetDlgItem(nID);
		RECT rc = {0};
		ctl.GetWindowRect(&rc);
		::MapWindowPoints(NULL,pT->m_hWnd, (LPPOINT)&rc, 2);
		
		for (int i = 0; i < m_arrData.GetSize(); i++)
		{
			if (m_arrData[i].m_nCtlID == nID)
			{
				m_arrData[i].m_dwResizeFlags = dwResizeFlags;
				if (nGroupStart == -1)
				{
					UpdateResizeData(m_arrData[i]);
				}
				break;
			}
		}
	}

	BOOL AddResize(int nID, DWORD dwResizeFlags)
	{
		T * pT = static_cast<T*>(this);
		CWindow ctl = pT->GetDlgItem(nID);
		if (ctl == NULL)
			return FALSE;
		RECT rc = {0};
		ctl.GetWindowRect(&rc);
		::MapWindowPoints(NULL,pT->m_hWnd, (LPPOINT)&rc, 2);
		
		DWORD dwGroupFlag = (nGroupStart != -1 && m_arrData.GetSize() == nGroupStart) ? _DLSZ_BEGIN_GROUP : 0;
		_AtlDlgResizeData data = { nID, dwResizeFlags | dwGroupFlag, {rc.left, rc.top, rc.right, rc.bottom} };
		m_arrData.Add(data);

		if (nGroupStart == -1)
		{
			UpdateResizeData(data);
		}
		return TRUE;
	}
	void BeginGroup()
	{
		ATLASSERT(nGroupStart == -1);
		nGroupStart = m_arrData.GetSize();
	}

	void EndGroup()
	{
		ATLASSERT(nGroupStart != -1);
		int nGroupCount = m_arrData.GetSize() - nGroupStart;
		m_arrData[nGroupStart].SetGroupCount(nGroupCount);
		nGroupStart = -1;

		T * pT = static_cast<T*>(this);
		RECT rc = {0};
		pT->GetClientRect(&rc);
		pT->SendMessage(WM_SIZE,0,MAKELPARAM(rc.right-rc.left,rc.bottom-rc.top));
	}

	void UpdateResizeData(_AtlDlgResizeData& data)
	{
		T * pT = static_cast<T*>(this);
		RECT rc = {0};
		pT->GetClientRect(&rc);
		RECT rectGroup = {0};
		pT->DlgResize_PositionControl(rc.right-rc.left,rc.bottom-rc.top,rectGroup,data, false);
	}
};

class CPanelCtrl : public CPanelCtrlImpl<CPanelCtrl>, public CDynamicDialogResize<CPanelCtrl>
{
public:
	DECLARE_WND_SUPERCLASS(_T("WTL_PanelCtrl"), GetWndClassName())
	
	bool m_bUseMinTrackSize;

	CPanelCtrl() : m_bUseMinTrackSize(false)
	{
	}

	BEGIN_MSG_MAP(CPanelCtrl)
		CHAIN_MSG_MAP(CPanelCtrlImpl<CPanelCtrl>)
		CHAIN_MSG_MAP(CDynamicDialogResize<CPanelCtrl>)
	END_MSG_MAP()

	void Init()
	{
		CPanelCtrlImpl<CPanelCtrl>::Init();

		DlgResize_Init(false,m_bUseMinTrackSize);
	}
};

#ifndef _WIN32_WCE

class CFramePanelCtrl : public CPanelCtrl, public CFrameDialog<CFramePanelCtrl>
{
public:
	BEGIN_MSG_MAP(CFramePanelCtrl)
		CHAIN_MSG_MAP(CFrameDialog<CFramePanelCtrl>)
		CHAIN_MSG_MAP(CPanelCtrl)
	END_MSG_MAP()

	BOOL RepositionDialog()
	{
		typedef WTL::CFrameDialog<CFramePanelCtrl> base;
		BOOL bRet = base::RepositionDialog();

		if (m_hWndStatusBar != NULL)
		{
		
			RECT rectSB = { 0 };
			::GetWindowRect(m_hWndStatusBar, &rectSB);
			ScreenToClient(&rectSB);
			m_sizeDialog.cy += rectSB.bottom-rectSB.top;
			
			UpdateFrameLayout();
		}	

		return bRet;
	}
};									 

#endif 

}; // namespace WTL

#endif //__VFCPANEL_H__