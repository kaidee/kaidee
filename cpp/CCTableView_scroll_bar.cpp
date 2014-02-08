CCTableView* tableView = CCTableView::create(this, CCSizeMake(762, 439));
if(tableView != NULL)
{
    tableView->setDirection(kCCScrollViewDirectionVertical);
    tableView->setPosition(ccp(33, 30));
    tableView->setDelegate(this);
    tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    this->addChild(tableView);
}



CCSprite* bar = CCSprite::create("ui/scrollBar.png");
if(bar != NULL)
{
    bar->ignoreAnchorPointForPosition(false);
    bar->setAnchorPoint(ccp(0.5, 1));
    bar->setPosition(ccp(805, 465));
    this->addChild(bar, 1, 1000);
}



CCTableViewCell* Fjut::tableCellAtIndex(CCTableView* table, unsigned int idx)
{
    CCString* string = CCString::createWithFormat("%d", idx);
   
    CCTableViewCell* cell = table->dequeueCell();
    if (cell == NULL)
    {
        cell = new CCTableViewCell();
        cell->autorelease();
 
        // test
        CCLabelTTF* label_ = CCLabelTTF::create(string->getCString(), "Aril", 15);
        if(label_ != NULL)
        {
            label_->setPosition(ccp(65, 56));
            label_->setColor(FONT_COLOR_Green);
            cell->addChild(label_, 1, 100);
        }
    }
    else
    {
        scrollBar(table); // ...
 
        CCLabelTTF* label_ = (CCLabelTTF*)cell->getChildByTag(100);
        if(label_ != NULL)
        {
            label_->setString(string->getCString());
        }
    }
 
    return cell;
}




void Fjut::scrollBar(CCTableView* table)
{
    CCNode* bar = this->getChildByTag(1000);
    if(bar == NULL)
    {
        return;
    }
 
    // tableSize.height == cell个数*cell的height
    CCSize tableSize = table->getContentSize();
    // CCTableView
    CCSize tableViewSize = table->getViewSize();
    // 每次拖动的偏移量？(负值)
    CCPoint contOffsetPos = table->getContentOffset();
 
    // 总的偏移量
    float maxOff = tableViewSize.height - tableSize.height;
    // 每次拖动的偏移量
    float curOff = contOffsetPos.y - maxOff;
    // 计算百分比
    float percentage = fabs(curOff)/fabs(maxOff);
 
    printf("curOff:%f, maxOff:%f, per:%f\n", curOff, maxOff, percentage);
     
    // 拖拉到最顶端或最低端后继续拖动(弹回)会出现percentage值小于0.1和大于1.0的情况，我们分别把percentage重置为0和1.0f
    if(percentage < 0.1f)
    {
        percentage = 0;
    }
    if(percentage > 1.0f)
    {
        percentage = 1.0f;
    }
 
    // bar移动到最顶端的position.y
    float barTopPosY = bar->getPosition().y;
    // bar移动到最低端的position.y
    float barLowPosY = 75.0f;
    // ....
    float h = barTopPosY - percentage*(barTopPosY- barLowPosY);;
 
    bar->setPosition(ccp(bar->getPosition().x, h));
}



http://www.cnblogs.com/fjut/archive/2013/05/25/3099347.html