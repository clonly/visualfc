#ifndef _LUA_BIND_FUNCTION_H
#define _LUA_BIND_FUNCTION_H
//generic by lua_bind_function.lua

#ifdef _MSC_VER
#define LUABIND_MEMBERFUNC_STDCALL _MSC_VER
#pragma warning (disable : 4786)
#endif

#define LUABIND_FUNCTION_STDCALL	1


template <typename T>
struct lua_bind_stack
{
	static T tovalue(lua_State * L, int arg) {
		return (T)(void*)lua_touserdata(L,arg);\
	}
};

template <typename R>
struct lua_bind_function
{
	static int call( R (*pfn)(), lua_State * L) {
		return lua_bind_pushvalue(L,(*pfn)() );
	}
#if defined (LUABIND_FUNCTION_STDCALL)
	static int call( R (__stdcall *pfn)(), lua_State * L) {
		return lua_bind_pushvalue(L,(*pfn)() );
	}
#endif
	template <typename CLS, typename CLS2>
	static int call(CLS * pcls, R (CLS2::*pfn)(), lua_State * L) {
		return lua_bind_pushvalue(L,(pcls->*pfn)() );
	}
#if defined (LUABIND_MEMBERFUNC_STDCALL)
	template <typename CLS, typename CLS2>
	static int call(CLS * pcls, R (__stdcall CLS2::*pfn)(), lua_State * L) {
		return lua_bind_pushvalue(L,pcls->*pfn)() );
	}
#endif
	template <typename T1>
	static int call( R (*pfn)(T1), lua_State * L) {
		return lua_bind_pushvalue(L, (*pfn)(lua_bind_stack<T1>::tovalue(L,1)) );
	}
#if defined (LUABIND_FUNCTION_STDCALL)
	template <typename T1>
	static int call( R (__stdcall *pfn)(T1), lua_State * L) {
		return lua_bind_pushvalue(L,(*pfn)(lua_bind_stack<T1>::tovalue(L,1))) ;
	}
#endif
	template <typename CLS, typename CLS2, typename T1>
	static int call(CLS * pcls, R (CLS2::*pfn)(T1), lua_State * L) {
		return lua_bind_pushvalue(L,(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2)) );
	}
#if defined (LUABIND_MEMBERFUNC_STDCALL)
	template <typename CLS, typename CLS2, typename T1>
	static int call(CLS * pcls, R (__stdcall CLS2::*pfn)(T1), lua_State * L) {
		return lua_bind_pushvalue(L,(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2))) ;
	}
#endif
	template <typename T1,typename T2>
	static int call( R (*pfn)(T1,T2), lua_State * L) {
		return lua_bind_pushvalue(L, (*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2)) );
	}
#if defined (LUABIND_FUNCTION_STDCALL)
	template <typename T1,typename T2>
	static int call( R (__stdcall *pfn)(T1,T2), lua_State * L) {
		return lua_bind_pushvalue(L,(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2))) ;
	}
#endif
	template <typename CLS, typename CLS2, typename T1,typename T2>
	static int call(CLS * pcls, R (CLS2::*pfn)(T1,T2), lua_State * L) {
		return lua_bind_pushvalue(L,(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3)) );
	}
#if defined (LUABIND_MEMBERFUNC_STDCALL)
	template <typename CLS, typename CLS2, typename T1,typename T2>
	static int call(CLS * pcls, R (__stdcall CLS2::*pfn)(T1,T2), lua_State * L) {
		return lua_bind_pushvalue(L,(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3))) ;
	}
#endif
	template <typename T1,typename T2,typename T3>
	static int call( R (*pfn)(T1,T2,T3), lua_State * L) {
		return lua_bind_pushvalue(L, (*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3)) );
	}
#if defined (LUABIND_FUNCTION_STDCALL)
	template <typename T1,typename T2,typename T3>
	static int call( R (__stdcall *pfn)(T1,T2,T3), lua_State * L) {
		return lua_bind_pushvalue(L,(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3))) ;
	}
#endif
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3>
	static int call(CLS * pcls, R (CLS2::*pfn)(T1,T2,T3), lua_State * L) {
		return lua_bind_pushvalue(L,(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4)) );
	}
#if defined (LUABIND_MEMBERFUNC_STDCALL)
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3>
	static int call(CLS * pcls, R (__stdcall CLS2::*pfn)(T1,T2,T3), lua_State * L) {
		return lua_bind_pushvalue(L,(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4))) ;
	}
#endif
	template <typename T1,typename T2,typename T3,typename T4>
	static int call( R (*pfn)(T1,T2,T3,T4), lua_State * L) {
		return lua_bind_pushvalue(L, (*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4)) );
	}
#if defined (LUABIND_FUNCTION_STDCALL)
	template <typename T1,typename T2,typename T3,typename T4>
	static int call( R (__stdcall *pfn)(T1,T2,T3,T4), lua_State * L) {
		return lua_bind_pushvalue(L,(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4))) ;
	}
#endif
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4>
	static int call(CLS * pcls, R (CLS2::*pfn)(T1,T2,T3,T4), lua_State * L) {
		return lua_bind_pushvalue(L,(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5)) );
	}
#if defined (LUABIND_MEMBERFUNC_STDCALL)
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4>
	static int call(CLS * pcls, R (__stdcall CLS2::*pfn)(T1,T2,T3,T4), lua_State * L) {
		return lua_bind_pushvalue(L,(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5))) ;
	}
#endif
	template <typename T1,typename T2,typename T3,typename T4,typename T5>
	static int call( R (*pfn)(T1,T2,T3,T4,T5), lua_State * L) {
		return lua_bind_pushvalue(L, (*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5)) );
	}
#if defined (LUABIND_FUNCTION_STDCALL)
	template <typename T1,typename T2,typename T3,typename T4,typename T5>
	static int call( R (__stdcall *pfn)(T1,T2,T3,T4,T5), lua_State * L) {
		return lua_bind_pushvalue(L,(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5))) ;
	}
#endif
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5>
	static int call(CLS * pcls, R (CLS2::*pfn)(T1,T2,T3,T4,T5), lua_State * L) {
		return lua_bind_pushvalue(L,(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6)) );
	}
#if defined (LUABIND_MEMBERFUNC_STDCALL)
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5>
	static int call(CLS * pcls, R (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5), lua_State * L) {
		return lua_bind_pushvalue(L,(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6))) ;
	}
#endif
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6>
	static int call( R (*pfn)(T1,T2,T3,T4,T5,T6), lua_State * L) {
		return lua_bind_pushvalue(L, (*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6)) );
	}
#if defined (LUABIND_FUNCTION_STDCALL)
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6>
	static int call( R (__stdcall *pfn)(T1,T2,T3,T4,T5,T6), lua_State * L) {
		return lua_bind_pushvalue(L,(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6))) ;
	}
#endif
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6>
	static int call(CLS * pcls, R (CLS2::*pfn)(T1,T2,T3,T4,T5,T6), lua_State * L) {
		return lua_bind_pushvalue(L,(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7)) );
	}
#if defined (LUABIND_MEMBERFUNC_STDCALL)
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6>
	static int call(CLS * pcls, R (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6), lua_State * L) {
		return lua_bind_pushvalue(L,(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7))) ;
	}
#endif
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7>
	static int call( R (*pfn)(T1,T2,T3,T4,T5,T6,T7), lua_State * L) {
		return lua_bind_pushvalue(L, (*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7)) );
	}
#if defined (LUABIND_FUNCTION_STDCALL)
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7>
	static int call( R (__stdcall *pfn)(T1,T2,T3,T4,T5,T6,T7), lua_State * L) {
		return lua_bind_pushvalue(L,(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7))) ;
	}
#endif
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7>
	static int call(CLS * pcls, R (CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7), lua_State * L) {
		return lua_bind_pushvalue(L,(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8)) );
	}
#if defined (LUABIND_MEMBERFUNC_STDCALL)
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7>
	static int call(CLS * pcls, R (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7), lua_State * L) {
		return lua_bind_pushvalue(L,(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8))) ;
	}
#endif
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8>
	static int call( R (*pfn)(T1,T2,T3,T4,T5,T6,T7,T8), lua_State * L) {
		return lua_bind_pushvalue(L, (*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8)) );
	}
#if defined (LUABIND_FUNCTION_STDCALL)
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8>
	static int call( R (__stdcall *pfn)(T1,T2,T3,T4,T5,T6,T7,T8), lua_State * L) {
		return lua_bind_pushvalue(L,(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8))) ;
	}
#endif
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8>
	static int call(CLS * pcls, R (CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8), lua_State * L) {
		return lua_bind_pushvalue(L,(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9)) );
	}
#if defined (LUABIND_MEMBERFUNC_STDCALL)
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8>
	static int call(CLS * pcls, R (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8), lua_State * L) {
		return lua_bind_pushvalue(L,(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9))) ;
	}
#endif
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9>
	static int call( R (*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9), lua_State * L) {
		return lua_bind_pushvalue(L, (*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9)) );
	}
#if defined (LUABIND_FUNCTION_STDCALL)
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9>
	static int call( R (__stdcall *pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9), lua_State * L) {
		return lua_bind_pushvalue(L,(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9))) ;
	}
#endif
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9>
	static int call(CLS * pcls, R (CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9), lua_State * L) {
		return lua_bind_pushvalue(L,(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10)) );
	}
#if defined (LUABIND_MEMBERFUNC_STDCALL)
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9>
	static int call(CLS * pcls, R (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9), lua_State * L) {
		return lua_bind_pushvalue(L,(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10))) ;
	}
#endif
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10>
	static int call( R (*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10), lua_State * L) {
		return lua_bind_pushvalue(L, (*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10)) );
	}
#if defined (LUABIND_FUNCTION_STDCALL)
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10>
	static int call( R (__stdcall *pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10), lua_State * L) {
		return lua_bind_pushvalue(L,(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10))) ;
	}
#endif
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10>
	static int call(CLS * pcls, R (CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10), lua_State * L) {
		return lua_bind_pushvalue(L,(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11)) );
	}
#if defined (LUABIND_MEMBERFUNC_STDCALL)
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10>
	static int call(CLS * pcls, R (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10), lua_State * L) {
		return lua_bind_pushvalue(L,(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11))) ;
	}
#endif
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11>
	static int call( R (*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11), lua_State * L) {
		return lua_bind_pushvalue(L, (*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10),
					lua_bind_stack<T11>::tovalue(L,11)) );
	}
#if defined (LUABIND_FUNCTION_STDCALL)
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11>
	static int call( R (__stdcall *pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11), lua_State * L) {
		return lua_bind_pushvalue(L,(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10),
					lua_bind_stack<T11>::tovalue(L,11))) ;
	}
#endif
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11>
	static int call(CLS * pcls, R (CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11), lua_State * L) {
		return lua_bind_pushvalue(L,(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11),
					lua_bind_stack<T11>::tovalue(L,12)) );
	}
#if defined (LUABIND_MEMBERFUNC_STDCALL)
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11>
	static int call(CLS * pcls, R (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11), lua_State * L) {
		return lua_bind_pushvalue(L,(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11),
					lua_bind_stack<T11>::tovalue(L,12))) ;
	}
#endif
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12>
	static int call( R (*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12), lua_State * L) {
		return lua_bind_pushvalue(L, (*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10),
					lua_bind_stack<T11>::tovalue(L,11),
					lua_bind_stack<T12>::tovalue(L,12)) );
	}
#if defined (LUABIND_FUNCTION_STDCALL)
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12>
	static int call( R (__stdcall *pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12), lua_State * L) {
		return lua_bind_pushvalue(L,(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10),
					lua_bind_stack<T11>::tovalue(L,11),
					lua_bind_stack<T12>::tovalue(L,12))) ;
	}
#endif
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12>
	static int call(CLS * pcls, R (CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12), lua_State * L) {
		return lua_bind_pushvalue(L,(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11),
					lua_bind_stack<T11>::tovalue(L,12),
					lua_bind_stack<T12>::tovalue(L,13)) );
	}
#if defined (LUABIND_MEMBERFUNC_STDCALL)
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12>
	static int call(CLS * pcls, R (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12), lua_State * L) {
		return lua_bind_pushvalue(L,(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11),
					lua_bind_stack<T11>::tovalue(L,12),
					lua_bind_stack<T12>::tovalue(L,13))) ;
	}
#endif
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13>
	static int call( R (*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13), lua_State * L) {
		return lua_bind_pushvalue(L, (*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10),
					lua_bind_stack<T11>::tovalue(L,11),
					lua_bind_stack<T12>::tovalue(L,12),
					lua_bind_stack<T13>::tovalue(L,13)) );
	}
#if defined (LUABIND_FUNCTION_STDCALL)
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13>
	static int call( R (__stdcall *pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13), lua_State * L) {
		return lua_bind_pushvalue(L,(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10),
					lua_bind_stack<T11>::tovalue(L,11),
					lua_bind_stack<T12>::tovalue(L,12),
					lua_bind_stack<T13>::tovalue(L,13))) ;
	}
#endif
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13>
	static int call(CLS * pcls, R (CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13), lua_State * L) {
		return lua_bind_pushvalue(L,(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11),
					lua_bind_stack<T11>::tovalue(L,12),
					lua_bind_stack<T12>::tovalue(L,13),
					lua_bind_stack<T13>::tovalue(L,14)) );
	}
#if defined (LUABIND_MEMBERFUNC_STDCALL)
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13>
	static int call(CLS * pcls, R (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13), lua_State * L) {
		return lua_bind_pushvalue(L,(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11),
					lua_bind_stack<T11>::tovalue(L,12),
					lua_bind_stack<T12>::tovalue(L,13),
					lua_bind_stack<T13>::tovalue(L,14))) ;
	}
#endif
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14>
	static int call( R (*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14), lua_State * L) {
		return lua_bind_pushvalue(L, (*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10),
					lua_bind_stack<T11>::tovalue(L,11),
					lua_bind_stack<T12>::tovalue(L,12),
					lua_bind_stack<T13>::tovalue(L,13),
					lua_bind_stack<T14>::tovalue(L,14)) );
	}
#if defined (LUABIND_FUNCTION_STDCALL)
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14>
	static int call( R (__stdcall *pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14), lua_State * L) {
		return lua_bind_pushvalue(L,(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10),
					lua_bind_stack<T11>::tovalue(L,11),
					lua_bind_stack<T12>::tovalue(L,12),
					lua_bind_stack<T13>::tovalue(L,13),
					lua_bind_stack<T14>::tovalue(L,14))) ;
	}
#endif
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14>
	static int call(CLS * pcls, R (CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14), lua_State * L) {
		return lua_bind_pushvalue(L,(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11),
					lua_bind_stack<T11>::tovalue(L,12),
					lua_bind_stack<T12>::tovalue(L,13),
					lua_bind_stack<T13>::tovalue(L,14),
					lua_bind_stack<T14>::tovalue(L,15)) );
	}
#if defined (LUABIND_MEMBERFUNC_STDCALL)
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14>
	static int call(CLS * pcls, R (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14), lua_State * L) {
		return lua_bind_pushvalue(L,(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11),
					lua_bind_stack<T11>::tovalue(L,12),
					lua_bind_stack<T12>::tovalue(L,13),
					lua_bind_stack<T13>::tovalue(L,14),
					lua_bind_stack<T14>::tovalue(L,15))) ;
	}
#endif
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15>
	static int call( R (*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15), lua_State * L) {
		return lua_bind_pushvalue(L, (*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10),
					lua_bind_stack<T11>::tovalue(L,11),
					lua_bind_stack<T12>::tovalue(L,12),
					lua_bind_stack<T13>::tovalue(L,13),
					lua_bind_stack<T14>::tovalue(L,14),
					lua_bind_stack<T15>::tovalue(L,15)) );
	}
#if defined (LUABIND_FUNCTION_STDCALL)
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15>
	static int call( R (__stdcall *pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15), lua_State * L) {
		return lua_bind_pushvalue(L,(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10),
					lua_bind_stack<T11>::tovalue(L,11),
					lua_bind_stack<T12>::tovalue(L,12),
					lua_bind_stack<T13>::tovalue(L,13),
					lua_bind_stack<T14>::tovalue(L,14),
					lua_bind_stack<T15>::tovalue(L,15))) ;
	}
#endif
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15>
	static int call(CLS * pcls, R (CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15), lua_State * L) {
		return lua_bind_pushvalue(L,(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11),
					lua_bind_stack<T11>::tovalue(L,12),
					lua_bind_stack<T12>::tovalue(L,13),
					lua_bind_stack<T13>::tovalue(L,14),
					lua_bind_stack<T14>::tovalue(L,15),
					lua_bind_stack<T15>::tovalue(L,16)) );
	}
#if defined (LUABIND_MEMBERFUNC_STDCALL)
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15>
	static int call(CLS * pcls, R (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15), lua_State * L) {
		return lua_bind_pushvalue(L,(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11),
					lua_bind_stack<T11>::tovalue(L,12),
					lua_bind_stack<T12>::tovalue(L,13),
					lua_bind_stack<T13>::tovalue(L,14),
					lua_bind_stack<T14>::tovalue(L,15),
					lua_bind_stack<T15>::tovalue(L,16))) ;
	}
#endif
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16>
	static int call( R (*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16), lua_State * L) {
		return lua_bind_pushvalue(L, (*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10),
					lua_bind_stack<T11>::tovalue(L,11),
					lua_bind_stack<T12>::tovalue(L,12),
					lua_bind_stack<T13>::tovalue(L,13),
					lua_bind_stack<T14>::tovalue(L,14),
					lua_bind_stack<T15>::tovalue(L,15),
					lua_bind_stack<T16>::tovalue(L,16)) );
	}
#if defined (LUABIND_FUNCTION_STDCALL)
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16>
	static int call( R (__stdcall *pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16), lua_State * L) {
		return lua_bind_pushvalue(L,(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10),
					lua_bind_stack<T11>::tovalue(L,11),
					lua_bind_stack<T12>::tovalue(L,12),
					lua_bind_stack<T13>::tovalue(L,13),
					lua_bind_stack<T14>::tovalue(L,14),
					lua_bind_stack<T15>::tovalue(L,15),
					lua_bind_stack<T16>::tovalue(L,16))) ;
	}
#endif
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16>
	static int call(CLS * pcls, R (CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16), lua_State * L) {
		return lua_bind_pushvalue(L,(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11),
					lua_bind_stack<T11>::tovalue(L,12),
					lua_bind_stack<T12>::tovalue(L,13),
					lua_bind_stack<T13>::tovalue(L,14),
					lua_bind_stack<T14>::tovalue(L,15),
					lua_bind_stack<T15>::tovalue(L,16),
					lua_bind_stack<T16>::tovalue(L,17)) );
	}
#if defined (LUABIND_MEMBERFUNC_STDCALL)
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16>
	static int call(CLS * pcls, R (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16), lua_State * L) {
		return lua_bind_pushvalue(L,(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11),
					lua_bind_stack<T11>::tovalue(L,12),
					lua_bind_stack<T12>::tovalue(L,13),
					lua_bind_stack<T13>::tovalue(L,14),
					lua_bind_stack<T14>::tovalue(L,15),
					lua_bind_stack<T15>::tovalue(L,16),
					lua_bind_stack<T16>::tovalue(L,17))) ;
	}
#endif
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17>
	static int call( R (*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17), lua_State * L) {
		return lua_bind_pushvalue(L, (*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10),
					lua_bind_stack<T11>::tovalue(L,11),
					lua_bind_stack<T12>::tovalue(L,12),
					lua_bind_stack<T13>::tovalue(L,13),
					lua_bind_stack<T14>::tovalue(L,14),
					lua_bind_stack<T15>::tovalue(L,15),
					lua_bind_stack<T16>::tovalue(L,16),
					lua_bind_stack<T17>::tovalue(L,17)) );
	}
#if defined (LUABIND_FUNCTION_STDCALL)
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17>
	static int call( R (__stdcall *pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17), lua_State * L) {
		return lua_bind_pushvalue(L,(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10),
					lua_bind_stack<T11>::tovalue(L,11),
					lua_bind_stack<T12>::tovalue(L,12),
					lua_bind_stack<T13>::tovalue(L,13),
					lua_bind_stack<T14>::tovalue(L,14),
					lua_bind_stack<T15>::tovalue(L,15),
					lua_bind_stack<T16>::tovalue(L,16),
					lua_bind_stack<T17>::tovalue(L,17))) ;
	}
#endif
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17>
	static int call(CLS * pcls, R (CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17), lua_State * L) {
		return lua_bind_pushvalue(L,(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11),
					lua_bind_stack<T11>::tovalue(L,12),
					lua_bind_stack<T12>::tovalue(L,13),
					lua_bind_stack<T13>::tovalue(L,14),
					lua_bind_stack<T14>::tovalue(L,15),
					lua_bind_stack<T15>::tovalue(L,16),
					lua_bind_stack<T16>::tovalue(L,17),
					lua_bind_stack<T17>::tovalue(L,18)) );
	}
#if defined (LUABIND_MEMBERFUNC_STDCALL)
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17>
	static int call(CLS * pcls, R (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17), lua_State * L) {
		return lua_bind_pushvalue(L,(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11),
					lua_bind_stack<T11>::tovalue(L,12),
					lua_bind_stack<T12>::tovalue(L,13),
					lua_bind_stack<T13>::tovalue(L,14),
					lua_bind_stack<T14>::tovalue(L,15),
					lua_bind_stack<T15>::tovalue(L,16),
					lua_bind_stack<T16>::tovalue(L,17),
					lua_bind_stack<T17>::tovalue(L,18))) ;
	}
#endif
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17,typename T18>
	static int call( R (*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18), lua_State * L) {
		return lua_bind_pushvalue(L, (*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10),
					lua_bind_stack<T11>::tovalue(L,11),
					lua_bind_stack<T12>::tovalue(L,12),
					lua_bind_stack<T13>::tovalue(L,13),
					lua_bind_stack<T14>::tovalue(L,14),
					lua_bind_stack<T15>::tovalue(L,15),
					lua_bind_stack<T16>::tovalue(L,16),
					lua_bind_stack<T17>::tovalue(L,17),
					lua_bind_stack<T18>::tovalue(L,18)) );
	}
#if defined (LUABIND_FUNCTION_STDCALL)
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17,typename T18>
	static int call( R (__stdcall *pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18), lua_State * L) {
		return lua_bind_pushvalue(L,(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10),
					lua_bind_stack<T11>::tovalue(L,11),
					lua_bind_stack<T12>::tovalue(L,12),
					lua_bind_stack<T13>::tovalue(L,13),
					lua_bind_stack<T14>::tovalue(L,14),
					lua_bind_stack<T15>::tovalue(L,15),
					lua_bind_stack<T16>::tovalue(L,16),
					lua_bind_stack<T17>::tovalue(L,17),
					lua_bind_stack<T18>::tovalue(L,18))) ;
	}
#endif
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17,typename T18>
	static int call(CLS * pcls, R (CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18), lua_State * L) {
		return lua_bind_pushvalue(L,(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11),
					lua_bind_stack<T11>::tovalue(L,12),
					lua_bind_stack<T12>::tovalue(L,13),
					lua_bind_stack<T13>::tovalue(L,14),
					lua_bind_stack<T14>::tovalue(L,15),
					lua_bind_stack<T15>::tovalue(L,16),
					lua_bind_stack<T16>::tovalue(L,17),
					lua_bind_stack<T17>::tovalue(L,18),
					lua_bind_stack<T18>::tovalue(L,19)) );
	}
#if defined (LUABIND_MEMBERFUNC_STDCALL)
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17,typename T18>
	static int call(CLS * pcls, R (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18), lua_State * L) {
		return lua_bind_pushvalue(L,(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11),
					lua_bind_stack<T11>::tovalue(L,12),
					lua_bind_stack<T12>::tovalue(L,13),
					lua_bind_stack<T13>::tovalue(L,14),
					lua_bind_stack<T14>::tovalue(L,15),
					lua_bind_stack<T15>::tovalue(L,16),
					lua_bind_stack<T16>::tovalue(L,17),
					lua_bind_stack<T17>::tovalue(L,18),
					lua_bind_stack<T18>::tovalue(L,19))) ;
	}
#endif
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17,typename T18,typename T19>
	static int call( R (*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19), lua_State * L) {
		return lua_bind_pushvalue(L, (*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10),
					lua_bind_stack<T11>::tovalue(L,11),
					lua_bind_stack<T12>::tovalue(L,12),
					lua_bind_stack<T13>::tovalue(L,13),
					lua_bind_stack<T14>::tovalue(L,14),
					lua_bind_stack<T15>::tovalue(L,15),
					lua_bind_stack<T16>::tovalue(L,16),
					lua_bind_stack<T17>::tovalue(L,17),
					lua_bind_stack<T18>::tovalue(L,18),
					lua_bind_stack<T19>::tovalue(L,19)) );
	}
#if defined (LUABIND_FUNCTION_STDCALL)
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17,typename T18,typename T19>
	static int call( R (__stdcall *pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19), lua_State * L) {
		return lua_bind_pushvalue(L,(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10),
					lua_bind_stack<T11>::tovalue(L,11),
					lua_bind_stack<T12>::tovalue(L,12),
					lua_bind_stack<T13>::tovalue(L,13),
					lua_bind_stack<T14>::tovalue(L,14),
					lua_bind_stack<T15>::tovalue(L,15),
					lua_bind_stack<T16>::tovalue(L,16),
					lua_bind_stack<T17>::tovalue(L,17),
					lua_bind_stack<T18>::tovalue(L,18),
					lua_bind_stack<T19>::tovalue(L,19))) ;
	}
#endif
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17,typename T18,typename T19>
	static int call(CLS * pcls, R (CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19), lua_State * L) {
		return lua_bind_pushvalue(L,(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11),
					lua_bind_stack<T11>::tovalue(L,12),
					lua_bind_stack<T12>::tovalue(L,13),
					lua_bind_stack<T13>::tovalue(L,14),
					lua_bind_stack<T14>::tovalue(L,15),
					lua_bind_stack<T15>::tovalue(L,16),
					lua_bind_stack<T16>::tovalue(L,17),
					lua_bind_stack<T17>::tovalue(L,18),
					lua_bind_stack<T18>::tovalue(L,19),
					lua_bind_stack<T19>::tovalue(L,20)) );
	}
#if defined (LUABIND_MEMBERFUNC_STDCALL)
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17,typename T18,typename T19>
	static int call(CLS * pcls, R (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19), lua_State * L) {
		return lua_bind_pushvalue(L,(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11),
					lua_bind_stack<T11>::tovalue(L,12),
					lua_bind_stack<T12>::tovalue(L,13),
					lua_bind_stack<T13>::tovalue(L,14),
					lua_bind_stack<T14>::tovalue(L,15),
					lua_bind_stack<T15>::tovalue(L,16),
					lua_bind_stack<T16>::tovalue(L,17),
					lua_bind_stack<T17>::tovalue(L,18),
					lua_bind_stack<T18>::tovalue(L,19),
					lua_bind_stack<T19>::tovalue(L,20))) ;
	}
#endif
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17,typename T18,typename T19,typename T20>
	static int call( R (*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20), lua_State * L) {
		return lua_bind_pushvalue(L, (*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10),
					lua_bind_stack<T11>::tovalue(L,11),
					lua_bind_stack<T12>::tovalue(L,12),
					lua_bind_stack<T13>::tovalue(L,13),
					lua_bind_stack<T14>::tovalue(L,14),
					lua_bind_stack<T15>::tovalue(L,15),
					lua_bind_stack<T16>::tovalue(L,16),
					lua_bind_stack<T17>::tovalue(L,17),
					lua_bind_stack<T18>::tovalue(L,18),
					lua_bind_stack<T19>::tovalue(L,19),
					lua_bind_stack<T20>::tovalue(L,20)) );
	}
#if defined (LUABIND_FUNCTION_STDCALL)
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17,typename T18,typename T19,typename T20>
	static int call( R (__stdcall *pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20), lua_State * L) {
		return lua_bind_pushvalue(L,(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10),
					lua_bind_stack<T11>::tovalue(L,11),
					lua_bind_stack<T12>::tovalue(L,12),
					lua_bind_stack<T13>::tovalue(L,13),
					lua_bind_stack<T14>::tovalue(L,14),
					lua_bind_stack<T15>::tovalue(L,15),
					lua_bind_stack<T16>::tovalue(L,16),
					lua_bind_stack<T17>::tovalue(L,17),
					lua_bind_stack<T18>::tovalue(L,18),
					lua_bind_stack<T19>::tovalue(L,19),
					lua_bind_stack<T20>::tovalue(L,20))) ;
	}
#endif
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17,typename T18,typename T19,typename T20>
	static int call(CLS * pcls, R (CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20), lua_State * L) {
		return lua_bind_pushvalue(L,(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11),
					lua_bind_stack<T11>::tovalue(L,12),
					lua_bind_stack<T12>::tovalue(L,13),
					lua_bind_stack<T13>::tovalue(L,14),
					lua_bind_stack<T14>::tovalue(L,15),
					lua_bind_stack<T15>::tovalue(L,16),
					lua_bind_stack<T16>::tovalue(L,17),
					lua_bind_stack<T17>::tovalue(L,18),
					lua_bind_stack<T18>::tovalue(L,19),
					lua_bind_stack<T19>::tovalue(L,20),
					lua_bind_stack<T20>::tovalue(L,21)) );
	}
#if defined (LUABIND_MEMBERFUNC_STDCALL)
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17,typename T18,typename T19,typename T20>
	static int call(CLS * pcls, R (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20), lua_State * L) {
		return lua_bind_pushvalue(L,(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11),
					lua_bind_stack<T11>::tovalue(L,12),
					lua_bind_stack<T12>::tovalue(L,13),
					lua_bind_stack<T13>::tovalue(L,14),
					lua_bind_stack<T14>::tovalue(L,15),
					lua_bind_stack<T15>::tovalue(L,16),
					lua_bind_stack<T16>::tovalue(L,17),
					lua_bind_stack<T17>::tovalue(L,18),
					lua_bind_stack<T18>::tovalue(L,19),
					lua_bind_stack<T19>::tovalue(L,20),
					lua_bind_stack<T20>::tovalue(L,21))) ;
	}
#endif
};
template <>
struct lua_bind_function<void>
{
	static int call( void (*pfn)(), lua_State * L) {
		(*pfn)();
		return 0;
	}
#if defined (LUABIND_FUNCTION_STDCALL)
	static int call( void (__stdcall *pfn)(), lua_State * L) {
		(*pfn)();
		return 0;
	}
#endif
	template <typename CLS, typename CLS2>
	static int call(CLS * pcls, void (CLS2::*pfn)(), lua_State * L) {
		(pcls->*pfn)();
		return 0;
	}
#if defined (LUABIND_MEMBERFUNC_STDCALL)
	template <typename CLS, typename CLS2>
	static int call(CLS * pcls, void (__stdcall CLS2::*pfn)(), lua_State * L) {
		pcls->*pfn)();
		return 0;
	}
#endif
	template <typename T1>
	static int call( void (*pfn)(T1), lua_State * L) {
		(*pfn)(lua_bind_stack<T1>::tovalue(L,1));
		return 0;
	}
#if defined (LUABIND_FUNCTION_STDCALL)
	template <typename T1>
	static int call( void (__stdcall *pfn)(T1), lua_State * L) {
		(*pfn)(lua_bind_stack<T1>::tovalue(L,1));
		return 0;
	}
#endif
	template <typename CLS, typename CLS2, typename T1>
	static int call(CLS * pcls, void (CLS2::*pfn)(T1), lua_State * L) {
		(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2));
		return 0;
	}
#if defined (LUABIND_MEMBERFUNC_STDCALL)
	template <typename CLS, typename CLS2, typename T1>
	static int call(CLS * pcls, void (__stdcall CLS2::*pfn)(T1), lua_State * L) {
		(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2));
		return 0;
	}
#endif
	template <typename T1,typename T2>
	static int call( void (*pfn)(T1,T2), lua_State * L) {
		(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2));
		return 0;
	}
#if defined (LUABIND_FUNCTION_STDCALL)
	template <typename T1,typename T2>
	static int call( void (__stdcall *pfn)(T1,T2), lua_State * L) {
		(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2));
		return 0;
	}
#endif
	template <typename CLS, typename CLS2, typename T1,typename T2>
	static int call(CLS * pcls, void (CLS2::*pfn)(T1,T2), lua_State * L) {
		(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3));
		return 0;
	}
#if defined (LUABIND_MEMBERFUNC_STDCALL)
	template <typename CLS, typename CLS2, typename T1,typename T2>
	static int call(CLS * pcls, void (__stdcall CLS2::*pfn)(T1,T2), lua_State * L) {
		(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3));
		return 0;
	}
#endif
	template <typename T1,typename T2,typename T3>
	static int call( void (*pfn)(T1,T2,T3), lua_State * L) {
		(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3));
		return 0;
	}
#if defined (LUABIND_FUNCTION_STDCALL)
	template <typename T1,typename T2,typename T3>
	static int call( void (__stdcall *pfn)(T1,T2,T3), lua_State * L) {
		(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3));
		return 0;
	}
#endif
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3>
	static int call(CLS * pcls, void (CLS2::*pfn)(T1,T2,T3), lua_State * L) {
		(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4));
		return 0;
	}
#if defined (LUABIND_MEMBERFUNC_STDCALL)
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3>
	static int call(CLS * pcls, void (__stdcall CLS2::*pfn)(T1,T2,T3), lua_State * L) {
		(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4));
		return 0;
	}
#endif
	template <typename T1,typename T2,typename T3,typename T4>
	static int call( void (*pfn)(T1,T2,T3,T4), lua_State * L) {
		(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4));
		return 0;
	}
#if defined (LUABIND_FUNCTION_STDCALL)
	template <typename T1,typename T2,typename T3,typename T4>
	static int call( void (__stdcall *pfn)(T1,T2,T3,T4), lua_State * L) {
		(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4));
		return 0;
	}
#endif
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4>
	static int call(CLS * pcls, void (CLS2::*pfn)(T1,T2,T3,T4), lua_State * L) {
		(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5));
		return 0;
	}
#if defined (LUABIND_MEMBERFUNC_STDCALL)
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4>
	static int call(CLS * pcls, void (__stdcall CLS2::*pfn)(T1,T2,T3,T4), lua_State * L) {
		(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5));
		return 0;
	}
#endif
	template <typename T1,typename T2,typename T3,typename T4,typename T5>
	static int call( void (*pfn)(T1,T2,T3,T4,T5), lua_State * L) {
		(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5));
		return 0;
	}
#if defined (LUABIND_FUNCTION_STDCALL)
	template <typename T1,typename T2,typename T3,typename T4,typename T5>
	static int call( void (__stdcall *pfn)(T1,T2,T3,T4,T5), lua_State * L) {
		(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5));
		return 0;
	}
#endif
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5>
	static int call(CLS * pcls, void (CLS2::*pfn)(T1,T2,T3,T4,T5), lua_State * L) {
		(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6));
		return 0;
	}
#if defined (LUABIND_MEMBERFUNC_STDCALL)
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5>
	static int call(CLS * pcls, void (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5), lua_State * L) {
		(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6));
		return 0;
	}
#endif
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6>
	static int call( void (*pfn)(T1,T2,T3,T4,T5,T6), lua_State * L) {
		(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6));
		return 0;
	}
#if defined (LUABIND_FUNCTION_STDCALL)
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6>
	static int call( void (__stdcall *pfn)(T1,T2,T3,T4,T5,T6), lua_State * L) {
		(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6));
		return 0;
	}
#endif
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6>
	static int call(CLS * pcls, void (CLS2::*pfn)(T1,T2,T3,T4,T5,T6), lua_State * L) {
		(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7));
		return 0;
	}
#if defined (LUABIND_MEMBERFUNC_STDCALL)
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6>
	static int call(CLS * pcls, void (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6), lua_State * L) {
		(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7));
		return 0;
	}
#endif
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7>
	static int call( void (*pfn)(T1,T2,T3,T4,T5,T6,T7), lua_State * L) {
		(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7));
		return 0;
	}
#if defined (LUABIND_FUNCTION_STDCALL)
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7>
	static int call( void (__stdcall *pfn)(T1,T2,T3,T4,T5,T6,T7), lua_State * L) {
		(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7));
		return 0;
	}
#endif
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7>
	static int call(CLS * pcls, void (CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7), lua_State * L) {
		(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8));
		return 0;
	}
#if defined (LUABIND_MEMBERFUNC_STDCALL)
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7>
	static int call(CLS * pcls, void (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7), lua_State * L) {
		(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8));
		return 0;
	}
#endif
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8>
	static int call( void (*pfn)(T1,T2,T3,T4,T5,T6,T7,T8), lua_State * L) {
		(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8));
		return 0;
	}
#if defined (LUABIND_FUNCTION_STDCALL)
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8>
	static int call( void (__stdcall *pfn)(T1,T2,T3,T4,T5,T6,T7,T8), lua_State * L) {
		(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8));
		return 0;
	}
#endif
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8>
	static int call(CLS * pcls, void (CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8), lua_State * L) {
		(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9));
		return 0;
	}
#if defined (LUABIND_MEMBERFUNC_STDCALL)
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8>
	static int call(CLS * pcls, void (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8), lua_State * L) {
		(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9));
		return 0;
	}
#endif
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9>
	static int call( void (*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9), lua_State * L) {
		(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9));
		return 0;
	}
#if defined (LUABIND_FUNCTION_STDCALL)
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9>
	static int call( void (__stdcall *pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9), lua_State * L) {
		(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9));
		return 0;
	}
#endif
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9>
	static int call(CLS * pcls, void (CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9), lua_State * L) {
		(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10));
		return 0;
	}
#if defined (LUABIND_MEMBERFUNC_STDCALL)
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9>
	static int call(CLS * pcls, void (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9), lua_State * L) {
		(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10));
		return 0;
	}
#endif
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10>
	static int call( void (*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10), lua_State * L) {
		(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10));
		return 0;
	}
#if defined (LUABIND_FUNCTION_STDCALL)
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10>
	static int call( void (__stdcall *pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10), lua_State * L) {
		(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10));
		return 0;
	}
#endif
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10>
	static int call(CLS * pcls, void (CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10), lua_State * L) {
		(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11));
		return 0;
	}
#if defined (LUABIND_MEMBERFUNC_STDCALL)
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10>
	static int call(CLS * pcls, void (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10), lua_State * L) {
		(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11));
		return 0;
	}
#endif
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11>
	static int call( void (*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11), lua_State * L) {
		(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10),
					lua_bind_stack<T11>::tovalue(L,11));
		return 0;
	}
#if defined (LUABIND_FUNCTION_STDCALL)
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11>
	static int call( void (__stdcall *pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11), lua_State * L) {
		(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10),
					lua_bind_stack<T11>::tovalue(L,11));
		return 0;
	}
#endif
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11>
	static int call(CLS * pcls, void (CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11), lua_State * L) {
		(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11),
					lua_bind_stack<T11>::tovalue(L,12));
		return 0;
	}
#if defined (LUABIND_MEMBERFUNC_STDCALL)
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11>
	static int call(CLS * pcls, void (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11), lua_State * L) {
		(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11),
					lua_bind_stack<T11>::tovalue(L,12));
		return 0;
	}
#endif
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12>
	static int call( void (*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12), lua_State * L) {
		(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10),
					lua_bind_stack<T11>::tovalue(L,11),
					lua_bind_stack<T12>::tovalue(L,12));
		return 0;
	}
#if defined (LUABIND_FUNCTION_STDCALL)
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12>
	static int call( void (__stdcall *pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12), lua_State * L) {
		(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10),
					lua_bind_stack<T11>::tovalue(L,11),
					lua_bind_stack<T12>::tovalue(L,12));
		return 0;
	}
#endif
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12>
	static int call(CLS * pcls, void (CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12), lua_State * L) {
		(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11),
					lua_bind_stack<T11>::tovalue(L,12),
					lua_bind_stack<T12>::tovalue(L,13));
		return 0;
	}
#if defined (LUABIND_MEMBERFUNC_STDCALL)
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12>
	static int call(CLS * pcls, void (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12), lua_State * L) {
		(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11),
					lua_bind_stack<T11>::tovalue(L,12),
					lua_bind_stack<T12>::tovalue(L,13));
		return 0;
	}
#endif
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13>
	static int call( void (*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13), lua_State * L) {
		(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10),
					lua_bind_stack<T11>::tovalue(L,11),
					lua_bind_stack<T12>::tovalue(L,12),
					lua_bind_stack<T13>::tovalue(L,13));
		return 0;
	}
#if defined (LUABIND_FUNCTION_STDCALL)
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13>
	static int call( void (__stdcall *pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13), lua_State * L) {
		(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10),
					lua_bind_stack<T11>::tovalue(L,11),
					lua_bind_stack<T12>::tovalue(L,12),
					lua_bind_stack<T13>::tovalue(L,13));
		return 0;
	}
#endif
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13>
	static int call(CLS * pcls, void (CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13), lua_State * L) {
		(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11),
					lua_bind_stack<T11>::tovalue(L,12),
					lua_bind_stack<T12>::tovalue(L,13),
					lua_bind_stack<T13>::tovalue(L,14));
		return 0;
	}
#if defined (LUABIND_MEMBERFUNC_STDCALL)
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13>
	static int call(CLS * pcls, void (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13), lua_State * L) {
		(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11),
					lua_bind_stack<T11>::tovalue(L,12),
					lua_bind_stack<T12>::tovalue(L,13),
					lua_bind_stack<T13>::tovalue(L,14));
		return 0;
	}
#endif
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14>
	static int call( void (*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14), lua_State * L) {
		(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10),
					lua_bind_stack<T11>::tovalue(L,11),
					lua_bind_stack<T12>::tovalue(L,12),
					lua_bind_stack<T13>::tovalue(L,13),
					lua_bind_stack<T14>::tovalue(L,14));
		return 0;
	}
#if defined (LUABIND_FUNCTION_STDCALL)
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14>
	static int call( void (__stdcall *pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14), lua_State * L) {
		(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10),
					lua_bind_stack<T11>::tovalue(L,11),
					lua_bind_stack<T12>::tovalue(L,12),
					lua_bind_stack<T13>::tovalue(L,13),
					lua_bind_stack<T14>::tovalue(L,14));
		return 0;
	}
#endif
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14>
	static int call(CLS * pcls, void (CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14), lua_State * L) {
		(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11),
					lua_bind_stack<T11>::tovalue(L,12),
					lua_bind_stack<T12>::tovalue(L,13),
					lua_bind_stack<T13>::tovalue(L,14),
					lua_bind_stack<T14>::tovalue(L,15));
		return 0;
	}
#if defined (LUABIND_MEMBERFUNC_STDCALL)
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14>
	static int call(CLS * pcls, void (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14), lua_State * L) {
		(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11),
					lua_bind_stack<T11>::tovalue(L,12),
					lua_bind_stack<T12>::tovalue(L,13),
					lua_bind_stack<T13>::tovalue(L,14),
					lua_bind_stack<T14>::tovalue(L,15));
		return 0;
	}
#endif
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15>
	static int call( void (*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15), lua_State * L) {
		(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10),
					lua_bind_stack<T11>::tovalue(L,11),
					lua_bind_stack<T12>::tovalue(L,12),
					lua_bind_stack<T13>::tovalue(L,13),
					lua_bind_stack<T14>::tovalue(L,14),
					lua_bind_stack<T15>::tovalue(L,15));
		return 0;
	}
#if defined (LUABIND_FUNCTION_STDCALL)
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15>
	static int call( void (__stdcall *pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15), lua_State * L) {
		(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10),
					lua_bind_stack<T11>::tovalue(L,11),
					lua_bind_stack<T12>::tovalue(L,12),
					lua_bind_stack<T13>::tovalue(L,13),
					lua_bind_stack<T14>::tovalue(L,14),
					lua_bind_stack<T15>::tovalue(L,15));
		return 0;
	}
#endif
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15>
	static int call(CLS * pcls, void (CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15), lua_State * L) {
		(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11),
					lua_bind_stack<T11>::tovalue(L,12),
					lua_bind_stack<T12>::tovalue(L,13),
					lua_bind_stack<T13>::tovalue(L,14),
					lua_bind_stack<T14>::tovalue(L,15),
					lua_bind_stack<T15>::tovalue(L,16));
		return 0;
	}
#if defined (LUABIND_MEMBERFUNC_STDCALL)
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15>
	static int call(CLS * pcls, void (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15), lua_State * L) {
		(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11),
					lua_bind_stack<T11>::tovalue(L,12),
					lua_bind_stack<T12>::tovalue(L,13),
					lua_bind_stack<T13>::tovalue(L,14),
					lua_bind_stack<T14>::tovalue(L,15),
					lua_bind_stack<T15>::tovalue(L,16));
		return 0;
	}
#endif
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16>
	static int call( void (*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16), lua_State * L) {
		(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10),
					lua_bind_stack<T11>::tovalue(L,11),
					lua_bind_stack<T12>::tovalue(L,12),
					lua_bind_stack<T13>::tovalue(L,13),
					lua_bind_stack<T14>::tovalue(L,14),
					lua_bind_stack<T15>::tovalue(L,15),
					lua_bind_stack<T16>::tovalue(L,16));
		return 0;
	}
#if defined (LUABIND_FUNCTION_STDCALL)
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16>
	static int call( void (__stdcall *pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16), lua_State * L) {
		(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10),
					lua_bind_stack<T11>::tovalue(L,11),
					lua_bind_stack<T12>::tovalue(L,12),
					lua_bind_stack<T13>::tovalue(L,13),
					lua_bind_stack<T14>::tovalue(L,14),
					lua_bind_stack<T15>::tovalue(L,15),
					lua_bind_stack<T16>::tovalue(L,16));
		return 0;
	}
#endif
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16>
	static int call(CLS * pcls, void (CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16), lua_State * L) {
		(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11),
					lua_bind_stack<T11>::tovalue(L,12),
					lua_bind_stack<T12>::tovalue(L,13),
					lua_bind_stack<T13>::tovalue(L,14),
					lua_bind_stack<T14>::tovalue(L,15),
					lua_bind_stack<T15>::tovalue(L,16),
					lua_bind_stack<T16>::tovalue(L,17));
		return 0;
	}
#if defined (LUABIND_MEMBERFUNC_STDCALL)
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16>
	static int call(CLS * pcls, void (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16), lua_State * L) {
		(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11),
					lua_bind_stack<T11>::tovalue(L,12),
					lua_bind_stack<T12>::tovalue(L,13),
					lua_bind_stack<T13>::tovalue(L,14),
					lua_bind_stack<T14>::tovalue(L,15),
					lua_bind_stack<T15>::tovalue(L,16),
					lua_bind_stack<T16>::tovalue(L,17));
		return 0;
	}
#endif
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17>
	static int call( void (*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17), lua_State * L) {
		(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10),
					lua_bind_stack<T11>::tovalue(L,11),
					lua_bind_stack<T12>::tovalue(L,12),
					lua_bind_stack<T13>::tovalue(L,13),
					lua_bind_stack<T14>::tovalue(L,14),
					lua_bind_stack<T15>::tovalue(L,15),
					lua_bind_stack<T16>::tovalue(L,16),
					lua_bind_stack<T17>::tovalue(L,17));
		return 0;
	}
#if defined (LUABIND_FUNCTION_STDCALL)
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17>
	static int call( void (__stdcall *pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17), lua_State * L) {
		(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10),
					lua_bind_stack<T11>::tovalue(L,11),
					lua_bind_stack<T12>::tovalue(L,12),
					lua_bind_stack<T13>::tovalue(L,13),
					lua_bind_stack<T14>::tovalue(L,14),
					lua_bind_stack<T15>::tovalue(L,15),
					lua_bind_stack<T16>::tovalue(L,16),
					lua_bind_stack<T17>::tovalue(L,17));
		return 0;
	}
#endif
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17>
	static int call(CLS * pcls, void (CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17), lua_State * L) {
		(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11),
					lua_bind_stack<T11>::tovalue(L,12),
					lua_bind_stack<T12>::tovalue(L,13),
					lua_bind_stack<T13>::tovalue(L,14),
					lua_bind_stack<T14>::tovalue(L,15),
					lua_bind_stack<T15>::tovalue(L,16),
					lua_bind_stack<T16>::tovalue(L,17),
					lua_bind_stack<T17>::tovalue(L,18));
		return 0;
	}
#if defined (LUABIND_MEMBERFUNC_STDCALL)
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17>
	static int call(CLS * pcls, void (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17), lua_State * L) {
		(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11),
					lua_bind_stack<T11>::tovalue(L,12),
					lua_bind_stack<T12>::tovalue(L,13),
					lua_bind_stack<T13>::tovalue(L,14),
					lua_bind_stack<T14>::tovalue(L,15),
					lua_bind_stack<T15>::tovalue(L,16),
					lua_bind_stack<T16>::tovalue(L,17),
					lua_bind_stack<T17>::tovalue(L,18));
		return 0;
	}
#endif
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17,typename T18>
	static int call( void (*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18), lua_State * L) {
		(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10),
					lua_bind_stack<T11>::tovalue(L,11),
					lua_bind_stack<T12>::tovalue(L,12),
					lua_bind_stack<T13>::tovalue(L,13),
					lua_bind_stack<T14>::tovalue(L,14),
					lua_bind_stack<T15>::tovalue(L,15),
					lua_bind_stack<T16>::tovalue(L,16),
					lua_bind_stack<T17>::tovalue(L,17),
					lua_bind_stack<T18>::tovalue(L,18));
		return 0;
	}
#if defined (LUABIND_FUNCTION_STDCALL)
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17,typename T18>
	static int call( void (__stdcall *pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18), lua_State * L) {
		(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10),
					lua_bind_stack<T11>::tovalue(L,11),
					lua_bind_stack<T12>::tovalue(L,12),
					lua_bind_stack<T13>::tovalue(L,13),
					lua_bind_stack<T14>::tovalue(L,14),
					lua_bind_stack<T15>::tovalue(L,15),
					lua_bind_stack<T16>::tovalue(L,16),
					lua_bind_stack<T17>::tovalue(L,17),
					lua_bind_stack<T18>::tovalue(L,18));
		return 0;
	}
#endif
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17,typename T18>
	static int call(CLS * pcls, void (CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18), lua_State * L) {
		(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11),
					lua_bind_stack<T11>::tovalue(L,12),
					lua_bind_stack<T12>::tovalue(L,13),
					lua_bind_stack<T13>::tovalue(L,14),
					lua_bind_stack<T14>::tovalue(L,15),
					lua_bind_stack<T15>::tovalue(L,16),
					lua_bind_stack<T16>::tovalue(L,17),
					lua_bind_stack<T17>::tovalue(L,18),
					lua_bind_stack<T18>::tovalue(L,19));
		return 0;
	}
#if defined (LUABIND_MEMBERFUNC_STDCALL)
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17,typename T18>
	static int call(CLS * pcls, void (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18), lua_State * L) {
		(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11),
					lua_bind_stack<T11>::tovalue(L,12),
					lua_bind_stack<T12>::tovalue(L,13),
					lua_bind_stack<T13>::tovalue(L,14),
					lua_bind_stack<T14>::tovalue(L,15),
					lua_bind_stack<T15>::tovalue(L,16),
					lua_bind_stack<T16>::tovalue(L,17),
					lua_bind_stack<T17>::tovalue(L,18),
					lua_bind_stack<T18>::tovalue(L,19));
		return 0;
	}
#endif
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17,typename T18,typename T19>
	static int call( void (*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19), lua_State * L) {
		(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10),
					lua_bind_stack<T11>::tovalue(L,11),
					lua_bind_stack<T12>::tovalue(L,12),
					lua_bind_stack<T13>::tovalue(L,13),
					lua_bind_stack<T14>::tovalue(L,14),
					lua_bind_stack<T15>::tovalue(L,15),
					lua_bind_stack<T16>::tovalue(L,16),
					lua_bind_stack<T17>::tovalue(L,17),
					lua_bind_stack<T18>::tovalue(L,18),
					lua_bind_stack<T19>::tovalue(L,19));
		return 0;
	}
#if defined (LUABIND_FUNCTION_STDCALL)
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17,typename T18,typename T19>
	static int call( void (__stdcall *pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19), lua_State * L) {
		(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10),
					lua_bind_stack<T11>::tovalue(L,11),
					lua_bind_stack<T12>::tovalue(L,12),
					lua_bind_stack<T13>::tovalue(L,13),
					lua_bind_stack<T14>::tovalue(L,14),
					lua_bind_stack<T15>::tovalue(L,15),
					lua_bind_stack<T16>::tovalue(L,16),
					lua_bind_stack<T17>::tovalue(L,17),
					lua_bind_stack<T18>::tovalue(L,18),
					lua_bind_stack<T19>::tovalue(L,19));
		return 0;
	}
#endif
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17,typename T18,typename T19>
	static int call(CLS * pcls, void (CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19), lua_State * L) {
		(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11),
					lua_bind_stack<T11>::tovalue(L,12),
					lua_bind_stack<T12>::tovalue(L,13),
					lua_bind_stack<T13>::tovalue(L,14),
					lua_bind_stack<T14>::tovalue(L,15),
					lua_bind_stack<T15>::tovalue(L,16),
					lua_bind_stack<T16>::tovalue(L,17),
					lua_bind_stack<T17>::tovalue(L,18),
					lua_bind_stack<T18>::tovalue(L,19),
					lua_bind_stack<T19>::tovalue(L,20));
		return 0;
	}
#if defined (LUABIND_MEMBERFUNC_STDCALL)
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17,typename T18,typename T19>
	static int call(CLS * pcls, void (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19), lua_State * L) {
		(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11),
					lua_bind_stack<T11>::tovalue(L,12),
					lua_bind_stack<T12>::tovalue(L,13),
					lua_bind_stack<T13>::tovalue(L,14),
					lua_bind_stack<T14>::tovalue(L,15),
					lua_bind_stack<T15>::tovalue(L,16),
					lua_bind_stack<T16>::tovalue(L,17),
					lua_bind_stack<T17>::tovalue(L,18),
					lua_bind_stack<T18>::tovalue(L,19),
					lua_bind_stack<T19>::tovalue(L,20));
		return 0;
	}
#endif
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17,typename T18,typename T19,typename T20>
	static int call( void (*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20), lua_State * L) {
		(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10),
					lua_bind_stack<T11>::tovalue(L,11),
					lua_bind_stack<T12>::tovalue(L,12),
					lua_bind_stack<T13>::tovalue(L,13),
					lua_bind_stack<T14>::tovalue(L,14),
					lua_bind_stack<T15>::tovalue(L,15),
					lua_bind_stack<T16>::tovalue(L,16),
					lua_bind_stack<T17>::tovalue(L,17),
					lua_bind_stack<T18>::tovalue(L,18),
					lua_bind_stack<T19>::tovalue(L,19),
					lua_bind_stack<T20>::tovalue(L,20));
		return 0;
	}
#if defined (LUABIND_FUNCTION_STDCALL)
	template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17,typename T18,typename T19,typename T20>
	static int call( void (__stdcall *pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20), lua_State * L) {
		(*pfn)(lua_bind_stack<T1>::tovalue(L,1),
					lua_bind_stack<T2>::tovalue(L,2),
					lua_bind_stack<T3>::tovalue(L,3),
					lua_bind_stack<T4>::tovalue(L,4),
					lua_bind_stack<T5>::tovalue(L,5),
					lua_bind_stack<T6>::tovalue(L,6),
					lua_bind_stack<T7>::tovalue(L,7),
					lua_bind_stack<T8>::tovalue(L,8),
					lua_bind_stack<T9>::tovalue(L,9),
					lua_bind_stack<T10>::tovalue(L,10),
					lua_bind_stack<T11>::tovalue(L,11),
					lua_bind_stack<T12>::tovalue(L,12),
					lua_bind_stack<T13>::tovalue(L,13),
					lua_bind_stack<T14>::tovalue(L,14),
					lua_bind_stack<T15>::tovalue(L,15),
					lua_bind_stack<T16>::tovalue(L,16),
					lua_bind_stack<T17>::tovalue(L,17),
					lua_bind_stack<T18>::tovalue(L,18),
					lua_bind_stack<T19>::tovalue(L,19),
					lua_bind_stack<T20>::tovalue(L,20));
		return 0;
	}
#endif
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17,typename T18,typename T19,typename T20>
	static int call(CLS * pcls, void (CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20), lua_State * L) {
		(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11),
					lua_bind_stack<T11>::tovalue(L,12),
					lua_bind_stack<T12>::tovalue(L,13),
					lua_bind_stack<T13>::tovalue(L,14),
					lua_bind_stack<T14>::tovalue(L,15),
					lua_bind_stack<T15>::tovalue(L,16),
					lua_bind_stack<T16>::tovalue(L,17),
					lua_bind_stack<T17>::tovalue(L,18),
					lua_bind_stack<T18>::tovalue(L,19),
					lua_bind_stack<T19>::tovalue(L,20),
					lua_bind_stack<T20>::tovalue(L,21));
		return 0;
	}
#if defined (LUABIND_MEMBERFUNC_STDCALL)
	template <typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17,typename T18,typename T19,typename T20>
	static int call(CLS * pcls, void (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20), lua_State * L) {
		(pcls->*pfn)(lua_bind_stack<T1>::tovalue(L,2),
					lua_bind_stack<T2>::tovalue(L,3),
					lua_bind_stack<T3>::tovalue(L,4),
					lua_bind_stack<T4>::tovalue(L,5),
					lua_bind_stack<T5>::tovalue(L,6),
					lua_bind_stack<T6>::tovalue(L,7),
					lua_bind_stack<T7>::tovalue(L,8),
					lua_bind_stack<T8>::tovalue(L,9),
					lua_bind_stack<T9>::tovalue(L,10),
					lua_bind_stack<T10>::tovalue(L,11),
					lua_bind_stack<T11>::tovalue(L,12),
					lua_bind_stack<T12>::tovalue(L,13),
					lua_bind_stack<T13>::tovalue(L,14),
					lua_bind_stack<T14>::tovalue(L,15),
					lua_bind_stack<T15>::tovalue(L,16),
					lua_bind_stack<T16>::tovalue(L,17),
					lua_bind_stack<T17>::tovalue(L,18),
					lua_bind_stack<T18>::tovalue(L,19),
					lua_bind_stack<T19>::tovalue(L,20),
					lua_bind_stack<T20>::tovalue(L,21));
		return 0;
	}
#endif
};
template <typename R>
inline int bind_function_call( R (*pfn)(), lua_State * L)
{
	return lua_bind_function<R>::call(pfn,L);
}
#if defined(LUABIND_FUNCTION_STDCALL)
template <typename R>
inline int bind_function_call(R (__stdcall *pfn)(), lua_State * L)
{
	return lua_bind_function<R>::call(pfn,L);
}
#endif
template <typename R, typename CLS, typename CLS2>
inline int bind_function_call(CLS * pcls, R (CLS2::*pfn)(), lua_State * L)
{
	return lua_bind_function<R>::call(pcls,pfn,L);
}
#if defined(LUABIND_MEMBERFUNC_STDCALL)
template <typename R, typename CLS, typename CLS2>
inline int bind_function_call(CLS * pcls, R (__stdcall CLS2::*pfn)(), lua_State * L)
{
	return lua_bind_function<R>::call(pcls,pfn,L);
}
#endif
template <typename R, typename T1>
inline int bind_function_call( R (*pfn)(T1), lua_State * L)
{
	return lua_bind_function<R>::call(pfn,L);
}
#if defined(LUABIND_FUNCTION_STDCALL)
template <typename R, typename T1>
inline int bind_function_call( R (__stdcall *pfn)(T1), lua_State * L)
{
	return lua_bind_function<R>::call(pfn,L);
}
#endif
template <typename R, typename CLS, typename CLS2, typename T1>
inline int bind_function_call(CLS * pcls, R (CLS2::*pfn)(T1), lua_State * L)
{
	return lua_bind_function<R>::call(pcls,pfn,L);
}
#if defined(LUABIND_MEMBERFUNC_STDCALL)
template <typename R, typename CLS, typename CLS2, typename T1>
inline int bind_function_call(CLS * pcls, R (__stdcall CLS2::*pfn)(T1), lua_State * L)
{
	return lua_bind_function<R>::call(pcls,pfn,L);
}
#endif
template <typename R, typename T1,typename T2>
inline int bind_function_call( R (*pfn)(T1,T2), lua_State * L)
{
	return lua_bind_function<R>::call(pfn,L);
}
#if defined(LUABIND_FUNCTION_STDCALL)
template <typename R, typename T1,typename T2>
inline int bind_function_call( R (__stdcall *pfn)(T1,T2), lua_State * L)
{
	return lua_bind_function<R>::call(pfn,L);
}
#endif
template <typename R, typename CLS, typename CLS2, typename T1,typename T2>
inline int bind_function_call(CLS * pcls, R (CLS2::*pfn)(T1,T2), lua_State * L)
{
	return lua_bind_function<R>::call(pcls,pfn,L);
}
#if defined(LUABIND_MEMBERFUNC_STDCALL)
template <typename R, typename CLS, typename CLS2, typename T1,typename T2>
inline int bind_function_call(CLS * pcls, R (__stdcall CLS2::*pfn)(T1,T2), lua_State * L)
{
	return lua_bind_function<R>::call(pcls,pfn,L);
}
#endif
template <typename R, typename T1,typename T2,typename T3>
inline int bind_function_call( R (*pfn)(T1,T2,T3), lua_State * L)
{
	return lua_bind_function<R>::call(pfn,L);
}
#if defined(LUABIND_FUNCTION_STDCALL)
template <typename R, typename T1,typename T2,typename T3>
inline int bind_function_call( R (__stdcall *pfn)(T1,T2,T3), lua_State * L)
{
	return lua_bind_function<R>::call(pfn,L);
}
#endif
template <typename R, typename CLS, typename CLS2, typename T1,typename T2,typename T3>
inline int bind_function_call(CLS * pcls, R (CLS2::*pfn)(T1,T2,T3), lua_State * L)
{
	return lua_bind_function<R>::call(pcls,pfn,L);
}
#if defined(LUABIND_MEMBERFUNC_STDCALL)
template <typename R, typename CLS, typename CLS2, typename T1,typename T2,typename T3>
inline int bind_function_call(CLS * pcls, R (__stdcall CLS2::*pfn)(T1,T2,T3), lua_State * L)
{
	return lua_bind_function<R>::call(pcls,pfn,L);
}
#endif
template <typename R, typename T1,typename T2,typename T3,typename T4>
inline int bind_function_call( R (*pfn)(T1,T2,T3,T4), lua_State * L)
{
	return lua_bind_function<R>::call(pfn,L);
}
#if defined(LUABIND_FUNCTION_STDCALL)
template <typename R, typename T1,typename T2,typename T3,typename T4>
inline int bind_function_call( R (__stdcall *pfn)(T1,T2,T3,T4), lua_State * L)
{
	return lua_bind_function<R>::call(pfn,L);
}
#endif
template <typename R, typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4>
inline int bind_function_call(CLS * pcls, R (CLS2::*pfn)(T1,T2,T3,T4), lua_State * L)
{
	return lua_bind_function<R>::call(pcls,pfn,L);
}
#if defined(LUABIND_MEMBERFUNC_STDCALL)
template <typename R, typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4>
inline int bind_function_call(CLS * pcls, R (__stdcall CLS2::*pfn)(T1,T2,T3,T4), lua_State * L)
{
	return lua_bind_function<R>::call(pcls,pfn,L);
}
#endif
template <typename R, typename T1,typename T2,typename T3,typename T4,typename T5>
inline int bind_function_call( R (*pfn)(T1,T2,T3,T4,T5), lua_State * L)
{
	return lua_bind_function<R>::call(pfn,L);
}
#if defined(LUABIND_FUNCTION_STDCALL)
template <typename R, typename T1,typename T2,typename T3,typename T4,typename T5>
inline int bind_function_call( R (__stdcall *pfn)(T1,T2,T3,T4,T5), lua_State * L)
{
	return lua_bind_function<R>::call(pfn,L);
}
#endif
template <typename R, typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5>
inline int bind_function_call(CLS * pcls, R (CLS2::*pfn)(T1,T2,T3,T4,T5), lua_State * L)
{
	return lua_bind_function<R>::call(pcls,pfn,L);
}
#if defined(LUABIND_MEMBERFUNC_STDCALL)
template <typename R, typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5>
inline int bind_function_call(CLS * pcls, R (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5), lua_State * L)
{
	return lua_bind_function<R>::call(pcls,pfn,L);
}
#endif
template <typename R, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6>
inline int bind_function_call( R (*pfn)(T1,T2,T3,T4,T5,T6), lua_State * L)
{
	return lua_bind_function<R>::call(pfn,L);
}
#if defined(LUABIND_FUNCTION_STDCALL)
template <typename R, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6>
inline int bind_function_call( R (__stdcall *pfn)(T1,T2,T3,T4,T5,T6), lua_State * L)
{
	return lua_bind_function<R>::call(pfn,L);
}
#endif
template <typename R, typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6>
inline int bind_function_call(CLS * pcls, R (CLS2::*pfn)(T1,T2,T3,T4,T5,T6), lua_State * L)
{
	return lua_bind_function<R>::call(pcls,pfn,L);
}
#if defined(LUABIND_MEMBERFUNC_STDCALL)
template <typename R, typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6>
inline int bind_function_call(CLS * pcls, R (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6), lua_State * L)
{
	return lua_bind_function<R>::call(pcls,pfn,L);
}
#endif
template <typename R, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7>
inline int bind_function_call( R (*pfn)(T1,T2,T3,T4,T5,T6,T7), lua_State * L)
{
	return lua_bind_function<R>::call(pfn,L);
}
#if defined(LUABIND_FUNCTION_STDCALL)
template <typename R, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7>
inline int bind_function_call( R (__stdcall *pfn)(T1,T2,T3,T4,T5,T6,T7), lua_State * L)
{
	return lua_bind_function<R>::call(pfn,L);
}
#endif
template <typename R, typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7>
inline int bind_function_call(CLS * pcls, R (CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7), lua_State * L)
{
	return lua_bind_function<R>::call(pcls,pfn,L);
}
#if defined(LUABIND_MEMBERFUNC_STDCALL)
template <typename R, typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7>
inline int bind_function_call(CLS * pcls, R (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7), lua_State * L)
{
	return lua_bind_function<R>::call(pcls,pfn,L);
}
#endif
template <typename R, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8>
inline int bind_function_call( R (*pfn)(T1,T2,T3,T4,T5,T6,T7,T8), lua_State * L)
{
	return lua_bind_function<R>::call(pfn,L);
}
#if defined(LUABIND_FUNCTION_STDCALL)
template <typename R, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8>
inline int bind_function_call( R (__stdcall *pfn)(T1,T2,T3,T4,T5,T6,T7,T8), lua_State * L)
{
	return lua_bind_function<R>::call(pfn,L);
}
#endif
template <typename R, typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8>
inline int bind_function_call(CLS * pcls, R (CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8), lua_State * L)
{
	return lua_bind_function<R>::call(pcls,pfn,L);
}
#if defined(LUABIND_MEMBERFUNC_STDCALL)
template <typename R, typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8>
inline int bind_function_call(CLS * pcls, R (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8), lua_State * L)
{
	return lua_bind_function<R>::call(pcls,pfn,L);
}
#endif
template <typename R, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9>
inline int bind_function_call( R (*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9), lua_State * L)
{
	return lua_bind_function<R>::call(pfn,L);
}
#if defined(LUABIND_FUNCTION_STDCALL)
template <typename R, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9>
inline int bind_function_call( R (__stdcall *pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9), lua_State * L)
{
	return lua_bind_function<R>::call(pfn,L);
}
#endif
template <typename R, typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9>
inline int bind_function_call(CLS * pcls, R (CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9), lua_State * L)
{
	return lua_bind_function<R>::call(pcls,pfn,L);
}
#if defined(LUABIND_MEMBERFUNC_STDCALL)
template <typename R, typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9>
inline int bind_function_call(CLS * pcls, R (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9), lua_State * L)
{
	return lua_bind_function<R>::call(pcls,pfn,L);
}
#endif
template <typename R, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10>
inline int bind_function_call( R (*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10), lua_State * L)
{
	return lua_bind_function<R>::call(pfn,L);
}
#if defined(LUABIND_FUNCTION_STDCALL)
template <typename R, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10>
inline int bind_function_call( R (__stdcall *pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10), lua_State * L)
{
	return lua_bind_function<R>::call(pfn,L);
}
#endif
template <typename R, typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10>
inline int bind_function_call(CLS * pcls, R (CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10), lua_State * L)
{
	return lua_bind_function<R>::call(pcls,pfn,L);
}
#if defined(LUABIND_MEMBERFUNC_STDCALL)
template <typename R, typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10>
inline int bind_function_call(CLS * pcls, R (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10), lua_State * L)
{
	return lua_bind_function<R>::call(pcls,pfn,L);
}
#endif
template <typename R, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11>
inline int bind_function_call( R (*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11), lua_State * L)
{
	return lua_bind_function<R>::call(pfn,L);
}
#if defined(LUABIND_FUNCTION_STDCALL)
template <typename R, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11>
inline int bind_function_call( R (__stdcall *pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11), lua_State * L)
{
	return lua_bind_function<R>::call(pfn,L);
}
#endif
template <typename R, typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11>
inline int bind_function_call(CLS * pcls, R (CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11), lua_State * L)
{
	return lua_bind_function<R>::call(pcls,pfn,L);
}
#if defined(LUABIND_MEMBERFUNC_STDCALL)
template <typename R, typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11>
inline int bind_function_call(CLS * pcls, R (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11), lua_State * L)
{
	return lua_bind_function<R>::call(pcls,pfn,L);
}
#endif
template <typename R, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12>
inline int bind_function_call( R (*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12), lua_State * L)
{
	return lua_bind_function<R>::call(pfn,L);
}
#if defined(LUABIND_FUNCTION_STDCALL)
template <typename R, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12>
inline int bind_function_call( R (__stdcall *pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12), lua_State * L)
{
	return lua_bind_function<R>::call(pfn,L);
}
#endif
template <typename R, typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12>
inline int bind_function_call(CLS * pcls, R (CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12), lua_State * L)
{
	return lua_bind_function<R>::call(pcls,pfn,L);
}
#if defined(LUABIND_MEMBERFUNC_STDCALL)
template <typename R, typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12>
inline int bind_function_call(CLS * pcls, R (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12), lua_State * L)
{
	return lua_bind_function<R>::call(pcls,pfn,L);
}
#endif
template <typename R, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13>
inline int bind_function_call( R (*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13), lua_State * L)
{
	return lua_bind_function<R>::call(pfn,L);
}
#if defined(LUABIND_FUNCTION_STDCALL)
template <typename R, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13>
inline int bind_function_call( R (__stdcall *pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13), lua_State * L)
{
	return lua_bind_function<R>::call(pfn,L);
}
#endif
template <typename R, typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13>
inline int bind_function_call(CLS * pcls, R (CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13), lua_State * L)
{
	return lua_bind_function<R>::call(pcls,pfn,L);
}
#if defined(LUABIND_MEMBERFUNC_STDCALL)
template <typename R, typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13>
inline int bind_function_call(CLS * pcls, R (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13), lua_State * L)
{
	return lua_bind_function<R>::call(pcls,pfn,L);
}
#endif
template <typename R, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14>
inline int bind_function_call( R (*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14), lua_State * L)
{
	return lua_bind_function<R>::call(pfn,L);
}
#if defined(LUABIND_FUNCTION_STDCALL)
template <typename R, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14>
inline int bind_function_call( R (__stdcall *pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14), lua_State * L)
{
	return lua_bind_function<R>::call(pfn,L);
}
#endif
template <typename R, typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14>
inline int bind_function_call(CLS * pcls, R (CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14), lua_State * L)
{
	return lua_bind_function<R>::call(pcls,pfn,L);
}
#if defined(LUABIND_MEMBERFUNC_STDCALL)
template <typename R, typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14>
inline int bind_function_call(CLS * pcls, R (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14), lua_State * L)
{
	return lua_bind_function<R>::call(pcls,pfn,L);
}
#endif
template <typename R, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15>
inline int bind_function_call( R (*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15), lua_State * L)
{
	return lua_bind_function<R>::call(pfn,L);
}
#if defined(LUABIND_FUNCTION_STDCALL)
template <typename R, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15>
inline int bind_function_call( R (__stdcall *pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15), lua_State * L)
{
	return lua_bind_function<R>::call(pfn,L);
}
#endif
template <typename R, typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15>
inline int bind_function_call(CLS * pcls, R (CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15), lua_State * L)
{
	return lua_bind_function<R>::call(pcls,pfn,L);
}
#if defined(LUABIND_MEMBERFUNC_STDCALL)
template <typename R, typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15>
inline int bind_function_call(CLS * pcls, R (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15), lua_State * L)
{
	return lua_bind_function<R>::call(pcls,pfn,L);
}
#endif
template <typename R, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16>
inline int bind_function_call( R (*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16), lua_State * L)
{
	return lua_bind_function<R>::call(pfn,L);
}
#if defined(LUABIND_FUNCTION_STDCALL)
template <typename R, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16>
inline int bind_function_call( R (__stdcall *pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16), lua_State * L)
{
	return lua_bind_function<R>::call(pfn,L);
}
#endif
template <typename R, typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16>
inline int bind_function_call(CLS * pcls, R (CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16), lua_State * L)
{
	return lua_bind_function<R>::call(pcls,pfn,L);
}
#if defined(LUABIND_MEMBERFUNC_STDCALL)
template <typename R, typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16>
inline int bind_function_call(CLS * pcls, R (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16), lua_State * L)
{
	return lua_bind_function<R>::call(pcls,pfn,L);
}
#endif
template <typename R, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17>
inline int bind_function_call( R (*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17), lua_State * L)
{
	return lua_bind_function<R>::call(pfn,L);
}
#if defined(LUABIND_FUNCTION_STDCALL)
template <typename R, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17>
inline int bind_function_call( R (__stdcall *pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17), lua_State * L)
{
	return lua_bind_function<R>::call(pfn,L);
}
#endif
template <typename R, typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17>
inline int bind_function_call(CLS * pcls, R (CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17), lua_State * L)
{
	return lua_bind_function<R>::call(pcls,pfn,L);
}
#if defined(LUABIND_MEMBERFUNC_STDCALL)
template <typename R, typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17>
inline int bind_function_call(CLS * pcls, R (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17), lua_State * L)
{
	return lua_bind_function<R>::call(pcls,pfn,L);
}
#endif
template <typename R, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17,typename T18>
inline int bind_function_call( R (*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18), lua_State * L)
{
	return lua_bind_function<R>::call(pfn,L);
}
#if defined(LUABIND_FUNCTION_STDCALL)
template <typename R, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17,typename T18>
inline int bind_function_call( R (__stdcall *pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18), lua_State * L)
{
	return lua_bind_function<R>::call(pfn,L);
}
#endif
template <typename R, typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17,typename T18>
inline int bind_function_call(CLS * pcls, R (CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18), lua_State * L)
{
	return lua_bind_function<R>::call(pcls,pfn,L);
}
#if defined(LUABIND_MEMBERFUNC_STDCALL)
template <typename R, typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17,typename T18>
inline int bind_function_call(CLS * pcls, R (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18), lua_State * L)
{
	return lua_bind_function<R>::call(pcls,pfn,L);
}
#endif
template <typename R, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17,typename T18,typename T19>
inline int bind_function_call( R (*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19), lua_State * L)
{
	return lua_bind_function<R>::call(pfn,L);
}
#if defined(LUABIND_FUNCTION_STDCALL)
template <typename R, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17,typename T18,typename T19>
inline int bind_function_call( R (__stdcall *pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19), lua_State * L)
{
	return lua_bind_function<R>::call(pfn,L);
}
#endif
template <typename R, typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17,typename T18,typename T19>
inline int bind_function_call(CLS * pcls, R (CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19), lua_State * L)
{
	return lua_bind_function<R>::call(pcls,pfn,L);
}
#if defined(LUABIND_MEMBERFUNC_STDCALL)
template <typename R, typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17,typename T18,typename T19>
inline int bind_function_call(CLS * pcls, R (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19), lua_State * L)
{
	return lua_bind_function<R>::call(pcls,pfn,L);
}
#endif
template <typename R, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17,typename T18,typename T19,typename T20>
inline int bind_function_call( R (*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20), lua_State * L)
{
	return lua_bind_function<R>::call(pfn,L);
}
#if defined(LUABIND_FUNCTION_STDCALL)
template <typename R, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17,typename T18,typename T19,typename T20>
inline int bind_function_call( R (__stdcall *pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20), lua_State * L)
{
	return lua_bind_function<R>::call(pfn,L);
}
#endif
template <typename R, typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17,typename T18,typename T19,typename T20>
inline int bind_function_call(CLS * pcls, R (CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20), lua_State * L)
{
	return lua_bind_function<R>::call(pcls,pfn,L);
}
#if defined(LUABIND_MEMBERFUNC_STDCALL)
template <typename R, typename CLS, typename CLS2, typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17,typename T18,typename T19,typename T20>
inline int bind_function_call(CLS * pcls, R (__stdcall CLS2::*pfn)(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20), lua_State * L)
{
	return lua_bind_function<R>::call(pcls,pfn,L);
}
#endif

#endif //_LUA_BIND_FUNCTION_H
