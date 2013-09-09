--定义2个表
a = {5, 6}
b = {7, 8}
--用c来做Metatable
c = {}
--重定义加法操作
c.__add = function(op1, op2)
   for _, item in ipairs(op2) do
      table.insert(op1, item)
   end
   return op1
end
--将a的Metatable设置为c
setmetatable(a, c)
--d现在的样子是{5,6,7,8}
d = a + b
-- print(d)
-- for i,v in ipairs(d) do
-- 	print(i,v)
-- end
-- print getmetatable(a)
-- for i,v in ipairs(dd) do
-- 	print(i,v)
-- end

list = {}
list.mt = {}
function list.new( ls )
	local l_ls = {}
	setmetatable(l_ls, list.mt)
	for i,v in ipairs(ls) do
		l_ls[i] = v
	end
	return l_ls
end

function list.add( lhs, rhs )
	local ret = list.new{}
	for i,v in ipairs(lhs) do
		ret[i] = v
	end
	for i,v in ipairs(rhs) do
		ret[table.maxn(ret)+1] = v
	end
	return ret
end

function list.tostring( ls )
	return "{" .. table.concat(ls, ", ") .. "}"
end

list.mt.__add = list.add
list.mt.__tostring = list.tostring

ls1 = list.new{"a", "b", "c"}
ls2 = list.new{"9", "2009"}

ls3 = ls1 + ls2
print(ls3)
for i, v in ipairs(ls3) do
	print(i, v)
end

