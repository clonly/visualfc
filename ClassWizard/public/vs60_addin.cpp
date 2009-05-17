// vs60_addin.cpp: implementation of the vs60_addin class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../VFCAddin/VFCAddin.h"
#include "vs60_addin.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

vs60_addin::vs60_addin()
{

}

vs60_addin::~vs60_addin()
{

}

int vs60_addin::get_line_column(const char * file, int line)
{
	CComPtr<IDispatch> Document;
	HRESULT hr = GetOpenFileDocument(Document,file);
	if (hr == S_FALSE)
		return false;
	
	CComQIPtr<ITextDocument, &IID_ITextDocument> pTextDocument(Document);
	if (pTextDocument == NULL)
		return false;

	CComPtr<IDispatch> Selection;
	hr = pTextDocument->get_Selection(&Selection);
	CComQIPtr<ITextSelection, &IID_ITextSelection> pSelection(Selection);
	if (pSelection == NULL)
	{
		return false;
	}	
	hr = pSelection->MoveTo(line,0,_variant_t(long(0)));
	hr = pSelection->SelectLine();
	CComBSTR bstr;
	pSelection->get_Text(&bstr);
	CString text = bstr;
	CString right = text;
	right.TrimLeft();
	return text.GetLength()-right.GetLength();
}

bool vs60_addin::goto_line(const char * file, int line)
{
	CComPtr<IDispatch> Document;
	HRESULT hr = GetOpenFileDocument(Document,file);
	if (hr == S_FALSE)
		return false;
	
	CComQIPtr<ITextDocument, &IID_ITextDocument> pTextDocument(Document);
	if (pTextDocument == NULL)
		return false;

	CComPtr<IDispatch> Selection;
	hr = pTextDocument->get_Selection(&Selection);
	CComQIPtr<ITextSelection, &IID_ITextSelection> pSelection(Selection);
	if (pSelection == NULL)
	{
		return false;
	}	
	hr = pSelection->GoToLine(line,_variant_t(long(0)));

	return (hr == S_OK);
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

LRESULT vs60_addin::InsertDocumentText(CComPtr<IDispatch> & Document, int line, int column, const char * text)
{
	CComQIPtr<ITextDocument, &IID_ITextDocument> pTextDocument(Document);
	if (pTextDocument == NULL)
		return false;

	CComPtr<IDispatch> Selection;
	pTextDocument->get_Selection(&Selection);
	CComQIPtr<ITextSelection, &IID_ITextSelection> pSelection(Selection);
	if (pSelection == NULL)
	{
		return false;
	}	

	HRESULT hr = pSelection->MoveTo(line,column,_variant_t(long(0)));
	hr = pSelection->put_Text(CComBSTR(text));


	return hr;
}

LRESULT vs60_addin::ReplaceDocumentText(CComPtr<IDispatch> & Document, int line, const char * old, const char * text)
{
	CComQIPtr<ITextDocument, &IID_ITextDocument> pTextDocument(Document);
	if (pTextDocument == NULL)
		return false;

	CComPtr<IDispatch> Selection;
	pTextDocument->get_Selection(&Selection);
	CComQIPtr<ITextSelection, &IID_ITextSelection> pSelection(Selection);
	if (pSelection == NULL)
	{
		return false;
	}
	HRESULT hr = pSelection->GoToLine(line,(_variant_t)(long)0);
	pSelection->SelectLine();
	VARIANT_BOOL bRet;
	CComVariant flag = (long)dsMatchWord;
	pSelection->ReplaceText(CComBSTR(old),CComBSTR(text),flag,&bRet);
	return hr;
}

LRESULT vs60_addin::SaveAllDocuments()
{
	HRESULT hr = S_OK;
	CComPtr<IDispatch> Documents;
	m_pApplication->get_Documents(&Documents);
	CComQIPtr<IDocuments,&IID_IDocuments> pDocuments(Documents);
	if (pDocuments == NULL)
		return S_FALSE;
	DsSaveStatus status;
	hr = pDocuments->SaveAll(_variant_t(true),&status);
	return hr;
}


LRESULT vs60_addin::GetOpenFileDocument(CComPtr<IDispatch> & Document, const char * file)
{
	HRESULT hr = S_OK;
	CComPtr<IDispatch> Documents;
	m_pApplication->get_Documents(&Documents);
	CComQIPtr<IDocuments,&IID_IDocuments> pDocuments(Documents);

	if (pDocuments == NULL)
		return S_FALSE;

	
	long count = 0;
	pDocuments->get_Count(&count);
	for (long i = 0; i < count; i++)
	{
		CComPtr<IDispatch> doc;
		pDocuments->Item(_variant_t(i),&doc);
		CComQIPtr<IGenericDocument, &IID_IGenericDocument> pDoc(doc);
		if (pDoc != NULL)
		{
			CComBSTR name;
			pDoc->get_FullName(&name);
			if (name == CComBSTR(file))
			{
				Document = doc;
				return S_OK;
			}
		}
	}

	_variant_t type = _bstr_t("Auto");
	CComBSTR filename = file;
	_variant_t readonly = bool(false);

	hr = pDocuments->Open(filename,type,readonly,&Document);
	return hr;
}


bool vs60_addin::insert_block(const char * file,int line,int column, const char * text)
{
	CComPtr<IDispatch> Document;
	HRESULT hr = GetOpenFileDocument(Document,file);
	if (hr != S_OK)
		return false;

	hr = InsertDocumentText(Document,line,column,text);
	return (bool)(hr == S_OK);
}

bool vs60_addin::replace_text(const char * file, int line, const char * old, const char * text)
{
	CComPtr<IDispatch> Document;

	HRESULT hr = GetOpenFileDocument(Document,file);
	if (hr != S_OK)
		return false;

	hr = ReplaceDocumentText(Document,line,old,text);
	return (bool)(hr == S_OK);
}

bool vs60_addin::add_project_file(const char * file)
{
	CComPtr<IDispatch> ActiveProject;
	CComPtr<IDispatch> ActiveDocument;
	m_pApplication->get_ActiveProject(&ActiveProject);
	m_pApplication->get_ActiveDocument(&ActiveDocument);
	CComQIPtr<IGenericProject, &IID_IGenericProject> pActiveProject(ActiveProject);	
	if (pActiveProject)
	{
		CComQIPtr<IBuildProject, &IID_IBuildProject> pBuildProject(pActiveProject);
		if (pBuildProject)
		{
			HRESULT hr = pBuildProject->AddFile(_bstr_t(file),_variant_t(long(0)));
			return hr == S_OK;
		}
	}
	return false;
}

const char * vs60_addin::get_project_path()
{
	static CString s_path;
	CComBSTR	ActiveFileName;		
	CComPtr<IDispatch> ActiveProject;
	m_pApplication->get_ActiveProject(&ActiveProject);
	CComQIPtr<IGenericProject, &IID_IGenericProject> pActiveProject(ActiveProject);	
	if (pActiveProject)
	{
		CComBSTR name;
		CComBSTR path;
		pActiveProject->get_FullName(&path);
		s_path = path;
		int pos = s_path.ReverseFind(_T('\\'));
		if (pos)
		{
			s_path = s_path.Left(pos);
			return (char*)(const char*)s_path;
		}
	}
	return "";
}

const char * vs60_addin::get_project_name()
{
	static CString s_name;
	CComBSTR	ActiveFileName;		
	CComPtr<IDispatch> ActiveProject;
	m_pApplication->get_ActiveProject(&ActiveProject);
	CComQIPtr<IGenericProject, &IID_IGenericProject> pActiveProject(ActiveProject);	
	if (pActiveProject)
	{
		CComBSTR name;
		pActiveProject->get_Name(&name);
		s_name = name;
		return s_name;
	}
	return "";
}

bool vs60_addin::ExecVFCWizard()
{
	if (m_fc.pvfc)
 	{
 		this->SaveAllDocuments();
 		CComBSTR	ActiveFileName;		
 		CComPtr<IDispatch> ActiveProject;
 		CComPtr<IDispatch> ActiveDocument;
 		m_pApplication->get_ActiveProject(&ActiveProject);
 		m_pApplication->get_ActiveDocument(&ActiveDocument);
 		CComQIPtr<IGenericProject, &IID_IGenericProject> pActiveProject(ActiveProject);	
 		CComQIPtr<IGenericDocument, &IID_IGenericDocument> pActiveDocument(ActiveDocument);
 		if (pActiveDocument)
 		{
 			pActiveDocument->get_Name(&ActiveFileName);
 		}
 		if (pActiveProject)
 		{
 			CComBSTR name;
 			CComBSTR path;
 			pActiveProject->get_FullName(&path);
 			pActiveProject->get_Name(&name);
 
 			m_dsp.load_dsp((CString)path);
 			
 			m_fc.pvfc->load_project((CString)name,(CString)ActiveFileName);
 		}
		else
		{
			m_fc.pvfc->load_project(NULL,NULL);
		}
 	}
	else
	{
		return false;
	}
	return true;
}
