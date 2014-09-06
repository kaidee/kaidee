--引入extern.lua
require "extern"
--test
local function test()
    local luaTable = {x=1, y=2}
    local N = class("N", luaTable)
    print("继承lua自定义的表，访问父类的x属性值：x="..N.x)
    
    local  testSprite = function ()
        return CCSprite:create("farm.jpg")
    end 
    local M = class("M", testSprite)
    local  m = M:new()
    m.customField = "customField"
    m:setOpacity(100)
    print("用C++本地类的方式继承，访问父类修改后的属性："..m:getOpacity())
    print("访问子类属性："..m:getOpacity())
end
test()