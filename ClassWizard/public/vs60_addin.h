// vs60_addin.h: interface for the vs60_addin class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VS60_ADDIN_H__EFBBDA31_CB24_4832_BF2E_CAFDCC226A5A__INCLUDED_)
#define AFX_VS60_ADDIN_H__EFBBDA31_CB24_4832_BF2E_CAFDCC226A5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./fc_core.h"
#include "./dspparser.h"

class vs60_addin  : public fox::vs_addin
{
public:
	IApplication* m_pApplication;
	fc_core	m_fc;
	dspparser	m_dsp;
	vs60_addin();
	virtual ~vs60_addin();
public:
	bool ExecVFCWizard();
	virtual int				get_version() { return 0x60;}
	virtual const char *	get_addin_name() { 
#ifdef EVC4
		return "EVC4 Addin"; 
#else
		return "VS60 Addin";
#endif
	}
	virtual int				get_line_column(const char * file, int line);
	virtual bool			insert_block(const char * file, int line, int column, const char * text);
	virtual bool			replace_text(const char * file, int line, const char * old, const char * text);
	virtual bool			goto_line(const char * file, int line);
	virtual int				get_project_file_count()
	{
		return m_dsp.source.GetSize();
	}
	virtual const char *	get_project_files(int i)
	{
		return (LPCTSTR)m_dsp.source[i];
	}
	virtual const char *	get_project_path();
	virtual const char *	get_project_name();
	virtual bool			add_project_file(const char * file);
	
	LRESULT GetOpenFileDocument(CComPtr<IDispatch> & Document, const char * file);
	LRESULT SaveAllDocuments();
	LRESULT InsertDocumentText(CComPtr<IDispatch> & Document, int line, int column, const char * text);
	LRESULT ReplaceDocumentText(CComPtr<IDispatch> & Document, int line, const char * old, const char * text);
};

#endif // !defined(AFX_VS60_ADDIN_H__EFBBDA31_CB24_4832_BF2E_CAFDCC226A5A__INCLUDED_)
