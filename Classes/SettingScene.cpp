//
//  SettingScene.cpp
//
//
//  Created by dotchi on 2014/06/02.
//
//
#import "SettingScene.h"

#import "SimpleAudioEngine.h"

#import "Game.h"
#import "GameUtil.h"

#import "NativeManager.h"
#import "SaveUtil.h"
#import "MySoundONOFFMenuItem.h"
#import "MyEasyMenuItem.h"
#import "MyButtonUtil.h"

#import "AndroidUtil.h"


#import "HowToScene.h"
#import "GameScene.h"
#import "YonkomaScene.h"
#import "GimmickListScene.h"
#import "FriendsScene.h"

USING_NS_CC;


SettingScene::~SettingScene(){
    //デストラクタ
    if (canDestroy) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("setting.plist");
        CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    }
    
}


CCScene* SettingScene::scene(){
    CCScene* scene=CCScene::create();
    SettingScene* layer=SettingScene::create();
    scene->addChild(layer);
    return scene;
}

#pragma mark 変数初期化
void SettingScene::initValue(){
    
	m_winSize = CCDirector::sharedDirector()->getWinSize();
    
    m_utils=GameUtil::create();
    this->addChild(m_utils,kGameLayerBackground0);
    
    m_winSize=CCDirector::sharedDirector()->getWinSize();
    
    m_frameCashe=CCSpriteFrameCache::sharedSpriteFrameCache();
    
    canDestroy=true;
    
    /* 乱数系列の変更 */
	srand((unsigned)time(NULL));
    
    // タッチ有効化
	setTouchEnabled(true);
	setTouchMode(kCCTouchesOneByOne);
}

//初期化
bool SettingScene::init(){
    //CCLOG("SettingScene::init");
    if (CCLayer::init()) {
        
        initValue();
        
        m_frameCashe->addSpriteFramesWithFile("setting.plist");
        
        //画面位置をセット
        setObjectPosition();
        
        //背景をセット
        setBackGround();
        
        //メニューアイテムをセット
        setMenuItem();
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        AndroidUtil::heapLogger();
        AndroidUtil::txtviewVisible();
#endif
        return true;
    } else {
        return false;
    }
}



#pragma mark 位置設定
//画面位置をセット
void SettingScene::setObjectPosition(){
    //サイズ別にセット
    if (m_winSize.height==1136) {
        //4インチ
        yMinus=0;
        
    } else {
        yMinus=44;
        
        NativeManager::closeIconView();
    }
    
        m_pt_4koma=ccp( 200,1000 );
        m_pt_friends=ccp( 500,1000 );
    
        m_pt_gimic=ccp( 200,700 );
        m_pt_howto=ccp( 500,700 );
    
    
        m_pt_sound=ccp( 200,400 );
        m_pt_vibe=ccp( 500,400 );
    
    
    m_pt_rev=ccp( 200,200 );
    m_pt_tw=ccp( 500,200 );
    
    
    m_pt_back=ccp( 500,100 );
    

}

#pragma mark 背景セット
void SettingScene::setBackGround(){
    //背景
    //黒
    m_backGroundSprite=CCSprite::createWithSpriteFrameName("set_bg.png");
    pos00(m_backGroundSprite);
    this->addChild(m_backGroundSprite);
    
}

#pragma mark メニューアイテムをセット
void SettingScene::setMenuItem(){
    
    //音設定ボタン
    MySoundONOFFMenuItem* _menu=new MySoundONOFFMenuItem();
    CCMenuItemToggle *_soundBtn = _menu->prepar("setting_btn_sound_on.png","setting_btn_sound_off.png", m_pt_sound, this, menu_selector(SettingScene::onSound));
    
    //4コマ
    MyEasyMenuItem* _4koma=MyEasyMenuItem::create("setting_btn_4koma.png", m_pt_4koma, this, menu_selector(SettingScene::on4koma));
    
    //ともだち
    MyEasyMenuItem* _friend=MyEasyMenuItem::create("setting_btn_friend.png", m_pt_friends, this, menu_selector(SettingScene::onFriends));
    
    //レビュー
    m_revBtn=MyEasyMenuItem::create("setting_btn_rev.png", m_pt_rev , this, menu_selector(SettingScene::onRev));
    
    //ギミック
    MyEasyMenuItem* _gimic=MyEasyMenuItem::create("setting_btn_gimmick.png", m_pt_gimic, this, menu_selector(SettingScene::onGimic));
    
    //遊び方
    MyEasyMenuItem* _how=MyEasyMenuItem::create("setting_btn_howto.png", m_pt_howto, this, menu_selector(SettingScene::onHowTo));
    
    
    //バイブ
    MyEasyMenuItem* _vibe=MyEasyMenuItem::create("top_set_btn.png", m_pt_vibe, this, menu_selector(SettingScene::onVibe));
    
    //TW
    MyEasyMenuItem* _tw=MyEasyMenuItem::create("setting_btn_tweet.png", m_pt_tw, this, menu_selector(SettingScene::onTw));
    
    //おすすめアプリ
    m_WallBtn=MyEasyMenuItem::create("setting_btn_wall.png", m_pt_wall, this, menu_selector(SettingScene::onWall));
    
    //もどる
    MyEasyMenuItem *_backItem = MyEasyMenuItem::create("btn_back.png", m_pt_back, this, menu_selector(SettingScene::onBack));
    

    CCMenu *_menuS = CCMenu::create(m_revBtn,_friend,_soundBtn,_4koma,_backItem,_tw,_vibe,_how,_gimic,NULL);
    
	_menuS->setPosition(ccp(0, 0));
    this->addChild(_menuS);
    

    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
    //m_revBtn->setVisible(GameUtil::getAppStatus());
    //m_WallBtn>setVisible(GameUtil::getAppStatus());
    
#endif
    
    
    
    
}




#pragma mark ボタンタップ処理

//おすすめボタンタップ
void SettingScene:: onBack(CCObject *pSender){
    changeSceneFade(GameScene::scene())
}
void SettingScene:: on4koma(CCObject *pSender){
    changeSceneFade(YonkomaScene::scene())
}
void SettingScene:: onFriends(CCObject *pSender){
    changeSceneFade(FriendsScene::scene())
}
void SettingScene:: onGimic(CCObject *pSender){
    changeSceneFade(GimmickListScene::scene())

}
void SettingScene:: onHowTo(CCObject *pSender){
    changeSceneFade(HowToScene::scene())
}
void SettingScene:: onSound(CCObject *pSender){

}

void SettingScene:: onVibe(CCObject *pSender){
    bool isV=SaveUtil::getSaveBool(USERDEFAULT_VIBE_ON_OFF, true);
    isV=!isV;
    SaveUtil::saveBool(USERDEFAULT_VIBE_ON_OFF, isV);
}
void SettingScene:: onLobi(CCObject *pSender){

}
void SettingScene:: onTw(CCObject *pSender){

}

void SettingScene:: onWall(CCObject *pSender){

}
void SettingScene:: onRev(CCObject *pSender){
    
}

#pragma mark tweet成功
void SettingScene::tweetDone(){
    //時間保存　LATEST_TWEET_TIME
    //
    SaveUtil::saveBool(BOOST_START_FLAG, true);
}

#pragma mark エンター
void SettingScene::onEnter(){
    CCLayer::onEnter();
    
    // !!!:------Google Analytics
    NativeManager::sendName2GA(SCENE_NAME_SETTING);
    My_setNotify(SettingScene::tweetDone, NOTIFICATION_TWEET_DONE)
}

#pragma mark エンターフィニッシュ
void SettingScene::onEnterTransitionDidFinish(){
    CCLayer::onEnterTransitionDidFinish();

}

#pragma mark Exit
void SettingScene::onExit(){
    CCLayer::onExit();
    My_unSetNotify( NOTIFICATION_TWEET_DONE)
}

#pragma mark Exitスタート
void SettingScene::onExitTransitionDidStart(){
    CCLayer::onExitTransitionDidStart();
    
    SaveUtil::saveInt(USERDEFAULT_FROM_LAUCH,klaunchSceneSetting);
}






