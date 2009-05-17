// Connect.cpp : CConnect 的具体实现
#include "stdafx.h"
#include "AddIn.h"
#include "Connect.h"

extern CAddInModule _AtlModule;

// CConnect
STDMETHODIMP CConnect::OnConnection(IDispatch *pApplication, ext_ConnectMode ConnectMode, IDispatch *pAddInInst, SAFEARRAY ** /*自定义*/ )
{
	HRESULT hr = S_OK;
	pApplication->QueryInterface(__uuidof(DTE2), (LPVOID*)&m_pDTE);
	pAddInInst->QueryInterface(__uuidof(EnvDTE::AddIn), (LPVOID*)&m_pAddInInstance);

	typedef struct
	{
		LPCTSTR name;
		LPCTSTR text;
		LPCTSTR tooltip;
	}COMMANDDEFS;

	// these command must be in left-to-right order of the toolbar buttons
	COMMANDDEFS s_cd[] = {
		{ "ClassWizard","ClassWizard","Winx ClassWizard", }, 
		{ "WTLWizard","WTLWizard","WTL ClassWizard",  }, 
		{ "WINXWizard","WINXWizard","WINX ClassWizard", }, 
		{ "Options", "Options","VisualFC Options ", }, 
	};

	if(ConnectMode == 5) //5 == ext_cm_UISetup
	{
		HRESULT hr = S_OK;
		CComPtr<IDispatch> pDisp;
		CComQIPtr<EnvDTE::Commands> pCommands;
		CComQIPtr<Commands2> pCommands2;
		CComQIPtr<_CommandBars> pCommandBars;
		CComPtr<CommandBarControl> pCommandBarControl;
		CComPtr<EnvDTE::Command> pCreatedCommandWTL;
		CComPtr<EnvDTE::Command> pCreatedCommandWinx;
		CComPtr<CommandBar> pMenuBarCommandBar;
		CComPtr<CommandBarControls> pMenuBarControls;
		CComPtr<CommandBarControl> pToolsCommandBarControl;
		CComQIPtr<CommandBar> pToolsCommandBar;
		CComQIPtr<CommandBarPopup> pToolsPopup;

		IfFailGoCheck(m_pDTE->get_Commands(&pCommands), pCommands);
		pCommands2 = pCommands;
		hr = (pCommands2->AddNamedCommand2(m_pAddInInstance, CComBSTR("VFC_WTL"), CComBSTR("VFC_WTL"), CComBSTR("Executes VisualFC WTl ClassWizard"), VARIANT_FALSE, CComVariant(IDB_BITMAP_WTL), NULL, EnvDTE::vsCommandStatusSupported+EnvDTE::vsCommandStatusEnabled, vsCommandStylePictAndText, vsCommandControlTypeButton, &pCreatedCommandWTL)) && (pCreatedCommandWTL);
		hr = (pCommands2->AddNamedCommand2(m_pAddInInstance, CComBSTR("VFC_WINX"), CComBSTR("VFC_WINX"), CComBSTR("Executes VisualFC Winx ClassWizard"), VARIANT_TRUE, CComVariant(59), NULL, EnvDTE::vsCommandStatusSupported+EnvDTE::vsCommandStatusEnabled, vsCommandStylePictAndText, vsCommandControlTypeButton, &pCreatedCommandWinx)) && (pCreatedCommandWinx);
		if (SUCCEEDED(hr))
		{
			//在“工具”菜单栏上添加一个按钮。
			IfFailGoCheck(m_pDTE->get_CommandBars(&pDisp), pDisp);
			pCommandBars = pDisp;

			//查找 MenuBar 命令栏，该命令栏是容纳所有主菜单项的顶级命令栏:
			IfFailGoCheck(pCommandBars->get_Item(CComVariant(L"MenuBar"), &pMenuBarCommandBar), pMenuBarCommandBar);
			IfFailGoCheck(pMenuBarCommandBar->get_Controls(&pMenuBarControls), pMenuBarControls);

			//在 MenuBar 命令栏上查找“工具”命令栏:
			IfFailGoCheck(pMenuBarControls->get_Item(CComVariant(L"Tools"), &pToolsCommandBarControl), pToolsCommandBarControl);
			pToolsPopup = pToolsCommandBarControl;
			IfFailGoCheck(pToolsPopup->get_CommandBar(&pToolsCommandBar), pToolsCommandBar);

			//添加控件:
			pDisp = NULL;
			IfFailGoCheck(pCreatedCommandWTL->AddControl(pToolsCommandBar, 1, &pDisp), pDisp);
			IfFailGoCheck(pCreatedCommandWinx->AddControl(pToolsCommandBar, 1, &pDisp), pDisp);
		}
		return S_OK;		
	}
Error:
	return hr;
}

STDMETHODIMP CConnect::OnDisconnection(ext_DisconnectMode /*RemoveMode*/, SAFEARRAY ** /*自定义*/ )
{
	m_pDTE = NULL;
	m_pAddInInstance = NULL;
	return S_OK;
}

STDMETHODIMP CConnect::OnAddInsUpdate (SAFEARRAY ** /*自定义*/ )
{
	return S_OK;
}

STDMETHODIMP CConnect::OnStartupComplete (SAFEARRAY ** /*自定义*/ )
{
	return S_OK;
}

STDMETHODIMP CConnect::OnBeginShutdown (SAFEARRAY ** /*自定义*/ )
{
	return S_OK;
}

STDMETHODIMP CConnect::QueryStatus(BSTR bstrCmdName, EnvDTE::vsCommandStatusTextWanted NeededText, EnvDTE::vsCommandStatus *pStatusOption, VARIANT *pvarCommandText)
{
  if(NeededText == EnvDTE::vsCommandStatusTextWantedNone)
	{
	  if(!_wcsicmp(bstrCmdName, L"FreeCode2005.Connect.VFC_WTL"))
	  {
		  *pStatusOption = (EnvDTE::vsCommandStatus)(EnvDTE::vsCommandStatusEnabled+EnvDTE::vsCommandStatusSupported);
	  }
	  else if(!_wcsicmp(bstrCmdName, L"FreeCode2005.Connect.VFC_WINX"))
	  {
		  *pStatusOption = (EnvDTE::vsCommandStatus)(EnvDTE::vsCommandStatusEnabled+EnvDTE::vsCommandStatusSupported);
	  }
  }
	return S_OK;
}

STDMETHODIMP CConnect::Exec(BSTR bstrCmdName, EnvDTE::vsCommandExecOption ExecuteOption, VARIANT * /*pvarVariantIn*/, VARIANT * /*pvarVariantOut*/, VARIANT_BOOL *pvbHandled)
{
	*pvbHandled = VARIANT_FALSE;
	if(ExecuteOption == EnvDTE::vsCommandExecOptionDoDefault)
	{
		if(!_wcsicmp(bstrCmdName, L"FreeCode2005.Connect.VFC_WTL"))
		{
			ExecWTLWizard();
			*pvbHandled = VARIANT_TRUE;
			return S_OK;
		}
		if(!_wcsicmp(bstrCmdName, L"FreeCode2005.Connect.VFC_WINX"))
		{
			ExecWINXWizard();
			*pvbHandled = VARIANT_TRUE;
			return S_OK;
		}
	}
	return S_OK;
}

EnvDTE::ProjectItemPtr FindItem(EnvDTE::ProjectPtr pProject, _bstr_t ItemName, EnvDTE::ProjectItemPtr pPrevElem)
{
	EnvDTE::ProjectItemsPtr pItems = NULL;
	if (pPrevElem == NULL)
	{
		pProject->get_ProjectItems(&pItems);
	}
	else
	{
		pPrevElem->get_ProjectItems(&pItems);
	}
	if (pItems == NULL)
		return EnvDTE::ProjectItemPtr(NULL);
	long Count;
	pItems->get_Count(&Count);
	if (Count == 0)
		return EnvDTE::ProjectItemPtr(NULL);
	for (long i = 1; i <= Count; i++)
	{
		EnvDTE::ProjectItemPtr pItem;
		pItems->Item(_variant_t(i), &pItem);
		_bstr_t IName;
		pItem->get_Name(IName.GetAddress());

		if (!_wcsicmp(IName, ItemName))
		{
			return pItem;
		}

		EnvDTE::ProjectItemPtr pItem2 = FindItem(pProject, ItemName, pItem);
		if (pItem2 != NULL)
			return pItem2;
	}
	return EnvDTE::ProjectItemPtr(NULL);
}

EnvDTE::ProjectItemPtr EnumItem(EnvDTE::ProjectPtr & pProject, CAtlArray<CString> & ar, EnvDTE::ProjectItemPtr pPrevElem)
{
	EnvDTE::ProjectItemsPtr pItems = NULL;
	if (pPrevElem == NULL)
	{
		pProject->get_ProjectItems(&pItems);
	}
	else
	{
		pPrevElem->get_ProjectItems(&pItems);
	}
	if (pItems == NULL)
		return EnvDTE::ProjectItemPtr(NULL);
	long Count;
	pItems->get_Count(&Count);
	if (Count == 0)
		return EnvDTE::ProjectItemPtr(NULL);
	for (long i = 1; i <= Count; i++)
	{
		EnvDTE::ProjectItemPtr pItem;
		pItems->Item(_variant_t(i), &pItem);
		_bstr_t IName;
		//pItem->get_Name(IName.GetAddress());
		pItem->get_FileNames(i,IName.GetAddress());
		/*
		if (!_wcsicmp(IName, ItemName))
		{
			return pItem;
		}
		*/
		ar.Add(IName);
		EnvDTE::ProjectItemPtr pItem2 = EnumItem(pProject, ar,pItem);
		if (pItem2 != NULL)
			return pItem2;
	}
	return EnvDTE::ProjectItemPtr(NULL);
}


bool CConnect::ExecWTLWizard()
{
	EnvDTE::ProjectPtr pProj;
	if (GetActiveProject(pProj) == E_FAIL)
		return false;

	EnvDTE::DocumentPtr pDoc;
	EnvDTE::TextDocumentPtr doc;
	EnvDTE::TextSelectionPtr p;

	m_files.RemoveAll();
	EnumItem(pProj,m_files,NULL);

	if (m_fc.pwtl)
	{
		if (pProj)
		{
			this->SaveAllDocuments();
			CComBSTR name;
			pProj->get_Name(&name);
			m_fc.pwtl->load_project(GetActiveWindow(),(CString)name,"",false);
		}
	}
	return true;
}

bool CConnect::ExecWINXWizard()
{
	EnvDTE::ProjectPtr pProj;
	if (GetActiveProject(pProj) == E_FAIL)
		return false;

	EnvDTE::DocumentPtr pDoc;
	EnvDTE::TextDocumentPtr doc;
	EnvDTE::TextSelectionPtr p;

	m_files.RemoveAll();
	EnumItem(pProj,m_files,NULL);

	if (m_fc.pwinx)
	{
		if (pProj)
		{
			this->SaveAllDocuments();
			CComBSTR name;
			pProj->get_Name(&name);
			m_fc.pwinx->load_project(GetActiveWindow(),(CString)name,"",false);
		}
	}
	return true;
}


HRESULT CConnect::GetActiveProject(EnvDTE::ProjectPtr& pProj)
{
	EnvDTE::DocumentPtr pCurDoc;
	m_pDTE->get_ActiveDocument(&pCurDoc);
	if (pCurDoc != NULL)
	{
		EnvDTE::ProjectItemPtr pProjItem;
		pCurDoc->get_ProjectItem(&pProjItem);
		if (pProjItem == NULL)
		{
			return E_FAIL;
		}
		return pProjItem->get_ContainingProject(&pProj);
	}
	else
	{
		_variant_t vt, vt2;

		if (FAILED(m_pDTE->get_ActiveSolutionProjects(&vt)))
		{
			return S_FALSE;
		}

		if (vt.vt != (VT_ARRAY | VT_VARIANT))
		{
			return S_FALSE;
		}
		SAFEARRAY* pArray = vt.parray;
		if (pArray->cDims != 1 && !(pArray->fFeatures & FADF_DISPATCH ))
		{
			return S_FALSE;
		}

		if (pArray[0].rgsabound[0].cElements > 0)
		{
			vt2 = ((_variant_t*)pArray[0].pvData)[0];
			pProj = vt2.pdispVal;
			if (pProj == NULL)
			{
				return S_FALSE;
			}
		}
		else
			return S_FALSE;
	}

	return S_OK;
}

HRESULT CConnect::GetSelectedProject(EnvDTE::ProjectPtr& pProj)
{
	EnvDTE::SelectedItemsPtr pSelItems;
	if (m_pDTE->get_SelectedItems(&pSelItems) == S_OK)
	{
		ATLASSERT(pSelItems != NULL);
		long Count;
		pSelItems->get_Count(&Count);
		if (Count)
		{
			EnvDTE::SelectedItemPtr pSelItem;
			pSelItems->Item(_variant_t(1), &pSelItem);
			ATLASSERT(pSelItem != NULL);
			EnvDTE::ProjectItemPtr pProjItem;
			pSelItem->get_ProjectItem(&pProjItem);
			if (pProjItem != NULL)
			{
				return pProjItem->get_ContainingProject(&pProj);
			}
		}
	}
	return E_FAIL;
}

HRESULT CConnect::SaveAllDocuments()
{
	EnvDTE::DocumentsPtr docs;
	HRESULT hr = m_pDTE->get_Documents(&docs);
	if (docs == NULL)
		return S_FALSE;
	hr = docs->SaveAll();
	return hr;
}

HRESULT CConnect::GetOpenFileDocument(EnvDTE::DocumentPtr & pDoc, const char * file)
{
	EnvDTE::DocumentsPtr docs;
	m_pDTE->get_Documents(&docs);
	long count = 0;
	docs->get_Count(&count);
	for (long i = 1; i <= count; i++)
	{
		EnvDTE::DocumentPtr doc;
		docs->Item((_variant_t)i,&doc);
		if (doc != NULL)
		{
			CComBSTR name;
			doc->get_FullName(&name);
			if (name == CComBSTR(file))
			{
				pDoc = doc;
				return S_OK;
			}
		}
	}
	CComBSTR type = _T("Auto");
	CComBSTR filename = file;
	_variant_t readonly = bool(false);

	HRESULT hr = docs->Open(filename,type,readonly,&pDoc);

	return hr;
}

bool CConnect::goto_line(const char *file, int line)
{
	EnvDTE::DocumentPtr	pDoc;
	HRESULT hr = GetOpenFileDocument(pDoc,file);
	if (hr == S_FALSE)
		return false;
	EnvDTE::TextDocumentPtr pTextDocument;
	pDoc->Object(CComBSTR("TextDocument"),(IDispatch**)&pTextDocument);

	if (pTextDocument == NULL)
		return false;

	EnvDTE::TextSelectionPtr pSelection;
	hr = pTextDocument->get_Selection(&pSelection);
	if (pSelection == NULL)
	{
		return false;
	}	

	hr = pSelection->GotoLine(line,_variant_t(long(0)));

	return (hr == S_OK);
}

int  CConnect::get_line_column(const char * file, int line)
{
	EnvDTE::DocumentPtr	pDoc;
	HRESULT hr = GetOpenFileDocument(pDoc,file);
	if (hr == S_FALSE)
		return false;
	EnvDTE::TextDocumentPtr pTextDocument;
	pDoc->Object(CComBSTR("TextDocument"),(IDispatch**)&pTextDocument);

	if (pTextDocument == NULL)
		return false;

	EnvDTE::TextSelectionPtr pSelection;
	hr = pTextDocument->get_Selection(&pSelection);
	if (pSelection == NULL)
	{
		return false;
	}	

	hr = pSelection->GotoLine(line,_variant_t(long(0)));
	hr = pSelection->SelectLine();
	CComBSTR bstr;
	pSelection->get_Text(&bstr);
	CString text = (_bstr_t)bstr;
	CString right = text;
	right.TrimLeft();
	return text.GetLength()-right.GetLength();
}

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

bool CConnect::insert_block(const char * file, int line, int column, const char * text)
{
	EnvDTE::DocumentPtr	pDoc;
	HRESULT hr = GetOpenFileDocument(pDoc,file);
	if (hr == S_FALSE)
		return false;
	EnvDTE::TextDocumentPtr pTextDocument;
	pDoc->Object(CComBSTR("TextDocument"),(IDispatch**)&pTextDocument);

	if (pTextDocument == NULL)
		return false;

	EnvDTE::TextSelectionPtr pSelection;
	hr = pTextDocument->get_Selection(&pSelection);
	if (pSelection == NULL)
	{
		return false;
	}	
	//MoveTo no all effictive
	//hr = pSelection->MoveTo(line,column,false);
	hr = pSelection->GotoLine(line,false);
	hr = pSelection->EndOfLine(0);
	pSelection->Insert(CComBSTR(text),EnvDTE::vsInsertFlagsCollapseToEnd);

	return (hr == S_OK);
}
bool CConnect::replace_text(const char * file, int line, const char * old, const char * text)
{
	EnvDTE::DocumentPtr	pDoc;
	HRESULT hr = GetOpenFileDocument(pDoc,file);
	if (hr == S_FALSE)
		return false;
	EnvDTE::TextDocumentPtr pTextDocument;
	pDoc->Object(CComBSTR("TextDocument"),(IDispatch**)&pTextDocument);

	if (pTextDocument == NULL)
		return false;

	EnvDTE::TextSelectionPtr pSelection;
	hr = pTextDocument->get_Selection(&pSelection);
	if (pSelection == NULL)
	{
		return false;
	}	
	hr = pSelection->GotoLine(line,(_variant_t)(long)0);
	pSelection->SelectLine();
	VARIANT_BOOL bRet;
	hr = pSelection->ReplaceTextA(CComBSTR(old),CComBSTR(text),EnvDTE::vsFindOptionsMatchWholeWord,&bRet);

	return hr == S_OK;
}
