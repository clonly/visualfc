#ifndef _WIZARDUI_H__
#define _WIZARDUI_H__
/*
#include <ShlGuid.h>
#include <atlapp.h>
#include <atlwin.h>
#include <atlmisc.h>
#include <atlframe.h>
#include <atlctrls.h>
#include <atlctrlx.h>
#include <atlsplit.h>
#include <atlddx.h>

#include "vfcframe.h"
#include "vfcpanel.h"
#include "vfcsplit.h"
#include "vfcpanes.h"

#include <map>

#include "../public/atltabex.h"
#include "../public/foxlib.h"
#include "../public/foxuilib.h"
#include "../public/qevent.h"
#include "../public/vfcfonts.h"
#include "../public/vfcsplit.h"
*/
#include "datalist_t.h"

#include "./codeparser.h"
#include "./codeupdate.h"
#include "./resource.h"

#include "page_base_t.h"

#include "page_winx_event.h"
#include "page_class_info.h"

//dialog resize
#include "page_dlsz_t.h"
#include "page_wtl_dlsz.h"
#include "page_winx_dlsz.h"

//dialog font
#include "page_font_t.h"
#include "page_wtl_font.h"
#include "page_winx_font.h"

//dialog notify
#include "page_notify_t.h"
#include "page_wtl_notify.h"
#include "page_winx_notify.h"

//dialog ddx
#include "page_ddx_t.h"
#include "page_wtl_ddx.h"
#include "page_winx_ddx.h"

//update ui
#include "page_upui_t.h"
#include "page_wtl_upui.h"
#include "page_winx_upui.h"

#include "wtl_event.h"
#include "page_event_t.h"
#include "page_wtl_event.h"
#include "vfc_config.h"
//page tools
#include "page_tools.h"
//page setup
#include "page_setup.h"
//page appwizard
#include "page_appwizard.h"
//page codewiz

class page_about : public ui_page_dialog_t<page_about,IDD_PAGE_ABOUT>,
				   public page_base_t<page_about>
{
public:
	CString addin_name;
	void OnInit()
	{
		CStatic win = GetDlgItem(IDC_VERSION_STATIC);
		win.SetWindowText(_T("VisualFC for ")+addin_name);
	}
};

class wizard_ui_item : public ui_simple_dialog_t<wizard_ui_item,IDD_WIZARD_DIALOG,true>,
					   public CMessageFilter, public CDialogFont<wizard_ui_item>
{
public:
public:
	BEGIN_DLGFONT_MAP(wizard_ui_item)
		DLGFONT_CONTROL_EX(IDC_PAGE_NAME, -18,0,0,0,700,255,0,0,0,3,2,1,18,_T("Times New Roman"))
		//DLGFONT_CONTROL_EX(IDC_PAGE_NAME, -20,0,0,0,700,255,0,0,0,3,2,1,18,_T("Times New Roman"))
	END_DLGFONT_MAP()
	
	virtual	void register_item(){}	//bind event
protected:
//	plugin::manager		m_plugins;
	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
	//	if (m_wndTab.PreTranslateMessage(pMsg))
	//		return TRUE;
		if (m_wndActivePage && ::IsDialogMessage(m_wndActivePage,pMsg))
			return TRUE;
		return CWindow::IsDialogMessage(pMsg);
	}

protected:
	codeparser			  & m_code;
	codeupdate			  & m_codeup;
	Token				  * m_tkcls;
	CAtlArray<tag_token*>	m_tags;
	CAtlArray<HTREEITEM>	m_items;
	CSimpleArray<project_dsp>	m_projects;
	
protected:
	CComboBox			m_projectCmb;
	CComboBox			m_classCmb;
	CComboBox			m_dialogCmb;
	CComboBox			m_menuCmb;
//	CTabCtrlEx			m_wndTab;
	CTreeViewCtrl		m_wndTree;
	HTREEITEM			m_itemNoProj;
	HWND				m_wndActivePage;

/*
	page_winx_event		m_page_winx_event;
	page_winx_notify	m_page_winx_notify;
	page_winx_font		m_page_winx_font;
	page_class_info		m_page_class_info;
	page_winx_dlsz		m_page_winx_dlsz;

	page_wtl_notify		m_page_wtl_notify;
	page_wtl_ddx		m_page_wtl_ddx;
	page_wtl_dlsz		m_page_wtl_dlsz;
	page_wtl_font		m_page_wtl_font;
*/
	page_about			m_page_about;
protected:
	QLib::Event<void,project_dsp*>		EventProjectChange;
	QLib::Event<void,WORD>				EventCloseProject;
	QLib::Event<void,Token*>		EventClassChange;
	QLib::Event<void,CResDialog*>	EventResDialogChange;
	QLib::Event<void,CResMenu*>		EventResMenuChange;
public:
/*
	template <typename T>
	void register_page(T & page, LPCTSTR lpszPageName = NULL)
	{
		page.pcode = &m_code;
		page.Create(m_hWnd);

		EventClassChange.bind(&page,&T::OnClassChange);
		EventResDialogChange.bind(&page,&T::OnResDialogChange);
		EventResMenuChange.bind(&page,&T::OnResMenuChange);
		EventCloseProject.bind(&page,&T::OnCloseProject);

		if (lpszPageName == NULL)
			m_wndTab.InsertItemEx(page.page_name(),page);
		else
			m_wndTab.InsertItemEx(lpszPageName,page);

		page.EventGoToLine.bind(this,&wizard_ui_item::OnGetToLine);
	}
*/
	template <typename T>
	HTREEITEM register_page(T & page, HTREEITEM root, LPCTSTR lpszPageName = NULL, bool bEventUser = false)
	{
		page.pcode = &m_code;
		page.pcodeup = &m_codeup;

		if (page.m_hWnd == NULL)
		{
			page.Create(m_hWnd);
		}

		EventProjectChange.bind(&page,&T::OnProjectChange);
		EventClassChange.bind(&page,&T::OnClassChange);
		EventResDialogChange.bind(&page,&T::OnResDialogChange);
		EventResMenuChange.bind(&page,&T::OnResMenuChange);
		EventCloseProject.bind(&page,&T::OnCloseProject);

		HTREEITEM item = NULL;
		if (lpszPageName == NULL)
			item = m_wndTree.InsertItem(page.page_name(),root,NULL);
		else
			item = m_wndTree.InsertItem(lpszPageName,root,NULL);

		if (item)
		{
			m_items.Add(item);
			m_wndTree.SetItemData(item,(DWORD)page.m_hWnd);
		}

		page.EventGoToLine.bind(this,&wizard_ui_item::OnGetToLine);

		return item;
	}

	void register_tag(tag_token * tag)
	{
		if (tag != NULL)
		{
			m_tags.Add(tag);
		}
	}

	wizard_ui_item(codeparser & code, codeupdate & codeup) : m_code(code), m_codeup(codeup)
	{
		m_codeup.pcode = &m_code;
		m_codeup.ptags = &m_tags;
	}
	virtual const char * name()
	{
		return "Winx Wizard";
	}
	virtual void set_vsaddin(fox::vs_addin * pvs)
	{
		m_codeup.pVSAddin = NULL;
		m_codeup.pVSAddin = pvs;

		if (pvs)
		{
			m_page_about.addin_name = pvs->get_addin_name();
		}
	}
public:
	BEGIN_MSG_MAP(wizard_ui_item)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		NOTIFY_HANDLER(IDC_PAGE_TREE, TVN_SELCHANGED, OnTvnSelchangedPageTree)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
	//	MESSAGE_HANDLER(WM_CLOSE, OnClose)
		COMMAND_HANDLER(IDC_CLASSNAME_COMBO, CBN_SELENDOK, OnSelchangeClassnameCombo)
		COMMAND_HANDLER(IDC_RESDIALOG_COMBO, CBN_SELENDOK, OnSelchangeResDialogCombo)
		COMMAND_HANDLER(IDC_RESMENU_COMBO,   CBN_SELENDOK, OnSelchangeResMenuCombo)
		CHAIN_MSG_MAP(ui_simple_dialog_base)
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

	BEGIN_DLGRESIZE_MAP(wizard_ui_item)
		//DLGRESIZE_CONTROL(IDC_PAGE_NAME, DLSZ_MOVE_Y)
		DLGRESIZE_CONTROL(IDC_LINE_STATIC, DLSZ_SIZE_X | DLSZ_MOVE_Y)
		DLGRESIZE_CONTROL(IDC_PAGE_TREE, DLSZ_SIZE_Y )
		DLGRESIZE_CONTROL(IDC_PAGE_STATIC, DLSZ_SIZE_X | DLSZ_SIZE_Y)
		DLGRESIZE_CONTROL(IDOK,DLSZ_MOVE_X | DLSZ_MOVE_Y)
		DLGRESIZE_CONTROL(IDCANCEL,DLSZ_MOVE_X | DLSZ_MOVE_Y)
	//	DLGRESIZE_CONTROL(IDC_PROJECT_COMBO,DLSZ_MOVE_Y)
	END_DLGRESIZE_MAP()
public:
//	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
//	{
//		HideLoop();
//		return 0;
//	}

//	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	{
		//enbale parent hwnd
//		HideLoop();
//		EventCloseProject(wID);
//		if (wID == IDCANCEL)
//			return wID;
//		m_codeup.ProcessUpdate();
//		m_code.ClearDSP();
//		return wID;
//	}
	BOOL OnClose()
	{
		EventCloseProject(IDOK);
		m_codeup.ProcessUpdate();
		m_code.ClearDSP();
		return TRUE;
	}
public:
	int AddProject(const char * project_name, const char * active_file)
	{
		project_dsp dsp;
		dsp.project_name = project_name;
		dsp.active_file = active_file;
		m_projects.Add(dsp);
		project_dsp * pdsp = &m_projects[m_projects.GetSize()-1];
		int item = m_projectCmb.AddString(pdsp->project_name);
		m_projectCmb.SetItemData(item,(DWORD)pdsp);
		return item;
	}
	void AddProjectClass(Token * tk)
	{
		int index = m_classCmb.AddString(tk->m_Name);
		m_classCmb.SetItemData(index,(DWORD)tk);
	}
	void AddProjectDialog(CResDialog * dlg)
	{
		int index = m_dialogCmb.AddString(dlg->m_ID);
		m_dialogCmb.SetItemData(index,(DWORD)dlg);
	}
	void AddProjectMenu(CResMenu * menu)
	{
		int index = m_menuCmb.AddString(menu->m_ID);
		m_menuCmb.SetItemData(index,(DWORD)menu);
	}

	void OnGetToLine(Token * tk)
	{
		if (m_codeup.GotoLine(tk) == true)
		{
			EndDialog(IDOK);
		}
	}

	void OnInit()
	{
		CenterWindow();
		m_itemNoProj = NULL;


		m_cfg.load();
		
		//enbale parent hwnd
		//m_wndTab.SubclassWindow(GetDlgItem(IDC_PANE_TAB));
		//m_wndTab.SetMinTabWidth(100);

		m_wndTree = GetDlgItem(IDC_PAGE_TREE);
		m_wndActivePage = NULL;

		m_projectCmb = GetDlgItem(IDC_PROJECT_COMBO);
		m_classCmb   = GetDlgItem(IDC_CLASSNAME_COMBO);
		m_dialogCmb  = GetDlgItem(IDC_RESDIALOG_COMBO);
		m_menuCmb    = GetDlgItem(IDC_RESMENU_COMBO);

		//virtual function
		
		EventProjectChange.bind(this,&wizard_ui_item::OnProjectChange);
		EventClassChange.bind(this,&wizard_ui_item::OnClassChange);
		EventResDialogChange.bind(this,&wizard_ui_item::OnResDialogChange);

		register_item();

		DlgFont_Init();

		//Loop.AddMessageFilter(this);

		//load project_dsp
		vfc_config cfg;
		cfg.load();

		if (lstrlen(m_dsp.active_file) == 0 && lstrlen(m_dsp.project_name) == 0)
		{
			if (m_itemNoProj != NULL)
				m_wndTree.SelectItem(m_itemNoProj);
		//	ShowLoop();
			return;
		}
		
		int item  = AddProject(m_dsp.project_name,m_dsp.active_file);
		project_dsp * pdsp = (project_dsp*)m_projectCmb.GetItemData(item);
		m_projectCmb.SetCurSel(item);
		EventProjectChange(pdsp);
	}
	
	vfc_config m_cfg;
	project_dsp m_dsp;

//DEL 	virtual void load_project(HWND hHostWnd, const char * name, const char * dspfile, bool bAppend)
//DEL 	{
//DEL 		m_dsp.project_name = name;
//DEL 		m_dsp.active_file = dspfile;
//DEL 		DoModal();
//DEL 		return;
//DEL 
//DEL 		vfc_config cfg;
//DEL 		cfg.load();
//DEL 		if (cfg != m_cfg)
//DEL 		{
//DEL 			m_wndTree.DeleteAllItems();
//DEL 			register_item();
//DEL 		}
//DEL 
//DEL 		if (bAppend == false)
//DEL 		{
//DEL 			m_projects.RemoveAll();
//DEL 			m_projectCmb.ResetContent();
//DEL 			m_classCmb.ResetContent();
//DEL 			m_dialogCmb.ResetContent();
//DEL 			m_menuCmb.ResetContent();
//DEL 		}
//DEL 
//DEL 		if (lstrlen(dspfile) == 0 && lstrlen(name) == 0)
//DEL 		{
//DEL 			if (m_itemNoProj != NULL)
//DEL 				m_wndTree.SelectItem(m_itemNoProj);
//DEL 		//	ShowLoop();
//DEL 			return;
//DEL 		}
//DEL 		
//DEL 		int item  = AddProject(name,dspfile);
//DEL 		project_dsp * pdsp = (project_dsp*)m_projectCmb.GetItemData(item);
//DEL 		m_projectCmb.SetCurSel(item);
//DEL 		EventProjectChange(pdsp);
//DEL 
//DEL 	//	ShowLoop();
//DEL 	}

	bool SelectCombo(CComboBox * cmb, DWORD dwData)
	{
		for (int i = 0; i < cmb->GetCount(); i++)
		{
			if (cmb->GetItemData(i) == dwData) {
				cmb->SetCurSel(i);
				return true;
			}
		}
		cmb->SetCurSel(-1);
		return false;
	}

	void OnProjectChange(project_dsp * dsp)
	{
		m_classCmb.ResetContent();
		m_dialogCmb.ResetContent();
		m_menuCmb.ResetContent();

		if (dsp == NULL)
			return;
		/*
		if (m_codeup.pVSAddin->get_version() == 0x60)
		{
			if (dsp == NULL)
				return;
			m_code.LoadVS606DSP(dsp->path);
		}
		*/
		//else
		CSimpleArray<CString> ar;
		for (size_t i = 0; i < m_codeup.pVSAddin->get_project_file_count(); i++)
		{
			ar.Add((CString)m_codeup.pVSAddin->get_project_files(i));
		}
		m_code.LoadSources(ar);
		//enum code
		m_code.EnumProjectClass(QLib::Event<void,Token*>(this,&wizard_ui_item::AddProjectClass));
		m_code.EnumResDialog(QLib::Event<void,CResDialog*>(this,&wizard_ui_item::AddProjectDialog));
		m_code.EnumResMenu(QLib::Event<void,CResMenu*>(this,&wizard_ui_item::AddProjectMenu));
		m_dialogCmb.AddString(_T("Null Dialog"));
		m_menuCmb.AddString(_T("Null Menu"));

		Token * tkcls = NULL;
		size_t i = 0;
		for (i = 0; i < m_classCmb.GetCount(); i++)
		{
			tkcls = (Token*)m_classCmb.GetItemData(i);
			if (tkcls && (get_file_title(get_file_name((LPCTSTR)tkcls->m_Filename)).CompareNoCase(get_file_title(dsp->active_file)) == 0 ))
			{
				m_classCmb.SetCurSel(i);
				break;
			}
		}
		if (tkcls == NULL || i == m_classCmb.GetCount())
		{
			if (m_classCmb.GetCount() >= 1)
			{
				m_classCmb.SetCurSel(0);
				tkcls = (Token*)m_classCmb.GetItemData(0);
			}
		}
		EventClassChange(tkcls);
	}

	void OnClassChange(Token * tkcls)
	{
		m_tkcls = tkcls;
		CResDialog * dlg = NULL;
		if (tkcls)
		{
			dlg = m_code.GetResDialog(tkcls);
			SelectCombo(&m_dialogCmb,(DWORD)dlg);
			EventResDialogChange(dlg);
		}
		if (tkcls)
			SetDlgItemText(IDC_FILENAME, tkcls->m_Filename+_T(";")+tkcls->m_ImplFilename);
		else
			SetDlgItemText(IDC_FILENAME,_T(""));
	}

	void OnResDialogChange(CResDialog * dlg)
	{
		CResMenu * menu = NULL;
		if (dlg && !dlg->m_Menu.IsEmpty()) {
			menu = m_code.GetResDialogMenu(dlg->m_Menu);
		}
		if (menu == NULL)
		{
			menu = GetWTLResMenu(m_tkcls);
		}
		SelectCombo(&m_menuCmb,(DWORD)menu);
		EventResMenuChange(menu);
	}

	CResMenu * GetWTLResMenu(Token * tkcls)
	{
		//DECLARE_FRAME_WND_CLASS(NULL, IDR_MAINFRAME)
		for (size_t i = 0; i < tkcls->m_Children.GetCount(); i++)
		{
			Token * tk = tkcls->m_Children[i];
			if (tk->m_Name == _T("DECLARE_FRAME_WND_CLASS"))
			{
				CString name, args;
				HelperGetTokenTag(tk,name,args);
				CAtlArray<CString> array;
				StringToArray(args,array,_T(","),true);
				if (array.GetCount() == 2)
				{
					return m_code.GetResDialogMenu(array[1]);
				}
			}
		}
		return NULL;
	}

	LRESULT OnSelchangeClassnameCombo(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		int index = m_classCmb.GetCurSel();
		if (index == -1) {
			return 0;
		}
		Token * tk = (Token*)m_classCmb.GetItemData(index);
		if (tk != NULL) {
			EventClassChange(tk);
		}
		return 0;
	}

	LRESULT OnSelchangeResDialogCombo(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		int index = m_dialogCmb.GetCurSel();
		if (index == -1) {
			return 0;
		}
		CResDialog * dlg = (CResDialog*)m_dialogCmb.GetItemData(index);
		EventResDialogChange(dlg);
		return 0;
	}

	LRESULT OnSelchangeResMenuCombo(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		int index = m_menuCmb.GetCurSel();
		if (index == -1) {
			return 0;
		}
		CResMenu * menu = (CResMenu*)m_menuCmb.GetItemData(index);
		EventResMenuChange(menu);
		return 0;
	}

	LRESULT OnTvnSelchangedPageTree(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
	{
		HTREEITEM item = m_wndTree.GetSelectedItem();
		if (item)
		{
			HWND hWnd = (HWND)m_wndTree.GetItemData(item);
			if (hWnd)
			{
				SetActivePage(hWnd);
				CString text;
				m_wndTree.GetItemText(item,text);
				SetDlgItemText(IDC_PAGE_NAME,text);
			}
		}
		return 0;
	}
	void SetActivePage(HWND hWnd)
	{
		if (m_wndActivePage)
		{
			::ShowWindow(m_wndActivePage,SW_HIDE);
		}
		CWindow page = GetDlgItem(IDC_PAGE_STATIC);
		RECT rc;
		page.GetWindowRect(&rc);
		ScreenToClient(&rc);

		::MoveWindow(hWnd,rc.left,rc.top,rc.right-rc.left,rc.bottom-rc.top,TRUE);
		::ShowWindow(hWnd,SW_SHOW);
		m_wndActivePage = hWnd;
	}

	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CDialogResize<wizard_ui_item>::OnSize(uMsg,wParam,lParam,bHandled);
		if (m_wndActivePage)
		{
			CWindow page = GetDlgItem(IDC_PAGE_STATIC);
			RECT rc;
			page.GetWindowRect(&rc);
			ScreenToClient(&rc);		
			::MoveWindow(m_wndActivePage,rc.left,rc.top,rc.right-rc.left,rc.bottom-rc.top,TRUE);
		}
		return 0;
	}
};

class wizard_vfc_ui_item : public wizard_ui_item
{
public:
	wizard_vfc_ui_item(codeparser & code, codeupdate & codeup) : 
		wizard_ui_item(code,codeup)
	{
	}
private:
	page_wtl_event		m_page_wtl_event;
	page_wtl_notify		m_page_wtl_notify;
	page_wtl_ddx		m_page_wtl_ddx;
	page_wtl_dlsz		m_page_wtl_dlsz;
	page_wtl_font		m_page_wtl_font;
	page_wtl_upui		m_page_wtl_upui;

	page_winx_event		m_page_winx_event;
	page_winx_notify	m_page_winx_notify;
	page_winx_ddx		m_page_winx_ddx;
	page_winx_font		m_page_winx_font;
	page_winx_dlsz		m_page_winx_dlsz;
	page_winx_upui		m_page_winx_upui;

	page_class_info		m_page_class_info;
	page_setup			m_page_setup;
	page_tools			m_page_tools;
	page_appwizard		m_page_appwizard;
	page_appwizard		m_page_codewiz;
protected:
	virtual void register_item()
	{	
		m_cfg.load();
		//register wtl
		HTREEITEM root = NULL;
		HTREEITEM item = NULL;
		if (m_cfg.bWTL)
		{
			root = m_wndTree.InsertItem( _T("WTL"),TVI_ROOT,NULL);
			
			item = register_page(m_page_wtl_event,root);
			register_tag(&m_page_wtl_event.m_tag);
			
			register_page(m_page_wtl_notify,root);
			register_tag(&m_page_wtl_notify.m_tag);
			
			register_page(m_page_wtl_ddx,root);
			register_tag(&m_page_wtl_ddx.m_tag);
			
			register_page(m_page_wtl_dlsz,root);
			register_tag(&m_page_wtl_dlsz.m_tag);
			
			register_page(m_page_wtl_upui,root);
			register_tag(&m_page_wtl_upui.m_tag);
			
			register_page(m_page_wtl_font,root);
			register_tag(&m_page_wtl_font.m_tag);
		}

		if (m_cfg.bWinx)
		{
			//register winx gui
			root = m_wndTree.InsertItem( _T("WinxGui"),TVI_ROOT,NULL);
			
			HTREEITEM itemWinx = register_page(m_page_winx_event,root);
			if (item == NULL)
				item = itemWinx;
			register_page(m_page_winx_notify,root);
			
			
			register_page(m_page_winx_dlsz,root);
			register_tag(&m_page_winx_dlsz.m_tag);
			
			register_page(m_page_winx_ddx,root);
			register_tag(&m_page_winx_ddx.m_tag);
			
			register_page(m_page_winx_upui,root);
			register_tag(&m_page_winx_upui.m_tag);
			
			register_page(m_page_winx_font,root);
			register_tag(&m_page_winx_font.m_tag);
		}
		//register class info
		register_page(m_page_class_info,TVI_ROOT);
		
		//page tools
		//register_page(m_page_tools,TVI_ROOT,_T("Tools"));
		//
		if (m_cfg.bCodeWizard)
		{
			m_page_codewiz.m_wizardPath = _T("CodeWizard");
			register_page(m_page_codewiz,TVI_ROOT,_T("CodeWizard"));
		}
		if (m_cfg.bAppWizard)
		{
			//appwizard
			m_itemNoProj = register_page(m_page_appwizard,TVI_ROOT,_T("AppWizard"));
		}

		root = m_wndTree.InsertItem( _T("VisualFC"),TVI_ROOT,NULL);
		register_page(m_page_setup,root,_T("Setup"),true);
		//register about
		HTREEITEM hAbout = register_page(m_page_about,root, _T("About"));

		if (item == NULL)
			item = hAbout;
		m_wndTree.SelectItem(item);
		
		SetWindowText(_T("VisualFC Class Wizard"));
	}
};

class vfc_core_item : public fox::vfc_item
{
protected:
	fox::vs_addin *			pVSAddin;
	CAtlArray<CString>		logs;
	codeparser				code;
	codeupdate				codeup;
	bool					bload;
public:
	vfc_core_item() : bload(false)
	{
	}
	virtual ~vfc_core_item()
	{
	}
	void add_log(const CString & log)
	{
		logs.Add((CString)log);
	}
	bool load_config()
	{
		int error = 0;
		logs.RemoveAll();
		if (!code.m_winxev.loadex(GetModulePath(_Module.m_hInst)+_T("\\winxevent.ini")))
		{
			add_log(_T("Load winxevent.ini false!"));
			error++;
		}
		if (!code.m_notify.loadex(GetModulePath(_Module.m_hInst)+_T("\\message.ini")))
		{
			add_log(_T("Load message.ini false!"));
			error++;
		}
		if (!code.m_wtlev.loadex(GetModulePath(_Module.m_hInst)+_T("\\wtlevent.ini")))
		{
			add_log(_T("Load wtlevent.ini false!"));
			error++;
		}
		if (!code.m_wtlev.load_kind(GetModulePath(_Module.m_hInst)+_T("\\wtlkind.ini")))
		{
			add_log(_T("Load wtlkind.ini false!"));
			error++;
		}
		if (error != 0)
		{
			CString text;
			for (int i = 0; i < logs.GetSize(); i++)
			{
				text += logs[i];
				text += _T("\r\n");
			}
			::MessageBox(GetActiveWindow(),text,_T("VisualFC Error!"),MB_OK | MB_ICONERROR);
			return false;
		}
		return true;
	}
public:
	virtual const char * name()
	{
		return "VisualFC";
	}

	virtual void  set_vsaddin(fox::vs_addin * pvs)
	{
		pVSAddin = pvs;
	}

	virtual void  load_project(const char * project_name, const char * active_file)
	{
		if (!bload && load_config())
		{
			bload = true;
		}
		wizard_vfc_ui_item item(code,codeup);
		item.set_vsaddin(pVSAddin);
		//item.load_project(hParent,name,activefile,bAppend);
		item.m_dsp.project_name = project_name;
		item.m_dsp.active_file = active_file;

		if (item.DoModal() == IDOK)
		{
			;//
		}
	}
};

extern "C"
fox::vfc_item * fox_get_item(int flag)
{
	return new vfc_core_item();//wizard_vfc_ui_item();
}

#endif 
