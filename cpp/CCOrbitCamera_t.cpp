 CCSprite *sprite1=CCSprite::create("44@2x.png");
    
    sprite1->setPosition(ccp(200, 300));
    
    this->addChild(sprite1, 1);
        
    CCSequence *seq1=CCSequence::create(CCDelayTime::create(0.5f),
        CCCallFuncN::create(this,callfuncN_selector(HelloWorld::testFlipCardCallFunc1)),
        CCDelayTime::create(1.0f),
        CCCallFuncN::create(this, callfuncN_selector(HelloWorld::testFlipCardCallFunc2)),
        CCDelayTime::create(0.5f),NULL);

    //第一个参数是旋转的时间，第二个参数是起始半径，第三个参数半径差，第四个参数是起始Z角，第五个参数是旋转Z角差，第六个参数是起始X角，最后一个参数旋转X角差，
    CCOrbitCamera *camera1=CCOrbitCamera::create(2.0, 1, 0, 0, -360, 0, 0);

    CCRepeatForever *repeat1 = CCRepeatForever::create(CCSpawn::create(seq1,camera1,NULL));

    sprite1->runAction(repeat1);
    
    CCSprite *sprite2=CCSprite::create("pokerBack@2x.png");
    
    sprite2->setPosition(ccp(200, 300));

    sprite2->setVisible(false);
    
    this->addChild(sprite2, 1);
    
    
   CCSequence *seq2=CCSequence::create(CCDelayTime::create(0.5f),
    CCCallFuncN::create(this,callfuncN_selector(HelloWorld::testFlipCardCallFunc2)),
    CCDelayTime::create(1.0f),
    CCCallFuncN::create(this, callfuncN_selector(HelloWorld::testFlipCardCallFunc1)),
    CCDelayTime::create(0.5f),NULL);
    
    CCOrbitCamera *camera2=CCOrbitCamera::create(2.0, 1, 0, 0, -360, 0, 0);
    
    CCRepeatForever *repeat2 = CCRepeatForever::create(CCSpawn::create(seq2,camera2,NULL));
    
    sprite2->runAction(repeat2);



void HelloWorld::testFlipCardCallFunc1(CCNode *node)
{

    CCSprite *sprite=(CCSprite *)node;

    sprite->setVisible(false);
    




}

void HelloWorld::testFlipCardCallFunc2(CCNode *node)
{
    
    CCSprite *sprite=(CCSprite *)node;
    
    sprite->setVisible(true);
    
    
}
