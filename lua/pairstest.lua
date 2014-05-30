local nt = nil
local t = {2,3}
-- local t = {2,2}



-- for k,v in pairs(t) do
-- 	print(k,v)
-- end

function get( x )
	return t[x] or {}
end

print(get(3))