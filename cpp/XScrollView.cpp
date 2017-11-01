#include "XScrollView.h"
#include "actions/CCActionInterval.h"
#include "actions/CCActionTween.h"
#include "actions/CCActionInstant.h"
#include "support/CCPointExtension.h"
#include "touch_dispatcher/CCTouchDispatcher.h"
#include "effects/CCGrid.h"
#include "CCDirector.h"
#include "kazmath/GL/matrix.h"
#include "touch_dispatcher/CCTouch.h"
#include "CCEGLView.h"

#define SCROLL_DEACCEL_RATE  0.95f
#define SCROLL_DEACCEL_DIST  1.0f
#define BOUNCE_DURATION      0.15f
#define INSET_RATIO          0.2f

XScrollView::XScrollView()
: m_fZoomScale(0.0f)
, m_fMinZoomScale(0.0f)
, m_fMaxZoomScale(0.0f)
, m_pDelegate(NULL)
, m_bDragging(false)
, m_bBounceable(false)
, m_eDirection(en_Scrollview_Direction_Both)
, m_bClippingToBounds(false)
, m_pContainer(NULL)
, m_bTouchMoved(false)
, m_fTouchLength(0.0f)
, m_pTouches(NULL)
, m_fMinScale(0.0f)
, m_fMaxScale(0.0f)
, m_iCellSpace(0)
, m_bRoll(true)
,m_bInitContainerSize(false)
{
}

XScrollView::~XScrollView()
{
	m_pTouches->release();
}

XScrollView* XScrollView::viewWithViewSize(CCSize size, CCNode* container/* = NULL*/)
{
	return XScrollView::Create(size, container);
}

XScrollView* XScrollView::Create(CCSize size, CCNode* container/* = NULL*/)
{
	XScrollView* pRet = new XScrollView();
	if (pRet && pRet->initWithViewSize(size, container))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

XScrollView* XScrollView::node()
{
	return XScrollView::Create();
}

XScrollView* XScrollView::Create()
{
	XScrollView* pRet = new XScrollView();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

void XScrollView::SetWindowPos(CCRect rect)
{
	XWindow::SetWindowPos(rect);
	if (m_bInitContainerSize)
	{
		m_pContainer->setPosition(ccp(0.0f, 0.0f));
		m_pContainer->setContentSize(rect.size);
	}
	this->setViewSize(rect.size);
}

bool XScrollView::initWithViewSize(CCSize size, CCNode *container/* = NULL*/)
{
	m_pContainer = (XWindow*)container;
	if (m_pContainer == NULL)
	{
		m_pContainer = new XWindow();
		m_pContainer->autorelease();
		m_pContainer->SetWndTraits(XWT_ENABLED,TRUE);
		m_pContainer->ignoreAnchorPointForPosition(false);
		m_pContainer->setAnchorPoint(ccp(0.0f, 0.0f));
	}
	this->setViewSize(size);
	setTouchEnabled(TRUE);
	m_pTouches = new CCArray();
	m_pDelegate = NULL;
	m_bBounceable = true;
	m_bClippingToBounds = true;
	m_eDirection  = en_Scrollview_Direction_Both;
	m_pContainer->setPosition(ccp(0.0f, 0.0f));
	m_pContainer->setContentSize(size);
	m_fTouchLength = 0.0f;
	this->addChild(m_pContainer);
	m_fMinScale = m_fMaxScale = 1.0f;
	return true;
}

bool XScrollView::init()
{
	return this->initWithViewSize(CCSizeMake(200, 200), NULL);
}

bool XScrollView::isNodeVisible(CCNode* node)
{
	const CCPoint offset = this->getContentOffset();
	const CCSize  size   = this->getViewSize();
	const float   scale  = this->getZoomScale();
    
	CCRect viewRect;
    
	viewRect = CCRectMake(-offset.x/scale, -offset.y/scale, size.width/scale, size.height/scale); 
    
	return viewRect.intersectsRect(node->boundingBox());
}

void XScrollView::pause(CCObject* sender)
{
	m_pContainer->pauseSchedulerAndActions();

	CCObject* pObj = NULL;
	CCArray* pChildren = m_pContainer->getChildren();

	CCARRAY_FOREACH(pChildren, pObj)
	{
		CCNode* pChild = (CCNode*)pObj;
		pChild->pauseSchedulerAndActions();
	}
}

void XScrollView::resume(CCObject* sender)
{
	CCObject* pObj = NULL;
	CCArray* pChildren = m_pContainer->getChildren();

	CCARRAY_FOREACH(pChildren, pObj)
	{
		CCNode* pChild = (CCNode*)pObj;
		pChild->resumeSchedulerAndActions();
	}

	m_pContainer->resumeSchedulerAndActions();
}

void XScrollView::setTouchEnabled(BOOL e)
{
	SetWndTraits(XWT_ENABLED,e);
	if (!e)
	{
		m_bDragging = false;
		m_bTouchMoved = false;
		m_pTouches->removeAllObjects();
	}
}

void XScrollView::setContentOffset(CCPoint offset, bool animated/* = false*/)
{
	if (animated)
	{ 
		//动画移动
		this->setContentOffsetInDuration(offset, BOUNCE_DURATION);
	} 
	else
	{ 
		if (!m_bBounceable)
		{	//限制移动最大值
			const CCPoint minOffset = this->minContainerOffset();
			const CCPoint maxOffset = this->maxContainerOffset();
			offset.x = MAX(minOffset.x, MIN(maxOffset.x, offset.x));
			offset.y = MAX(minOffset.y, MIN(maxOffset.y, offset.y));
		}
		m_pContainer->setPosition(offset); 
		if (m_pDelegate != NULL)
		{
			m_pDelegate->scrollViewDidScroll(this);
		}
	}
}

void XScrollView::setContentOffsetInDuration(CCPoint offset, float dt)
{
	CCFiniteTimeAction *scroll, *expire;
	scroll = CCMoveTo::create(dt, offset);
	expire = CCCallFuncN::create(this, callfuncN_selector(XScrollView::stoppedAnimatedScroll));
	m_pContainer->runAction(CCSequence::create(scroll, expire, NULL));
	this->schedule(schedule_selector(XScrollView::performedAnimatedScroll));
}

CCPoint XScrollView::getContentOffset()
{
	return m_pContainer->getPosition();
}

void XScrollView::setZoomScale(float s)
{
	if (m_pContainer->getScale() != s)
	{
		CCPoint oldCenter, newCenter;
		CCPoint center;
        
		if (m_fTouchLength == 0.0f) 
		{
			center = ccp(m_tViewSize.width*0.5f, m_tViewSize.height*0.5f);
			center = this->convertToWorldSpace(center);
		}
		else
		{
			center = m_tTouchPoint;
		}
        
		oldCenter = m_pContainer->convertToNodeSpace(center);
		m_pContainer->setScale(MAX(m_fMinScale, MIN(m_fMaxScale, s)));
		newCenter = m_pContainer->convertToWorldSpace(oldCenter);
        
		const CCPoint offset = ccpSub(center, newCenter);
		if (m_pDelegate != NULL)
		{
			m_pDelegate->scrollViewDidZoom(this);
		}
		this->setContentOffset(ccpAdd(m_pContainer->getPosition(),offset));
	}
}

float XScrollView::getZoomScale()
{
	return m_pContainer->getScale();
}

void XScrollView::setZoomScale(float s, bool animated)
{
	if (animated)
	{
		this->setZoomScaleInDuration(s, BOUNCE_DURATION);
	}
	else
	{
		this->setZoomScale(s);
	}
}

void XScrollView::setZoomScaleInDuration(float s, float dt)
{
	if (dt > 0)
	{
		if (m_pContainer->getScale() != s)
		{
			CCActionTween *scaleAction;
			scaleAction = CCActionTween::create(dt, "zoomScale", m_pContainer->getScale(), s);
			this->runAction(scaleAction);
		}
	}
	else
	{
		this->setZoomScale(s);
	}
}

void XScrollView::setViewSize(CCSize size)
{
	m_tViewSize = size;
}

CCNode * XScrollView::getContainer()
{
	return this->m_pContainer;
}

void XScrollView::setContainer(CCNode * pContainer)
{
	this->removeAllChildrenWithCleanup(true);

	if (!pContainer) return;

	this->m_pContainer = (XWindow*)pContainer;

	this->m_pContainer->ignoreAnchorPointForPosition(false);
	this->m_pContainer->setAnchorPoint(ccp(0.0f, 0.0f));

	this->addChild(this->m_pContainer);

	this->setViewSize(this->m_tViewSize);
}

void XScrollView::relocateContainer(bool animated)
{
	CCPoint oldPoint, min, max;
	float newX, newY;    
	min = this->minContainerOffset();
	max = this->maxContainerOffset();    
	oldPoint = m_pContainer->getPosition();
	newX     = oldPoint.x;
	newY     = oldPoint.y;
	if (m_eDirection == en_Scrollview_Direction_Both || m_eDirection == en_Scrollview_Direction_H)
	{
		newX     = MIN(newX, max.x);
		newX     = MAX(newX, min.x);
	}
	if (m_eDirection == en_Scrollview_Direction_Both || m_eDirection == en_Scrollview_Direction_V)
	{
		newY     = MIN(newY, max.y);
		newY     = MAX(newY, min.y);
	}
	if(m_eDirection == en_Scrollview_Direction_H)
	{
		newY = 0;
	}
	if(m_eDirection == en_Scrollview_Direction_V)
	{
		newX = 0;
	}
	if (newY != oldPoint.y || newX != oldPoint.x)
	{
		this->setContentOffset(ccp(newX, newY), animated);
	}
}

CCPoint XScrollView::maxContainerOffset()
{
	return ccp(0.0f, 0.0f);
}

CCPoint XScrollView::minContainerOffset()
{
	return ccp(m_tViewSize.width - m_pContainer->getContentSize().width, 
				m_tViewSize.height - m_pContainer->getContentSize().height);
}

void XScrollView::deaccelerateScrolling(float dt)
{
	if (m_bDragging)
	{
		this->unschedule(schedule_selector(XScrollView::deaccelerateScrolling));
		return;
	}    
	float newX, newY;
	CCPoint maxInset, minInset;    
	m_pContainer->setPosition(ccpAdd(m_pContainer->getPosition(), m_tScrollDistance));    
	if (m_bBounceable)
	{
		maxInset = m_fMaxInset;
		minInset = m_fMinInset;
	}
	else
	{
		maxInset = this->maxContainerOffset();
		minInset = this->minContainerOffset();
	}    
	//check to see if offset lies within the inset bounds
	newX     = MIN(m_pContainer->getPosition().x, maxInset.x);
	newX     = MAX(newX, minInset.x);
	newY     = MIN(m_pContainer->getPosition().y, maxInset.y);
	newY     = MAX(newY, minInset.y);
	if(m_eDirection == en_Scrollview_Direction_H)
	{
		newY = 0;
	}
	if(m_eDirection == en_Scrollview_Direction_V)
	{
		newX = 0;
	}
	m_tScrollDistance     = ccpSub(m_tScrollDistance, ccp(newX - m_pContainer->getPosition().x, newY - m_pContainer->getPosition().y));
	m_tScrollDistance     = ccpMult(m_tScrollDistance, SCROLL_DEACCEL_RATE);
	this->setContentOffset(ccp(newX,newY));
	if(m_eDirection == en_Scrollview_Direction_H)
	{
		newY = 0;
	}
	if(m_eDirection == en_Scrollview_Direction_V)
	{
		newX = 0;
	}
	if ((fabsf(m_tScrollDistance.x) <= SCROLL_DEACCEL_DIST && fabsf(m_tScrollDistance.y) <= SCROLL_DEACCEL_DIST) ||
		newX == maxInset.x || newX == minInset.x ||
		newY == maxInset.y || newY == minInset.y)
	{
		this->unschedule(schedule_selector(XScrollView::deaccelerateScrolling));
		this->relocateContainer(true);
	}
}

void XScrollView::stoppedAnimatedScroll(CCNode * node)
{
	this->unschedule(schedule_selector(XScrollView::performedAnimatedScroll));
}

void XScrollView::performedAnimatedScroll(float dt)
{
	if (m_bDragging)
	{
		this->unschedule(schedule_selector(XScrollView::performedAnimatedScroll));
		return;
	}
	if (m_pDelegate != NULL)
	{
		m_pDelegate->scrollViewDidScroll(this);
	}
}

const CCSize & XScrollView::getContentSize()
{
	return m_pContainer->getContentSize();
}

void XScrollView::setContentSize(const CCSize & size)
{
	if (this->getContainer() != NULL)
	{
		this->getContainer()->setContentSize(size);
		this->updateInset();
	}
}

void XScrollView::UpdateContenSize()
{
	CCArray* ccArray = m_pContainer->getChildren();
	if(ccArray == NULL)
	{
		return;
	}
	if(ccArray->count() == 0)
	{
		setContentSize(CCSizeMake(0,0));
		return;
	}
	CCObject* Object;
	CCARRAY_FOREACH(ccArray,Object)
	{
		CCNode* nodeChild = (CCNode*)Object;
		if(nodeChild)
		{
			CCSize size = getContentSize();
			CCSize sizeChild = nodeChild->getContentSize();
			CCPoint ptChild = nodeChild->getPosition();
			float fX = sizeChild.width + ptChild.x;
			float fY = sizeChild.height + ptChild.y;
			if(fX > size.width)
			{
				size.width += (fX - size.width);
			}
			if(fY > size.height)
			{
				size.height += (fY-size.height);
			}
			setContentSize(size);
		}
	}
}

XWindow* XScrollView::FindWindowByID(int iID)
{
	return m_pContainer->FindWindowByID(iID);
}

void XScrollView::updateInset()
{
	if (this->getContainer() != NULL)
	{
		m_fMaxInset = this->maxContainerOffset();
		m_fMaxInset = ccp(m_fMaxInset.x + m_tViewSize.width * INSET_RATIO * m_pContainer->getScale(),
			m_fMaxInset.y + m_tViewSize.height * INSET_RATIO);
		m_fMinInset = this->minContainerOffset();
		m_fMinInset = ccp(m_fMinInset.x - m_tViewSize.width * INSET_RATIO * m_pContainer->getScale(),
			m_fMinInset.y - m_tViewSize.height * INSET_RATIO);
	}
}

/**
	* make sure all children go to the container
	*/
void XScrollView::addChild(CCNode * child, int zOrder, int tag)
{
	child->ignoreAnchorPointForPosition(false);
	child->setAnchorPoint(ccp(0.0f, 0.0f));
	if (m_pContainer != child) 
	{
		m_pContainer->SetWndTraits(XWT_ENABLED,TRUE);
		m_pContainer->addChild(child, zOrder, tag);
	}
	else 
	{
		XWindow::addChild(child, zOrder, tag);
	}
}

void XScrollView::addChild(CCNode * child, int zOrder)
{
	this->addChild(child, zOrder, child->getTag());
}

void XScrollView::addChild(CCNode * child)
{
	this->addChild(child, child->getZOrder(), child->getTag());
}

/**
	* clip this view so that outside of the visible bounds can be hidden.
	*/
void XScrollView::beforeDraw()
{
	if (m_bClippingToBounds) 
	{
		CCPoint screenPos = this->convertToWorldSpace(ccp(0,0));
		glEnable(GL_SCISSOR_TEST);
		float s = this->getScale();
		CCEGLView::sharedOpenGLView()->setScissorInPoints(
			screenPos.x*s,
			screenPos.y*s,
			m_tViewSize.width*WND_SCALE_X,
			m_tViewSize.height*WND_SCALE_Y);		
	}
}

/**
	* retract what's done in beforeDraw so that there's no side effect to
	* other nodes.
	*/
void XScrollView::afterDraw()
{
	if (m_bClippingToBounds)
	{
		glDisable(GL_SCISSOR_TEST);
	}
}

void XScrollView::visit()
{
	// quick return if not visible
	if (!isVisible())
	{
		return;
	}
	kmGLPushMatrix();	
	if (m_pGrid && m_pGrid->isActive())
	{
		m_pGrid->beforeDraw();
		this->transformAncestors();
	}

	this->transform();
	this->beforeDraw();

	if(m_pChildren)
	{
		ccArray *arrayData = m_pChildren->data;
		unsigned int i=0;
		
		// draw children zOrder < 0
		for( ; i < arrayData->num; i++ )
		{
			CCNode *child =  (CCNode*)arrayData->arr[i];
			if ( child->getZOrder() < 0 )
			{
				child->visit();
			}
			else
			{
				break;
			}
		}	
		this->draw();	
		// draw children zOrder >= 0
		for( ; i < arrayData->num; i++ )
		{
			CCNode* child = (CCNode*)arrayData->arr[i];
			child->visit();
		}       
	}
	else
	{
		this->draw();
	}

	this->afterDraw();
	if ( m_pGrid && m_pGrid->isActive())
	{
		m_pGrid->afterDraw(this);
	}

	kmGLPopMatrix();
}

bool XScrollView::OnTouchBegan(CCTouch* touch, CCEvent* event)
{
	if (this->isVisible() == false || IsEnabled() == FALSE)
	{
		return true;
	}
	if (!m_bRoll)
	{
		return m_pContainer->OnTouchBegan(touch,event);
	}
	m_pointStar = convertTouchToNodeSpace(touch);
	CCRect frame;
	//world
	CCNode* nodeParent = getParent();
	if(nodeParent)
	{
		frame = CCRectMake(
			nodeParent->getPosition().x + this->getPosition().x,
			nodeParent->getPosition().y + this->getPosition().y,
			m_tViewSize.width,
			m_tViewSize.height);
	}
	else
	{
			frame = CCRectMake(this->getPosition().x, this->getPosition().y, m_tViewSize.width, m_tViewSize.height);
	} 
		CCPoint ptTouch = ccpAdd(convertTouchToNodeSpace(touch), ccp(frame.origin.x, frame.origin.y));
	CCPoint ptWorld = m_pContainer->convertToWorldSpace(ptTouch);
	//dispatcher does not know about clipping. reject touches outside visible bounds.
	if (m_pTouches->count() > 2 ||
		m_bTouchMoved          ||
		!frame.containsPoint(ptTouch))
	{
		return m_pContainer->OnTouchBegan(touch,event);
	}

	if (!m_pTouches->containsObject(touch))
	{
		m_pTouches->addObject(touch);
	}

	if (m_pTouches->count() == 1)
	{
		m_tTouchPoint = ccpAdd(this->convertTouchToNodeSpace(touch),ccp(frame.origin.x, frame.origin.y));
		m_bTouchMoved     = false;
		m_bDragging     = true; //dragging started
		m_tScrollDistance = ccp(0.0f, 0.0f);
		m_fTouchLength    = 0.0f;
	}
	else if (m_pTouches->count() == 2)
	{
		m_tTouchPoint  = ccpMidpoint(this->convertTouchToNodeSpace((CCTouch*)m_pTouches->objectAtIndex(0)),
									this->convertTouchToNodeSpace((CCTouch*)m_pTouches->objectAtIndex(1)));
		m_fTouchLength = ccpDistance(m_pContainer->convertTouchToNodeSpace((CCTouch*)m_pTouches->objectAtIndex(0)),
									m_pContainer->convertTouchToNodeSpace((CCTouch*)m_pTouches->objectAtIndex(1)));
		m_bDragging  = false;
	}
	return m_pContainer->OnTouchBegan(touch,event);
}

bool XScrollView::OnTouchMove(CCTouch* touch, CCEvent* event)
{
	if (!this->isVisible())
	{
		return m_pContainer->OnTouchMove(touch,event);
	}
	//可视区域比内容大,则不需要移动
	CCSize sizeContainer = getContentSize();
	if(m_eDirection == en_Scrollview_Direction_H)
	{
		if(sizeContainer.width < m_tViewSize.width)
		{
			return m_pContainer->OnTouchMove(touch,event);
		}
	}
	if(m_eDirection == en_Scrollview_Direction_V)
	{
		if(sizeContainer.height < m_tViewSize.height)
		{
			return m_pContainer->OnTouchMove(touch,event);
		}
	}
	CCPoint point;
	CCNode* nodeParent = getParent();
	CCRect  frame;
	if(nodeParent)
	{
		frame = CCRectMake(nodeParent->getPosition().x + this->getPosition().x,
			nodeParent->getPosition().y + this->getPosition().y, 
			m_tViewSize.width, 
			m_tViewSize.height);
	}
	else
	{
		frame = CCRectMake(this->getPosition().x, this->getPosition().y, m_tViewSize.width, m_tViewSize.height);
	}

	point = ccpAdd(convertTouchToNodeSpace(touch), ccp(frame.origin.x, frame.origin.y));
	if(!frame.containsPoint(point))
	{
		//已经移出有效区
		OnTouchEnded(touch,event);
	}
	if (m_pTouches->containsObject(touch))
	{
		if (m_pTouches->count() == 1 && m_bDragging)
		{
			CCPoint moveDistance, newPoint, maxInset, minInset;
			float newX, newY;
            
			m_bTouchMoved  = true;
			newPoint=  ccpAdd(this->convertTouchToNodeSpace((CCTouch*)m_pTouches->objectAtIndex(0)),ccp(frame.origin.x, frame.origin.y));
			moveDistance = ccpSub(newPoint, m_tTouchPoint);
			m_tTouchPoint  = newPoint;			
			point = this->convertToWorldSpace(newPoint);
			if (frame.containsPoint(newPoint))
			{
				switch (m_eDirection)
				{
					case en_Scrollview_Direction_V:
						moveDistance = ccp(0.0f, moveDistance.y);
						break;
					case en_Scrollview_Direction_H:
						moveDistance = ccp(moveDistance.x, 0.0f);
						break;
					default:
						break;
				}
				m_pContainer->setPosition(ccpAdd(m_pContainer->getPosition(), moveDistance));
				maxInset = m_fMaxInset;
				minInset = m_fMinInset;
				//check to see if offset lies within the inset bounds
				newX = MIN(m_pContainer->getPosition().x, maxInset.x);
				newX = MAX(newX, minInset.x);
				newY = MIN(m_pContainer->getPosition().y, maxInset.y);
				newY = MAX(newY, minInset.y);
				if(m_eDirection == en_Scrollview_Direction_H)
				{
					newY = 0;
				}
				if(m_eDirection == en_Scrollview_Direction_V)
				{
					newX = 0;
				}
				m_tScrollDistance = ccpSub(moveDistance, ccp(newX - m_pContainer->getPosition().x, newY - m_pContainer->getPosition().y));
				this->setContentOffset(ccp(newX, newY));
			}
		}
		else if (m_pTouches->count() == 2 && !m_bDragging)
		{
			const float len = ccpDistance(m_pContainer->convertTouchToNodeSpace((CCTouch*)m_pTouches->objectAtIndex(0)),
											m_pContainer->convertTouchToNodeSpace((CCTouch*)m_pTouches->objectAtIndex(1)));
			this->setZoomScale(this->getZoomScale()*len/m_fTouchLength);
		}
		return m_pContainer->OnTouchMove(touch,event);
	}
	m_pTouches->removeAllObjects();
	m_pContainer->OnTouchEnded(touch,event);
	return false;
}

bool XScrollView::OnTouchEnded(CCTouch* touch, CCEvent* event)
{
	if (!this->isVisible())
	{
		return m_pContainer->OnTouchEnded(touch,event);
	}
	if (m_pTouches->containsObject(touch))
	{
		if (m_pTouches->count() == 1 && m_bTouchMoved)
		{
			this->schedule(schedule_selector(XScrollView::deaccelerateScrolling));
		}
		m_pTouches->removeObject(touch);
	} 

	if (m_pTouches->count() == 0)
	{
		m_bDragging = false;    
		m_bTouchMoved = false;
	}
	return m_pContainer->OnTouchEnded(touch,event);
}

bool XScrollView::OnTouchCancelled(CCTouch* touch, CCEvent* event)
{
	if (!this->isVisible())
	{
		return XWindow::OnTouchCancelled(touch,event);
	}
	m_pTouches->removeObject(touch); 
	if (m_pTouches->count() == 0)
	{
		m_bDragging = false;    
		m_bTouchMoved = false;
	}
	return XWindow::OnTouchCancelled(touch,event);
}

void XScrollView::addNodeToContainer(CCNode *node)
{
	node->retain();
	CCSize size = m_pContainer->getContentSize();
	node->setAnchorPoint(CCPointZero);
	CCPoint  nodeRoot  = this->getPosition();
	CCArray* ccArray = m_pContainer->getChildren();
	CCObject* Object;
	int i = 0;
	if(m_eDirection == en_Scrollview_Direction_V)
	{
		CCARRAY_FOREACH(ccArray,Object)
		{
			CCNode* nodeChild = (CCNode*)Object;
			if(nodeChild)
			{
				CCPoint  nodePoint = nodeChild->getPosition();
				nodeChild->setPosition(0,nodePoint.y+node->getContentSize().height+m_iCellSpace);
				int iTag = nodeChild->getTag();
				if(iTag >= i)
				{
					i = iTag+1;
				}
			}
		}
		m_pContainer->addChild(node,0,i);
		node->setPosition(ccp(0,0));
		setContentSize(CCSizeMake(size.width,size.height+node->getContentSize().height+m_iCellSpace));
	}
	else if(m_eDirection == en_Scrollview_Direction_H)
	{
		CCARRAY_FOREACH(ccArray,Object)
		{
			CCNode* nodeChild = (CCNode*)Object;
			if(nodeChild)
			{	
				CCPoint  nodePoint = nodeChild->getPosition();
				nodeChild->setPosition(nodePoint.x + node->getContentSize().width+m_iCellSpace,0);
				int iTag = nodeChild->getTag();
				if(iTag >= i)
				{
					i = iTag+1;
				}
			}
		}
		m_pContainer->addChild(node,0,i);
		node->setPosition(ccp(0,0));
		setContentSize(CCSizeMake(size.width+node->getContentSize().width+m_iCellSpace,size.height));
	}
	node->release();
}

void XScrollView::scrollTheView(float fLen)
{
	CCPoint point = ccp(0,fLen);
	if(m_eDirection == en_Scrollview_Direction_V)
	{
			point = ccp(0,fLen);
	}
	else if(m_eDirection == en_Scrollview_Direction_H)
	{
			point = ccp(fLen,0);
	}
	CCPoint pointNow = getContentOffset();
	setContentOffset(ccpAdd(pointNow,point));
}

int XScrollView::getCellHeight()
{
	CCArray* ccArray = m_pContainer->getChildren();
	CCObject* Object;
	CCARRAY_FOREACH(ccArray,Object)
	{
		CCNode* nodeChild = (CCNode*)Object;
		if(nodeChild)
		{	
			return nodeChild->getContentSize().height;
			break;
		}
	}
	return 0;
}

int XScrollView::getCellSpace()
{
	return m_iCellSpace;
}

void XScrollView::setCellSpace(int iCellSpace)
{
	m_iCellSpace = iCellSpace;
}

void XScrollView::setBroll(bool bRoll)
{
	m_bRoll = bRoll;
}

void XScrollView::reTag()
{
	CCArray* ccArray = m_pContainer->getChildren();
	CCObject* Object = NULL;
	int iTag = 0;
	CCARRAY_FOREACH(ccArray,Object)
	{
		CCNode* nodeChild = (CCNode*)Object;
		if(nodeChild)
		{
			nodeChild->setTag(iTag);
			iTag = iTag + 1;
		}
	}
}

void XScrollView::setInitContainerSize(bool bInitContainerSize)
{
	m_bInitContainerSize = bInitContainerSize;
	if (m_bInitContainerSize)
	{
		m_pContainer->setPosition(ccp(0.0f, 0.0f));
		m_pContainer->setContentSize(this->GetWindowRect().size);
	}
}

int XScrollView::GetWindowType()
{
	return WT_SUPERSCROLLVIEW;
}
