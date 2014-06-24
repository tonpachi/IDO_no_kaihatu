//
//  KasiGetLayer.cpp
//  kyojin
//
//  Created by コトブキ タロウ on 2014/02/21.
//
//

#import "KasiGetLayer.h"
#import "Game.h"
#import "GameUtil.h"

#import "SaveUtil.h"


#import "MyEasyMenuItem.h"

#import "cocos2d.h"


USING_NS_CC;

KasiGetLayer::KasiGetLayer(){
    
}

KasiGetLayer::~KasiGetLayer(){

}

//初期化
bool KasiGetLayer::init(){
    if (CCLayer::init()) {
        // タッチ有効化
        setTouchEnabled(true);
        setTouchMode(kCCTouchesOneByOne);
        //タッチの優先順位上げる
        this->setTouchPriority(kModalLayerPriority_a);

        m_winSize = CCDirector::sharedDirector()->getWinSize();
        
        //黒背景
        CCSprite* m_blackBg = GameUtil::makeBlackBg(m_winSize.width, m_winSize.height);
        pos00(m_blackBg)
        this->addChild(m_blackBg,kGameLayerBackground0);

        
        return true;
    } else {
        return false;
    }
}


void KasiGetLayer::show(int kind,CCObject *target,SEL_MenuHandler selector){
    
    //画像
    CCSprite *_sp;
    if (kind == 0) {
        _sp = CCSprite::createWithSpriteFrameName("okashiget1.png");
        
        SaveUtil::incrimentSave(USERDEFAULT_HAS_COOKIE);
        
    } else if (kind == 1) {
        _sp = CCSprite::createWithSpriteFrameName("okashiget2.png");
        
        SaveUtil::incrimentSave(USERDEFAULT_HAS_AME);
        
    } else {
        _sp = CCSprite::createWithSpriteFrameName("okashiget3.png");
        
        SaveUtil::incrimentSave(USERDEFAULT_HAS_PAN);
        
    }
    
    posCenter(_sp)
    this->addChild(_sp,kGameLayerOnBg1);
    
    //もどる 閉じる
    MyEasyMenuItem *_backItem = MyEasyMenuItem::create("ok_btn.png", ccp(320,400), target, selector);
    
    CCMenu *_menuS = CCMenu::create(_backItem,NULL);
    _menuS->setPosition(ccp(0, 0));
    _menuS->setTouchPriority(kModalLayerPriority_a_menu);
    this->addChild(_menuS,kGameLayerMenu);

}


bool KasiGetLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
	return true;
}

