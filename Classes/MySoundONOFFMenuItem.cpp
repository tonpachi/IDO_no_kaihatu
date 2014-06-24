//
//  MySoundONOFFMenuItem.cpp
//  kyojin
//
//  Created by コトブキ タロウ on 2014/02/28.
//
//

#import "MySoundONOFFMenuItem.h"
#import "SaveUtil.h"
#import "GameUtil.h"
#import "NativeManager.h"


USING_NS_CC;

MySoundONOFFMenuItem::MySoundONOFFMenuItem():m_orgTarget(NULL),m_orgSelector(NULL)
{
    isOn=SaveUtil::getSaveBool(USERDEFAULT_SOUND_ON_OFF);
}
MySoundONOFFMenuItem::~MySoundONOFFMenuItem(){
    
}

CCMenuItemToggle* MySoundONOFFMenuItem::prepar(const char* pngName1,const char* pngName2,CCPoint pnt, CCObject *target, SEL_MenuHandler selector) {
    // 元のセレクタを保持
    m_orgTarget = target;
    m_orgSelector = selector;

    //テクスチャアトラス使ったらはこっち
    CCSprite* btn_Off=CCSprite::createWithSpriteFrameName(pngName1);
    CCSprite* btn_On=CCSprite::createWithSpriteFrameName(pngName2);
    
    CCSprite* btn_Off_tap=CCSprite::createWithSpriteFrameName(pngName1);
    CCSprite* btn_On_tap=CCSprite::createWithSpriteFrameName(pngName2);
    
    btn_Off_tap->setColor(ccc3(128, 128, 128));
    btn_On_tap->setColor(ccc3(128, 128, 128));
    //ノーマル
    //    CCSprite* nBtn=CCSprite::create(pngName);
    //    CCSprite* oBtn=CCSprite::create(pngName);
    
    // サウンドボタンOFF(トグルスイッチ用)
    CCMenuItemSprite* menuButton_off=CCMenuItemSprite::create(btn_Off,btn_Off_tap,NULL);
    //menuButton_off->setTarget(target, NULL);
//    menuButton_off->setNormalImage(btn_Off);
//    menuButton_off->setSelectedImage(btn_Off_tap);
    
    // サウンドボタンON(トグルスイッチ用)
    CCMenuItemSprite* menuButton_on=CCMenuItemSprite::create(btn_On,btn_On_tap,NULL);
    //menuButton_on->setTarget(target, NULL);
//    menuButton_on->setNormalImage(btn_On);
//    menuButton_on->setSelectedImage(btn_On_tap);
    
    // このクラスでタップイベントを取得するように登録する
    //return initWithNormalSprite(nBtn, oBtn, NULL, this, menu_selector(MySoundONOFFMenuItem::onTapThis));
    CCMenuItemToggle* _toggle=createWithTarget(this,menu_selector(MySoundONOFFMenuItem::onTapThis),menuButton_off,menuButton_on,NULL);
    _toggle->setPosition(pnt);
    if (isOn) {
            _toggle->setSelectedIndex(0);
    }else{
            _toggle->setSelectedIndex(1);
    }
	return _toggle;
}


void MySoundONOFFMenuItem::onTapThis(cocos2d::CCObject *sender) {
	// ボタンが押されたイベント内で効果音を鳴らすとか
	isOn = !isOn;
	if (isOn) {
		CCLOG("onTapThis turn ON");
        GameUtil::tapButtonEffect(isOn);
        // !!!:------Google Analytics
        NativeManager::sendClickEvent2GA(SCENE_NAME_SETTING,GA_BUTTON_SOUND_TURN_ON);
	}
	else {
		CCLOG("onTapThis turn OFF");
        // !!!:------Google Analytics
        NativeManager::sendClickEvent2GA(SCENE_NAME_SETTING,GA_BUTTON_SOUND_TURN_OFF);
	}
    SaveUtil::saveBool(USERDEFAULT_SOUND_ON_OFF,isOn);
    
    // 元のセレクタを呼び出す
    if (m_orgTarget && m_orgSelector) {
        (m_orgTarget->*m_orgSelector)(this);
    }
}


MySoundONOFFMenuItem *MySoundONOFFMenuItem::create(const char *pngName1,const char* pngName2, CCPoint pnt,CCObject *target,SEL_MenuHandler selector){
    
    MySoundONOFFMenuItem *pRet = new MySoundONOFFMenuItem();
    if (pRet ) {//&& pRet->prepar(pngName1,pngName2, target, selector)
		//pRet->autorelease();
        pRet->setPosition(pnt);
        CCLOG("prepar passed");
		return pRet;
	}
	//CC_SAFE_DELETE(pRet);
	return NULL;
}