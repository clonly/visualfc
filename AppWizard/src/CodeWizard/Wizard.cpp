// Wizard.cpp: implementation of the CWizard class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Wizard.h"
#include "WizardSheet.h"
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
	info.cfg.load(info.templatePath+_T("\\codewiz.ini"),"setup");

	info.bUseConstruction = info.cfg.bConstruction;
	info.bUseDestruction = info.cfg.bDestruction;
	info.bUseCppFiles = info.cfg.bEnableCPP;
	
	//load base class
	CString strInfFile = info.templatePath + "\\basecls.inf";
	str_vector array;
	int i = 0;
	wizard.load_file_vector(strInfFile,array);
	for (i = 0; i < array.size(); i++)
	{
		code_baseclass cb(array[i]);
		if (!cb.code.IsEmpty())
		{
			info.ar_baseclass.push_back(cb);
		}
	}
	if (info.ar_baseclass.size() > 0)
	{
		info.strBaseClass = info.ar_baseclass[0].baseclass;
	}
	array.clear();
	//laod code ext
	strInfFile = info.templatePath + "\\codeext.inf";
	wizard.load_file_vector(strInfFile,array);
	for (i = 0; i < array.size(); i++)
	{
		code_ext ce(array[i]);
		if (!ce.code.IsEmpty())
		{
			info.ar_ext.push_back(ce);
		}
	}

	CWizardSheet wiz(&info,0,NULL);
	info.event_finish.bind(this,&CWizard::make_project);
	wiz.DoModal();
	return info.nWizardRet;
}

bool CWizard::make_project()
{
	wizard.clear();

	if (info.strClassName.IsEmpty())
	{
		MessageBox(GetActiveWindow(),_T("Class Name Empty !!!"),_T("Code Wizard"),MB_ICONEXCLAMATION);
		return false;
	}
	if (info.strFileName.IsEmpty())
	{
		MessageBox(GetActiveWindow(),_T("File Name Empty !!!"),_T("Code Wizard"),MB_ICONEXCLAMATION);
		return false;
	}
	if (info.strProjectPath.IsEmpty())
	{
		MessageBox(GetActiveWindow(),_T("Project Path Empty !!!"),_T("Code Wizard"),MB_ICONEXCLAMATION);
		return false;
	}
	if (::PathFileExists(info.strProjectPath) == FALSE)
	{
		MessageBox(GetActiveWindow(),_T("Project Path Not Valid !!!"),_T("Code Wizard"),MB_ICONEXCLAMATION);
		return false;
	}

	wizard.AddSymbol("CODE_CLASS_NAME",info.strClassName);
	wizard.AddSymbol("CODE_FILE_NAME",info.strFileName);
	wizard.AddSymbol("CODE_DIALOG_ID", info.strDialogID);
	wizard.AddSymbol("CODE_PROJECT_PATH",info.strProjectPath);
	
	wizard.AddSymbol("CODE_USE_CPP_FILES",info.bUseCppFiles);
	wizard.AddSymbol("CODE_USE_STDAFX",info.bUseStdAfx);
	wizard.AddSymbol("CODE_USE_RESOURCE",info.bUseResource);
	wizard.AddSymbol("CODE_USE_CONSTRUCTION",info.bUseConstruction);
	wizard.AddSymbol("CODE_USE_DESTRUCTION",info.bUseDestruction);
	wizard.AddSymbol("CODE_USE_GUIDSYMBOL",info.bUseGuidSymbol);

/*
	wizard.AddSymbol("CODE_USE_MODAL",info.bUseModal);
	wizard.AddSymbol("CODE_USE_MSGFILTER",info.bUseMsgFilter);
	wizard.AddSymbol("CODE_USE_IDLE",info.bUseIdle);
	wizard.AddSymbol("CODE_USE_UPUI",info.bUseUpUI);
	wizard.AddSymbol("CODE_USE_DDX",info.bUseDDX);
	wizard.AddSymbol("CODE_USE_RESIZE",info.bUseResize);
*/
	//code ext
	int i = 0;
	for (i = 0; i < info.ar_ext.size(); i++)
	{
		code_ext & ce = info.ar_ext[i];
		wizard.AddSymbol(ce.code,ce.bsel);
	}
	//code base class
	if (!info.strBaseClass.IsEmpty())
	{
		wizard.AddSymbol("CODE_BASE_CLASS",info.strBaseClass);
		wizard.AddSymbol("CODE_USE_BASE_CLASS",true);
		for (i = 0; i < info.ar_baseclass.size(); i++)
		{
			code_baseclass & cb = info.ar_baseclass[i];
			if (cb.baseclass == info.strBaseClass)
			{
				wizard.AddSymbol(cb.code,true);
				break;
			}
		}
	}


	CString strInfFile = info.templatePath + "\\Templates.inf";

	str_vector array;
	wizard.load_file_vector(strInfFile,array);

	CConfirmDlg dlg;
	dlg.m_projectPath = info.strProjectPath;
	
	CString t1,t2,t3,t4,t5;
	wizard.get_define_info(t1);
	wizard.get_output_info(t2);
	for (str_vector::iterator it = array.begin(); it != array.end(); it++)
	{
		t4 = *it;
		t4.TrimLeft();
		t4.TrimRight();
		if (!t4.IsEmpty())
		{
			t5 = GetTargetName(t4,info.strProjectName);
			if (::PathFileExists(t5) == TRUE)
			{
				MessageBox(GetActiveWindow(),_T("The file path is exists: ")+t5,_T("Code Wizard"),MB_ICONEXCLAMATION);
				wizard.clear();
				return false;
			}

			t3 += _T(".\\")+t5;
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
}

bool CWizard::AddFilesToProject(const CString &strProjectName, const CString &strProjectPath, str_vector &array)
{
	wizard.AddSymbol("INSERT_LOCATION_COMMENT","VisualFC AppWizard will insert additional declarations immediately before the previous line.");

	CString strTemplatePath = info.templatePath;
	
	CString strTpl;
	CString strName;

/*
	if (!::CreateDirectory(strProjectPath,0))
	{
		MessageBox(NULL,"Unable Create Direct "+ strProjectPath,"WTLAppWizard",MB_OK | MB_ICONWARNING);
		return false;
	}
	::CreateDirectory(strProjectPath+_T("\\res"),0);
*/
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
				if (info.bUseGuidSymbol)
				{
					strFileNS = _T("VFC_")+strFileNS+_T("__");
					wizard.AddSymbol(_T("FILE_NAME_SYMBOL"),strFileNS+wizard.make_include_guid()+_T("__INCLUDED_"));
				}
				else
					wizard.AddSymbol(_T("FILE_NAME_SYMBOL"),_T("__")+strFileNS+_T("__"));
			}
			else
			{
				wizard.AddSymbol(_T("FILE_NAME_SYMBOL"),false);
			}
			BOOL bRet = FALSE;
			if (bCopyOnly)
				bRet = ::CopyFile(strTemplate,strFile,FALSE);
			else
				bRet = wizard.make_file(strTemplate,strFile);
			if (bRet)
			{
				info.p_return_files->push(strFile);
			}
			
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

CString CWizard::GetTargetName(const CString &strName, const CString &strProjectName)
{
	CString strTarget = strName;
	CString strExt = strName.Right(strName.GetLength()-strName.ReverseFind('.'));
	strExt.MakeLower();
	if (strExt == _T(".h"))
		strTarget = info.strFileName+strExt;
	else if (strExt == _T(".cpp"))
		strTarget = info.strFileName+strExt;
	return strTarget;
}
