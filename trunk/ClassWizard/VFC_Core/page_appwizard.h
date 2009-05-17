#ifndef _PAGE_APPWIZARD_H_
#define _PAGE_APPWIZARD_H_

#include "../public/appwiz_plugin.h"
#include "../public/codewiz_plugin.h"
#include <set>

class page_appwizard : public ui_page_dialog_t<page_appwizard,IDD_PAGE_APPWIZARD>,
					   public page_base_t<page_appwizard>,
					   public CWinDataExchange<page_appwizard>
{
public:
	CTreeViewCtrl	m_rootTree;
	std::vector<CString> ar_idd;
	CString				 strProjectName;
	void OnProjectChange(project_dsp * dsp)
	{
		strProjectName = dsp->project_name;
		ar_idd.clear();

		std::vector<CResDialog*> array;
		for (size_t i = 0; i < pcode->m_Tokens.GetCount(); i++)
		{
			Token * tk = pcode->m_Tokens[i];
			if (tk->m_TokenKind == tkClass)
			{
				CResDialog * res = pcode->GetResDialog(tk);
				if (res != NULL)
				{
					array.push_back(res);
				}
			}
		}
		for (size_t i = 0; i < pcode->m_Res.m_Dialogs.GetCount(); i++)
		{
			size_t j = 0;
			for (j = 0; j < array.size(); j++)
			{
				if (array[j] == &pcode->m_Res.m_Dialogs[i])
				{
					break;
				}
			}
			if (j == array.size())
			{
				ar_idd.push_back(pcode->m_Res.m_Dialogs[i].m_ID);
			}
		}
	}

	BEGIN_MSG_MAP(page_appwizard)
		NOTIFY_HANDLER(IDC_ROOT_TREE, TVN_SELCHANGED, OnTvnSelchangedRootTree)
		NOTIFY_HANDLER(IDC_ROOT_TREE, NM_CLICK, OnNmClickRootTree)
		COMMAND_ID_HANDLER(IDC_GO_BTN, OnGoBtn)
		NOTIFY_HANDLER(IDC_APPWIZARD_LIST, NM_DBLCLK, OnNmDblclkAppwizardList)
		NOTIFY_HANDLER(IDC_APPWIZARD_LIST, NM_CLICK, OnNmClickAppwizardList)
		NOTIFY_HANDLER(IDC_APPWIZARD_LIST, LVN_ITEMCHANGED, OnLvnItemchangedAppwizardList)
		CHAIN_MSG_MAP(ui_page_dialog_base)
	END_MSG_MAP()

	CString m_wizardPath;
	
	CEdit	m_projEdit;
	CListViewCtrl	m_projList;
	fox::simple_plugin::manager<fox::appwiz_config> m_plugin;
	CImageList		m_imageList;

	BEGIN_DLGRESIZE_MAP(page_appwizard)
		DLGRESIZE_CONTROL(IDC_ROOT_TREE, DLSZ_SIZE_Y)
		DLGRESIZE_CONTROL(IDC_APPWIZARD_LIST, DLSZ_SIZE_X | DLSZ_SIZE_Y)
		DLGRESIZE_CONTROL(IDC_GO_BTN, DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(IDC_APPWIZARD_INFO, DLSZ_SIZE_X | DLSZ_MOVE_Y)
	END_DLGRESIZE_MAP()
	
	BEGIN_DDX_MAP(page_appwizard)
		DDX_CONTROL_HANDLE(IDC_ROOT_TREE, m_rootTree)
		DDX_CONTROL_HANDLE(IDC_APPWIZARD_LIST, m_projList)
		DDX_CONTROL_HANDLE(IDC_APPWIZARD_INFO, m_projEdit)
	END_DDX_MAP();
	
	page_appwizard()
	{
		m_wizardPath = _T("AppWizard");
		m_imageList.Create(IDB_IMAGE,32,1,ILC_COLOR24);
	}
	~page_appwizard()
	{
		m_imageList.Destroy();
	}
	void OnInit()
	{
		DoDataExchange(false);

		m_projList.SetImageList(m_imageList,LVSIL_SMALL);
		m_projList.SetImageList(m_imageList,LVSIL_NORMAL);
		LoadPlugins();
	}
	BOOL LoadPlugins()
	{
		if (!m_plugin.load(GetModulePath(_Module.m_hInst)+_T("\\")+m_wizardPath))
			return FALSE;
		std::set<CString> root_set;
		for (int i = 0, j = 0; i < m_plugin.ar.size(); i++)
		{
			fox::appwiz_config & cfg = m_plugin.ar[i];
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
		//	int item = m_projList.InsertItem(i,m_plugin.ar[i].name,cfg.iIcon);
			root_set.insert(cfg.root);
		//	m_projList.SetItemData(item,i);
		}
		m_rootTree.InsertItem(_T("All"),TVI_ROOT,NULL);
		for (std::set<CString>::iterator it = root_set.begin(); it != root_set.end(); it++)
		{
			HTREEITEM item = m_rootTree.InsertItem(*it,TVI_ROOT,NULL);
		}

		DoTreeChanged("All",true);
		return TRUE;
	}
	BOOL RunWizard()
	{
		int icur = m_projList.GetSelectionMark();
		if (icur == -1)
			return FALSE;

		fox::appwiz_config * cfg = (fox::appwiz_config*)m_projList.GetItemData(icur);
		if (cfg == NULL)
			return FALSE;
		return RunAppWizard(*cfg);
	}
	BOOL RunAppWizard(fox::appwiz_config & cfg)
	{
		fox::simple_plugin::loadlib lib;
		CString path = cfg.rootPath+_T("\\")+cfg.runtime;
		if (lib.load(path))
		{
			int (*run_wizard)(const char *) = NULL;
			int (*run_wizard_ex)(fox::codewiz_args*) = NULL;
			if (lib.GetFunc(run_wizard_ex,"run_wizard_ex"))
			{
				std::vector<const char*> ptr;
				for (size_t i = 0; i < ar_idd.size(); i++)
				{
					ptr.push_back(ar_idd[i]);
				}
				fox::codewiz_args args;
				lstrcpy(args.codewiz_name,cfg.name);
				lstrcpy(args.codewiz_info,cfg.info);
				lstrcpy(args.template_path,cfg.rootPath+_T("\\")+cfg.templates);
				if (pcodeup->pVSAddin != NULL)
				{
					lstrcpy(args.project_path,pcodeup->pVSAddin->get_project_path());
				}
				lstrcpy(args.project_name,this->strProjectName);
				if (ar_idd.size() != 0)
				{
					lstrcpy(args.idd,ar_idd[0]);
				}
				args.idd_num = ar_idd.size();
				args.idd_array = &ptr[0];
				int ret = (*run_wizard_ex)(&args);
				if (ret == 0 && pcodeup->pVSAddin != NULL)
				{
					CString text = args.codewiz_name;
					text += _T("\r\n\r\n");
					text += _T("Add project files:\r\n");
					fox::code_file * next = &args.return_files;
					while (next)
					{
						pcodeup->pVSAddin->add_project_file(next->path);
						text += _T("file:\t");
						text += next->path;
						text += _T("\t\r\n");
						next = next->next;
					}
					MessageBox(text,"Code Wizard", MB_ICONASTERISK);
					return TRUE;
				}
			}
			else if (lib.GetFunc(run_wizard,"run_wizard"))
			{
				int ret = (*run_wizard)(cfg.rootPath+_T("\\")+cfg.templates);
				if (ret == 0)
				{
					return TRUE;
				}
			}
		}
		return FALSE;
	}

	BOOL DoItemChanged()
	{
		int icur = m_projList.GetSelectionMark();
		if (icur == -1)
			return FALSE;
		fox::appwiz_config * cfg = (fox::appwiz_config*)m_projList.GetItemData(icur);
		if (cfg)
		{
			m_projEdit.SetWindowText(cfg->get_title());
		}
		else
		{
			m_projEdit.SetWindowText("");
		}
		return TRUE;
	}
	
	BOOL DoTreeChanged(LPCTSTR lpszRoot = "", bool bAll = false)
	{
		CString root = lpszRoot;
		if (root.IsEmpty())
		{
			HTREEITEM item = m_rootTree.GetSelectedItem();
			m_rootTree.GetItemText(item,root);
		}	
		if (root == "All")
		{
			bAll = true;
		}
		m_projList.DeleteAllItems();
		for (int i = 0; i < m_plugin.ar.size(); i++)
		{
			fox::appwiz_config & cfg = m_plugin.ar[i];
			if (cfg.root == root || bAll)
			{
				int item = m_projList.InsertItem(i,m_plugin.ar[i].name,cfg.iIcon);
				m_projList.SetItemData(item,(DWORD)&cfg);			
			}
		}
		return TRUE;
	}

	LRESULT OnGoBtn(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		RunWizard();
		return 0;
	}
	LRESULT OnNmDblclkAppwizardList(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
	{
		RunWizard();
		return 0;
	}
	LRESULT OnNmClickAppwizardList(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
	{
		DoItemChanged();
		return 0;
	}
	LRESULT OnLvnItemchangedAppwizardList(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
	{
		DoItemChanged();
		return 0;
	}
	LRESULT OnNmClickRootTree(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
	{
		DoTreeChanged();
		return 0;
	}
	LRESULT OnTvnSelchangedRootTree(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
	{
		DoTreeChanged();
		return 0;
	}
};

#endif