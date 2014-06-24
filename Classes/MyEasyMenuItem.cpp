//
//  MyEasyMenuItem.cpp
//  kyojin
//
//  Created by コトブキ タロウ on 2014/02/28.
//
//

#import "MyEasyMenuItem.h"
#import "GameUtil.h"
#import "SaveUtil.h"
#import "NativeManager.h"

USING_NS_CC;

MyEasyMenuItem::MyEasyMenuItem()
: m_orgTarget(NULL)
, m_orgSelector(NULL)
{
    isOn=SaveUtil::getSaveBool(USERDEFAULT_SOUND_ON_OFF);
    isGA=false;
}
MyEasyMenuItem::~MyEasyMenuItem(){
    
}

bool MyEasyMenuItem::prepar(const char* pngName, CCPoint pnt, CCObject *target, SEL_MenuHandler selector) {
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
    return initWithNormalSprite(nBtn, oBtn, NULL, this, menu_selector(MyEasyMenuItem::onTapThis));
}

MyEasyMenuItem *MyEasyMenuItem::create(const char *pngName, CCPoint pnt,CCObject *target,SEL_MenuHandler selector){
    
    MyEasyMenuItem *pRet = new MyEasyMenuItem();
	
    if (pRet && pRet->prepar(pngName, pnt, target, selector)) {
		//pRet->autorelease();
        pRet->setPosition(pnt);
		return pRet;
	}
	//CC_SAFE_DELETE(pRet);
	return NULL;
}
MyEasyMenuItem *MyEasyMenuItem::createAnc00(const char *pngName, CCPoint pnt,CCObject *target,SEL_MenuHandler selector){
    
    MyEasyMenuItem *pRet = new MyEasyMenuItem();
	
    if (pRet && pRet->prepar(pngName, pnt, target, selector)) {
		pRet->setAnchorPoint(ccp(0,0));
        pRet->setPosition(pnt);
		return pRet;
	}
	//CC_SAFE_DELETE(pRet);
	return NULL;
}

void MyEasyMenuItem::onTapThis(cocos2d::CCObject *sender) {
	// ボタンが押されたイベント内で効果音を鳴らす
    isOn=SaveUtil::getSaveBool(USERDEFAULT_SOUND_ON_OFF);
    if (isOn) {
        GameUtil::tapButtonEffect(isOn);
    }
    // 元のセレクタを呼び出す
    if (m_orgTarget && m_orgSelector) {
        (m_orgTarget->*m_orgSelector)(this);
    }
    
    if (isGA) {
        // !!!:------Google Analytics
        NativeManager::sendClickEvent2GA(GAscenename,GAbuttonname);
    }
}



void MyEasyMenuItem::setButtonGA(const char* scenename,const char* buttonname){
    GAscenename=scenename;
    GAbuttonname=buttonname;
    isGA=true;
}



