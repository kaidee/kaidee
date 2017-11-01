
-- print(a)
-- function f( ... )
-- 	print (...)
-- 	return 'has called'
-- end

-- -- a = { [f(1)] = g; "x", "y"; x = 1, f(x), [30] = 23; 45 }
-- table = { [f('w')] = g; "x", "y"; x = 1, f(1), [30] = 23; 45 }
-- for i,v in ipairs(table) do
-- 	print(i,'==>', v)
-- end
-- print("================")
-- for k,v in pairs(table) do
-- 	print(k,v)
-- end
-- print (#(table))

local t = {2,3,4}
-- if type(t) == 'table' then
-- 	print("xxxxx")
-- end

-- local l = #t
-- print(l)

-- function get(  )
-- 	local x = t[5]
-- 	if x then
-- 		return x
-- 	end
-- end

-- xx = get()
-- print("xx: ",xx)

print(table.find(3))