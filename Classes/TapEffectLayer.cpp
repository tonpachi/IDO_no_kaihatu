//
//  TapEffectLayer.cpp
//  kyojin
//
//  Created by コトブキ タロウ on 2014/02/21.
//
//

#import "TapEffectLayer.h"
#import "Game.h"
#import "GameUtil.h"

#import "SaveUtil.h"


#import "MyEasyMenuItem.h"

#import "cocos2d.h"


USING_NS_CC;

TapEffectLayer::TapEffectLayer(){
    
}

TapEffectLayer::~TapEffectLayer(){

}

//初期化
bool TapEffectLayer::init(){
    if (CCLayer::init()) {
        
        m_winSize = CCDirector::sharedDirector()->getWinSize();
        
        int yMinus;
        //サイズ別にセット
        if (m_winSize.height==1136) {
            //4インチ
            yMinus=0;
            
        } else {
            yMinus=44;
        }
        //メーター位置
        CCPoint m_p_meter = ccp(0, 902-yMinus);
        show(m_p_meter);

        
        return true;
    } else {
        return false;
    }
}
void TapEffectLayer::show(CCPoint pt){

    //タップしたところに何か出すらしい
    CCSprite *skull = CCSprite::createWithSpriteFrameName("skull.png");
    skull->setAnchorPoint(ccp(0.5, 0.5));
    skull->setPosition(pt);
    
    CCFiniteTimeAction *_fade = CCFadeTo::create(1.0f,0);
    //runActionをするspを引数にとる
    CCCallFuncN *_endfunc = CCCallFuncN::create(this,callfuncN_selector(TapEffectLayer::deleteSelf));
    
    CCSequence *_squences = CCSequence::create(_fade,_endfunc, NULL);
    skull->runAction(CCRepeatForever::create(_squences));
    
    this->addChild(skull);
}

void TapEffectLayer::deleteSelf(CCNode* sender){
    sender->removeFromParentAndCleanup(true);
}