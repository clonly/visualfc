#ifndef _ATL_TABCTRLEX_H_
#define _ATL_TABCTRLEX_H_

class CTabCtrlEx : public CWindowImpl<CTabCtrlEx,CTabCtrl>
{
protected:
	int		m_nCurSel;
	int		m_top;
public:
	CTabCtrlEx() : m_nCurSel(-1), m_top(70)
	{
	}
	DECLARE_WND_SUPERCLASS(NULL, CTabCtrl::GetWndClassName())
	BOOL PreTranslateMessage(MSG* pMsg)
	{
		if(IsWindow() == FALSE)
			return FALSE;

		BOOL bRet = FALSE;

		// Check for TabView built-in accelerators (Ctrl+Tab/Ctrl+Shift+Tab - next/previous page)
		int nCount = GetItemCount();
		if(nCount > 0)
		{
			bool bControl = (::GetKeyState(VK_CONTROL) < 0);
			if((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_TAB) && bControl)
			{
				if(nCount > 1)
				{
					int nPage = m_nCurSel;
					bool bShift = (::GetKeyState(VK_SHIFT) < 0);
					if(bShift)
						nPage = (nPage > 0) ? (nPage - 1) : (nCount - 1);
					else
						nPage = ((nPage >= 0) && (nPage < (nCount - 1))) ? (nPage + 1) : 0;

					SetActiveItem(nPage);
				}

				bRet = TRUE;
			}
		}

		// If we are doing drag-drop, check for Escape key that cancels it
		// Pass the message to the active page
		if(bRet == FALSE)
		{
			if(m_nCurSel != -1)
			{
			//	bRet = (BOOL)::SendMessage(GetPageHWND(m_nActivePage), WM_FORWARDMSG, 0, (LPARAM)pMsg);
				if (::IsDialogMessage(GetItemClient(m_nCurSel),pMsg))
					return TRUE;
			}
		}

		return CWindowImpl<CTabCtrlEx,CTabCtrl>::IsDialogMessage(pMsg);
	}

public:
	int InsertItemEx(LPCTSTR lpszItem, HWND hWnd, int iImage = 0)
	{
		return InsertItemEx(GetItemCount(),lpszItem,hWnd,iImage);
	}
	int InsertItemEx(int nItem, LPCTSTR lpszItem, HWND hWnd, int iImage = 0)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		TCITEM tci = { 0 };
		tci.mask = TCIF_TEXT | TCIF_IMAGE;
		tci.pszText = (LPTSTR) lpszItem;
		tci.iImage = iImage;
		int nRet = (int)::SendMessage(m_hWnd, TCM_INSERTITEM, nItem, (LPARAM)&tci);
		if (nRet != -1)
		{
			SetItemClient(nItem,hWnd);
		}
		return nRet;
	}
	BOOL SetItemClient(int nItem, HWND hWnd)
	{	
		TCITEM tci = {0};
		tci.mask = TCIF_PARAM;
		tci.lParam = (DWORD)hWnd;
		::SendMessage(m_hWnd,TCM_SETITEM,nItem,(LPARAM)&tci);

		RECT rc;
		GetClientRect(&rc);
		AdjustRect(FALSE,&rc);
		rc.left -= 2;
		rc.top  += m_top;

		::SetParent(hWnd,m_hWnd);
		::MoveWindow(hWnd,rc.left,rc.top,rc.right-rc.left,rc.bottom-rc.top,TRUE);

		return TRUE;
	}
	HWND GetItemClient(int nItem)
	{
		TCITEM tci = {0};
		tci.mask = TCIF_PARAM;
		::SendMessage(m_hWnd,TCM_GETITEM,nItem,(LPARAM)&tci);
		return (HWND)tci.lParam;
	}
	BOOL SetActiveItem(int nItem)
	{
		if (m_nCurSel != nItem)
		{
			HWND hOldWnd = GetItemClient(m_nCurSel);
			::ShowWindow(hOldWnd,SW_HIDE);
			m_nCurSel = nItem;
		}
		SetCurSel(nItem);
		HWND hWnd = GetItemClient(nItem);
		::ShowWindow(hWnd,SW_SHOW);
		return hWnd != NULL;
	}

public:
	BEGIN_MSG_MAP(CTabCtrlEx)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		REFLECTED_NOTIFY_CODE_HANDLER(TCN_SELCHANGE, OnSelchangeTab)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()

	LRESULT OnSelchangeTab(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
	{
		// TODO : Add Code for control notification handler.
		int nItem = GetCurSel();
		SetActiveItem(nItem);
		return 0;
	}
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// TODO : Add Code for message handler. Call DefWindowProc if necessary.
		for (int i = 0; i < GetItemCount(); i++)
		{
			HWND hWnd = GetItemClient(i);
			RECT rc;
			GetClientRect(&rc);
			AdjustRect(FALSE,&rc);
			rc.left -= 2;
			rc.top  += m_top;

			::MoveWindow(hWnd,rc.left,rc.top,rc.right-rc.left,rc.bottom-rc.top,TRUE);
		}
		return 0;
	}
};

#endif //