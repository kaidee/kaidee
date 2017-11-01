bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    ize visibleSize = Director::getInstance()->getVisibleSize();
    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setAnchorPoint(Point(0.5, 0.5));
    sprite->setPosition(Point(visibleSize.width / 3, visibleSize.height / 3));
    this->addChild(sprite);
    graySprite(sprite);
    return true;
}
 
void HelloWorld::graySprite(Sprite * sprite)
{
    if(sprite)
    {
        GLProgram * p = new GLProgram();
        p->initWithFilenames("gray.vsh", "gray.fsh");
        p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
        p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
        p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
        p->link();
        p->updateUniforms();
        sprite->setShaderProgram(p);
    }
}