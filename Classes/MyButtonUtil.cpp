//
//  MyButtonUtil.cpp
//  highandlowrun
//
//  Created by コトブキ タロウ on 2013/10/24.
//
//

#import "MyButtonUtil.h"
USING_NS_CC;

CCMenuItemImage* MyButtonUtil::makeCCMenuItemImage(const char* pngName,CCPoint pnt,CCLayer *target,SEL_MenuHandler selector) {
    //ボタンを返す
    //テクスチャアトラス使ったらはこっち
    CCSprite* nBtn=CCSprite::createWithSpriteFrameName(pngName);
    CCSprite* oBtn=CCSprite::createWithSpriteFrameName(pngName);
    //ノーマル
//    CCSprite* nBtn=CCSprite::create(pngName);
//    CCSprite* oBtn=CCSprite::create(pngName);
    oBtn->setColor(ccc3(128, 128, 128));
    
    CCMenuItemImage* menuButton=CCMenuItemImage::create();
    menuButton->setTarget(target, selector);
    
    menuButton->setNormalImage(nBtn);
    menuButton->setSelectedImage(oBtn);
    //menuButton->setAnchorPoint(ccp(0, 0));
    menuButton->setPosition(pnt);
	return menuButton;
}

CCMenuItemLabel* MyButtonUtil::makeCCMenuItemLabel(const char* buttontext,CCPoint pnt,CCLayer *target,SEL_MenuHandler selector) {
    //ボタンを返す
    CCMenuItemLabel* menuButton=CCMenuItemLabel::create(CCLabelTTF::create(buttontext, "Thonburi", 50), target, selector);
    menuButton->setColor(ccRED);
    //menuButton->setAnchorPoint(ccp(0, 0));
    menuButton->setPosition(pnt);
	return menuButton;
}

