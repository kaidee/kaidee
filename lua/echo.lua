
function echo(...)
    local arr = {}
    for i, a in ipairs({...}) do
        arr[#arr + 1] = tostring(a)
    end
    print(table.concat(arr, "\b"))
end

echo(2,3.5,"hio", {'hi','you'})
-- print ("hh")
mytable = { 10, ddd = 30, 12, 13, fff=false }
print(mytable.fff)