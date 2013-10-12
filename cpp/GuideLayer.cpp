#include "GuideLayer.h"
#include "CCommon.h"

bool GuideLayer::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
   setTouchEnabled(true);
    m_pMsgDictionary = readDictionaryFromPlist("guide_msg.plist", "");
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    CCClippingNode* pClip=CCClippingNode::create();
    pClip->setInverted(true);
    addChild(pClip);
    
    CCLayerColor* pColor=CCLayerColor::create(ccc4(0,0,0,180));
    pClip->addChild(pColor);
    
    
    //添加圆和手的图片

    mCircle=CCSprite::create("guide_circle.png");
    float fRadius=mCircle->getContentSize().width*0.5;//圆的半径
    mCircle->setPosition(ccp(fRadius, fRadius));
    mCircle->runAction(CCRepeatForever::create(CCSequence::createWithTwoActions(CCScaleBy::create(0.05f, 0.95f),
                                                                                CCScaleTo::create(0.125f, 1))));
    addChild(mCircle);
        
    //绘制圆形区域
    static ccColor4F green = {1, 1, 1, 1};//顶点颜色,这里我们没有实质上没有绘制,所以看不出颜色
  
    const int nCount=100;//圆形其实可以看做正多边形,我们这里用正100边型来模拟园
    const float coef = 2.0f * (float)M_PI/nCount;//计算每两个相邻顶点与中心的夹角
    static CCPoint circle[nCount];//顶点数组
    for(unsigned int i = 0;i <nCount; i++) {
        float rads = i*coef;//弧度
        circle[i].x = fRadius * cosf(rads);//对应顶点的x
        circle[i].y = fRadius * sinf(rads);//对应顶点的y
    }
    mStencil=CCDrawNode::create();
    mStencil->drawPolygon(circle, nCount, green, 0, green);//绘制这个多边形!
    //动起来
    mStencil->runAction(CCRepeatForever::create(CCSequence::createWithTwoActions(CCScaleBy::create(0.05f, 0.95f),
                                                                                 CCScaleTo::create(0.125f, 1))));
    mStencil->setPosition(ccp(mCircle->getPosition().x, mCircle->getPosition().y));
    //设这模板
    pClip->setStencil(mStencil);
  
    m_obRect=CCRectMake(
                               mCircle->getPosition().x-fRadius,
                               mCircle->getPosition().y-fRadius,
                               fRadius,
                               fRadius);
    return true;
}

void GuideLayer::registerWithTouchDispatcher()
{
    //使用-128和CCMenu优先级相同,并且吞掉事件true//
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -130, true);
    CCLayer::registerWithTouchDispatcher();
}

void GuideLayer::refreshRect(CCPoint pos,CCRect rect, int pType)
{
    
    m_obRect = rect;
    float fRadius=mCircle->getContentSize().width*0.5;
    float scale = rect.size.width/fRadius;
    mCircle->setScale(scale);
    mCircle->setPosition(pos);
    
    mStencil->setPosition(ccp(mCircle->getPosition().x, mCircle->getPosition().y));
    mStencil->setScale(scale);
}

bool GuideLayer::ccTouchBegan( CCTouch* pTouch, CCEvent* pEvent )
{
    //得到触摸位置
    CCPoint touchPoint = pTouch->getLocation();
   
    //判断点是否在矩形中
    if (m_obRect.containsPoint(touchPoint))
    {
        return false;
    }
    return true;
}

void GuideLayer::setGuideVisible(bool isVisible)
{
    this->setVisible(isVisible);
    setTouchEnabled(isVisible);
}

CCString* GuideLayer::getGuideMsgByType(int pType)
{
    char typeStr[10];
    sprintf(typeStr, "%d", pType);
    CCString* msg = (CCString*)m_pMsgDictionary->objectForKey(typeStr);
    return msg;
}

//从plist里面随机读取字符串
CCString* randomStrFromPlist(const char *pszFilename,int startNum,int endNum)
{
    srand(get_now_time());
    std::string nameFile = CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile(pszFilename, "zh-Hans.lproj");
    CCDictionary * nameData = CCDictionary::createWithContentsOfFileThreadSafe(nameFile.c_str());
    int randomKey = RandExt(startNum, endNum);
    std::ostringstream randomNameOss;
    randomNameOss<<randomKey;
    CCString* nameStr = (CCString*)nameData->objectForKey(randomNameOss.str());
    nameData->autorelease();
    return nameStr;
}

//从plist里面读取dictionary
CCDictionary* readDictionaryFromPlist(const char *pszFilename, const char* pszFileFolder)
{
    std::string fileName = CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile(pszFilename, pszFileFolder);
    CCDictionary* dictionary = CCDictionary::createWithContentsOfFileThreadSafe(fileName.c_str());
    return dictionary;
}

CCRenderTexture* createStroke(cocos2d::CCLabelTTF *label, float size, cocos2d::ccColor3B color)
{
    float x=label->getTexture()->getContentSize().width+size*2;
    float y=label->getTexture()->getContentSize().height+size*2;
    CCRenderTexture *rt=CCRenderTexture::create(x, y);
    CCPoint originalPos=label->getPosition();
    ccColor3B originalColor=label->getColor();
    label->setColor(color);
    ccBlendFunc originalBlend=label->getBlendFunc();
    label->setBlendFunc((ccBlendFunc){GL_SRC_ALPHA,GL_ONE});
    CCPoint center=ccp(x/2+size, y/2+size);
    rt->begin();
    for (int i=0; i<360; i+=15) {
        float _x=center.x+sin(CC_DEGREES_TO_RADIANS(i))*size;
        float _y=center.y+cos(CC_DEGREES_TO_RADIANS(i))*size;
        
        label->setPosition(ccp(_x, _y));
        label->visit();
        
    }
    rt->end();
    label->setPosition(originalPos);
    label->setColor(originalColor);
    label->setBlendFunc(originalBlend);
    float rtX=originalPos.x-size;
    float rtY=originalPos.y-size;
    
    rt->setPosition(ccp(rtX, rtY));
    
    return rt;
}

#include <sys/sysctl.h>
#include <mach/mach.h>
#include <mach/mach_host.h>
double availableMemory()
{
    vm_statistics_data_t vmStats;
    mach_msg_type_number_t infoCount = HOST_VM_INFO_COUNT;
    kern_return_t kernReturn
    = host_statistics(mach_host_self(),
                      HOST_VM_INFO,
                      (host_info_t)&vmStats,
                      &infoCount);
    if(kernReturn != KERN_SUCCESS) {
        return 0;
    }
    return ((vm_page_size * vmStats.free_count) / 1024.0) / 1024.0;
}

double memoryInfo()
{
    struct task_basic_info info;
    mach_msg_type_number_t size = sizeof(info);
    kern_return_t kerr = task_info(mach_task_self(), TASK_BASIC_INFO, (task_info_t)&info, &size);
    return (kerr == KERN_SUCCESS) ? (info.resident_size/1024.0)/1024.0 : 0; // size in
//    vm_statistics_data_t vmStats;
//    mach_msg_type_number_t infoCount = HOST_VM_INFO_COUNT;
//    kern_return_t kernReturn
//    = host_statistics(mach_host_self(),
//                      HOST_VM_INFO,
//                      (host_info_t)&vmStats,
//                      &infoCount);
//    if(kernReturn != KERN_SUCCESS) {
//        return 0;
//    }
//    return ((vm_page_size * (vmStats.active_count + vmStats.inactive_count + vmStats.wire_count) ) / 1024.0) / 1024.0;
}

void CMainScene::showGuideLayer(CCNode* node, GUIDE_TAG msgType)  
{  
    int stepType = USER_DEFAULT_INT(GUIDE_CUR_STEP);  
    if (stepType == msgType) {  
        SAVE_USER_DEFAULT_INT(GUIDE_CUR_STEP, stepType+1);  
        CCPoint pos = node->getParent()->convertToWorldSpace(node->getPosition());  
        CCRect rect = CCRectMake(pos.x, pos.y, node->getContentSize().width, node->getContentSize().height);  
        m_pGuideLayer->setGuideVisible(true);  
        m_pGuideLayer->refreshRect(pos, rect, msgType);  
    }  
}