// Commands.cpp : implementation file
//

#include "stdafx.h"
#include "FreeCode.h"
#include "Commands.h"
#include "dspparser.h"

#include <comdef.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommands
//DEL const char * CCommands::get_project_dsp()
//DEL {
//DEL 	CComPtr<IDispatch> ActiveProject;
//DEL 	m_pApplication->get_ActiveProject(&ActiveProject);
//DEL 	CComQIPtr<IGenericProject, &IID_IGenericProject> pActiveProject(ActiveProject);
//DEL 
//DEL 	if (pActiveProject)
//DEL 	{
//DEL 		CComBSTR bstrText;
//DEL 		pActiveProject->get_FullName(&bstrText);
//DEL 		return (LPCTSTR)CString(bstrText);
//DEL 	}	
//DEL 	return NULL;
//DEL }

int CCommands::get_line_column(const char * file, int line)
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

bool CCommands::goto_line(const char * file, int line)
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

LRESULT CCommands::InsertDocumentText(CComPtr<IDispatch> & Document, int line, int column, const char * text)
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

LRESULT CCommands::ReplaceDocumentText(CComPtr<IDispatch> & Document, int line, const char * old, const char * text)
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

LRESULT CCommands::SaveAllDocuments()
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


LRESULT CCommands::GetOpenFileDocument(CComPtr<IDispatch> & Document, const char * file)
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


bool CCommands::insert_block(const char * file,int line,int column, const char * text)
{
	CComPtr<IDispatch> Document;
	HRESULT hr = GetOpenFileDocument(Document,file);
	if (hr != S_OK)
		return false;
	hr = InsertDocumentText(Document,line,column,text);
	return (bool)(hr == S_OK);
}

bool CCommands::replace_text(const char * file, int line, const char * old, const char * text)
{
	CComPtr<IDispatch> Document;
	HRESULT hr = GetOpenFileDocument(Document,file);
	if (hr != S_OK)
		return false;

	hr = ReplaceDocumentText(Document,line,old,text);
	return (bool)(hr == S_OK);
}

CCommands::CCommands()
{
	m_pApplication = NULL;
	m_pApplicationEventsObj = NULL;
	m_pDebuggerEventsObj = NULL;	
}

CCommands::~CCommands()
{
	ASSERT (m_pApplication != NULL);
	m_pApplication->Release();
}

void CCommands::SetApplicationObject(IApplication* pApplication)
{
	// This function assumes pApplication has already been AddRef'd
	//  for us, which CDSAddIn did in its QueryInterface call
	//  just before it called us.
	m_pApplication = pApplication;

	// Create Application event handlers
	XApplicationEventsObj::CreateInstance(&m_pApplicationEventsObj);
	m_pApplicationEventsObj->AddRef();
	m_pApplicationEventsObj->Connect(m_pApplication);
	m_pApplicationEventsObj->m_pCommands = this;

	// Create Debugger event handler
	CComPtr<IDispatch> pDebugger;
	if (SUCCEEDED(m_pApplication->get_Debugger(&pDebugger)) 
		&& pDebugger != NULL)
	{
		XDebuggerEventsObj::CreateInstance(&m_pDebuggerEventsObj);
		m_pDebuggerEventsObj->AddRef();
		m_pDebuggerEventsObj->Connect(pDebugger);
		m_pDebuggerEventsObj->m_pCommands = this;
	}

	m_fc.load(this);
	m_fc.create();
}

void CCommands::UnadviseFromEvents()
{
	ASSERT (m_pApplicationEventsObj != NULL);
	m_pApplicationEventsObj->Disconnect(m_pApplication);
	m_pApplicationEventsObj->Release();
	m_pApplicationEventsObj = NULL;

	if (m_pDebuggerEventsObj != NULL)
	{
		// Since we were able to connect to the Debugger events, we
		//  should be able to access the Debugger object again to
		//  unadvise from its events (thus the VERIFY_OK below--see stdafx.h).
		CComPtr<IDispatch> pDebugger;
		VERIFY_OK(m_pApplication->get_Debugger(&pDebugger));
		ASSERT (pDebugger != NULL);
		m_pDebuggerEventsObj->Disconnect(pDebugger);
		m_pDebuggerEventsObj->Release();
		m_pDebuggerEventsObj = NULL;
	}
	m_fc.free();
}


/////////////////////////////////////////////////////////////////////////////
// Event handlers

// TODO: Fill out the implementation for those events you wish handle
//  Use m_pCommands->GetApplicationObject() to access the Developer
//  Studio Application object

// Application events

HRESULT CCommands::XApplicationEvents::BeforeBuildStart()
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::BuildFinish(long nNumErrors, long nNumWarnings)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::BeforeApplicationShutDown()
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::DocumentOpen(IDispatch* theDocument)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::BeforeDocumentClose(IDispatch* theDocument)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::DocumentSave(IDispatch* theDocument)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::NewDocument(IDispatch* theDocument)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::WindowActivate(IDispatch* theWindow)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::WindowDeactivate(IDispatch* theWindow)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::WorkspaceOpen()
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::WorkspaceClose()
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::NewWorkspace()
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

// Debugger event

HRESULT CCommands::XDebuggerEvents::BreakpointHit(IDispatch* pBreakpoint)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}


/////////////////////////////////////////////////////////////////////////////
// CCommands methods
//DEL STDMETHODIMP CCommands::ClassWizard()
//DEL {
//DEL 	// TODO: Add your implementation code here
//DEL 	VERIFY_OK(m_pApplication->EnableModeless(VARIANT_FALSE));
//DEL 
//DEL 	if (!m_fox.p_item.empty() )
//DEL 	{
//DEL 		if (m_fox.p_item->handle() == NULL)
//DEL 		{
//DEL 			HWND hParent = ::GetActiveWindow();
//DEL 			m_fox.p_item->create(hParent,CWindow::rcDefault);
//DEL 		}
//DEL 		if (m_fox.p_item->handle() != NULL)
//DEL 		{
//DEL 			this->SaveAllDocuments();
//DEL 			
//DEL 			CComPtr<IDispatch> ActiveProject;
//DEL 			m_pApplication->get_ActiveProject(&ActiveProject);
//DEL 			CComQIPtr<IGenericProject, &IID_IGenericProject> pActiveProject(ActiveProject);	
//DEL 			if (pActiveProject)
//DEL 			{
//DEL 				CComBSTR name;
//DEL 				CComBSTR path;
//DEL 				pActiveProject->get_FullName(&path);
//DEL 				pActiveProject->get_Name(&name);
//DEL 
//DEL //				m_fox.p_item->load_project((CString)name,(CString)path,false);
//DEL 			}
//DEL 		}
//DEL 	}
//DEL 	VERIFY_OK(m_pApplication->EnableModeless(VARIANT_TRUE));
//DEL 
//DEL 	return S_OK;
//DEL }

STDMETHODIMP CCommands::WTLWizard()
{
	// TODO: Add your implementation code here
	VERIFY_OK(m_pApplication->EnableModeless(VARIANT_FALSE));

	if (m_fc.pwtl)
	{
		this->SaveAllDocuments();
		CComBSTR	ActiveFileName("");		
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
		else
		{
			ActiveFileName = _T("");
		}
		if (pActiveProject)
		{
			CComBSTR name;
			CComBSTR path;
			pActiveProject->get_FullName(&path);
			pActiveProject->get_Name(&name);

			m_dsp.load_dsp((CString)path);
			
			m_fc.pwtl->load_project(GetActiveWindow(),(CString)name,(CString)ActiveFileName,false);
		}
	}
	VERIFY_OK(m_pApplication->EnableModeless(VARIANT_TRUE));

	return S_OK;
}

STDMETHODIMP CCommands::WINXWizard()
{
	// TODO: Add your implementation code here
	VERIFY_OK(m_pApplication->EnableModeless(VARIANT_FALSE));
	if (m_fc.pwinx)
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
			
			m_fc.pwinx->load_project(GetActiveWindow(),(CString)name,(CString)ActiveFileName,false);
		}
	}
	VERIFY_OK(m_pApplication->EnableModeless(VARIANT_TRUE));

	return S_OK;
}

STDMETHODIMP CCommands::Options()
{
	// TODO: Add your implementation code here

	return S_OK;
}
