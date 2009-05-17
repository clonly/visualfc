// WizardInfo.h: interface for the CWizardInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WIZARDINFO_H__8145D181_A062_4641_A704_89B59CA3913B__INCLUDED_)
#define AFX_WIZARDINFO_H__8145D181_A062_4641_A704_89B59CA3913B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../vs_wizard/vs_wizard.h"
#include "../public/codewiz_plugin.h"
/*
standard code template

//standard
CODE_PROJECT_NAME - str
CODE_CLASS	  - str	
CODE_BASE_CLASS   - array
CODE_CLASS_FILE   - str
CODE_FILE_NAME_SYMBOL - auto

//base bBase
CODE_USE_CPP_FILES	- sel
CODE_USE_STDAFX		- sel
CODE_USE_CONSTRUCTION	- sel
CODE_USE_DESTRUCTION	- sel
CODE_USE_RESOURCE	- sel
CODE_TEMPALTE_IDD - array -> auto

//ext bExt
CODE_USE_DDX		- sel
CODE_USE_UPDATEUI	- sel
CODE_USE_MESSAGE	- sel
CODE_USE_DLGRESIZE	- sel
CODE_USE_MODAL		- sel

//user bUser
str_set CODE_DEFINE	- array
str_map CODE_OUTPUT	- array
*/
template <typename ArrayT>
inline void StringToArray(LPCTSTR text, ArrayT & array, LPCTSTR separator = _T(""), bool trimSpaces = true)
{
    CString search = text;
    int seplen = CString(separator).GetLength();
    while (true)
    {
        int idx = search.Find(separator);
        if (idx == -1)
        {
            if (trimSpaces)
            {
                search.TrimLeft();
                search.TrimRight();
            }
            if (!search.IsEmpty())
                array.Add(search);
            break;
        }
        CString part = search.Left(idx);
        search.Delete(0, idx + seplen);
        if (trimSpaces)
        {
            part.TrimLeft();
            part.TrimRight();
        }
        if (!part.IsEmpty())
            array.Add(part);
    }
}
struct code_ext
{
	CString code;
	CString info;
	bool	bsel;
	code_ext()
	{
		bsel = false;
	}
	code_ext(LPCTSTR lpszText)
	{
		bsel = false;
		CSimpleArray<CString> ar;
		StringToArray(lpszText,ar,_T(","));
		if (ar.GetSize() >= 1)
			code = ar[0];
		if (ar.GetSize() >= 2)
			bsel = ar[1] != _T("0");
		if (ar.GetSize() >= 3)
			info = ar[2];
	}
};

struct code_baseclass
{
	CString code;
	CString baseclass;
	code_baseclass(LPCTSTR lpszText)
	{
		CSimpleArray<CString> ar;
		StringToArray(lpszText,ar,_T(","));
		if (ar.GetSize() >= 1)
			code = ar[0];
		if (ar.GetSize() >= 2)
			baseclass = ar[1];
	}
};

class CWizardInfo  : public vs_wizard_info
{
public:
	CWizardInfo();
	virtual ~CWizardInfo();
	
	fox::code_file * p_return_files;

	CString strCodeWizInfo;
	CString	strCodeWizName;
	CString strProjectPath;
	CString strProjectName;
	CString	strClassName;
	CString strBaseClass;
	CString strFileName;
	CString	strDialogID;

	bool	bUseCppFiles;
	bool	bUseStdAfx;
	bool	bUseResource;
	bool	bUseConstruction;
	bool	bUseDestruction;
	bool	bUseGuidSymbol;

	// 
	std::vector<code_ext>	ar_ext;
	std::vector<code_baseclass> ar_baseclass;
/*
	bool	bUseDDX;
	bool	bUseUpUI;
	bool	bUseMsgFilter;
	bool	bUseIdle;
	bool	bUseResize;
	bool	bUseModal;
*/
	fox::codewiz_config cfg;

	str_vector	ar_id;
};

#endif // !defined(AFX_WIZARDINFO_H__8145D181_A062_4641_A704_89B59CA3913B__INCLUDED_)
