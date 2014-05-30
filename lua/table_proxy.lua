-- t = {} -- original table (created somewhere) -- keep a private access to original table
-- local _t = t
-- -- create proxy
-- t = {}
-- -- create metatable
-- local mt = {
--    __index = function (t,k)
-- 	   print("*access to element " .. tostring(k))
-- 	   return _t[k]  -- access the original table
--    end,
--    __newindex = function (t,k,v)
-- 	   print("*update of element " .. tostring(k) ..
--               " to " .. tostring(v))
-- 	   _t[k] = v     -- update original table
-- 	end
-- }
-- setmetatable(t, mt)
-- t.s='sss'
-- print(t.s)



-- create private index
local index = {}
-- create metatable
local mt = {
	__index = function (t,k)
	       print("*access to element " .. tostring(k))
	       return t[index][k]   -- access the original table
	   end,
	__newindex = function(t,k,v)
			print("*update of element " .. tostring(k) .. " to ".. tostring(v))
			t[index][k] = v
		end
	}
function track (t)
   local proxy = {}
   proxy[index] = t
   setmetatable(proxy, mt)
   return proxy
end

t = track(t)

t.s='sss'
print(t.s)


-- ┌─[kaidee@kaidee-dev] - [~/github/kaidee/lua] - [二  5 27, 02:53]
-- └─[$] <git:(master*)> lua table_proxy.lua
-- *update of element s to sss
-- *access to element table: 0x7f832840a1d0
-- *access to element table: 0x7f832840a1d0
-- *access to element table: 0x7f832840a1d0
-- ...
-- *access to element table: 0x7f832840a1d0
-- *access to element table: 0x7f832840a1d0
-- *access to element table: 0x7f832840a1d0
-- *access to element table: 0x7f832840a1d0
-- *access to element table: 0x7f832840a1d0
-- lua: C stack overflow
-- stack traceback:
-- 	[C]: in function 'print'
-- 	table_proxy.lua:28: in function <table_proxy.lua:27>
-- 	table_proxy.lua:29: in function <table_proxy.lua:27>
-- 	table_proxy.lua:29: in function <table_proxy.lua:27>
-- 	table_proxy.lua:29: in function <table_proxy.lua:27>
-- 	table_proxy.lua:29: in function <table_proxy.lua:27>
-- 	table_proxy.lua:29: in function <table_proxy.lua:27>
-- 	table_proxy.lua:29: in function <table_proxy.lua:27>
-- 	table_proxy.lua:29: in function <table_proxy.lua:27>
-- 	table_proxy.lua:29: in function <table_proxy.lua:27>
-- 	...
-- 	table_proxy.lua:29: in function <table_proxy.lua:27>
-- 	table_proxy.lua:29: in function <table_proxy.lua:27>
-- 	table_proxy.lua:29: in function <table_proxy.lua:27>
-- 	table_proxy.lua:29: in function <table_proxy.lua:27>
-- 	table_proxy.lua:29: in function <table_proxy.lua:27>
-- 	table_proxy.lua:29: in function <table_proxy.lua:27>
-- 	table_proxy.lua:29: in function <table_proxy.lua:27>
-- 	table_proxy.lua:33: in function <table_proxy.lua:31>
-- 	table_proxy.lua:45: in main chunk
-- 	[C]: ?


	