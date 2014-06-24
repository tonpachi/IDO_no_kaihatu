//
//  TitleScene.cpp
//
//
//  Created by dotchi on 2014/06/02.
//
//
#import "TitleScene.h"

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


TitleScene::~TitleScene(){
    //デストラクタ
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("top.plist");
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();

}


CCScene* TitleScene::scene(){
    CCScene* scene=CCScene::create();
    TitleScene* layer=TitleScene::create();
    scene->addChild(layer);
    return scene;
}

#pragma mark 変数初期化
void TitleScene::initValue(){
    
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
bool TitleScene::init(){
    //CCLOG("TitleScene::init");
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
void TitleScene::setObjectPosition(){
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
void TitleScene::setBackGround(){
    //背景
    //黒
    m_backGroundSprite=CCSprite::createWithSpriteFrameName("title_bg.png");
    pos00(m_backGroundSprite);
    this->addChild(m_backGroundSprite);
    
}

#pragma mark メニューアイテムをセット
void TitleScene::setMenuItem(){
    
    
    MyEasyMenuItem *_backItem = MyEasyMenuItem::create("btn_title_start.png", ccp(320, 307), this, menu_selector(TitleScene::tapButton));


    CCMenu *_menuS = CCMenu::create(_backItem,NULL);

	_menuS->setPosition(ccp(0, 0));
    this->addChild(_menuS);

    
}

//毎回呼ばれるメインループ
void TitleScene::mainLoop(){
    i_nowSec=floor(GetSecond());
    
    
}


void TitleScene::gameStart(){
    //ループ系スタート
    this->schedule(schedule_selector(TitleScene::mainLoop), 1);
    
    
    
}

#pragma mark ボタンタップ処理

void TitleScene::tapButton(CCObject *pSender){
    //
    changeSceneFade(GameScene::scene())
}




#pragma mark エンター
void TitleScene::onEnter(){
    CCLayer::onEnter();
    
    //通知受け取り設定
    My_setNotify(TitleScene::onPause, NOTIFICATION_PAUSE)
    
    // !!!:------Google Analytics
    NativeManager::sendName2GA(SCENE_NAME_SETTING);
}

#pragma mark エンターフィニッシュ
void TitleScene::onEnterTransitionDidFinish(){
    CCLayer::onEnterTransitionDidFinish();
    
    gameStart();
}

#pragma mark Exit
void TitleScene::onExit(){
    CCLayer::onExit();
    //通知受け取り解放
    My_unSetNotify(NOTIFICATION_PAUSE)
    
    //スケジュール全部止める

    
}

#pragma mark Exitスタート
void TitleScene::onExitTransitionDidStart(){
    CCLayer::onExitTransitionDidStart();
    
    SaveUtil::saveInt(USERDEFAULT_FROM_LAUCH,klaunchSceneAppDeligate);
}



#pragma mark バックグラウンドにまわる時よぶfunc
void TitleScene::onPause(){
    CCLOG("onPause");
    //ステージ
    SaveUtil::saveInt(USERDEFAULT_STAGE, i_nowStageNum);

    i_nowSec = floor(GetSecond());
    
    //アプリ終了時の時間
    SaveUtil::saveInt(USERDEFAULT_APP_PAUSE_TIME,i_nowSec);
}








bool TitleScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    if (canTouch==false) return true;
	
    // タッチ開始時の座標を保存
	CCDirector *pDirector = CCDirector::sharedDirector();
	touchStartPoint = pDirector->convertToGL(pTouch->getLocationInView());

    
	return true;
}

void TitleScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
    if (canTouch==false) return;
    
	// タップポイント取得
	CCDirector *pDirector = CCDirector::sharedDirector();
	CCPoint tpoint = pDirector->convertToGL(pTouch->getLocationInView());

    
}

// スワイプ中
void TitleScene::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent) {
    CCLog("ccTouchMoved");
    if (canTouch==false) return;
    
	// タップポイント取得
	CCDirector *pDirector = CCDirector::sharedDirector();
	CCPoint tpoint = pDirector->convertToGL(pTouch->getLocationInView());
    
    
}
// タップキャンセル時
void TitleScene::ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent) {
    CCLog("TouchCancelled");
    if (canTouch==false) return;
    
	// タップポイント取得
	CCDirector *pDirector = CCDirector::sharedDirector();
	CCPoint tpoint = pDirector->convertToGL(pTouch->getLocationInView());
    
}

