//CScrollViewTest.h


//CCLayer *m_pLayer;

//CCScrollView *m_pScrollView;

//CCPoint m_touchPoint;

//bool m_isMoving;

//void adjustScrollView();

CScrollViewTest::CScrollViewTest()
:m_isMoving（false）
{
	  m_pLayer= CCLayer::create();
	  char helpstr[30] = {0};
	  for (int i = 1; i <= 4; ++ i)//页背景
	  {
		   memset(helpstr, 0, sizeof(helpstr));
		   sprintf(helpstr,"bg_%02d.png",i);
		   CCSprite *pSprite = CCSprite::create(helpstr);
		   pSprite->setPosition(ccp(visibleSize.width * (i-0.5f), visibleSize.height / 2));
		   m_pLayer->addChild(pSprite);
	  }
	  m_pScrollView = CCScrollView::create(CCSizeMake(1024, 640), m_pLayer);
	  m_pScrollView->setPosition(CCPointZero);
	  m_pScrollView->setContentOffset(CCPointZero);
	  m_pScrollView->setDelegate(this);
	  m_pScrollView->setDirection(kCCScrollViewDirectionHorizontal);
	  m_pLayer->setContentSize(CCSizeMake(1024*2, 640));
	 
	  this->addChild(m_pScrollView);
}

bool CScrollViewTest::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
 m_touchPoint = pTouch->getLocation();
 return true;
}

void CScrollViewTest::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
 if (!m_isMoving) {
  m_isMoving = true;
 }
}

void CScrollViewTest::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
 if(m_isMoving){
  adjustScrollView();
  return;}
}

void CScrollViewTest::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
   if(m_isMoving) adjustScrollView();
}

void CScrollViewTest::adjustScrollView()
{
	 // 关闭CCScrollView中的自调整
	     m_pScrollView->unscheduleAllSelectors();
	
	  INT32 i32pageNum =  4;//翻页数
	
	  int x = m_pScrollView->getContentOffset().x;
	
	  BOOL bOffline = FALSE;
	  if( x <= (-1)*( (i32pageNum-1)*600+300) )
	   bOffline = TRUE;
	
	
	 int offset = (int) x % (int)600;
	 // 调整位置
	 CCPoint adjustPos;
	 // 调整动画时间
	 float adjustAnimDelay;
	
	 if (offset < -600*0.5 && !bOffline ) {
	  // 计算下一页位置，时间
	  adjustPos = ccpSub(m_pScrollView->getContentOffset(), ccp(600 + offset, 0));
	  adjustAnimDelay = (float) (600 + offset) / 800;
	 }
	 else {
	  // 计算当前页位置，时间
	  adjustPos = ccpSub(m_pScrollView->getContentOffset(), ccp(offset, 0));
	  // 这里要取绝对值，否则在第一页往左翻动的时，保证adjustAnimDelay为正数
	  adjustAnimDelay = (float) abs(offset) / 800;
	 }
	
	 // 调整位置
	 m_pScrollView->setContentOffsetInDuration(adjustPos, adjustAnimDelay);
}

////////////////////
// tableview // CTableViewTest.cpp  //CCPoint m_TouchBeginPos;
////////////////////

CTableViewTest::CTableViewTest(void)
{

	this->setTouchEnabled(TRUE);
	m_pTableView = CCTableView::create(this, CCSizeMake(1024, 640));
	m_pTableView->setDirection(kCCScrollViewDirectionHorizontal);
	m_pTableView->setPosition(ccp(CCPointZero));
	m_pTableView->setDelegate(this);
	this->addChild(m_pTableView);
	m_pTableView->reloadData();
}

bool CTableViewTest::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	m_TouchBeginPos = pTouch->getLocation();
	return true;
}

void CTableViewTest::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint EndPos =  pTouch->getLocation();

	if( EndPos.x == m_TouchBeginPos.x )
		return;

	m_pTableView->unscheduleAllSelectors();

	INT32 i32PagNum =  2;

	int x = m_pTableView->getContentOffset().x;

	bool bOffline = false;
	if( x <= (-1)*( (i32PagNum-1)*600+300) )
		bOffline = TRUE;

	int offset = (int) x % 600;

	// 调整位置   
	CCPoint adjustPos;
	// 调整动画时间   
	float adjustAnimDelay;

	if (offset <= -300 && !bOffline ) { 
		// 计算下一页位置，时间
		adjustPos = ccpSub(m_pTableView->getContentOffset(), ccp(600 + offset, 0));  
		adjustAnimDelay = (float) (600 + offset) / 1000;
	}  
	else {  
		// 计算当前页位置，时间   
		adjustPos = ccpSub(m_pTableView->getContentOffset(), ccp(offset, 0));  
		// 这里要取绝对值，否则在第一页往左翻动的时，保证adjustAnimDelay为正数   
		adjustAnimDelay = (float) abs(offset) / 1000; 
	}   
	// 调整位置
	m_pTableView->setContentOffsetInDuration(adjustPos, adjustAnimDelay);  

}