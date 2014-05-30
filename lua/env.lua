-- t = {} 
-- m = { a = " and ", b = "Li Lei", c = "Han Meimei" }
-- setmetatable(t, { __index = m})  --表{ __index=m }作为表t的元表
-- for k, v in pairs(t) do  --穷举表t  
-- 	print(k, v) 
-- end 
-- 	print("-------------") 
-- 	print(t.b, t.a, t.c)
-- require "echo"
print(_G)
for k,v in pairs(_LOADED) do
	print(k)
	for k,v in pairs({v}) do
		print(k,v)
	end
end
-- hhhhhh
