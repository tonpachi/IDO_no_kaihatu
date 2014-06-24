//
//  HowToScene.cpp
//  nagure
//
//  Created by dotchi on 2013/09/26.
//
//
#import "HowToScene.h"
#import "Game.h"

#import "NativeManager.h"
#import "SaveUtil.h"

#import "MyEasyMenuItem.h"
#import "SettingScene.h"
#import "GameUtil.h"
#import "AndroidUtil.h"

#import "GameScene.h"

using namespace cocos2d;


CCScene* HowToScene::scene(){
    CCScene* scene=CCScene::create();
    HowToScene* layer=HowToScene::create();
    scene->addChild(layer);
    return scene;
}

HowToScene::~HowToScene(){
    //デストラクタ
    if (canDestroy) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("setting.plist");
        CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    }
    
}

//初期化
bool HowToScene::init(){
    //CCLOG("HowToScene::init");
    if (CCLayer::init()) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        AndroidUtil::txtviewVisible();
#endif
        m_winSize=CCDirector::sharedDirector()->getWinSize();
        canDestroy=false;
        
        //画面位置をセット
        setObjectPosition();
        
        //背景をセット
        setBackGround();
        
        //メニューアイテムをセット
        setMenuItem();
        
        return true;
    } else {
        return false;
    }
}



#pragma mark 画面初期設定

//画面位置をセット
void HowToScene::setObjectPosition(){
    //サイズ別にセット
    //戻るボタン
    
    if (m_winSize.height==1136) {
            m_p_BackButton=ccp(570, 880);
    } else {
            m_p_BackButton=ccp(570, 520);
        NativeManager::set960Icon();
    }

}

//背景セット
void HowToScene::setBackGround(){
    //背景
    ///////////////
    // !!!:自作のviewPagerをadd
    _pager=MySpritePager::create();
    this->addChild(_pager);
    
    //表示する大きさと座標　　anchor(0,0)で
    _pager->prepere(640,m_winSize.height, ccp(0,0));
    //必要な分 画像をadd
    _pager->addSpByFilename("howto1.png");
    _pager->addSpByFilename("howto2.png");
    _pager->addSpByFilename("howto3.png");
    
    //左右のボタン使うならadd
    _pager->myInitButton("zukan_page_l.png", ccp(52,520), "zukan_page_r.png", ccp(588,520));
    
}

// !!!:endSlideAnim
void HowToScene::endSlideAnim() {

	//表示更新
    if (_pager->myGetNowShowing()==2) {
        backButton->setVisible(true);
    }else{
        backButton->setVisible(false);
    }
    
}


//メニューアイテムをセット
void HowToScene::setMenuItem(){
    //CCLOG("HowToScene::setMenuItem");
    //戻るボタン
    backButton=MyEasyMenuItem::create("set_home_btn.png", m_p_BackButton, this, menu_selector(HowToScene::tapBackButton));

    
    CCMenu* menu=CCMenu::create(backButton,NULL);
    menu->setPosition(CCPointZero);
    
    this->addChild(menu);
    
    backButton->setVisible(false);
}


#pragma mark ボタンタップ処理

//戻るボタンタップ
void HowToScene::tapBackButton(){
    


}



void HowToScene::onEnter(){
    CCLayer::onEnter();
    //入れ替わりアニメ終了時呼ばれる
    My_setNotify(HowToScene::endSlideAnim, NOTIFY_SP_PAGER)
}

void HowToScene::onEnterTransitionDidFinish(){
    CCLayer::onEnterTransitionDidFinish();
    //ad設定
    NativeManager::setHowToAd();
}

void HowToScene::onExit(){
    CCLayer::onExit();
    //通知受け取り解放
    My_unSetNotify(NOTIFY_SP_PAGER)
}

void HowToScene::onExitTransitionDidStart(){
    CCLayer::onExitTransitionDidStart();
    //ad解放
    NativeManager::closeAd();
}
