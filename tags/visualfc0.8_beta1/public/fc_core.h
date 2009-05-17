#ifndef _VFC_CORE_H_
#define _VFC_CORE_H_

#include "foxlib.h"
#include "foxuilib.h"

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
	fox::ui::vs_item	* pwtl;
	fox::ui::vs_item	* pwinx;
public:
	fc_core() : hLib(NULL), pwtl(NULL), pwinx(NULL)
	{	
	}
	~fc_core()
	{
		free();
	}

	void create()
	{
		RECT rc = { CW_USEDEFAULT, CW_USEDEFAULT, 0, 0 };
		if (pwtl)
			pwtl->create(NULL,rc);
		if (pwinx)
			pwinx->create(NULL,rc);
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
				pwtl = pfn(0x1000);
				pwinx = pfn(0x2000);
				if (pwtl)
				{
					pwtl->set_vsaddin(paddin);
				}
				if (pwinx)
				{
					pwinx->set_vsaddin(paddin);
				}
				return true;
			}
		}
		return false;
	}
	void free()
	{
		if (pwtl)
		{
			if (pwtl->handle())
				::DestroyWindow(pwtl->handle());
			delete pwtl;
			pwtl = NULL;
		}
		if (pwinx)
		{
			if (pwinx->handle())
			{
				::DestroyWindow(pwinx->handle());
			}
			delete pwinx;
			pwinx = NULL;
		}
		if (hLib)
		{
			FreeLibrary(hLib);
			hLib = NULL;
		}

	}
};

#endif