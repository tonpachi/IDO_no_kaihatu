//
//  TempScene.cpp
//
//
//  Created by dotchi on 2014/06/02.
//
//
#import "TempScene.h"

#import "SimpleAudioEngine.h"

#import "Game.h"
#import "GameUtil.h"

#import "NativeManager.h"
#import "SaveUtil.h"
#import "MySoundONOFFMenuItem.h"
#import "MyEasyMenuItem.h"
#import "MyButtonUtil.h"
#import "GameScene.h"
#import "AndroidUtil.h"

#import "HowToScene.h"

USING_NS_CC;


TempScene::~TempScene(){
    //デストラクタ
    if (canDestroy) {
        //CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("setting.plist");
        //CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    }

}


CCScene* TempScene::scene(){
    CCScene* scene=CCScene::create();
    TempScene* layer=TempScene::create();
    scene->addChild(layer);
    return scene;
}

#pragma mark 変数初期化
void TempScene::initValue(){
    
	m_winSize = CCDirector::sharedDirector()->getWinSize();
    
    m_utils=GameUtil::create();
    this->addChild(m_utils,kGameLayerBackground0);
    
    m_winSize=CCDirector::sharedDirector()->getWinSize();
    
    m_frameCashe=CCSpriteFrameCache::sharedSpriteFrameCache();
    
    i_nowStageNum=SaveUtil::getSaveInt(USERDEFAULT_STAGE, 1);
    
    canTouch=true;
    
    canDestroy=true;
    
    /* 乱数系列の変更 */
	srand((unsigned)time(NULL));
    
    // タッチ有効化
	setTouchEnabled(true);
	setTouchMode(kCCTouchesOneByOne);
}

//初期化
bool TempScene::init(){
    //CCLOG("TempScene::init");
    if (CCLayer::init()) {
        
        initValue();

        //m_frameCashe->addSpriteFramesWithFile("setting.plist");
        

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
void TempScene::setObjectPosition(){
    //サイズ別にセット
    if (m_winSize.height==1136) {
        //4インチ
        yMinus=0;

    } else {
        yMinus=44;
        
        NativeManager::closeIconView();
    }
    
    
    
}

#pragma mark 背景セット
void TempScene::setBackGround(){
    //背景
    //黒
    m_backGroundSprite=CCSprite::createWithSpriteFrameName("TempScene_bg.png");
    pos00(m_backGroundSprite);
    this->addChild(m_backGroundSprite);
    
}

#pragma mark メニューアイテムをセット
void TempScene::setMenuItem(){
    
    
    MyEasyMenuItem *_backItem = MyEasyMenuItem::create("top_set_btn.png", ccp(320, 307), this, menu_selector(TempScene::tapButton));


    CCMenu *_menuS = CCMenu::create(_backItem,NULL);

	_menuS->setPosition(ccp(0, 0));
    this->addChild(_menuS);

    
}

//毎回呼ばれるメインループ
void TempScene::mainLoop(){
    i_nowSec=floor(GetSecond());
    
    
}

#pragma mark onPause
void TempScene::onPause(){
    CCLOG("onPause");
    //ループ系ストップ
    this->unscheduleAllSelectors();
    //ステージ
    SaveUtil::saveInt(USERDEFAULT_STAGE, i_nowStageNum);
    
    i_nowSec = floor(GetSecond());
    
    //アプリ終了時の時間
    SaveUtil::saveInt(USERDEFAULT_APP_PAUSE_TIME,i_nowSec);
    
}

#pragma mark onResume
void TempScene::onResume(){
    CCLOG("onResume");
    //ループ系スタート
    this->schedule(schedule_selector(TempScene::mainLoop), 1);
    

}

#pragma mark ボタンタップ処理

void TempScene::tapButton(CCObject *pSender){
    //
    changeSceneFade(GameScene::scene())
}




#pragma mark エンター
void TempScene::onEnter(){
    CCLayer::onEnter();
    //通知受け取り設定
    My_setNotify(TempScene::onPause, NOTIFICATION_PAUSE)
    My_setNotify(TempScene::onResume, NOTIFICATION_RESUME)
    
    
    // !!!:------Google Analytics
    NativeManager::sendName2GA(SCENE_NAME_SETTING);
}

#pragma mark エンターフィニッシュ
void TempScene::onEnterTransitionDidFinish(){
    CCLayer::onEnterTransitionDidFinish();
    SaveUtil::saveInt(USERDEFAULT_FROM_LAUCH,kSetingScene);
    
    
    onResume();
}

#pragma mark Exit
void TempScene::onExit(){
    CCLayer::onExit();
    //通知受け取り解放
    My_unSetNotify(NOTIFICATION_PAUSE)
    My_unSetNotify(NOTIFICATION_RESUME)
    
    //スケジュール全部止める

    
}

#pragma mark Exitスタート
void TempScene::onExitTransitionDidStart(){
    CCLayer::onExitTransitionDidStart();
}












bool TempScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    if (!canTouch) return true;
	
    // タッチ開始時の座標を保存
	CCDirector *pDirector = CCDirector::sharedDirector();
	touchStartPoint = pDirector->convertToGL(pTouch->getLocationInView());

    
	return true;
}

void TempScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
    if (!canTouch) return;
    
	// タップポイント取得
	CCDirector *pDirector = CCDirector::sharedDirector();
	CCPoint tpoint = pDirector->convertToGL(pTouch->getLocationInView());

    
}

// スワイプ中
void TempScene::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent) {
    CCLog("ccTouchMoved");
    if (!canTouch) return;
    
	// タップポイント取得
	CCDirector *pDirector = CCDirector::sharedDirector();
	CCPoint tpoint = pDirector->convertToGL(pTouch->getLocationInView());
    
    
}
// タップキャンセル時
void TempScene::ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent) {
    CCLog("TouchCancelled");
    if (!canTouch) return;
    
	// タップポイント取得
	CCDirector *pDirector = CCDirector::sharedDirector();
	CCPoint tpoint = pDirector->convertToGL(pTouch->getLocationInView());
    
}

