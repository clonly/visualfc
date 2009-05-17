// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "aboutdlg.h"
#include "MainDlg.h"

BOOL CMainDlg::PreTranslateMessage(MSG* pMsg)
{
	return CWindow::IsDialogMessage(pMsg);
}

BOOL CMainDlg::OnIdle()
{
	return FALSE;
}

LRESULT CMainDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// center the dialog on the screen
	CenterWindow();

	// set icons
	HICON hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
		IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
	SetIcon(hIcon, TRUE);
	HICON hIconSmall = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
		IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
	SetIcon(hIconSmall, FALSE);

	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);

	UIAddChildWindowContainer(m_hWnd);

	DoDataExchange(false);
	m_wndSplit.SetSplitterPanes(m_projTree,m_projList);
	m_wndSplit.SetSplitterPos(100);

	DlgResize_Init();

	BOOL b = m_imageList.Create(IDB_IMAGE,32,1,ILC_COLOR24);
	m_projList.SetImageList(m_imageList,LVSIL_SMALL);
	m_projList.SetImageList(m_imageList,LVSIL_NORMAL);

	LoadAppWiz();
//	LoadCodeWiz();

	return TRUE;
}

LRESULT CMainDlg::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// unregister message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->RemoveMessageFilter(this);
	pLoop->RemoveIdleHandler(this);

	m_imageList.Destroy();

	return 0;
}

LRESULT CMainDlg::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CAboutDlg dlg;
	dlg.DoModal();
	return 0;
}

LRESULT CMainDlg::OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add validation code 
	CloseDialog(wID);
	return 0;
}

LRESULT CMainDlg::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CloseDialog(wID);
	return 0;
}

void CMainDlg::CloseDialog(int nVal)
{
	DestroyWindow();
	::PostQuitMessage(nVal);
}

LRESULT CMainDlg::OnGoBtn(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	RunWizard();
	return 0;
}
LRESULT CMainDlg::OnItemchangedProjectList(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
{
	int icur = m_projList.GetSelectionMark();
	if (icur == -1)
		return 0;
	fox::simple_plugin::config_base * cfg = (fox::simple_plugin::config_base*)(void*)m_projList.GetItemData(icur);
	if (cfg)
	{
		m_projEdit.SetWindowText(cfg->get_title());
	}
	return 0;
}
LRESULT CMainDlg::OnNmDblclkProjectList(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
{
	RunWizard();
	return 0;
}
LRESULT CMainDlg::OnTvnSelchangedProjectTree(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
{
	ChangeTree();
	return 0;
}
LRESULT CMainDlg::OnNmClickProjectTree(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
{
	ChangeTree();
	return 0;
}
/*
CString GetFilePath(fox::plugin::config & cfg)
{
	CString path = cfg.path;
	path += _T("\\");
	path += cfg.runtime.library;
	return path;
}
*/
BOOL CMainDlg::LoadAppWiz()
{
	if (!m_appwiz.load(WTL::GetExePath()+_T("\\AppWizard")))
		return FALSE;
	std::set<CString> tree;
	for (int i = 0, j = 0; i < m_appwiz.ar.size(); i++)
	{
		fox::appwiz_config & cfg = m_appwiz.ar[i];
		CString path = cfg.rootPath+_T("\\")+cfg.icon;

		HICON hIcon = (HICON)::LoadImage(_Module.m_hInst,path,IMAGE_ICON,32,32,LR_DEFAULTCOLOR | LR_LOADFROMFILE);
		if (hIcon)
		{
			m_imageList.AddIcon(hIcon);
			::DestroyIcon(hIcon);
			j++;
			cfg.iIcon = j;
		}
		else
		{
			cfg.iIcon = 0;
		}
		int item = m_projList.InsertItem(i,m_appwiz.ar[i].name,cfg.iIcon);

		tree.insert(cfg.root);

		m_projList.SetItemData(item,(DWORD)&cfg);
	}
	
	for (std::set<CString>::iterator it = tree.begin(); it != tree.end(); it++)
	{
		HTREEITEM item = m_projTree.InsertItem(*it,TVI_ROOT,NULL);


	}
	return TRUE;
}

BOOL CMainDlg::LoadCodeWiz()
{
	if (!m_codewiz.load(WTL::GetExePath() + _T("\\CodeWiz")) )
		return FALSE;
	for (int i = 0, j = 0; i < m_codewiz.ar.size(); i++)
	{
		fox::codewiz_config & cfg = m_codewiz.ar[i];
		CString path = cfg.rootPath+_T("\\")+cfg.icon;

		HICON hIcon = (HICON)::LoadImage(_Module.m_hInst,path,IMAGE_ICON,32,32,LR_DEFAULTCOLOR | LR_LOADFROMFILE);
		if (hIcon)
		{
			m_imageList.AddIcon(hIcon);
			::DestroyIcon(hIcon);
			j++;
			cfg.iIcon = j;
		}
		else
		{
			cfg.iIcon = 0;
		}
		int item = m_projList.InsertItem(i,m_codewiz.ar[i].name,cfg.iIcon);

		m_projList.SetItemData(item,(DWORD)&cfg);
	}
	return TRUE;
}


BOOL CMainDlg::RunWizard()
{
	int icur = m_projList.GetSelectionMark();
	if (icur == -1)
		return FALSE;
	fox::simple_plugin::config_base * cfg = (fox::simple_plugin::config_base*)(void*)m_projList.GetItemData(icur);
	if (cfg == 0)
		return FALSE;
	
	if (cfg->guid == _T("appwiz"))
	{
		return RunAppWizard((fox::appwiz_config*)cfg);
	}
	return FALSE;
}

BOOL CMainDlg::RunAppWizard(fox::appwiz_config *cfg)
{
	fox::simple_plugin::loadlib lib;
	CString path = cfg->rootPath+_T("\\")+cfg->runtime;
	if (lib.load(path))
	{
		int (*run_wizard)(const char *) = NULL;
		int (*run_wizard_ex)(fox::codewiz_args*) = NULL;
		if (lib.GetFunc(run_wizard_ex,"run_wizard_ex"))
		{
			char ids[][20] = {"IDD_ABOUT","IDD_MAINDLG"};
			const char * ptr[2];
			ptr[0] = ids[0];
			ptr[1] = ids[1];
			fox::codewiz_args args;
			lstrcpy(args.codewiz_name,cfg->name);
			lstrcpy(args.codewiz_info,cfg->info);
			lstrcpy(args.template_path,cfg->rootPath+_T("\\")+cfg->templates);
			lstrcpy(args.project_path,"c:\\test");
			lstrcpy(args.project_name,"test");
			lstrcpy(args.idd,"IDD_ABOUT");
			args.idd_num = 2;
			args.idd_array = ptr;
			int ret = (*run_wizard_ex)(&args);
			if (ret == 0)
			{
				CString text;
				fox::code_file * next = &args.return_files;
				while (next)
				{
					text += _T("file: ");
					text += next->path;
					text += "\r\n";
					next = next->next;
				}
				MessageBox(text,_T("Code Wizard"));
				return TRUE;
			}
		}
		else if (lib.GetFunc(run_wizard,"run_wizard"))
		{
			int ret = (*run_wizard)(cfg->rootPath+_T("\\")+cfg->templates);
			if (ret == 0)
			{
				CloseDialog(IDOK);
				return TRUE;
			}
		}
	}
	return FALSE;
}

void CMainDlg::ChangeTree()
{
	HTREEITEM item = m_projTree.GetSelectedItem();
	CString root;
	m_projTree.GetItemText(item,root);

	m_projList.DeleteAllItems();
	for (int i = 0; i < m_appwiz.ar.size(); i++)
	{
		fox::appwiz_config & cfg = m_appwiz.ar[i];
		if (cfg.root == root)
		{
			int item = m_projList.InsertItem(i,m_appwiz.ar[i].name,cfg.iIcon);
			m_projList.SetItemData(item,(DWORD)&cfg);

		}
	}
}
