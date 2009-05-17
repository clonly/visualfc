// CodeWizard.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

#include "resource.h"

#include "Wizard.h"
#include "../public/codewiz_plugin.h"

CAppModule _Module;

#ifdef _USRDLL
extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
		HRESULT hRes = ::CoInitialize(NULL);
		// If you are running on NT 4.0 or higher you can use the following call instead to 
		// make the EXE free threaded. This means that calls come in on a random RPC thread.
		//	HRESULT hRes = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
		ATLASSERT(SUCCEEDED(hRes));
		
		// this resolves ATL window thunking problem when Microsoft Layer for Unicode (MSLU) is used
		::DefWindowProc(NULL, 0, 0, 0L);
		
		AtlInitCommonControls(ICC_COOL_CLASSES | ICC_BAR_CLASSES);	// add flags to support other controls
		
		hRes = _Module.Init(NULL, hInstance);
		ATLASSERT(SUCCEEDED(hRes));
    }
    else if (dwReason == DLL_PROCESS_DETACH)
	{
		_Module.Term();
		::CoUninitialize();
	}
    return TRUE;    // ok
}
extern "C"
__declspec(dllexport) int run_wizard(const char * path)
{
	// -1 no run
	// 0 success
	// 1 cancel
	// 2 error
	CWizard wiz;
	wiz.info.templatePath = path;
	int nRet = wiz.ExecuteWizard();
	return nRet;
}

extern "C"
__declspec(dllexport) int run_wizard_ex(fox::codewiz_args * args)
{
	// -1 no run
	// 0 success
	// 1 cancel
	// 2 error
	CWizard wiz;
	wiz.info.templatePath = args->template_path;
	wiz.info.strDialogID = args->idd;
	wiz.info.strProjectName = args->project_name;
	wiz.info.strProjectPath = args->project_path;
	wiz.info.strCodeWizName = args->codewiz_name;
	wiz.info.strCodeWizInfo = args->codewiz_info;
	wiz.info.p_return_files = &args->return_files;

	for (int i = 0; i < args->idd_num; i++)
	{
		if (args->idd_array[i] == NULL)
			break;
		wiz.info.ar_id.push_back(args->idd_array[i]);
	}
	int nRet = wiz.ExecuteWizard();
	return nRet;
}
#else

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR /*lpstrCmdLine*/, int /*nCmdShow*/)
{
	HRESULT hRes = ::CoInitialize(NULL);
// If you are running on NT 4.0 or higher you can use the following call instead to 
// make the EXE free threaded. This means that calls come in on a random RPC thread.
//	HRESULT hRes = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
	ATLASSERT(SUCCEEDED(hRes));

	// this resolves ATL window thunking problem when Microsoft Layer for Unicode (MSLU) is used
	::DefWindowProc(NULL, 0, 0, 0L);

	AtlInitCommonControls(ICC_BAR_CLASSES);	// add flags to support other controls

	hRes = _Module.Init(NULL, hInstance);
	ATLASSERT(SUCCEEDED(hRes));

	int nRet = 0;
	// BLOCK: Run application
	{
		CWizard wiz;
		wiz.info.strDialogID = "IDD_ABOUT";
		wiz.info.ar_id.push_back("IDD_ABOUT");
		wiz.info.ar_id.push_back("IDD_MAINDLG");
		wiz.info.templatePath = "F:\\VFC_Projects\\AppWizard\\bin\\WTLDialog\\Templates";
		nRet = wiz.ExecuteWizard();
	}

	_Module.Term();
	::CoUninitialize();

	return nRet;
}

#endif


