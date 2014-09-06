--克隆一个对象
function clone(object)
	--用于存储被访问过的对象的表
    local lookup_table = {}
    local function _copy(object)
        if type(object) ~= "table" then--如果类别不等于table，返回当前参数
            return object
        elseif lookup_table[object] then--如果备份表中存在该对象，则直接返回
            return lookup_table[object]
        end
        local new_table = {}--创建一个新的表
        lookup_table[object] = new_table--把即将被访问过的表存到备份表
        for key, value in pairs(object) do--遍历，赋值
            new_table[_copy(key)] = _copy(value)
        end
        return setmetatable(new_table, getmetatable(object))--设置元表，用于继承
    end
    return _copy(object)
end

--Create an class.
--创建类（类名， 父类）
function class(classname, super)
    local superType = type(super)--获取父类的类型
    local cls--定义一个变量，用来存储新创建的类的属性和函数

    if superType ~= "function" and superType ~= "table" then--如果父类不是function类别或表类别，父类置空
        superType = nil
        super = nil
    end

    if superType == "function" or (super and super.__ctype == 1) then--如果父类型是个function或者来自是c++的类
        -- inherited from native C++ Object
        print(superType)
        cls = {}

        if superType == "table" then--来自引擎自带的c++类
            -- copy fields from super
            for k,v in pairs(super) do cls[k] = v end
            cls.__create = super.__create
            cls.super    = super
        else--function
            cls.__create = super
        end

        cls.ctor    = function() end--构造
        cls.__cname = classname--类名
        cls.__ctype = 1--指明派生与C++的类
        --创建一个用于创建类的实例的方法
        function cls.new(...)
            local instance = cls.__create(...)
            -- copy fields from class to native object
            for k,v in pairs(cls) do instance[k] = v end--拷贝属性
            instance.class = cls--创建一个属性，指向cls
            instance:ctor(...)--构造
            return instance
        end

    else
        -- inherited from Lua Object
        if super then--如果父类不为空
            cls = clone(super)--把类克隆，放到cls中
            cls.super = super--创建一个属性，指向父类
        else
            cls = {ctor = function() end}--否则创建一个空的构造函数
        end

        cls.__cname = classname--创建一个属性，指明类的名称
        cls.__ctype = 2 -- lua 指明继承自lua自定义的表
        cls.__index = cls --把__index指向自己，用于形成一个继承的原型链
        --创建一个用于创建类的实例的方法
        function cls.new(...)
            local instance = setmetatable({}, cls)--创建一个空表，并设置它的元表为cls，即继承cls
            instance.class = cls--创建一个属性，指向cls
            instance:ctor(...)--调用构造函数
            return instance
        end
    end

    return cls
end