

function readOnly (t)
   local proxy = {}
   local mt = {         -- create metatable
       __index = t,
       __newindex = function (t,k,v)
          error("attempt to update a read-only table", 2)
       end
	}
   setmetatable(proxy, mt)
   return proxy
end

days = readOnly{"Sunday", "Monday", "Tuesday", "Wednesday",
       "Thursday", "Friday", "Saturday"}
print(days[1])       --> Sunday
days[2] = "Noday"

-- ┌─[kaidee@kaidee-dev] - [~/github/kaidee/lua] - [二  5 27, 02:54]
-- └─[$] <git:(master*)> lua read_only.lua
-- Sunday
-- lua: read_only.lua:18: attempt to update a read-only table
-- stack traceback:
-- 	[C]: in function 'error'
-- 	read_only.lua:8: in function <read_only.lua:7>
-- 	read_only.lua:18: in main chunk
-- 	[C]: ?