function modify( var )
	var.a = 3
end

var_name = {a=4, item_id=123}

ref=var_name
modify(ref)
print(var_name.a)

require "ret"
print(test.item)
print(test.getIDofItem(var_name))