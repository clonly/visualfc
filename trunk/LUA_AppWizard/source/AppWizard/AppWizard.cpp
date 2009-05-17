// AppWizard.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <shellapi.h>
#include <tchar.h>

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	TCHAR path[MAX_PATH];
	TCHAR ini[MAX_PATH];
	TCHAR lua[MAX_PATH];
	TCHAR main[MAX_PATH];
	TCHAR file_lua[MAX_PATH];
	TCHAR file_main[MAX_PATH];
	TCHAR * ptr;
	::GetModuleFileNameA(hInstance,path,MAX_PATH);
	ptr = ::_tcsrchr(path,_T('\\'));
	path[ptr-path] = '\0';
	strcpy(ini,path);
	strcat(ini,"\\setup.ini");
	::GetPrivateProfileString(_T("SETUP"),_T("LUA"),"wlua.exe",lua,MAX_PATH,ini);
	::GetPrivateProfileString(_T("SETUP"),_T("FILE"),"main.wlua",main,MAX_PATH,ini);
	strcpy(file_lua,path);
	strcat(file_lua,"\\");
	strcat(file_lua,lua);
	strcpy(file_main,path);
	strcat(file_main,"\\");
	strcat(file_main,main);
	::ShellExecute(NULL,"open",file_lua,file_main,path,SW_SHOW);
	return 0;
}



