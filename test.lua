local iconv = require "liconv"

local f = io.open("utf8","rb");
local u = f:read "a"
f:close()
print(u)
local gbk = iconv.iconv("UTF-8","GBK",u)
print(gbk)

assert(iconv.iconv("","","") == nil,"empty err")
assert(iconv.iconv("aa","bb","") == nil,"iconv_open err")
assert(iconv.iconv("UTF-8","bb","") == nil,"iconv_open err")
assert(iconv.iconv("UTF-8","GBK","") == nil,"empty source err")

	
