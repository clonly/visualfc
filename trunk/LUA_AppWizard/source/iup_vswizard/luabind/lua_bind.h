#ifndef _LUA_BIND_H_
#define _LUA_BIND_H_

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}
#pragma comment(lib,"lua51.lib")

#include "lua_bind_function.h"

#define PREMAKE_LUABIND_STACK(type,func)\
template <>\
struct lua_bind_stack<type>\
{\
	static type tovalue(lua_State * L, int arg) {\
		return (type)func(L,arg);\
	}\
};

#define PREMAKE_LUABIND_PUSHV(type,comp_type,_func)\
int lua_bind_pushvalue(lua_State * L, type value) {\
	_func(L,(comp_type)value);\
	return 1;\
}

#define MAKE_BIND_FUNCTION(_func)\
static int ll_bind_##_func(lua_State * L){\
	return bind_function_call(&_func,L);\
}

#define MAKE_CLASS_CREATE(cls)\
static int ll_##cls##_create(lua_State * L){	\
	typedef lua_bind_userdata_t<cls>	lua_bind_userdata;\
	cls * p;\
	lua_bind_userdata * u;\
	u = (lua_bind_userdata*)lua_newuserdata(L,sizeof(lua_bind_userdata));\
	u->p = NULL;\
	u->L = L;\
	p = u->p = new cls();\
	if (!p)\
		luaL_error(L,"lua bind class %s create failed",#cls);\
	luaL_getmetatable(L,"lua_bind_"#cls);\
	lua_setmetatable(L,-2);\
	return 1;\
};

#define MAKE_CLASS_DESTROY(cls)\
static int ll_##cls##_destroy(lua_State * L){\
	typedef lua_bind_userdata_t<cls>	lua_bind_userdata;\
	lua_bind_userdata * u = (lua_bind_userdata*)luaL_checkudata(L,1,"lua_bind_"#cls);\
	if (u->p)\
		delete u->p;\
	u->p = NULL;\
	return 0;\
};
/*
#define MAKE_CLASS_BIND(cls)\
static int ll_##cls##_bind(lua_State * L){\
	typedef lua_bind_userdata_t<cls>	lua_bind_userdata;\
	lua_bind_userdata * u = (lua_bind_userdata*)luaL_checkudata(L,1,"lua_bind_"#cls);\
	luaL_checktype(u->L,2,LUA_TTABLE);\
	lua_pushvalue(u->L,2);\                                                   
	lua_setfenv(u->L,-2);\
	u->p->L = u->L;\
	return 0;\
};
*/




#define MAKE_BIND_CLASS(cls)\
	MAKE_CLASS_CREATE(cls)\
	MAKE_CLASS_DESTROY(cls)\
	static const char * ll_##cls##_metaname()\
	{\
		return "lua_bind_"#cls;\
	}\
	cls * stack_##cls##_toptr(lua_State * L, int arg)\
	{\
		typedef lua_bind_userdata_t<cls>	lua_bind_userdata;\
		lua_bind_userdata * u = (lua_bind_userdata*)luaL_checkudata(L,1,"lua_bind_"#cls);\
		return u->p;\
	}\
	static int lua_bind_pushvalue(lua_State * L, cls * p) {\
		typedef lua_bind_userdata_t<cls>	lua_bind_userdata;\
		lua_bind_userdata * u;\
		u = (lua_bind_userdata*)lua_newuserdata(L,sizeof(lua_bind_userdata));\
		u->p = p;\
		if (!p)\
			luaL_error(L,"lua bind class %s create failed",#cls);\
		luaL_getmetatable(L,"lua_bind_"#cls);\
		lua_setmetatable(L,-2); return 1;\
	}\
	PREMAKE_LUABIND_STACK(cls*,stack_##cls##_toptr)\
	PREMAKE_LUABIND_STACK(const cls*,stack_##cls##_toptr)\
	PREMAKE_LUABIND_STACK(cls,*stack_##cls##_toptr)\
	PREMAKE_LUABIND_STACK(const cls,*stack_##cls##_toptr)\
	PREMAKE_LUABIND_STACK(cls&,*stack_##cls##_toptr)\
	PREMAKE_LUABIND_STACK(const cls&,*stack_##cls##_toptr)


#define BEGIN_CLASS_FIELD(cls)\
template <bool bread>\
struct ll_##cls##_field {\
static int call(lua_State * L)\
{\
	typedef lua_bind_userdata_t<cls>	lua_bind_userdata;\
	lua_bind_userdata * u = (lua_bind_userdata*)luaL_checkudata(L,1,"lua_bind_"#cls);\
	if (bread) 	lua_newtable(L);	//create table


#define CLASS_FIELD(value)\
	if (bread) {\
		lua_bind_pushvalue(L,u->p->value);\
		lua_setfield(L,-2,#value);\
	}\
	else {\
		lua_pushstring(L,#value);\
		lua_gettable(L,-2);\
		lua_bind_tovalue(L,&u->p->value);\
		lua_pop(L,1);\
	}


#define END_CLASS_FIELD()\
	return 1;\
}\
};

#define BEGTIN_CLASS(CLS)\
template <typename CLS>\
struct lua_bind_class\
{\
typedef CLS	type_cls;\
static const char * get_bind_metaname() {\
	return "lua_bind_"#CLS;\
}

#define DEF_MEMBER(func_name,func)\
static int func_name(lua_State * L) {\
	typedef lua_bind_userdata_t<type_cls> lua_bind_userdata;\
	lua_bind_userdata * u = (lua_bind_userdata*)luaL_checkudata(L,1,get_bind_metaname());\
	return bind_function_call(u->p,_func,L);\
}

#define END_CLASS();\
};

#define BEGIN_CLASS_MEMBER(cls)\
struct ll_##cls##_member {\
	typedef cls type_cls;\
static const char * get_bind_metaname(){\
	return "lua_bind_"#cls;\
}

#define CLASS_MEMBER_EX(_func_name,_func)\
static int _func_name(lua_State * L){\
	typedef lua_bind_userdata_t<type_cls>	lua_bind_userdata;\
	lua_bind_userdata * u = (lua_bind_userdata*)luaL_checkudata(L,1,get_bind_metaname());\
	return bind_function_call(u->p,_func,L);\
}

#define CLASS_MEMBER(_func)\
static int _func(lua_State * L){\
	typedef lua_bind_userdata_t<type_cls>	lua_bind_userdata;\
	lua_bind_userdata * u = (lua_bind_userdata*)luaL_checkudata(L,1,get_bind_metaname());\
	return bind_function_call(u->p,&type_cls::_func,L);\
}

#define END_CLASS_MEMBER()\
};

static void lua_bind_tovalue(lua_State * L, int * ptr)
{
	if (lua_isnumber(L,-1))
	{
		*ptr = (int)lua_tonumber(L,-1);
	}
}
static void lua_bind_tovalue(lua_State * L, long * ptr)
{
	if (lua_isnumber(L,-1))
	{
		*ptr = (int)lua_tonumber(L,-1);
	}
}
static void lua_bind_tovalue(lua_State * L, const char * * ptr)
{
	if (lua_isstring(L,-1))
	{
		*ptr = (const char *)lua_tostring(L,-1);
	}
}

const char * stack_tostring(lua_State * L, int arg)
{
	size_t len;
	return luaL_checklstring(L,arg,&len);
}

PREMAKE_LUABIND_PUSHV(int,int,lua_pushinteger)
PREMAKE_LUABIND_PUSHV(char,int,lua_pushinteger)
PREMAKE_LUABIND_PUSHV(unsigned int,int,lua_pushinteger)
PREMAKE_LUABIND_PUSHV(long,int,lua_pushinteger)
PREMAKE_LUABIND_PUSHV(unsigned long,int,lua_pushinteger)
PREMAKE_LUABIND_PUSHV(const char *,const char *,lua_pushstring)

PREMAKE_LUABIND_STACK(int,luaL_checkinteger)
PREMAKE_LUABIND_STACK(char,luaL_checkinteger)
PREMAKE_LUABIND_STACK(unsigned char,luaL_checkinteger)
PREMAKE_LUABIND_STACK(unsigned int,luaL_checkinteger)
PREMAKE_LUABIND_STACK(unsigned long,luaL_checkinteger)
PREMAKE_LUABIND_STACK(double,luaL_checknumber)
PREMAKE_LUABIND_STACK(const char *,stack_tostring)
PREMAKE_LUABIND_STACK(int const *,stack_tostring)
PREMAKE_LUABIND_STACK(char *,stack_tostring)
PREMAKE_LUABIND_STACK(unsigned char * ,stack_tostring)
PREMAKE_LUABIND_STACK(const unsigned char * ,stack_tostring)
PREMAKE_LUABIND_STACK(const wchar_t *, stack_tostring)
PREMAKE_LUABIND_STACK(unsigned short *, stack_tostring)
PREMAKE_LUABIND_STACK(long,luaL_checkinteger)

#endif
