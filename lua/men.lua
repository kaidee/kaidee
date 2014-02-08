local results = {}
function mem_loadstring (s)
if results[s] then -- result available? 
	return results[s] -- reuse it
else
       local res = loadstring(s)
       results[s] = res
       return res
	end 
end

local results = {}
setmetatable(results, {__mode = "v"}) -- make values weak 
function mem_loadstring (s)
   -- ...    -- as before
end

-- function createRGB (r, g, b)
--    return {red = r, green = g, blue = b}
-- end

local results = {}
setmetatable(results, {__mode = "v"}) -- make values weak 
function createRGB (r, g, b)
   local key = r .. "-" .. g .. "-" .. b
   if results[key] then 
   	return results[key]
   else
       local newcolor = {red = r, green = g, blue = b}
       results[key] = newcolor
       return newcolor
	end 
end