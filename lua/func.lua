function func( ... )
	print (...)
	-- local arg = ...
	-- print(arg.s, arg.d)
	local function g( ... )
		print (...)
		return 'function g has called'
	end
	g('gg')
	return 'called'
end

-- func('2')
-- func[['w']]
-- print (func"hello")
-- func(e)
-- r = func().g('RR')
-- print(r)
-- func'sss'
func{s='sdf', d=22}