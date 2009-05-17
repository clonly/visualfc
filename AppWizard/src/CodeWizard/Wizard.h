// Wizard.h: interface for the CWizard class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WIZARD_H__B7747FF6_73A4_4D0A_BEAE_CCBAAECC5729__INCLUDED_)
#define AFX_WIZARD_H__B7747FF6_73A4_4D0A_BEAE_CCBAAECC5729__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WizardInfo.h"

class CWizard  
{
public:
	CString GetTargetName(const CString & strName, const CString & strProjectName);
	bool AddFilesToProject(const CString & strProjectName, const CString &strProjectPath, str_vector & array);
	bool make_project();
	int ExecuteWizard();
	CWizard();
	virtual ~CWizard();
	
	CWizardInfo	info;
	vs_wizard	wizard;
};

#endif // !defined(AFX_WIZARD_H__B7747FF6_73A4_4D0A_BEAE_CCBAAECC5729__INCLUDED_)
