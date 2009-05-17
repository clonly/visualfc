// CodeExtPage.cpp: implementation of the CCodeExtPage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CodeExtPage.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCodeExtPage::CCodeExtPage()
{
	SetTitle("Code Wizard 8.0 - Step 2 of 2");
	SetHeaderTitle("Application Type");
	SetHeaderSubTitle("Selection Application Type");
	m_dwButton = PSWIZB_BACK | PSWIZB_FINISH;
}

CCodeExtPage::~CCodeExtPage()
{

}

void CCodeExtPage::OnInit()
{
	m_extList.InsertColumn(0,_T("CODE_EXT_DEFINE"),LVCFMT_LEFT,200);
	m_extList.InsertColumn(1,_T("CODE_EXT_INFO"),LVCFMT_LEFT,200);
	
	for (int i = 0; i < info->ar_ext.size(); i++)
	{
		code_ext & ce = info->ar_ext[i];
		int item = m_extList.InsertItem(i,ce.code);
		m_extList.SetItemText(item,1,ce.info);
		m_extList.SetCheckState(item,ce.bsel);
	}
}
