#ifndef __DRAGGABLE_NODE_H__
#define __DRAGGABLE_NODE_H__

#include "cocos2d.h"

namespace foo {

class DraggableNode : public cocos2d::CCLayer {

public:
    DraggableNode();
    virtual ~DraggableNode();

    static DraggableNode* node(void);

    virtual void registerWithTouchDispatcher(void);

    virtual void visit(void);

    virtual bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
    virtual void ccTouchCancelled(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);

private:
    void _tryFireDragDropped(cocos2d::CCTouch* pTouch);

private:
    bool mDragging;
    cocos2d::CCPoint mPos;
    cocos2d::CCPoint mOff;

};

}

#endif // __DRAGGABLE_NODE_H__