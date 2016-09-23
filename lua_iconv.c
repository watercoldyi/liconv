#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

#include <windows.h>
#include <stdlib.h>
#include <string.h>



static int
_utf8_to_gbk(lua_State *L,const char *from){
	int r = MultiByteToWideChar(CP_UTF8,0,from,-1,NULL,0);
	if(r <= 0 ) return -1;
	int size = r*2;
	char buf[size];
	r = MultiByteToWideChar(CP_UTF8,0,from,-1,buf,size);
	if(r <= 0 ) return -1;
	r = WideCharToMultiByte(CP_ACP,0,buf,-1,NULL,0,NULL,NULL);
	luaL_Buffer gbk;
	char *p = luaL_buffinitsize(L,&gbk,r);
	r = WideCharToMultiByte(CP_ACP,0,buf,-1,p,r,NULL,NULL);
	if(r>0){
		luaL_pushresultsize(&gbk,r);
		return 0;
	}
	return -1;
}

static int
_gbk_to_utf8(lua_State *L,const char *from){
	int r = MultiByteToWideChar(CP_ACP,0,from,-1,NULL,0);
	if(r <= 0 ) return -1;
	int size = r*2;
	char buf[size];
	r = MultiByteToWideChar(CP_ACP,0,from,-1,buf,size);
	if(r <= 0 ) return -1;
	r = WideCharToMultiByte(CP_UTF8,0,buf,-1,NULL,0,NULL,NULL);
	luaL_Buffer utf8;
	char *p = luaL_buffinitsize(L,&utf8,r);
	r = WideCharToMultiByte(CP_UTF8,0,buf,-1,p,r,NULL,NULL);
	if(r>0){
		luaL_pushresultsize(&utf8,r);
		return 0;
	}
	return -1;
}

static int
lconv(lua_State *L){
	const char *from = lua_tostring(L,1);
	const char *to = lua_tostring(L,2);
	const char *s = lua_tostring(L,3);
	if(strcmp(from,to) == 0 ){
		lua_pushvalue(L,3);
		return 1;
	}
	if(strcmp(from,"gbk") == 0 ){
		if(strcmp(to,"utf8") == 0){
			if (_gbk_to_utf8(L,s)){
				lua_pushnil(L);
				return 1;
			}
		}
		else{
			lua_pushnil(L);
			lua_pushliteral(L,"not support the convert");
			return 2;
		}
	}
	else if(strcmp(from,"utf8") == 0 ){
		if(strcmp(to,"gbk") == 0){
			if(_utf8_to_gbk(L,s)){
				lua_pushnil(L);
				return 1;
			}
		}
		else{
			lua_pushnil(L);
			lua_pushliteral(L,"not support the convert");
			return 2;
		}
	}
	else{
		lua_pushnil(L);
		lua_pushliteral(L,"not support the convert");
		return 2;
	}
	return 1;
}

int
luaopen_liconv(lua_State *L){
	static luaL_Reg f[] = {
		{"conv",lconv},
		{NULL,NULL}
	};
	luaL_newlib(L,f);
	return 1;
}
