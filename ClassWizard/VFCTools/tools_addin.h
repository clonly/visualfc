// tools_addin.h: interface for the tools_addin class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOOLS_ADDIN_H__8F5A2BE8_9774_414B_B30D_57AA0E2DE26D__INCLUDED_)
#define AFX_TOOLS_ADDIN_H__8F5A2BE8_9774_414B_B30D_57AA0E2DE26D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../public/fc_core.h"
#include "../public/dspparser.h"

class tools_addin : public fox::vs_addin  
{
public:
	bool LoadVSProject(const CString & proj);
	fc_core	m_fc;
	dspparser	m_dsp;
	CString		m_projName;

	bool ExecVFCWizard();
	tools_addin();
	virtual ~tools_addin();

	virtual int				get_version();
	virtual const char *	get_addin_name();
	virtual int				get_line_column(const char * file, int line);
	virtual bool			insert_block(const char * file, int line, int column, const char * text);
	virtual bool			replace_text(const char * file, int line, const char * old, const char * text);
	virtual bool			goto_line(const char * file, int line);
	virtual int				get_project_file_count();
	virtual const char *	get_project_files(int i);
	virtual const char *	get_project_path();
	virtual const char *	get_project_name();
	virtual bool			add_project_file(const char * file);
};

#endif // !defined(AFX_TOOLS_ADDIN_H__8F5A2BE8_9774_414B_B30D_57AA0E2DE26D__INCLUDED_)
