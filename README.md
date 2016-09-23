
simple character convert for lua,suport lua 5.3   


complie
-----
just only suport windows(mingw)   
"make mingw"    

Lua API
----
```
local liconv = require "liconv"
```
* `liconv.conv(from,to,s)` convert    
  `from` character encode for s. "gbk" or "utf8"    
  `to` character encode for target. "gbk" or "utf8"   
  `s` string that would convert   

  return s, if from equal to;return nil,if convert fail;return string,if convert success



