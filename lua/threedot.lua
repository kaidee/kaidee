-- Code highlighting produced by Actipro CodeHighlighter (freeware)http://www.CodeHighlighter.com/-->
collectgarbage("stop")
print("init memory:"..collectgarbage("count"))

function test(...)
    -- return 1 + select(1, ...) --A result memory:22.2587890625

    --select(1,...);return 1 --B result memory:22.2587890625

    --return 1, ... --C result memory:22.0947265625

    -- return 1 + arg[1] --D result memory:803.3623046875

    -- return 1 --E result memory:803.3544921875

    --return 1 + 1 --F result memory:803.3544921875

    return 1, unpack(arg) --G result memory:803.5185546875

    -- return 1, arg[1], ... --H error attempt to index local 'arg' (a nil value)

    --return 1 + #{...} --I result memory:490.9072265625
    
    -- select(1,...);return 1,{1} --J result memory:491.0712890625
end

print("start memory:"..collectgarbage("count"))
for i = 1, 10000 do
    test(i)
end
print("result memory:"..collectgarbage("count"))

-- init memory:29.521484375
-- start memory:29.64453125
-- result memory:1201.6279296875
-- [Finished in 0.0s]