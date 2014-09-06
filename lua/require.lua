local D = require "define"

-- print(D.a)
local d = D:create(22)
print(d.a)
-- print(D.a)
local dd = D:create(333)
print(dd.a)
print(d.a)
-- print(D.a)

print(string.sub('fla_res', 1, 2))