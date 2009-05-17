#ifndef _VFC_CORE_H_
#define _VFC_CORE_H_

#include "foxlib.h"

class fc_core
{
public:
	static CString GetModulePath(HMODULE hMod)
	{
		CString path;
		//取得程序所在路径
		TCHAR exeFullPath[MAX_PATH];
		::GetModuleFileName(hMod,exeFullPath,MAX_PATH);
		CString strPath = exeFullPath;
		int r = strPath.ReverseFind(_T('\\'));
		if (r != -1)
		{
			path = strPath.Left(r);
		}
		return path;
	}
public:
	HMODULE	hLib;
	fox::vfc_item	* pvfc;
public:
	fc_core() : hLib(NULL), pvfc(NULL)
	{	
	}
	~fc_core()
	{
		free();
	}

	bool load(HMODULE hModule, fox::vs_addin * paddin) 
	{
		hLib = ::LoadLibrary(GetModulePath(hModule)+_T("\\vfc_core.dll"));
		if (hLib)
		{
			typedef fox::vfc_item * CREATE_PROC(int falg);
			CREATE_PROC * pfn = NULL;
			pfn = (CREATE_PROC*)::GetProcAddress(hLib,"fox_get_item");
			if (pfn)
			{
				pvfc = pfn(0x1000);
				if (pvfc)
				{
					pvfc->set_vsaddin(paddin);
				}
				return true;
			}
		}
		return false;
	}
	void free()
	{
		if (pvfc)
		{
			delete pvfc;
			pvfc = NULL;
		}
		if (hLib)
		{
			FreeLibrary(hLib);
			hLib = NULL;
		}
	}
};
/*
// modeless dialog base
class fc_core
{
protected:
	CString GetModulePath(HMODULE hMod)
	{
		CString path;
		//取得程序所在路径
		TCHAR exeFullPath[MAX_PATH];
		::GetModuleFileName(hMod,exeFullPath,MAX_PATH);
		CString strPath = exeFullPath;
		int r = strPath.ReverseFind(_T('\\'));
		if (r != -1)
		{
			path = strPath.Left(r);
		}
		return path;
	}
public:
	HMODULE	hLib;
	fox::ui::vs_item	* pvfc;
public:
	fc_core() : hLib(NULL), pvfc(NULL)
	{	
	}
	~fc_core()
	{
		free();
	}

	void create()
	{
		RECT rc = { CW_USEDEFAULT, CW_USEDEFAULT, 0, 0 };
		if (pvfc)
			pvfc->create(NULL,rc);
	}
	bool load(HMODULE hModule, fox::vs_addin * paddin) 
	{
		hLib = ::LoadLibrary(GetModulePath(hModule)+_T("\\vfc_core.dll"));
		if (hLib)
		{
			typedef fox::ui::vs_item * CREATE_PROC(int falg);
			CREATE_PROC * pfn = NULL;
			pfn = (CREATE_PROC*)::GetProcAddress(hLib,"fox_get_item");
			if (pfn)
			{
				pvfc = pfn(0x1000);
				if (pvfc)
				{
					pvfc->set_vsaddin(paddin);
				}
				return true;
			}
		}
		return false;
	}
	void free()
	{
		if (pvfc)
		{
			if (pvfc->handle())
				::DestroyWindow(pvfc->handle());
			delete pvfc;
			pvfc = NULL;
		}
		if (hLib)
		{
			FreeLibrary(hLib);
			hLib = NULL;
		}
	}
};
*/

#endif