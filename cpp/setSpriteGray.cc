void setGray(Node *node)
{
  USING_NS_CC;
  do
  {
    const GLchar* pszFragSource =
            "#ifdef GL_ES \n \
         precision mediump float; \n \
         #endif \n \
         uniform sampler2D u_texture; \n \
         varying vec2 v_texCoord; \n \
         varying vec4 v_fragmentColor; \n \
         void main(void) \n \
         { \n \
         // Convert to greyscale using NTSC weightings \n \
         vec4 col = texture2D(u_texture, v_texCoord); \n \
         float grey = dot(col.rgb, vec3(0.299, 0.587, 0.114)); \n \
         gl_FragColor = vec4(grey, grey, grey, col.a); \n \
         }";
       
    GLProgram* pProgram = new GLProgram();
    pProgram->initWithByteArrays(ccPositionTextureColor_noMVP_vert, pszFragSource);
    node->setGLProgram();
    CHECK_GL_ERROR_DEBUG();
  }while(0);
}

/*
--不进行灰化的对象特有的方法
DisplayUtil.LIST_DONT_GRAY = {
    "getSprite",     --ProgressTimer
    "setString",     --Label
}
--判断能否灰化
function DisplayUtil.canGray(node)
    for i,v in ipairs(DisplayUtil.LIST_DONT_GRAY) do
        if node[v] then
            return false
        end
    end
    return true
end
--灰化对象
function DisplayUtil.setGray(node, v)
    if type(node) ~= "userdata" then
        printError("node must be a userdata")
        return
    end
    if v == nil then
        v = true
    end
    if not node.__isGray__ then
        node.__isGray__ = false
    end
    if v == node.__isGray__ then
        return
    end
    if v then
        if DisplayUtil.canGray(node) then
        --调用C++的setGray方法
            setGray(tolua.cast(node, "cocos2d::Node"))
            --
            -- local glProgram = node:getGLProgram()
            -- node:setGLProgram(glProgram)
            -- node:getGLProgram():bindAttribLocation(cc.ATTRIBUTE_NAME_POSITION, cc.VERTEX_ATTRIB_POSITION)
            -- node:getGLProgram():bindAttribLocation(cc.ATTRIBUTE_NAME_COLOR, cc.VERTEX_ATTRIB_COLOR)
            -- node:getGLProgram():bindAttribLocation(cc.ATTRIBUTE_NAME_TEX_COORD, cc.VERTEX_ATTRIB_TEX_COORDS)
            --不知道为什么下面2行一定要写
            node:getGLProgram():link()
            node:getGLProgram():updateUniforms()
        end
        --children
        local children = node:getChildren()
        if children and table.nums(children) > 0 then
            --遍历子对象设置
            for i,v in ipairs(children) do
                if DisplayUtil.canGray(v) then
                    DisplayUtil.setGray(v)
                end
            end
        end
    else
        DisplayUtil.removeGray(node)
    end
    node.__isGray__ = v
end
--取消灰化
function DisplayUtil.removeGray(node)
    if type(node) ~= "userdata" then
        printError("node must be a userdata")
        return
    end
    if not node.__isGray__ then
        return
    end
    if DisplayUtil.canGray(node) then
        local glProgram = cc.GLProgramCache:getInstance():getGLProgram(
            "ShaderPositionTextureColor_noMVP")
        node:setGLProgram(glProgram)
        -- glProgram:bindAttribLocation(cc.ATTRIBUTE_NAME_POSITION, cc.VERTEX_ATTRIB_POSITION)
        -- glProgram:bindAttribLocation(cc.ATTRIBUTE_NAME_COLOR, cc.VERTEX_ATTRIB_COLOR)
        -- glProgram:bindAttribLocation(cc.ATTRIBUTE_NAME_TEX_COORD, cc.VERTEX_ATTRIB_TEX_COORDS)
        --不知道为什么下面2行不能写，写了会出问题
        -- glProgram:link()
        -- glProgram:updateUniforms()
    end
    --children
    local children = node:getChildren()
    if children and table.nums(children) > 0 then
        --遍历子对象设置
        for i,v in ipairs(children) do
            if DisplayUtil.canGray(v) then
                DisplayUtil.removeGray(v)
            end
        end
    end
    node.__isGray__ = false
end
*/