#ifndef _WIZARDUI_H__
#define _WIZARDUI_H__

#include <ShlGuid.h>
#include <atlapp.h>
#include <atlwin.h>
#include <atlmisc.h>
#include <atlframe.h>
#include <atlctrls.h>
#include <atlctrlx.h>
#include <atlsplit.h>
#include <atlddx.h>



#include <map>

#include "../public/atltabex.h"
#include "../public/foxlib.h"
#include "../public/foxuilib.h"
#include "../public/qevent.h"
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


class page_about : public ui_page_dialog_t<page_about,IDD_PAGE_ABOUT>,
				   public page_base_t<page_about>
{
public:
	CString addin_name;
	void OnInit()
	{
		CStatic win = GetDlgItem(IDC_VERSION_STATIC);
		win.SetWindowText(_T("FreeCode for ")+addin_name);
	}
};

class wizard_ui_item : public ui_item_dialog_t<wizard_ui_item,IDD_WIZARD_DIALOG,true,fox::ui::vs_item>, 
					   public CMessageFilter
{
public:
	struct project_dsp
	{
		CString project_name;
		CString active_file;
	};
public:
	virtual	void register_item(){}	//bind event
protected:
//	plugin::manager		m_plugins;
	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		if (m_wndTab.PreTranslateMessage(pMsg))
			return TRUE;
		return CWindow::IsDialogMessage(pMsg);
	}

protected:
	codeparser				m_code;
	codeupdate				m_codeup;
	Token				  * m_tkcls;
	CAtlArray<tag_token*>	m_tags;
	CSimpleArray<project_dsp>	m_projects;
	
protected:
	CComboBox			m_projectCmb;
	CComboBox			m_classCmb;
	CComboBox			m_dialogCmb;
	CComboBox			m_menuCmb;
	CTabCtrlEx			m_wndTab;

	page_winx_event		m_page_winx_event;
	page_winx_notify	m_page_winx_notify;
	page_winx_font		m_page_winx_font;
	page_class_info		m_page_class_info;
	page_about			m_page_about;
	page_winx_dlsz		m_page_winx_dlsz;

	page_wtl_notify		m_page_wtl_notify;
	page_wtl_ddx		m_page_wtl_ddx;
	page_wtl_dlsz		m_page_wtl_dlsz;
	page_wtl_font		m_page_wtl_font;
protected:
	QLib::Event<void,project_dsp*>		EventProjectChange;
	QLib::Event<void>				EventCloseProject;
	QLib::Event<void,Token*>		EventClassChange;
	QLib::Event<void,CResDialog*>	EventResDialogChange;
	QLib::Event<void,CResMenu*>		EventResMenuChange;
public:
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
	void register_tag(tag_token * tag)
	{
		if (tag != NULL)
		{
			m_tags.Add(tag);
		}
	}

	wizard_ui_item()
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
		if (pvs != NULL)
		{
			m_page_about.addin_name = pvs->get_addin_name();
		}
	}
public:
	BEGIN_MSG_MAP(wizard_ui_item)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
		MESSAGE_HANDLER(WM_CLOSE, OnClose)
		COMMAND_HANDLER(IDC_CLASSNAME_COMBO, CBN_SELENDOK, OnSelchangeClassnameCombo)
		COMMAND_HANDLER(IDC_RESDIALOG_COMBO, CBN_SELENDOK, OnSelchangeResDialogCombo)
		COMMAND_HANDLER(IDC_RESMENU_COMBO,   CBN_SELENDOK, OnSelchangeResMenuCombo)
		CHAIN_MSG_MAP(ui_item_dialog_base)
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

	BEGIN_DLGRESIZE_MAP(wizard_ui_item)
		DLGRESIZE_CONTROL(IDOK,DLSZ_MOVE_X | DLSZ_MOVE_Y)
		DLGRESIZE_CONTROL(IDCANCEL,DLSZ_MOVE_X | DLSZ_MOVE_Y)
		DLGRESIZE_CONTROL(IDC_STATIC_PROJECT,DLSZ_MOVE_Y)
		DLGRESIZE_CONTROL(IDC_PROJECT_COMBO,DLSZ_MOVE_Y)
		DLGRESIZE_CONTROL(IDC_PANE_TAB,DLSZ_SIZE_X | DLSZ_SIZE_Y)
		//DLGRESIZE_CONTROL(IDOK,DLSZ_MOVE_Y)
		//DLGRESIZE_CONTROL(IDCANCEL,DLSZ_MOVE_Y)
	END_DLGRESIZE_MAP()
public:
	CMessageLoop Loop;
	HWND		m_hHostWnd;
	void HideLoop()
	{
		PostMessage(WM_QUIT,0,0);
		::EnableWindow(m_hHostWnd,TRUE);
		ShowWindow(SW_HIDE);
		EventCloseProject();
	}
	void ShowLoop()
	{
		ShowWindow(SW_SHOW);
		::EnableWindow(m_hHostWnd,FALSE);
		Loop.Run();
	}
public:
	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		HideLoop();
		return 0;
	}
	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		//enbale parent hwnd
		HideLoop();
		if (wID == IDCANCEL)
			return wID;
		m_codeup.ProcessUpdate();
		m_code.ClearDSP();
		return wID;
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
			HideLoop();
		}
	}

	void OnInit()
	{
		CenterWindow();
		if (!m_code.m_winxev.loadex(GetModulePath(_Module.m_hInst)+_T("\\winxevent.ini")))
		{
			MessageBox(_T("Load winxevent.ini false!"));
		}
		if (!m_code.m_notify.loadex(GetModulePath(_Module.m_hInst)+_T("\\message.ini")))
		{
			MessageBox(_T("Load message.ini false!"));
		}
		
		//enbale parent hwnd
		m_wndTab.SubclassWindow(GetDlgItem(IDC_PANE_TAB));
		//m_wndTab.SetMinTabWidth(100);

		m_projectCmb = GetDlgItem(IDC_PROJECT_COMBO);
		m_classCmb   = GetDlgItem(IDC_CLASSNAME_COMBO);
		m_dialogCmb  = GetDlgItem(IDC_RESDIALOG_COMBO);
		m_menuCmb    = GetDlgItem(IDC_RESMENU_COMBO);

		//virtual function
		
		EventProjectChange.bind(this,&wizard_ui_item::OnProjectChange);
		EventClassChange.bind(this,&wizard_ui_item::OnClassChange);
		EventResDialogChange.bind(this,&wizard_ui_item::OnResDialogChange);

		register_item();
		register_page(m_page_about,_T("About"));
/*
		//register page
		register_page(m_page_winx_event);
		register_page(m_page_winx_notify);


		register_page(m_page_winx_dlsz);
		register_tag(&m_page_winx_dlsz.m_tag);

		register_page(m_page_winx_font);
		register_tag(&m_page_winx_font.m_tag);

		register_page(m_page_wtl_notify);
		register_tag(&m_page_wtl_notify.m_tag);

		register_page(m_page_wtl_ddx);
		register_tag(&m_page_wtl_ddx.m_tag);

		register_page(m_page_wtl_dlsz);
		register_tag(&m_page_wtl_dlsz.m_tag);

		register_page(m_page_wtl_font);
		register_tag(&m_page_wtl_font.m_tag);

		register_page(m_page_class_info);
		register_page(m_page_about,_T("About"));
	//	register_page(m_page_winx_prop);
*/
		m_wndTab.SetActiveItem(0);	

		Loop.AddMessageFilter(this);
	}
	
	virtual void load_project(HWND hHostWnd, const char * name, const char * dspfile, bool bAppend)
	{
		m_hHostWnd = hHostWnd;
		if (bAppend == false)
		{
			m_projects.RemoveAll();
			m_projectCmb.ResetContent();
			m_classCmb.ResetContent();
			m_dialogCmb.ResetContent();
			m_menuCmb.ResetContent();
		}
		
		int item  = AddProject(name,dspfile);
		project_dsp * pdsp = (project_dsp*)m_projectCmb.GetItemData(item);
		m_projectCmb.SetCurSel(item);
		EventProjectChange(pdsp);

		ShowLoop();
	}

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
		{
			CSimpleArray<CString> ar;
			for (size_t i = 0; i < m_codeup.pVSAddin->get_file_count(dsp->project_name); i++)
			{
				ar.Add((CString)m_codeup.pVSAddin->get_files(dsp->project_name,i));
			}
			m_code.LoadSources(ar);
		}
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
			if (tkcls && (get_file_name((LPCTSTR)tkcls->m_Filename) == dsp->active_file))
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
			dlg = m_code.GetResDialog(tkcls);
		SelectCombo(&m_dialogCmb,(DWORD)dlg);
		EventResDialogChange(dlg);
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
};

class wizard_winx_ui_item : public wizard_ui_item
{
private:
	page_winx_event		m_page_winx_event;
	page_winx_notify	m_page_winx_notify;
	page_winx_ddx		m_page_winx_ddx;
	page_winx_font		m_page_winx_font;
	page_winx_dlsz		m_page_winx_dlsz;
	page_winx_upui		m_page_winx_upui;
	page_class_info		m_page_class_info;
protected:
	virtual void register_item()
	{
		register_page(m_page_winx_event);
		register_page(m_page_winx_notify);


		register_page(m_page_winx_dlsz);
		register_tag(&m_page_winx_dlsz.m_tag);

		register_page(m_page_winx_ddx);
		register_tag(&m_page_winx_ddx.m_tag);

		register_page(m_page_winx_upui);
		register_tag(&m_page_winx_upui.m_tag);

		register_page(m_page_winx_font);
		register_tag(&m_page_winx_font.m_tag);
		
		register_page(m_page_class_info);

		SetWindowText(_T("Winx Class Wizard"));
	}
};

class wizard_wtl_ui_item : public wizard_ui_item
{
private:
	page_wtl_event		m_page_wtl_event;
	page_wtl_notify		m_page_wtl_notify;
	page_wtl_ddx		m_page_wtl_ddx;
	page_wtl_dlsz		m_page_wtl_dlsz;
	page_wtl_font		m_page_wtl_font;
	page_wtl_upui		m_page_wtl_upui;
	page_class_info		m_page_class_info;
protected:
	virtual void register_item()
	{	
		register_page(m_page_wtl_event);
		register_tag(&m_page_wtl_event.m_tag);

		register_page(m_page_wtl_notify);
		register_tag(&m_page_wtl_notify.m_tag);

		register_page(m_page_wtl_ddx);
		register_tag(&m_page_wtl_ddx.m_tag);

		register_page(m_page_wtl_dlsz);
		register_tag(&m_page_wtl_dlsz.m_tag);

		register_page(m_page_wtl_upui);
		register_tag(&m_page_wtl_upui.m_tag);

		register_page(m_page_wtl_font);
		register_tag(&m_page_wtl_font.m_tag);

		register_page(m_page_class_info);

		SetWindowText(_T("WTL Class Wizard"));
	}
};

extern "C"
fox::ui::item * fox_get_item(int flag)
{
	if (flag == 0x1000)
		return new wizard_wtl_ui_item();
	else if (flag == 0x2000)
		return new wizard_winx_ui_item();
	return NULL;
}

extern "C"
fox::ui::item * fox_get_interface()
{
	fox::ui::item * item =  new wizard_ui_item;
	return item;
}

#endif 
