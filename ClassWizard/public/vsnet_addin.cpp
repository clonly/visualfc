// vsnet_addin.cpp : implementation of the vsnet_addin class
//
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "vsnet_addin.h"

static EnvDTE::ProjectItemPtr FindItem(EnvDTE::ProjectPtr pProject, _bstr_t ItemName, EnvDTE::ProjectItemPtr pPrevElem)
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

static EnvDTE::ProjectItemPtr EnumItem(EnvDTE::ProjectPtr & pProject, CSimpleArray<CString> & ar, EnvDTE::ProjectItemPtr pPrevElem)
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
	for (short i = 1; i <= Count; i++)
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
		CString Name = (LPCTSTR)IName;
		ar.Add(Name);
		EnvDTE::ProjectItemPtr pItem2 = EnumItem(pProject, ar,pItem);
		if (pItem2 != NULL)
			return pItem2;
	}
	return EnvDTE::ProjectItemPtr(NULL);
}


vsnet_addin::vsnet_addin()
{
	m_fc.load(_AtlModule.GetResourceInstance(),this);
}
vsnet_addin::~vsnet_addin()
{
	m_fc.free();
}

HRESULT vsnet_addin::GetActiveProject(EnvDTE::ProjectPtr& pProj)
{
	EnvDTE::DocumentPtr pCurDoc;
	m_pDTE->get_ActiveDocument(&pCurDoc);
	if (pCurDoc != NULL)
	{
		EnvDTE::ProjectItemPtr pProjItem;
		pCurDoc->get_ProjectItem(&pProjItem);
		if (pProjItem == NULL)
		{
			return S_FALSE;
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

HRESULT vsnet_addin::GetSelectedProject(EnvDTE::ProjectPtr& pProj)
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

HRESULT vsnet_addin::SaveAllDocuments()
{
	EnvDTE::DocumentsPtr docs;
	HRESULT hr = m_pDTE->get_Documents(&docs);
	if (docs == NULL)
		return S_FALSE;
	hr = docs->SaveAll();
	return hr;
}

HRESULT vsnet_addin::GetOpenFileDocument(EnvDTE::DocumentPtr & pDoc, const char * file)
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

bool vsnet_addin::goto_line(const char *file, int line)
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

int  vsnet_addin::get_line_column(const char * file, int line)
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
	CString text = (LPCTSTR)(_bstr_t)bstr;
	CString right = text;
	right.TrimLeft();
	return text.GetLength()-right.GetLength();
}

bool vsnet_addin::add_project_file(const char * file)
{
	EnvDTE::ProjectPtr pProj;
	HRESULT hr = S_FALSE;
	if (GetActiveProject(pProj) == S_FALSE || pProj == NULL)
	{
		return false;
	}
	EnvDTE::ProjectItemsPtr pItems;
	if (pProj->get_ProjectItems(&pItems) == S_FALSE || pItems == NULL)
	{
		return false;
	}
	EnvDTE::ProjectItemPtr pItem;
	hr = pItems->AddFromFile(_bstr_t(file),&pItem);
/*
	EnvDTE::ItemOperationsPtr pItemOpr;
	m_pDTE->get_ItemOperations(&pItemOpr);
	EnvDTE::ProjectItemPtr item;
	pItemOpr->AddExistingItem(_bstr_t(file),&item);
*/
	return hr == S_OK;
}

const char * vsnet_addin::get_project_path()
{
	EnvDTE::ProjectPtr pProj;
	if (GetActiveProject(pProj) == S_FALSE || pProj == NULL)
	{
		return "";
	}
	EnvDTE::DocumentPtr pDoc;
	EnvDTE::TextDocumentPtr doc;
	EnvDTE::TextSelectionPtr p;
	CComBSTR name;
	pProj->get_FullName(&name);
	static CString s_path;
	s_path = name;
	int pos = s_path.ReverseFind(_T('\\'));
	if (pos)
	{
		s_path = s_path.Left(pos);
		return (char*)(const char*)s_path;
	}
	return "";
}
const char * vsnet_addin::get_project_name()
{
	EnvDTE::ProjectPtr pProj;
	if (GetActiveProject(pProj) == S_FALSE || pProj == NULL)
	{
		return "";
	}
	EnvDTE::DocumentPtr pDoc;
	EnvDTE::TextDocumentPtr doc;
	EnvDTE::TextSelectionPtr p;
	CComBSTR name;
	pProj->get_Name(&name);
	static CString s_path;
	s_path = name;
	return (char*)(const char*)s_path;
	return "";
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

bool vsnet_addin::insert_block(const char * file, int line, int column, const char * text)
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

bool vsnet_addin::replace_text(const char * file, int line, const char * old, const char * text)
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

bool vsnet_addin::ExecVFCWizard()
{
	if (m_fc.pvfc)
	{
		EnvDTE::ProjectPtr pProj;
		if (GetActiveProject(pProj) == S_FALSE || pProj == NULL)
		{
			m_fc.pvfc->load_project(NULL,NULL);
			return false;
		}
		EnvDTE::DocumentPtr pDoc;
		m_pDTE->get_ActiveDocument(&pDoc);
		CComBSTR active_file;
		if (pDoc != NULL)
		{
			pDoc->get_Name(&active_file);
		}	
		m_files.RemoveAll();
		EnumItem(pProj,m_files,NULL);
		this->SaveAllDocuments();
		CComBSTR name;
		pProj->get_Name(&name);
		m_fc.pvfc->load_project((CString)name,(CString)active_file);
	}
	return true;
}