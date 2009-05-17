// Wizard.cpp: implementation of the CWizard class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Wizard.h"
#include "wizardsheet.h"
#include "confirmdlg.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWizard::CWizard()
{

}

CWizard::~CWizard()
{

}

int CWizard::ExecuteWizard()
{
	CWizardSheet wizard(&info,0,NULL);
	info.event_finish.bind(this,&CWizard::on_evnet_finish);
	wizard.DoModal();
	return info.nWizardRet;
}

bool CWizard::on_evnet_finish()
{
	return make_project();
}

static CString CreateSafeName(const CString & in)
{
	return in;
}

bool CWizard::make_project()
{
	wizard.AddSymbol(info.ar_app[info.nAppType],true);
	wizard.AddSymbol("WTL_APPTYPE_DLG_MODAL",info.bModalDialog);
	wizard.AddSymbol("WTL_COM_SERVER",info.bComServer);
	wizard.AddSymbol("WTL_USE_CPP_FILES",info.bCppFiles);
	wizard.AddSymbol("WTL_USE_TOOLBAR",info.bToolBar);
	wizard.AddSymbol("WTL_USE_STATUSBAR",info.bStatusBar);
	wizard.AddSymbol("WTL_ENABLE_AX",info.bEnableActiveX);
	wizard.AddSymbol("WTL_HOST_AX",info.bHostActiveX);
	wizard.AddSymbol("WTL_USE_VIEW",info.bUseView);
	wizard.AddSymbol("PROJECT_LANG_"+info.ar_lang[info.nAppLang],true);


	wizard.AddSymbol("PROJECT_NAME",info.strProjectName);
	wizard.AddSymbol("PROJECT_PATH",info.strProjectPath);
	wizard.AddSymbol("PROJECT_ENCODE","Windows-1252");
	wizard.AddSymbol("PROJECT_GUID",wizard.make_guid());


	if (info.nSDKType == 0)
	{
		wizard.AddSymbol("WTL_SDKTYPE_NODEF",true);
	}
	else if (info.nSDKType == 1)
	{
		wizard.AddSymbol("WTL_SDKTYPE_0400",true);
	}
	else if (info.nSDKType == 2)
	{
		wizard.AddSymbol("WTL_SDKTYPE_0500",true);
	}
	else if (info.nSDKType == 3)
	{
		wizard.AddSymbol("WTL_SDKTYPE_0600",true);
	}

	if (info.nAppType == 3)
	{
		wizard.AddSymbol("WTL_MAINDLG_FILE","MainDlg");
	}
	else
	{
		wizard.AddSymbol("WTL_FRAME_CLASS","CMainFrame");
		wizard.AddSymbol("WTL_FRAME_FILE","MainFrm");
		wizard.AddSymbol("WTL_FRAME_BASE_CLASS","CFrameWindowImpl");
		
		if (info.nAppType == 2)
		{
			wizard.AddSymbol("WTL_CHILD_FRAME_FILE","ChildFrm");
			wizard.AddSymbol("WTL_CHILD_FRAME_CLASS","CChildFrame");
		}
	}

	if (info.bVS60)
		wizard.AddSymbol("PROJECT_VS60",true);
	if (info.bVS2002)
		wizard.AddSymbol("PROJECT_VS2002",true);
	if (info.bVS2003)
		wizard.AddSymbol("PROJECT_VS2003",true);
	if (info.bVS2005)
		wizard.AddSymbol("PROJECT_VS2005",true);
	if (info.bVS2008)
		wizard.AddSymbol("PROJECT_VS2008",true);

	if (info.nAppType == 3 || info.nAppType == 4)
		wizard.AddSymbol("WTL_USE_VIEW",true);
	
	// Create symbols based on the project name
	CString strSafeProjectName = CreateSafeName(info.strProjectName);
	wizard.AddSymbol("SAFE_PROJECT_NAME", strSafeProjectName);
	CString tmp = strSafeProjectName.Left(1);
	tmp.MakeUpper();
	tmp += strSafeProjectName.Right(strSafeProjectName.GetLength()-1);
	wizard.AddSymbol("NICE_SAFE_PROJECT_NAME", tmp);
	tmp.MakeUpper();
	wizard.AddSymbol("UPPERCASE_SAFE_PROJECT_NAME", tmp);
	
	// Set current year symbol
	SYSTEMTIME st = {0};
	::GetLocalTime(&st);
	if(st.wYear >= 2003)
	{
		tmp.Format(_T("%d"),st.wYear);
		wizard.AddSymbol("WTL_CURRENT_YEAR", tmp);
	}
	
	// Set APPID and LIBID symbols for COM servers
	if(wizard.FindSymbol("WTL_COM_SERVER"))
	{
		wizard.AddSymbol("WTL_APPID", wizard.make_guid());
		
		wizard.AddSymbol("WTL_LIBID", wizard.make_guid());
	}		// Set app type symbols
	// Set app type symbols
	if(wizard.FindSymbol("WTL_APPTYPE_SDI"))
	{
		wizard.AddSymbol("WTL_FRAME_BASE_CLASS","CFrameWindowImpl");
	}
	else if(wizard.FindSymbol("WTL_APPTYPE_MTSDI"))
	{
		wizard.AddSymbol("WTL_FRAME_BASE_CLASS","CFrameWindowImpl");
	}
	else if(wizard.FindSymbol("WTL_APPTYPE_MDI"))
	{
		wizard.AddSymbol("WTL_FRAME_BASE_CLASS","CMDIFrameWindowImpl");
		wizard.AddSymbol("WTL_CHILD_FRAME_BASE_CLASS","CMDIChildWindowImpl");
	}
	else if(wizard.FindSymbol("WTL_APPTYPE_DLG"))
	{
		wizard.AddSymbol("WTL_MAINDLG_CLASS","CMainDlg");
		if(wizard.FindSymbol("WTL_ENABLE_AX"))
			wizard.AddSymbol("WTL_MAINDLG_BASE_CLASS", "CAxDialogImpl");
		else
			wizard.AddSymbol("WTL_MAINDLG_BASE_CLASS", "CDialogImpl");
		
		if (!wizard.FindSymbol("WTL_APPTYPE_DLG_FRAME"))
		{
			wizard.AddSymbol("WTL_USE_TOOLBAR", false);
			wizard.AddSymbol("WTL_USE_REBAR", false);
			wizard.AddSymbol("WTL_USE_CMDBAR", false);
			wizard.AddSymbol("WTL_USE_STATUSBAR", false);
			wizard.AddSymbol("WTL_USE_VIEW", false);
		}
	}
	
	
	// Set view symbols
	if(wizard.FindSymbol("WTL_USE_VIEW"))
	{
		CString strViewFile = info.strProjectName + "View";
		wizard.AddSymbol("WTL_VIEW_FILE", strViewFile);
		
		CString strViewClass = "C" + wizard.FindSymbolVal("NICE_SAFE_PROJECT_NAME") + "View";
		wizard.AddSymbol("WTL_VIEW_CLASS", strViewClass);
		
		wizard.AddSymbol("WTL_VIEWTYPE_GENERIC", false);
		wizard.AddSymbol("WTL_VIEW_BASE_CLASS","CWindowImpl");
		wizard.AddSymbol("WTL_VIEW_STYLES","WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN");
		wizard.AddSymbol("WTL_VIEW_EX_STYLES","WS_EX_CLIENTEDGE");

		switch(info.nViewType)
		{
		case 1:
			wizard.AddSymbol("WTL_VIEWTYPE_FORM", true);
			if(wizard.FindSymbol("WTL_ENABLE_AX") && wizard.FindSymbol("WTL_HOST_AX"))
				wizard.AddSymbol("WTL_VIEW_BASE_CLASS", "CAxDialogImpl");
			else
				wizard.AddSymbol("WTL_VIEW_BASE_CLASS", "CDialogImpl");
			break;
		case 2:
			wizard.AddSymbol("WTL_VIEWTYPE_LISTBOX", true);
			wizard.AddSymbol("WTL_VIEW_BASE", "CListBox");
			wizard.AddSymbol("WTL_VIEW_STYLES", "WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | LBS_NOINTEGRALHEIGHT | LBS_NOTIFY | LBS_WANTKEYBOARDINPUT");
			break;
		case 3:
			wizard.AddSymbol("WTL_VIEWTYPE_EDIT", true);
			wizard.AddSymbol("WTL_VIEW_BASE", "CEdit");
			wizard.AddSymbol("WTL_VIEW_STYLES", "WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_HSCROLL | WS_VSCROLL | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE | ES_NOHIDESEL");
			break;
		case 4:
			wizard.AddSymbol("WTL_VIEWTYPE_LISTVIEW", true);
			wizard.AddSymbol("WTL_VIEW_BASE", "CListViewCtrl");
			wizard.AddSymbol("WTL_VIEW_STYLES", "WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | LVS_REPORT | LVS_SHOWSELALWAYS");
			break;
		case 5:
			wizard.AddSymbol("WTL_VIEWTYPE_TREEVIEW", true);
			wizard.AddSymbol("WTL_VIEW_BASE", "CTreeViewCtrl");
			wizard.AddSymbol("WTL_VIEW_STYLES", "WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | TVS_HASLINES | TVS_LINESATROOT | TVS_SHOWSELALWAYS");
			break;
		case 6:
			wizard.AddSymbol("WTL_VIEWTYPE_RICHEDIT", true);
			wizard.AddSymbol("WTL_VIEW_BASE", "CRichEditCtrl");
			wizard.AddSymbol("WTL_VIEW_STYLES", "WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_HSCROLL | WS_VSCROLL | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE | ES_NOHIDESEL | ES_SAVESEL");
			break;
		case 7:
			wizard.AddSymbol("WTL_VIEWTYPE_HTML", true);
			wizard.AddSymbol("WTL_VIEW_BASE", "CAxWindow");
			wizard.AddSymbol("WTL_ENABLE_AX", true);
			wizard.AddSymbol("WTL_VIEW_STYLES", "WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_HSCROLL | WS_VSCROLL");
			break;
		case 8:
			wizard.AddSymbol("WTL_VIEWTYPE_SCROLL", true);
			wizard.AddSymbol("WTL_VIEW_BASE_CLASS", "CScrollWindowImpl");
			wizard.AddSymbol("WTL_VIEW_STYLES", "WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_HSCROLL | WS_VSCROLL");
			break;
		default:
			wizard.AddSymbol("WTL_VIEWTYPE_GENERIC", true);
			break;
		}
		
		if(wizard.FindSymbol("WTL_APPTYPE_TABVIEW"))
			wizard.AddSymbol("WTL_VIEW_EX_STYLES", "0");
	}


	CString strInfFile = info.templatePath + "\\Templates.inf";

	str_vector array;
	wizard.load_file_vector(strInfFile,array);

	CConfirmDlg dlg;
	dlg.m_projectPath = info.strProjectPath;
	
	CString t1,t2,t3;
	wizard.get_define_info(t1);
	wizard.get_output_info(t2);
	CString t4;
	for (str_vector::iterator it = array.begin(); it != array.end(); it++)
	{
		t4 = *it;
		t4.TrimLeft();
		t4.TrimRight();
		if (!t4.IsEmpty())
		{
			t3 += _T(".\\")+GetTargetName(t4,info.strProjectName);
			t3 += _T("\r\n");
		}
	}
	dlg.m_info = t1+_T("\r\n")+t2+_T("\r\n")+t3;

	if (dlg.DoModal() == IDOK)	
	{
		return AddFilesToProject(info.strProjectName,info.strProjectPath,array);
	}
	else
	{
		wizard.clear();
		return false;
	}
	return false;
}

CString CWizard::GetTargetName(const CString & strName, const CString & strProjectName)
{
	CString strTarget = strName;
	CString strResPath = "res\\";
	
	if(strName.Mid(0, 4) == "root")
	{
		int nNameLen = strName.GetLength();
		if(strName == "root.ico" || strName == "rootDoc.ico" || strName == "root.exe.manifest")
		{
			strTarget = strResPath + strProjectName + strName.Mid(4, nNameLen - 4);
		}
		else if (strName.Right(3) == _T(".rc"))
		{
			strTarget = strProjectName+_T(".rc");
		}
		else
		{
			strTarget = strProjectName + strName.Mid(4, nNameLen - 4);
		}
	}
	else if(strName == "frame.h")
	{
		strTarget = "MainFrm.h";
	}
	else if(strName == "frame.cpp")
	{
		strTarget = "MainFrm.cpp";
	}
	else if(strName == "view.h")
	{
		strTarget = strProjectName + "View.h";
	}
	else if(strName == "view.cpp")
	{
		strTarget = strProjectName + "View.cpp";
	}
	else if(strName == "toolbar.bmp")
	{
		strTarget = strResPath + strName;
	}
	
	return strTarget; 
}

bool CWizard::AddFilesToProject(const CString & strProjectName, const CString &strProjectPath, str_vector & array)
{
	wizard.AddSymbol("INSERT_LOCATION_COMMENT","VisualFC AppWizard will insert additional declarations immediately before the previous line.");

	CString strTemplatePath = info.templatePath;
	
	CString strTpl;
	CString strName;

	if (!::CreateDirectory(strProjectPath,0))
	{
		MessageBox(NULL,"Unable Create Direct "+ strProjectPath,"WTLAppWizard",MB_OK | MB_ICONWARNING);
		return false;
	}
	::CreateDirectory(strProjectPath+_T("\\res"),0);


	for (int i = 0; i < array.size(); i++)
	{
		strTpl = array[i];
		strTpl.TrimLeft();
		strTpl.TrimRight();
		if (!strTpl.IsEmpty())
		{
			strName = strTpl;
			CString strTarget = GetTargetName(strName, strProjectName);
			CString strTemplate = strTemplatePath + '\\' + strTpl;
			CString strFile = strProjectPath + '\\' + strTarget;
					
			bool bCopyOnly = false;  //"true" will only copy the file from strTemplate to strTarget without rendering/adding to the project
			CString strExt = strName.Right(strName.GetLength()-strName.ReverseFind('.'));
			if(strExt==".bmp" || strExt==".ico" || strExt==".gif" || strExt==".rtf" || strExt==".css")
				bCopyOnly = true;
			
			if (strExt == _T(".h"))
			{
				CString strFileNS = strTarget;
				strFileNS.Replace(_T("."),_T("_"));
				strFileNS.MakeUpper();
				strFileNS = _T("VFC_")+strFileNS+_T("__");
				wizard.AddSymbol(_T("FILE_NAME_SYMBOL"),strFileNS+wizard.make_include_guid()+_T("_"));
			}
			else
			{
				wizard.AddSymbol(_T("FILE_NAME_SYMBOL"),false);
			}

			if (bCopyOnly)
				::CopyFile(strTemplate,strFile,FALSE);
			else
				wizard.make_file(strTemplate,strFile);


			
			// don't add these files to the project
			/*
			if(strTarget == strProjectName + ".h" ||
				strTarget == strProjectName + "ps.mk" ||
				strTarget == strProjectName + "ps.def")
				continue;
			*/
		}
	}
	return true;
}