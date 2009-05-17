// iup_vswizard.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"

#include <shlwapi.h>
#pragma comment(lib,"shlwapi.lib")

extern "C"
{
#include "lua.h"
}

#include "luabind/lua_bind_data.h"
#include "luabind/lua_bind.h"
#include "vs_wizard.h"

CAppModule _Module;

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

        _Module.Init(NULL,hInstance);
        DisableThreadLibraryCalls(hInstance);
    }
    else if (dwReason == DLL_PROCESS_DETACH)
	{
       _Module.Term();
	}
    return TRUE;    // ok
}

class lua_vswizard
{
public:
	inline void AddSymbolVal(const char * key, const char * value)
	{
		wiz.AddSymbol(key,value);
	}
	inline void AddSymbol(const char * key, bool bAdd)
	{
		wiz.AddSymbol(key,bAdd);
	}
	inline bool FindSymbol(const char * key)
	{
		return wiz.FindSymbol(key);
	}
	inline const char * FindSymbolVal(const char * key)
	{
		m_temp = wiz.FindSymbolVal(key);
		return m_temp;
	}
	inline bool MakeFile(const char * lpszFileIn, const char * lpszFileOut)
	{
		return wiz.make_file(lpszFileIn,lpszFileOut);
	}
	inline const char * MakeGUID()
	{
		m_temp = wiz.make_guid();
		return m_temp;
	}
	inline const char * MakeIncludeGUID()
	{
		m_temp = wiz.make_include_guid();
		return m_temp;
	}
	inline bool MakeDir(const char * path)
	{
		return ::CreateDirectory(path,0);
	}
	inline bool CopyFile(const char * source, const char * target)
	{
		return ::CopyFile(source,target,FALSE);
	}
	inline void Clear()
	{
		wiz.clear();
	}
	inline const char * LoadFileInfo(const char * lpszFileIn)
	{
		str_vector ar;
		m_temp = "";
		wiz.load_file_vector(lpszFileIn,ar);
		for (int i = 0; i < ar.size(); i++)
		{
			m_temp += ar[i];
			m_temp += "\r\n";
		}
		return m_temp;
	}
protected:
	vs_wizard wiz;
	CString	  m_temp;
};

MAKE_BIND_FUNCTION(PathFileExists)

MAKE_BIND_CLASS(lua_vswizard)
BEGIN_CLASS_MEMBER(lua_vswizard)
	CLASS_MEMBER(Clear)
	CLASS_MEMBER(LoadFileInfo)
	CLASS_MEMBER(MakeGUID)
	CLASS_MEMBER(MakeIncludeGUID)
	CLASS_MEMBER(MakeFile)
	CLASS_MEMBER(CopyFile)
	CLASS_MEMBER(MakeDir)
END_CLASS_MEMBER()

static int ll_AddSymbol(lua_State * L){
	typedef lua_bind_userdata_t<lua_vswizard>	lua_bind_userdata;
	lua_bind_userdata * u = (lua_bind_userdata*)luaL_checkudata(L,1,ll_lua_vswizard_member::get_bind_metaname());
	//return bind_function_call(u->p,&type_cls::_func,L);
	const char * key = NULL;
	unsigned int len = 0;
	if (lua_type(L,2) == LUA_TSTRING)
	{
		key = lua_tolstring(L,2,&len);
	}

	if (lua_gettop(L) == 2 || lua_type(L,3) == LUA_TBOOLEAN)
	{
		bool bAdd = true;
		if (lua_type(L,3) == LUA_TBOOLEAN)
			bAdd = (bool)lua_toboolean(L,3);
		u->p->AddSymbol(key,bAdd);
	}
	else if (lua_type(L,3) == LUA_TSTRING)
	{
		const char * val = lua_tolstring(L,3,&len);
		u->p->AddSymbolVal(key,val);
	}
	return 0;
}

static int ll_FindSymbol(lua_State * L){
	typedef lua_bind_userdata_t<lua_vswizard>	lua_bind_userdata;
	lua_bind_userdata * u = (lua_bind_userdata*)luaL_checkudata(L,1,ll_lua_vswizard_member::get_bind_metaname());
	//return bind_function_call(u->p,&type_cls::_func,L);
	const char * key = NULL;
	unsigned int len = 0;
	
	key = luaL_checklstring(L,2,&len);
	bool b = u->p->FindSymbol(key);
	if (b)
	{
		lua_pushboolean(L,b);
		return 1;
	}
	const char * val = u->p->FindSymbolVal(key);
	if (val != NULL)
	{
		lua_pushstring(L,val);
		return 1;
	}
	return 0;
}

static int ll_get_local_info(lua_State * L) {
	int lcid = luaL_checkinteger(L,1);
	char buf[64] = {0};
	::GetLocaleInfoA(lcid,4,buf,64);
	if (strlen(buf) != 0)
	{
		lua_pushstring(L,buf);
	}
	return 1;
}

static int ll_get_local_lang(lua_State * L) {
	char buf[64] = {0};
	GetLocaleInfo(LOCALE_SYSTEM_DEFAULT,   LOCALE_SABBREVLANGNAME,   buf,   64); 
	if (strlen(buf) != 0)
	{
		lua_pushstring(L,buf);
	}
	return 1;
}

static int ll_get_module_path(lua_State * L) {
	CString path;
	//取得程序所在路径
	TCHAR exeFullPath[MAX_PATH];
	::GetModuleFileNameA(_Module.m_hInst,exeFullPath,MAX_PATH);
	CString strPath = exeFullPath;
	int r = strPath.ReverseFind(_T('\\'));
	if (r != -1)
	{
		path = strPath.Left(r);
	}
	lua_pushstring(L,path);
	return 1;
}

static int ll_path_exists(lua_State * L) {
	unsigned int len = 0;
	const char * sz = luaL_checklstring(L,1,&len); 
	if (len != 0 && ::PathFileExists(sz) != FALSE)
	{
		lua_pushboolean(L,true);
	}
	else
		lua_pushboolean(L,false);
	return 1;
}

static const struct luaL_Reg lua_vswizard_f[] = {
	{"new",&ll_lua_vswizard_create},
	{"get_local_lang",&ll_get_local_lang},
	{"get_local_info",&ll_get_local_info},
	{"get_module_path",&ll_get_module_path},
	{"path_exists",&ll_path_exists},
	{NULL,NULL}
};


static const struct luaL_Reg lua_vswizard_m[] = {
	{"__gc",&ll_lua_vswizard_destroy},
	{"AddSymbol",&ll_AddSymbol},
	{"FindSymbol",&ll_FindSymbol},
	{"Clear",&ll_lua_vswizard_member::Clear},
	{"MakeFile",&ll_lua_vswizard_member::MakeFile},
	{"LoadFileInfo",&ll_lua_vswizard_member::LoadFileInfo},
	{"MakeGUID",&ll_lua_vswizard_member::MakeGUID},
	{"MakeIncludeGUID",&ll_lua_vswizard_member::MakeIncludeGUID},
	{"CopyFile",&ll_lua_vswizard_member::CopyFile},
	{"MakeDir",&ll_lua_vswizard_member::MakeDir},
	{NULL,NULL}
};

extern "C"
__declspec(dllexport)
int luaopen_vswizard(lua_State * L)
{
	luaL_newmetatable(L,ll_lua_vswizard_metaname());
	lua_pushvalue(L,-1);
	lua_setfield(L,-2,"__index");
	luaL_register(L,NULL,lua_vswizard_m);
	luaL_register(L,"vswizard",lua_vswizard_f);
	return 1;
}
