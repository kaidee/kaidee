module("test", package.seeall)

function getIDofItem(item)
    return (item and item.item_id) or nil
end


local item = {item_id=123}
print(getIDofItem(item))