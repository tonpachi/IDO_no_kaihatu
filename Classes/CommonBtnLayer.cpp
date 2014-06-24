//
//  CommonBtnLayer.cpp
//  kyojin
//
//  Created by コトブキ タロウ on 2014/02/21.
//
//

#import "CommonBtnLayer.h"
#include "SaveUtil.h"
#import "GameUtil.h"

#import "cocos2d.h"

#import <iostream>
#import <list>
#import <string>
#import <vector>
#import "MyAnimationUtil.h"
#import "KasiGetLayer.h"
#import "MyEasyMenuItem.h"

USING_NS_CC;
using namespace std;

CommonBtnLayer::CommonBtnLayer(){
    
}

CommonBtnLayer::~CommonBtnLayer(){
    //デストラクタ


}

//初期化
bool CommonBtnLayer::init(){
    CCLOG("CommonBtnLayer::init");
    if (CCLayer::init()) {
        
        m_winSize = CCDirector::sharedDirector()->getWinSize();
        
        if (m_winSize.height==1136) {
            //m_pt_wall
        }else{
            
        }
        
        m_pt_wall=ccp(340,1000);
        
        m_pt_okashi=ccp(50, 207);
        m_pt_kumotsu=ccp(174, 207);
        m_pt_friends=ccp(328, 207);
        m_pt_setting=ccp(482, 207);
        
        
        return true;
    } else {
        return false;
    }
}



void CommonBtnLayer::prepare(CCObject *target,SEL_MenuHandler Okasoselector,SEL_MenuHandler Kumotuselector,SEL_MenuHandler Friendselector,SEL_MenuHandler Settingselector,SEL_MenuHandler wallselector){
    
    
    //えさ
    MyEasyMenuItem *_backItem = MyEasyMenuItem::create("btn_Item.png", m_pt_okashi, this, Okasoselector);
    
    //供物
    MyEasyMenuItem *_item = MyEasyMenuItem::create("btn_Item.png", m_pt_kumotsu, this,Kumotuselector);
    
    //アルバム
    MyEasyMenuItem* _fri=MyEasyMenuItem::create("btn_friend.png", m_pt_friends, this, Friendselector);
    
    //設定
    MyEasyMenuItem* _set=MyEasyMenuItem::create("btn_setting.png", m_pt_setting, this,Settingselector);
    
    //wall
    MyEasyMenuItem* _wall=MyEasyMenuItem::create("btn_wall.png", m_pt_wall, this,wallselector);
    
    
    
    CCMenu *_menuS = CCMenu::create(_wall,_item,_fri,_set,_backItem,NULL);
    
	_menuS->setPosition(ccp(0, 0));
    this->addChild(_menuS);
    
}

void CommonBtnLayer::setNewSignFriend(){
    //newと出す
    //CCSprite *onew =MyAnimationUtil::createSpNewSign(ccp(482+50, 307+55));
    //this->addChild(onew,kGameLayerMenu);
}