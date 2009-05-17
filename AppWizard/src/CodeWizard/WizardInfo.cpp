// WizardInfo.cpp: implementation of the CWizardInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WizardInfo.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWizardInfo::CWizardInfo()
{
	bUseCppFiles = true;
	bUseStdAfx = true;
	bUseResource = true;
	bUseConstruction = true;
	bUseDestruction = true;
	bUseGuidSymbol = true;
/*
	bUseModal = false;
	bUseMsgFilter = false;
	bUseIdle = false;
	bUseResize = false;
	bUseUpUI = false;
	bUseDDX = false;
*/
}

CWizardInfo::~CWizardInfo()
{

}
