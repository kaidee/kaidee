#include "DraggableNode.h"

namespace foo {

DraggableNode::DraggableNode() : mDragging(false) {
}

DraggableNode::~DraggableNode() {
}

DraggableNode* DraggableNode::node(void) {
    DraggableNode* pRet = new DraggableNode();
    if(pRet && pRet->init()) {
        pRet->setIsTouchEnabled(true);
        pRet->autorelease();
        return pRet;
    } else {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

void DraggableNode::registerWithTouchDispatcher(void) {
    cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, RTP_DRAGGABLE_NODE, true);
}

void DraggableNode::visit(void) {
    if(!mDragging) {
        cocos2d::CCLayer::visit();

        return;
    }

    kmGLPushMatrix();
    kmGLTranslatef(mPos.x - mOff.x, mPos.y - mOff.y, 0.0f);
    cocos2d::CCLayer::visit();
    kmGLPopMatrix();
}

bool DraggableNode::ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent) {
    if(!m_bIsVisible || !getRichEnabled())
        return false;

    cocos2d::CCPoint tp = convertTouchToNodeSpace(pTouch);

    if(cocos2d::CCRect::CCRectContainsPoint(cocos2d::CCRect(0.0f, 0.0f, getContentSize().width, getContentSize().height), tp)) {
        mOff = cocos2d::CCDirector::sharedDirector()->convertToGL(pTouch->locationInView());
        mOff = convertToNodeSpace(mOff);

        if(!pTouch->getIsFake() && m_pScriptHandlerEntry) {
            excuteScriptTouchHandler(cocos2d::CCTOUCHBEGAN, pTouch);
        }

        return true;
    } else {
        return false;
    }
}

void DraggableNode::ccTouchMoved(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent) {
    mDragging = true;
    mPos = cocos2d::CCDirector::sharedDirector()->convertToGL(pTouch->locationInView());
    mPos = convertToNodeSpace(mPos);

    cocos2d::CCLayer::ccTouchMoved(pTouch, pEvent);
}

void DraggableNode::ccTouchEnded(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent) {
    _tryFireDragDropped(pTouch);

    cocos2d::CCLayer::ccTouchEnded(pTouch, pEvent);

    mDragging = false;
}

void DraggableNode::ccTouchCancelled(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent) {
    cocos2d::CCLayer::ccTouchCancelled(pTouch, pEvent);

    mDragging = false;
}

void DraggableNode::_tryFireDragDropped(cocos2d::CCTouch* pTouch) {
    cocos2d::CCPoint tp = getParent() ?
        getParent()->convertTouchToNodeSpace(pTouch) : convertTouchToNodeSpace(pTouch);

    bool contains = cocos2d::CCRect::CCRectContainsPoint(
        cocos2d::CCRect(0.0f, 0.0f, getContentSize().width, getContentSize().height),
        tp
    );

    if(contains) return;

    cocos2d::CCPoint pos = pTouch->locationInView();
    int id = 0;
    cocos2d::CCEGLView::sharedOpenGLView().handleTouchesBegin(1, &id, &pos.x, &pos.y, true);
    cocos2d::CCEGLView::sharedOpenGLView().handleTouchesDrop(1, &id, &pos.x, &pos.y);
}

}