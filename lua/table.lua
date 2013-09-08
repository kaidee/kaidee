
-- print(a)
function f( ... )
	print (...)
	return 'has called'
end

-- a = { [f(1)] = g; "x", "y"; x = 1, f(x), [30] = 23; 45 }
table = { [f('w')] = g; "x", "y"; x = 1, f(1), [30] = 23; 45 }
for i,v in ipairs(table) do
	print(i,'==>', v)
end
print("================")
for k,v in pairs(table) do
	print(k,v)
end
print (#(table))