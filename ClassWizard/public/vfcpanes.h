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

// Module: vfcpanes.h
// Creator: visualfc 
// Email: visualfc@gmail.com
// open source: http://sf.net/projects/visualfc
// Date: 2008-01-06

#ifndef __VFCPANES_H__
#define __VFCPANES_H__

#ifndef __ATLCTRLX_H__
	#include <atlctrlx.h>
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes in this file:
//
// CLayoutPanes

namespace WTL
{

class CLayoutPanes : public CPaneContainerImpl<CLayoutPanes>
{
public:
	BEGIN_MSG_MAP(CLayoutPanes)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		CHAIN_MSG_MAP(CPaneContainerImpl<CLayoutPanes>)
		FORWARD_NOTIFICATIONS()
	END_MSG_MAP()

	DECLARE_WND_CLASS_EX(_T("WTL_LayoutPanes"), 0, -1)

	void UpdateLayout()
	{
		RECT rcClient = { 0 };
		GetClientRect(&rcClient);
		UpdateLayout(rcClient.right, rcClient.bottom);
	}

	void UpdateLayout(int cxWidth, int cyHeight)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		RECT rect = { 0 };

		if(IsVertical())
		{
			::SetRect(&rect, 0, 0, m_cxyHeader, cyHeight);
			if(m_tb.m_hWnd != NULL)
				m_tb.SetWindowPos(NULL, m_cxyBorder, m_cxyBorder + m_cxyBtnOffset, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);

			if(m_wndClient.m_hWnd != NULL)
			{
				RECT rc = { m_cxyHeader, 0, cxWidth, cyHeight };
				DWORD dwFlag = SWP_NOZORDER;
				if (m_wndClient.GetParent() != m_hWnd)
				{
					dwFlag = 0;
					ClientToScreen(&rc);
					CWindow(m_wndClient.GetParent()).ScreenToClient(&rc);
				}
				//m_wndClient.SetWindowPos(NULL, m_cxyHeader, 0, cxWidth - m_cxyHeader, cyHeight, SWP_NOZORDER);
				m_wndClient.SetWindowPos(NULL, rc.left, rc.top, cxWidth - m_cxyHeader, cyHeight, dwFlag);
			}
			else
				rect.right = cxWidth;
		}
		else
		{
			::SetRect(&rect, 0, 0, cxWidth, m_cxyHeader);
			if(m_tb.m_hWnd != NULL)
				m_tb.SetWindowPos(NULL, rect.right - m_cxToolBar, m_cxyBorder + m_cxyBtnOffset, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);

			if(m_wndClient.m_hWnd != NULL)
			{
				RECT rc = { 0, m_cxyHeader,  cxWidth, cyHeight };
				DWORD dwFlag = SWP_NOZORDER;
				if (m_wndClient.GetParent() != m_hWnd)
				{
					dwFlag = 0;
					ClientToScreen(&rc);
					CWindow(m_wndClient.GetParent()).ScreenToClient(&rc);
				}
				m_wndClient.SetWindowPos(NULL, rc.left, rc.top, cxWidth, cyHeight - m_cxyHeader, dwFlag);
			//	m_wndClient.SetWindowPos(NULL, 0, m_cxyHeader, cxWidth, cyHeight - m_cxyHeader, SWP_NOZORDER);
			}
			else
				rect.bottom = cyHeight;
		}

		InvalidateRect(&rect);
	}

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
#ifndef _WIN32_WCE
		ModifyStyleEx(0,WS_EX_CONTROLPARENT,0);	
#endif
		return 0;
	}
};

}; //namespace WTL

#endif //__VFCPANES_H__