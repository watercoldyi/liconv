#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "iconv.h"
#include <stdlib.h>
#include <string.h>

static int
lconv(lua_State *L){
	const char *from = lua_tostring(L,1);
	const char *to = lua_tostring(L,2);
	size_t ns = 0;
	const char *s = lua_tolstring(L,3,&ns);
	iconv_t cd = NULL;
	if(from == to ||  ns == 0) goto fail;
	cd = iconv_open(to,from);
	if(cd == NULL) goto fail;
	char buf[4096];
	char *pin = (char*)s;
	luaL_Buffer b;
	luaL_buffinit(L,&b);
	while(1){
		char *pout = buf;
		size_t nbuf = 4096;
		int r = iconv(cd,&pin,&ns,&pout,&nbuf);
		if(r && nbuf == 4096){
			goto fail;
		}
		else if(r == 0){
			luaL_addlstring(&b,buf,nbuf == 0 ? 4096:4096 - nbuf);
			break;
		}
		else{
			luaL_addlstring(&b,buf,nbuf == 0 ? 4096:4096 - nbuf);
		}
	}
	luaL_pushresult(&b);
	iconv_close(cd);
	return 1;
fail:
	if(cd) iconv_close(cd);
	lua_pushnil(L);
	return 1;
}

int
luaopen_liconv(lua_State *L){
	static luaL_Reg f[] = {
		{"iconv",lconv},
		{NULL,NULL}
	};
	luaL_newlib(L,f);
	return 1;
}
