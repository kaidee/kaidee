/******************************************************************
** 文件名:	XScrollView.h
** 版  权:	
** 创建人:	world
** 日  期:	2012/12/10
** 版  本:	
** 描  述:	scrollView控件
** 应  用:  

**************************** 修改记录 ******************************
** 修改人: 
** 日  期: 
** 描  述: 
********************************************************************/
#ifndef __X_SUPER_SCROLLVIEW_H__
#define __X_SUPER_SCROLLVIEW_H__

#include "XWindow.h"
#include "WndDef.h"
USING_NS_CC;

enum en_Scrollview_Direction
{
	en_Scrollview_Direction_H = 0,			//水平
	en_Scrollview_Direction_V = 1,			//垂直
	en_Scrollview_Direction_Both = 2,
};

class XScrollView;

class XScrollViewDelegate
{
public:
    virtual ~XScrollViewDelegate() {}
    virtual void scrollViewDidScroll(XScrollView* view) = 0;
    virtual void scrollViewDidZoom(XScrollView* view) = 0;
};

class XScrollView: public XWindow
{
public:
    XScrollView();
    virtual ~XScrollView();
public:
	bool init();
    CC_DEPRECATED_ATTRIBUTE static XScrollView* viewWithViewSize(CCSize size, CCNode* container = NULL);
    static XScrollView* Create(CCSize size, CCNode* container = NULL);
    CC_DEPRECATED_ATTRIBUTE static XScrollView* node();
    static XScrollView* Create();
public:
	virtual int			GetWindowType();
public:
	
    bool					initWithViewSize(CCSize size, CCNode* container = NULL);
    void					setContentOffset(CCPoint offset, bool animated = false);
    CCPoint					getContentOffset();
    void					setContentOffsetInDuration(CCPoint offset, float dt); 
    void					setZoomScale(float s);
    void					setZoomScale(float s, bool animated);
    float					getZoomScale();
    void					setZoomScaleInDuration(float s, float dt);
    CCPoint					minContainerOffset();
    CCPoint					maxContainerOffset(); 
    bool					isNodeVisible(CCNode * node);
    void					pause(CCObject* sender);
    void					resume(CCObject* sender);
    bool					isDragging() {return m_bDragging;}
    bool					isTouchMoved() { return m_bTouchMoved; }
    bool					isBounceable() { return m_bBounceable; }
    void					setBounceable(bool bBounceable) { m_bBounceable = bBounceable; } //是否回弹
    CCSize					getViewSize() { return m_tViewSize; } 
    void					setViewSize(CCSize size);
    CCNode*					getContainer();
    void					setContainer(CCNode * pContainer);
    en_Scrollview_Direction getDirection() { return m_eDirection; }	// 设置滚动的方向
    virtual void			setDirection(en_Scrollview_Direction eDirection) { m_eDirection = eDirection; }
    XScrollViewDelegate*	getDelegate() { return m_pDelegate; }
    void					setDelegate(XScrollViewDelegate* pDelegate) { m_pDelegate = pDelegate; }
	void					updateInset();
	bool					isClippingToBounds() { return m_bClippingToBounds; }
	void					setClippingToBounds(bool bClippingToBounds) { m_bClippingToBounds = bClippingToBounds; }
	void					setTouchEnabled(BOOL e);
	void					UpdateContenSize();					// 更新container的大小
	void					addNodeToContainer(CCNode *node);	// 把node加到内容的开始处
	void					scrollTheView(float fLen);			// 使版在Y轴滚动一段距离
	int						getCellHeight();					// 取得一个cell的高度
	int						getCellSpace();						// 取得cell间的间距
	void					setCellSpace(int iCellSpace);		// 设置cell间的间距
	void					setBroll(bool bRoll);				// 设置是否可滚动
	void					setInitContainerSize(bool bInitContainerSize);
	void					reTag();
public:
	virtual void			SetWindowPos(CCRect rect);
	virtual bool			OnTouchBegan(CCTouch* touch, CCEvent* event);
	virtual bool			OnTouchMove(CCTouch* touch, CCEvent* event);
	virtual bool			OnTouchEnded(CCTouch* touch, CCEvent* event);
	virtual	bool			OnTouchCancelled(CCTouch* touch, CCEvent* event);
	virtual void			setContentSize(const CCSize & size);
	virtual const CCSize&	getContentSize();
	virtual void			visit();
    virtual void			addChild(CCNode * child, int zOrder, int tag);
    virtual void			addChild(CCNode * child, int zOrder);
    virtual void			addChild(CCNode * child);
	virtual XWindow*		FindWindowByID(int iID);
private:
    /**
     * Init this object with a given size to clip its content.
     *
     * @param size view size
     * @return initialized scroll view object
     */
    bool initWithViewSize(CCSize size);
    /**
     * Relocates the container at the proper offset, in bounds of max/min offsets.
     *
     * @param animated If YES, relocation is animated
     */
    void relocateContainer(bool animated);
    /**
     * implements auto-scrolling behavior. change SCROLL_DEACCEL_RATE as needed to choose
     * deacceleration speed. it must be less than 1.0f.
     *
     * @param dt delta
     */
    void deaccelerateScrolling(float dt);
    /**
     * This method makes sure auto scrolling causes delegate to invoke its method
     */
    void performedAnimatedScroll(float dt);
    /**
     * Expire animated scroll delegate calls
     */
    void stoppedAnimatedScroll(CCNode* node);
    /**
     * clip this view so that outside of the visible bounds can be hidden.
     */
    void beforeDraw();
    /**
     * retract what's done in beforeDraw so that there's no side effect to
     * other nodes.
     */
    void afterDraw();
    /**
     * Zoom handling
     */
    void handleZoom();

protected:
    /**
     * current zoom scale
     */
    float		m_fZoomScale;
    /**
     * min zoom scale
     */
    float		m_fMinZoomScale;
    /**
     * max zoom scale
     */
    float		m_fMaxZoomScale;
    /**
     * scroll view delegate
     */
    XScrollViewDelegate* m_pDelegate;

    en_Scrollview_Direction m_eDirection;
    /**
     * If YES, the view is being dragged.
     */
    bool		m_bDragging;

    /**
     * Content offset. Note that left-bottom point is the origin
     */
    CCPoint m_tContentOffset;

    /**
     * Container holds scroll view contents, Sets the scrollable container object of the scroll view
     */
    XWindow*	m_pContainer;
    /**
     * Determiens whether user touch is moved after begin phase.
     */
    bool		m_bTouchMoved;
    /**
     * max inset point to limit scrolling by touch
     */
    CCPoint		m_fMaxInset;
    /**
     * min inset point to limit scrolling by touch
     */
    CCPoint		m_fMinInset;
    /**
     * Determines whether the scroll view is allowed to bounce or not.
     */
    bool		m_bBounceable;

    bool		m_bClippingToBounds;

    /**
     * scroll speed
     */
    CCPoint		m_tScrollDistance;
    /**
     * Touch point
     */
    CCPoint		m_tTouchPoint;
    /**
     * length between two fingers
     */
    float		m_fTouchLength;
    /**
     * UITouch objects to detect multitouch
     */
    CCArray*	m_pTouches;
    /**
     * size to clip. CCNode boundingBox uses contentSize directly.
     * It's semantically different what it actually means to common scroll views.
     * Hence, this scroll view will use a separate size property.
     */
    CCSize		m_tViewSize;
    /**
     * max and min scale
     */
    float		m_fMinScale, m_fMaxScale;

	int			m_iCellSpace;		//两个cell间的间距

	CCPoint		m_pointStar;		//刚点击的坐标

	bool		m_bRoll;			//是否可以滚动

	bool		m_bInitContainerSize;	//是否需要初始化Container
};

#endif 
