#ifndef __new_guide__GuideLayer__
#define __new_guide__GuideLayer__
#include "cocos2d.h"
using namespace cocos2d;

class GuideLayer : public cocos2d::CCLayer
{
private:
    CCSprite* mCircle;
    CCDrawNode *mStencil;
    CCRect m_obRect;
    CCDictionary* m_pMsgDictionary;
public:
    virtual bool init();
    virtual void registerWithTouchDispatcher();
    void refreshRect(CCPoint pos,CCRect rect, int pType);
    bool ccTouchBegan( CCTouch* pTouch, CCEvent* pEvent );
    CCString* getGuideMsgByType(int pType);
    void setGuideVisible(bool isVisible);
    CREATE_FUNC(GuideLayer);
};

#endif /* defined(__new_guide__GuideLayer__) */

// http://www.tuicool.com/articles/iUrA7f
// 问题描述：

// 　　CCClippingNode在Windows下显示正常，能够正常裁剪，但移植真机后，iOS系统下却无法正常裁剪；

// 解决办法：

// 　　使用cocos2dx建立的默认工程，是不开启Stencil Buffer的，需要自己手动开启；

// 　　开启办法：打开AppController.mm，将初始化EAGLView的代码里的GL_DEPTH_COMPONENT16改成GL_DEPTH24_STENCIL8_OES即可。