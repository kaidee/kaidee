struct transformValues_ 拥有如下几个参数
 
CCPoint pos; // position x and y 位置
CCPoint scale; // scale x and y 放大缩小
float rotation; 旋转
CCPoint skew; // skew x and y 倾斜
CCPoint ap; // anchor point in pixels 锚点
bool visible; 是否可见
 
Public Member Functions
virtual GLubyte getOpacity (void)
  getOpacity 获取透明度
virtual void setOpacity (GLubyte var)
  setOpacity 设置透明度
virtual const ccColor3B & getColor (void)
  getColor 获取颜色
virtual void setColor (const ccColor3B &var)
  setColor 设置颜色
virtual void draw (void) 绘制 可以覆盖转换为自己的绘制方式
  Override this method to draw your own node.
bool isDirty (void) 精灵是否需要更新在自己所在在的位图上
  whether or not the Sprite needs to be updated in the Atlas
void setDirty (bool bDirty) 设置是否需要更新
  make the Sprite to be updated in the Atlas.
ccV3F_C4B_T2F_Quad getQuad (void) 获取文本位置 顶点位置 和颜色
  get the quad (tex coords, vertex coords and color) information
bool isTextureRectRotated (void) 是否旋转
  returns whether or not the texture rectangle is rotated
unsigned int getAtlasIndex (void) 获取所在图片集ID
  Set the index used on the TextureAtlas.
void setAtlasIndex (unsigned int uAtlasIndex) 设置说属图片集ID
  Set the index used on the TextureAtlas.
const CCRect & getTextureRect (void) 返回精灵大小
  returns the rect of the CCSprite in points
bool isUsesBatchNode (void) 判断精灵是否在 CCSpriteBatchNode 渲染
  whether or not the Sprite is rendered using a CCSpriteBatchNode
void setUsesSpriteBatchNode (bool bUsesSpriteBatchNode) 设置该精灵对象在 CCSpriteBatchNode 中被渲染
  make the Sprite been rendered using a CCSpriteBatchNode
CCTextureAtlas * getTextureAtlas (void) 获取设置地图纹理
void setTextureAtlas (CCTextureAtlas *pobTextureAtlas)
CCSpriteBatchNode * getSpriteBatchNode (void) 设置和获取一批精灵集
void setSpriteBatchNode (CCSpriteBatchNode *pobSpriteBatchNode)
ccHonorParentTransform getHonorParentTransform (void) 是否根据其父的矩阵变化而改变
  whether or not to transform according to its parent transformations.
void setHonorParentTransform (ccHonorParentTransform eHonorParentTransform)
  whether or not to transform according to its parent transformations.
const CCPoint & getOffsetPositionInPixels (void) 获取便宜位置（象素）
  Get offset position of the sprite.
ccBlendFunc getBlendFunc (void) 设置获取混合方法
  conforms to CCTextureProtocol protocol
void setBlendFunc (ccBlendFunc blendFunc)
  conforms to CCTextureProtocol protocol
  CCSprite (void)
virtual ~CCSprite (void)
virtual bool init (void)
virtual void removeChild (CCNode *pChild, bool bCleanup) 移除孩子 是否清理action
  Removes a child from the container.
virtual void removeAllChildrenWithCleanup (bool bCleanup)
  Removes all children from the container and do a cleanup all running actions depending on the cleanup parameter.
virtual void reorderChild (CCNode *pChild, int zOrder) 移除孩子由zOrder决定
  Reorders a child according to a new z value.
virtual void addChild (CCNode *pChild)
  Adds a child to the container with z-order as 0.
virtual void addChild (CCNode *pChild, int zOrder)
  Adds a child to the container with a z-order If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
virtual void addChild (CCNode *pChild, int zOrder, int tag)
  Adds a child to the container with z order and tag If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
virtual void setDirtyRecursively (bool bValue)
virtual void setPosition (const CCPoint &pos) 设置位置
  setPosition
virtual void setPositionInPixels (const CCPoint &pos) 设置位置（象素）
  setPositionInPixels
virtual void setRotation (float fRotation) 设置旋转
  setRotation
virtual void setSkewX (float sx) 设置倾斜XY
  setSkewX
virtual void setSkewY (float sy)
  setSkewY
virtual void setScaleX (float fScaleX) 设置放大缩小
  setScaleX
virtual void setScaleY (float fScaleY)
  setScaleY
virtual void setScale (float fScale)
  The scale factor of the node.
virtual void setVertexZ (float fVertexZ) 设置Z轴顶点坐标
  setVertexZ
virtual void setAnchorPoint (const CCPoint &anchor) 设置锚点坐标
  setAnchorPoint
virtual void setIsRelativeAnchorPoint (bool bRelative) 设置是否相对锚点坐标
  setIsRelativeAnchorPoint
virtual void setIsVisible (bool bVisible) 设置是否可见
  setIsVisible
void setFlipX (bool bFlipX) 设置X翻转Y翻转
void setFlipY (bool bFlipY)
bool isFlipX (void)
  whether or not the sprite is flipped horizontally.
bool isFlipY (void)
  whether or not the sprite is flipped vertically.
void updateColor (void)
virtual void setIsOpacityModifyRGB (bool bValue) 设置是否RGB透明修饰
  opacity: conforms to CCRGBAProtocol protocol
virtual bool getIsOpacityModifyRGB (void)
  returns whether or not the opacity will be applied using glColor(R,G,B,opacity) or glColor(opacity, opacity, opacity, opacity);
virtual void setTexture (CCTexture2D *texture) 设置纹理
virtual CCTexture2D * getTexture (void)
bool initWithTexture (CCTexture2D *pTexture) 初始化精灵精灵通过纹理
  Initializes an sprite with a texture.
bool initWithTexture (CCTexture2D *pTexture, const CCRect &rect) 初始化sprite通过纹理和矩形
  Initializes an sprite with a texture and a rect.
bool initWithSpriteFrame (CCSpriteFrame *pSpriteFrame)初始化精灵通过精灵帧
bool initWithSpriteFrameName (const char *pszSpriteFrameName)
  Initializes an sprite with an sprite frame name. 初始化精灵通过一个精灵帧名称
bool initWithFile (const char *pszFilename)初始化精灵通过一个图片地址
  Initializes an sprite with an image filename.
bool initWithFile (const char *pszFilename, const CCRect &rect)
  Initializes an sprite with an image filename, and a rect. 初始化精灵通过一个图片地址和矩形
bool initWithBatchNode (CCSpriteBatchNode *batchNode, const CCRect &rect)初始化精灵通过精灵集合和一个矩形
  Initializes an sprite with an CCSpriteBatchNode and a rect in points.
bool initWithBatchNodeRectInPixels (CCSpriteBatchNode *batchNode, const CCRect &rect)
  Initializes an sprite with an CCSpriteBatchNode and a rect in pixels.
void updateTransform (void) 更新矩阵
  updates the quad according the the rotation, position, scale values.
void useSelfRender (void)使用自身渲染
  tell the sprite to use self-render.
void setTextureRect (const CCRect &rect)更新精灵在纹理上的矩形
  updates the texture rect of the CCSprite in points.
void setTextureRectInPixels (const CCRect &rect, bool rotated, const CCSize &size)
  updates the texture rect, rectRotated and untrimmed size of the CCSprite in pixels
void useBatchNode (CCSpriteBatchNode *batchNode)使用精灵集
  tell the sprite to use batch node render.
void setDisplayFrame (CCSpriteFrame *pNewFrame)设置显示帧
  sets a new display frame to the CCSprite.
bool isFrameDisplayed (CCSpriteFrame *pFrame)判断当前显示帧
  returns whether or not a CCSpriteFrame is being displayed
CCSpriteFrame * displayedFrame (void)返回当前显示帧
  returns the current displayed frame.
void setDisplayFrameWithAnimationName (const char *animationName, int frameIndex) 设置动画并设置显示索引
  changes the display frame with animation name and index.
Static Public Member Functions
static CCSprite * spriteWithTexture (CCTexture2D *pTexture)
  Creates an sprite with a texture. 通过纹理创建一个精灵
static CCSprite * spriteWithTexture (CCTexture2D *pTexture, const CCRect &rect)
  Creates an sprite with a texture and a rect. 通过纹理和矩形创建一个精灵
static CCSprite * spriteWithTexture (CCTexture2D *pTexture, const CCRect &rect, const CCPoint &offset)
  Creates an sprite with a texture, a rect and offset. 通过纹理和偏移矩形创建一个精灵
static CCSprite * spriteWithSpriteFrame (CCSpriteFrame *pSpriteFrame)
  Creates an sprite with an sprite frame. 通过帧创建一个精灵
static CCSprite * spriteWithSpriteFrameName (const char *pszSpriteFrameName)
  Creates an sprite with an sprite frame name. 通过帧名称创建一个精灵
static CCSprite * spriteWithFile (const char *pszFileName)
  Creates an sprite with an image filename. 通过图片创建一个精灵
static CCSprite * spriteWithFile (const char *pszFileName, const CCRect &rect)
  Creates an sprite with an image filename and a rect. 通过图片和矩形创建一个精灵
static CCSprite * spriteWithBatchNode (CCSpriteBatchNode *batchNode, const CCRect &rect)
  Creates an sprite with an CCBatchNode and a rect. 通过精灵集和矩形创建一个精灵
Protected Member Functions
void updateTextureCoords (const CCRect &rect) 更新纹理位置 矩形
void updateBlendFunc (void) 更新混合方法
void getTransformValues (struct transformValues_ *tv) 获取矩阵参数
Protected Attributes
GLubyte m_nOpacity 透明
  Opacity: conforms to CCRGBAProtocol protocol.
ccColor3B m_sColor 颜色
  Color: conforms with CCRGBAProtocol protocol.
CCTextureAtlas * m_pobTextureAtlas 地图集
unsigned int m_uAtlasIndex 地图集索引
CCSpriteBatchNode * m_pobBatchNode 精灵集
ccHonorParentTransform m_eHonorParentTransform 是否随父矩阵变换
bool m_bDirty 是否更新
bool m_bRecursiveDirty ？
bool m_bHasChildren 是否有子对象
ccBlendFunc m_sBlendFunc 是否混合方法
CCTexture2D * m_pobTexture 纹理
bool m_bUsesBatchNode 是否使用精灵集
CCRect m_obRect 矩形
CCRect m_obRectInPixels
bool m_bRectRotated 是否矩形旋转
CCPoint m_obOffsetPositionInPixels 偏移
CCPoint m_obUnflippedOffsetPositionFromCenter
ccV3F_C4B_T2F_Quad m_sQuad QUAD
ccColor3B m_sColorUnmodified 原始颜色
bool m_bOpacityModifyRGB 是否透明修饰
bool m_bFlipX 是否X翻转
bool m_bFlipY 是否Y翻转