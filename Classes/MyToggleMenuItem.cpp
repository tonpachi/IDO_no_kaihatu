//
//  MyToggleMenuItem.cpp
//  kyojin
//
//  Created by コトブキ タロウ on 2014/02/28.
//
//

#import "MyToggleMenuItem.h"

USING_NS_CC;

MyToggleMenuItem::MyToggleMenuItem()
: m_orgTarget(NULL)
, m_orgSelector(NULL)
{
    
}
MyToggleMenuItem::~MyToggleMenuItem(){
    
}

bool MyToggleMenuItem::prepar(const char* pngName, CCPoint pnt, CCObject *target, SEL_MenuHandler selector) {
    // 元のセレクタを保持
    m_orgTarget = target;
    m_orgSelector = selector;
    
    
    //ボタンを返す
    //テクスチャアトラス使ったらはこっち
    CCSprite* nBtn=CCSprite::createWithSpriteFrameName(pngName);
    CCSprite* oBtn=CCSprite::createWithSpriteFrameName(pngName);
    //ノーマル
    //    CCSprite* nBtn=CCSprite::create(pngName);
    //    CCSprite* oBtn=CCSprite::create(pngName);
    oBtn->setColor(ccc3(128, 128, 128));
    // このクラスでタップイベントを取得するように登録する
    return initWithNormalSprite(nBtn, oBtn, NULL, this, menu_selector(MyToggleMenuItem::onTapThis));
}

MyToggleMenuItem *MyToggleMenuItem::create(const char *pngName, CCPoint pnt,CCObject *target,SEL_MenuHandler selector){
    
    MyToggleMenuItem *pRet = new MyToggleMenuItem();
	
    if (pRet && pRet->prepar(pngName, pnt, target, selector)) {
		//pRet->autorelease();
        pRet->setPosition(pnt);
		return pRet;
	}
	//CC_SAFE_DELETE(pRet);
	return NULL;
}

void MyToggleMenuItem::onTapThis(cocos2d::CCObject *sender) {
	// ボタンが押されたイベント内で効果音を鳴らす
	CCLOG("sugee");
    
    // 元のセレクタを呼び出す
    if (m_orgTarget && m_orgSelector) {
        (m_orgTarget->*m_orgSelector)(this);
    }
}
