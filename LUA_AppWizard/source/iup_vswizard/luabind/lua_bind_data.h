// lua_bind_data.h : interface of the lua_bind_data class
//
/////////////////////////////////////////////////////////////////////////////
#ifndef __LUA_BIND_DATA_H__
#define __LUA_BIND_DATA_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

template <typename T>
struct lua_bind_userdata_t{
	lua_State * L;
	T		  * p;
};
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// VisualFC AppWizard will insert additional declarations immediately before the previous line.
#endif // __LUA_BIND_DATA_H__
