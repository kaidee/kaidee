local T = {}
T.__index = T
-- T.a = nil
T.b = 2

function T:change( value )
	T.a = value
end

function T:create( value )
	-- T:change(value)
	-- if value then
		self.a = value
	-- end
	return self
end

return T