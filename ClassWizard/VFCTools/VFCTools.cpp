// VFCTools.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "tools_addin.h"

char info[] = 
"VisualFC Tools" "\r\n"
"\r\n"
"For VS2005/VS2008/VCExpress Tools" "\r\n"
"Command:\tC:\\VisualFC\\bin\\VFCTools.exe" "\r\n"
"Arguments:\t$(ProjectDir)$(ProjectFileName)" "\r\n"
"\r\n"
"For Code::Blocks Tools" "\r\n"
"Executable:\tC:\\VisualFC\\bin\\VFCTools.exe" "\r\n"
"Parameters:\t${PROJECT_DIR}${PROJECT_FILENAME}"
;

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	tools_addin vfc;
	if (vfc.m_fc.load(hInstance,&vfc))
	{
		if (lstrlen(lpCmdLine) != 0)
		{
			CString proj = lpCmdLine;
			proj.TrimLeft(_T('\"'));
			proj.TrimRight(_T('\"'));
			vfc.LoadVSProject(proj);
			vfc.ExecVFCWizard();
		}
		else
		{
			MessageBox(GetActiveWindow(),info,_T("VisualFC Tools"),MB_OK | MB_ICONINFORMATION);
				//_T("\r\nVisualFC for VS2005/VS2008/VCExpress Tools\r\n\r\nCommand:\tC:\\VisualFC\\bin\\VFCTools.exe\r\nArguments:\t$(ProjectDir)$(ProjectFileName)"),_T("VisualFC Tools"),MB_OK | MB_ICONINFORMATION);
		}
	}

	return 0;
}



