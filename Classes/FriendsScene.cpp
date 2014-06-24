//
//  FriendsScene.cpp
//
//
//  Created by dotchi on 2014/06/02.
//
//
#import "FriendsScene.h"

#import "SimpleAudioEngine.h"

#import "Game.h"
#import "GameUtil.h"

#import "NativeManager.h"
#import "SaveUtil.h"
#import "MySoundONOFFMenuItem.h"
#import "MyEasyMenuItem.h"
#import "MyButtonUtil.h"

#import "AndroidUtil.h"

#import "GameScene.h"
#import "LakeScene.h"
#import "GraveScene.h"
#import "SettingScene.h"


USING_NS_CC;


FriendsScene::~FriendsScene(){
    //デストラクタ
    if (canDestroy) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("friends.plist");
        CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("chara.plist");
        CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    }
    
}


CCScene* FriendsScene::scene(){
    CCScene* scene=CCScene::create();
    FriendsScene* layer=FriendsScene::create();
    scene->addChild(layer);
    return scene;
}

#pragma mark 変数初期化
void FriendsScene::initValue(){
    
	m_winSize = CCDirector::sharedDirector()->getWinSize();
    
    m_utils=GameUtil::create();
    this->addChild(m_utils,kGameLayerBackground0);
    
    m_winSize=CCDirector::sharedDirector()->getWinSize();
    
    m_frameCashe=CCSpriteFrameCache::sharedSpriteFrameCache();
    
    m_fr_num=1;
    
    canTouch=true;
    
    canDestroy=true;
    

    /* 乱数系列の変更 */
	srand((unsigned)time(NULL));
    
    // タッチ有効化
	setTouchEnabled(true);
	setTouchMode(kCCTouchesOneByOne);
    
    CCLOG("FriendsScene::initValue");
}

//初期化
bool FriendsScene::init(){
    //CCLOG("FriendsScene::init");
    if (CCLayer::init()) {
        
        initValue();
        
        
        m_frameCashe->addSpriteFramesWithFile("friends.plist");
        m_frameCashe->addSpriteFramesWithFile("chara.plist");

        
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
void FriendsScene::setObjectPosition(){
    //サイズ別にセット
    if (m_winSize.height==1136) {
        //4インチ
        yMinus=0;
        
    } else {
        yMinus=44;
        
        NativeManager::closeIconView();
    }
    
    m_p_wallButton=ccp(100, 300);
    
    //戻るボタン
    m_p_BackButton = ccp(560, 173);
    
    //Twitterボタン
    
    m_p_chara = ccp(320, 807);
    
    m_p_panel = ccp(320,311);
    
    m_p_maru = ccp(0, 920);
    
    m_p_title= ccp(322, 967);
    m_p_name= ccp(325, 440);
    
    
    m_p_zukan= ccp(550, 855);
}

#pragma mark 背景セット
void FriendsScene::setBackGround(){
    //背景
    //黒
    m_backGroundSprite=CCSprite::createWithSpriteFrameName("zukan_bg.png");
    pos00(m_backGroundSprite);
    this->addChild(m_backGroundSprite,kGameLayerBackground0);
    
    ///////////////
    // !!!:自作のviewPagerをadd
    m_pager=FriendPagerLayer::create();
    this->addChild(m_pager,kGameLayerOnBg1);
    
    //表示する大きさと座標　　anchor(0,0)で
    m_pager->prepere(640,583, ccp(0,420));
    
    
    tapEffect = TapEffectLayer::create();
    this->addChild(tapEffect,kGameLayerOnBg4);

}

#pragma mark メニューアイテムをセット
void FriendsScene::setMenuItem(){
    
    //メニュ
    //おすすめアプリ
    MyEasyMenuItem* _rew=MyEasyMenuItem::create("btn_wall.png", m_p_wallButton, this, menu_selector(FriendsScene::tapButton));
    
    //もどる
    MyEasyMenuItem *_backItem = MyEasyMenuItem::create("btn_back.png", m_p_BackButton, this, menu_selector(FriendsScene::tapButton));
    
    //CCMenu *_menuS = CCMenu::create(_rev,_rew,_menuItem,_backItem,NULL);
    CCMenu *_menuS = CCMenu::create(_rew,_backItem,NULL);
    
	_menuS->setPosition(ccp(0, 0));
    this->addChild(_menuS);
    

    
    
    
    
}

//毎回呼ばれるメインループ
void FriendsScene::mainLoop(){
    i_nowSec=floor(GetSecond());
    
    
}


void FriendsScene::gameStart(){
    //ループ系スタート
    this->schedule(schedule_selector(FriendsScene::mainLoop), 1);
    
    
    
}

#pragma mark ボタンタップ処理

//もどる
void FriendsScene::tapButton(CCObject *pSender){
    int _scene=SaveUtil::getSaveInt(USERDEFAULT_FROM_LAUCH);
    CCTransitionFade *transition;
    switch (_scene) {
        case klaunchSceneIdo:
            transition=CCTransitionFade::create(FLOAT_SCENE_MOVE_TIME, GameScene::scene());
            break;
        case klaunchSceneIke:
            transition=CCTransitionFade::create(FLOAT_SCENE_MOVE_TIME, LakeScene::scene());
            break;
        case klaunchSceneHaka:
            transition=CCTransitionFade::create(FLOAT_SCENE_MOVE_TIME, GraveScene::scene());
            break;
        case klaunchSceneSetting:
            transition=CCTransitionFade::create(FLOAT_SCENE_MOVE_TIME, SettingScene::scene());
            break;
        default:
            transition=CCTransitionFade::create(FLOAT_SCENE_MOVE_TIME, GameScene::scene());
            break;
    }
    CCDirector::sharedDirector()->replaceScene(transition);

}



#pragma mark エンター
void FriendsScene::onEnter(){
    CCLayer::onEnter();
    
    // !!!:------Google Analytics
    NativeManager::sendName2GA(SCENE_NAME_SETTING);
}

#pragma mark エンターフィニッシュ
void FriendsScene::onEnterTransitionDidFinish(){
    CCLayer::onEnterTransitionDidFinish();

    //gameStart();
}

#pragma mark Exit
void FriendsScene::onExit(){
    CCLayer::onExit();

    
    //スケジュール全部止める
    
    
}

#pragma mark Exitスタート
void FriendsScene::onExitTransitionDidStart(){
    CCLayer::onExitTransitionDidStart();
    
    SaveUtil::saveInt(USERDEFAULT_FROM_LAUCH,klaunchSceneAlbumAScene);
}



#pragma mark バックグラウンドにまわる時よぶfunc
void FriendsScene::onPause(){
    CCLOG("onPause");
}


bool FriendsScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    if (canTouch==false) return true;
	
    // タッチ開始時の座標を保存
	CCDirector *pDirector = CCDirector::sharedDirector();
	touchStartPoint = pDirector->convertToGL(pTouch->getLocationInView());
    
        tapEffect->show(touchStartPoint);
    
	return true;
}
/*
void FriendsScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
    if (canTouch==false) return;
    
	// タップポイント取得
	CCDirector *pDirector = CCDirector::sharedDirector();
	CCPoint tpoint = pDirector->convertToGL(pTouch->getLocationInView());
    
    
}

// スワイプ中
void FriendsScene::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent) {
    CCLog("ccTouchMoved");
    if (canTouch==false) return;
    
	// タップポイント取得
	CCDirector *pDirector = CCDirector::sharedDirector();
	CCPoint tpoint = pDirector->convertToGL(pTouch->getLocationInView());
    
    
}
// タップキャンセル時
void FriendsScene::ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent) {
    CCLog("TouchCancelled");
    if (canTouch==false) return;
    
	// タップポイント取得
	CCDirector *pDirector = CCDirector::sharedDirector();
	CCPoint tpoint = pDirector->convertToGL(pTouch->getLocationInView());
    
}
*/
