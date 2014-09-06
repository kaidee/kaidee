function shallowcopy(orig)
    local orig_type = type(orig)
    local copy
    if orig_type == 'table' then
        copy = {}
        for orig_key, orig_value in pairs(orig) do
            copy[orig_key] = orig_value
        end
    else -- number, string, boolean, etc
        copy = orig
    end
    return copy
end

function deepcopy(orig)
    local orig_type = type(orig)
    local copy
    if orig_type == 'table' then
        copy = {}
        for orig_key, orig_value in next, orig, nil do
            copy[deepcopy(orig_key)] = deepcopy(orig_value)
        end
        setmetatable(copy, deepcopy(getmetatable(orig)))
    else -- number, string, boolean, etc
        copy = orig
    end
    return copy
end

mt = {2,3,4,5}

t = {1,9,{"dd", "rr"}}

-- setmetatable(t, mt)

sc = shallowcopy(t)
dc = deepcopy(t)

-- for k,v in pairs(sc) do
--     print(k,v)
-- end

-- print(sc[3][1])
_items={  }
roleID = 1000

local roleItems = _items[roleID]
if not roleItems then
    roleItems = {}
    _items[roleID] = roleItems
end
table.insert(roleItems, "item")
table.insert(roleItems, "item2")
table.insert(roleItems, "item3")

for k,v in pairs(_items[roleID]) do
    -- print(k,v)
end










