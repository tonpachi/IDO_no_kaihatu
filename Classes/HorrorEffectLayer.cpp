//
//  HorrorEffectLayer.cpp
//  kyojin
//
//  Created by コトブキ タロウ on 2014/02/21.
//
//

#import "HorrorEffectLayer.h"
#import "Game.h"
#import "GameUtil.h"

#import "SaveUtil.h"



#import "cocos2d.h"
#import "MyAnimationUtil.h"

USING_NS_CC;

HorrorEffectLayer::HorrorEffectLayer(){
    
}

HorrorEffectLayer::~HorrorEffectLayer(){

}

//初期化
bool HorrorEffectLayer::init(){
    if (CCLayer::init()) {
        
        m_mode=-1;
        
        m_winSize = CCDirector::sharedDirector()->getWinSize();
        
        int yMinus;
        //サイズ別にセット
        if (m_winSize.height==1136) {
            //4インチ
            yMinus=0;
            
        } else {
            yMinus=44;
        }

        return true;
    } else {
        return false;
    }
}

void HorrorEffectLayer::setMode(int mode){
    m_mode=mode;
    if (mode==1) {
        //気配のみ
        CCAnimation* ani=MyAnimationUtil::setKomaAniByFileName2("", "", 0.1f, -1);
        anc00(allSp);
        allSp->runAction(CCAnimate::create(ani));
    }else{
        //出現
        CCAnimation* ani=MyAnimationUtil::setKomaAniByFileName2("", "", 0.1f, -1);
        anc00(allSp);
        allSp->runAction(CCAnimate::create(ani));
    }
}



void HorrorEffectLayer::show(){
    this->addChild(allSp);
}

void HorrorEffectLayer::stopAnim(){
    allSp->stopAllActions();
    
}


void HorrorEffectLayer::deleteSelf(CCNode* sender){
    sender->removeFromParentAndCleanup(true);
}


#pragma mark エンター
void HorrorEffectLayer::onEnter(){
    CCLayer::onEnter();
    // !!!:------Google Analytics
    //NativeManager::sendName2GA(SCENE_NAME_SETTING);
}

#pragma mark エンターフィニッシュ
void HorrorEffectLayer::onEnterTransitionDidFinish(){
    CCLayer::onEnterTransitionDidFinish();
}

#pragma mark Exit
void HorrorEffectLayer::onExit(){
    CCLayer::onExit();
}
#pragma mark Exitスタート
void HorrorEffectLayer::onExitTransitionDidStart(){
    CCLayer::onExitTransitionDidStart();
}