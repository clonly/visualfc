// vs_wizard.h: interface for the vs_wizard class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VS_WIZARD_H__8A8AB2C1_6A1D_4768_A013_A7984B116DD8__INCLUDED_)
#define AFX_VS_WIZARD_H__8A8AB2C1_6A1D_4768_A013_A7984B116DD8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <map>
#include <set>
#include <string>

//#include "../public/qevent.h"

typedef std::vector<CString>		str_vector;
typedef std::map<CString,CString>   str_map;
typedef std::set<CString>			str_set;

class vs_wizard_info
{
public:
	void save_cfg_int(LPCTSTR lpszkey, int val);
	int load_cfg_int(LPCTSTR lpszKey, int def);
	bool check_project_name(LPCTSTR lpszFileName);
	vs_wizard_info();

	static CString GetModulePath(HMODULE hMod);

	void save_cfg_str(LPCTSTR lpszKey, LPCTSTR lpszVal);
	CString load_cfg_str(LPCTSTR lpszKey, LPCTSTR lpszDef = _T(""));
	void save_cfg_bool(LPCTSTR lpszKey,bool bval);
	bool load_cfg_bool(LPCTSTR lpszKey,bool bdef);

	bool load_lang();
	std::vector<CString>	ar_lang;
	int			nAppLang;


	CString		templatePath;
	CString		cfgPath;
	CString		cfgApp;
	
	int			nWizardRet;

//	QLib::Event<bool>	event_finish;
};

class vs_wizard  
{
public:
	CString make_include_guid();
	void clear();
	void get_output_info(CString & text);
	void get_define_info(CString & text);
	CString make_guid();
	CString FindSymbolVal(LPCTSTR lpszKey);
	bool FindSymbol(LPCTSTR lpszKey);
	void AddSymbol(LPCTSTR lpszDefine, bool bAdd);
	void AddSymbol(LPCTSTR lpszKey, LPCTSTR lpszValue);
	bool make_file(LPCTSTR lpszFileIn, LPCTSTR lpszFileOut);
	bool load_file_vector(LPCTSTR lpszFileIn, str_vector &array);
protected:
	bool get_vector_alltrue(std::vector<bool> &array);
	bool line_to_array(LPCTSTR lpszLine, str_vector & array, int & flag);
	bool get_define_line(LPCTSTR lpszLine);
	void replace_line(LPCTSTR in, CString &out);
public:
	vs_wizard();
	virtual ~vs_wizard();

	str_map					m_output;	//[!output xxx]
	str_set					m_define;   //[!if xxx && xx]
};

#endif // !defined(AFX_VS_WIZARD_H__8A8AB2C1_6A1D_4768_A013_A7984B116DD8__INCLUDED_)
