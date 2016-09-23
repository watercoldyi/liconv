all:
	echo "please input platfrom,mingw or linux"

mingw:liconv.dll
linux:liconv.so

liconv.dll:lua_iconv.c
	gcc -std=c99  -shared -Wall -o $@ $^ -I/usr/local/include -L/usr/local/bin -llua53

liconv.so:lua_iconv.c
	echo "not supoort"

