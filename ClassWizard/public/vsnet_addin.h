// vsnet_addin.h : interface of the vsnet_addin class
//
/////////////////////////////////////////////////////////////////////////////
#if !defined(VFC_VSNET_ADDIN_H__9E5785BA_6015_48be_8589_5C263A475981__INCLUDED_)
#define VFC_VSNET_ADDIN_H__9E5785BA_6015_48be_8589_5C263A475981__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "fc_core.h"

#ifdef VFC_VS2003
#pragma warning( disable : 4278 )
//The following #import imports DTE based on it's LIBID
#import "libid:80cc9f66-e7d8-4ddd-85b6-d9e6cd0e93e2" version("7.0") lcid("0") raw_interfaces_only named_guids
#pragma warning( default : 4278 )
using namespace EnvDTE;
#else
using namespace EnvDTE80;
#endif

class vsnet_addin : public fox::vs_addin
{
public:
	vsnet_addin();
	virtual ~vsnet_addin();
	CSimpleArray<CString>	m_files;
public:
	fc_core	   m_fc;
	bool ExecVFCWizard();
public:
	virtual int				get_version() { return 0x2003; }
	virtual const char *	get_addin_name() { 
		//return "VS.NET Addin"; 
		CComBSTR version;
		m_pDTE->get_Version(&version);
		CString text = _T("Visual Studio Version ");
		text += +version;
		return text;
	}

	virtual int get_project_file_count()
	{
		return (int)m_files.GetSize();
	}
	virtual const char * get_project_files(int i)
	{
		return (LPCTSTR)m_files[i];
	}
	virtual bool goto_line(const char * file, int line);
	virtual int  get_line_column(const char * file, int line);
	virtual bool insert_block(const char * file, int line, int column, const char * text);
	virtual bool replace_text(const char * file, int line, const char * old, const char * text);
	virtual bool add_project_file(const char * file);
	virtual const char * get_project_path();
	virtual const char * get_project_name();
public:
	LRESULT GetActiveProject(EnvDTE::ProjectPtr& pProj);
	HRESULT GetSelectedProject(EnvDTE::ProjectPtr& pProj);
	HRESULT GetOpenFileDocument(EnvDTE::DocumentPtr & pDoc, const char * file);
	HRESULT SaveAllDocuments();
#ifdef VFC_VS2003
	CComPtr<EnvDTE::_DTE> m_pDTE;
#else
	CComPtr<DTE2> m_pDTE;
#endif
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// VisualFC AppWizard will insert additional declarations immediately before the previous line.
#endif // !defined(VFC_VSNET_ADDIN_H__9E5785BA_6015_48be_8589_5C263A475981__INCLUDED_)
