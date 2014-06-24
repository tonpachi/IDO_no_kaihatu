//
//  EvolutionScene.cpp
//
//
//  Created by dotchi on 2014/06/02.
//
//
#import "EvolutionScene.h"

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

#import "My4SpritePager.h"

USING_NS_CC;


EvolutionScene::~EvolutionScene(){
    //デストラクタ
    if (canDestroy) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("evo.plist");
        CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(usePlistName);
        
        CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    }
    
}


CCScene* EvolutionScene::scene(){
    CCScene* scene=CCScene::create();
    EvolutionScene* layer=EvolutionScene::create();
    scene->addChild(layer);
    return scene;
}

#pragma mark 変数初期化
void EvolutionScene::initValue(){
    
	m_winSize = CCDirector::sharedDirector()->getWinSize();
    
    m_utils=GameUtil::create();
    this->addChild(m_utils,kGameLayerBackground0);
    
    m_winSize=CCDirector::sharedDirector()->getWinSize();
    
    m_frameCashe=CCSpriteFrameCache::sharedSpriteFrameCache();
    
    nowStageNum=SaveUtil::getSaveInt(USERDEFAULT_STAGE, 1);
    
    canTouch=true;
    
    canDestroy=true;
    
    /* 乱数系列の変更 */
	srand((unsigned)time(NULL));
    
    // タッチ有効化
	setTouchEnabled(true);
	setTouchMode(kCCTouchesOneByOne);
}

//初期化
bool EvolutionScene::init(){
    //CCLOG("EvolutionScene::init");
    if (CCLayer::init()) {
        
        initValue();
        
        
        
        m_frameCashe->addSpriteFramesWithFile("evo.plist");
        
        
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
void EvolutionScene::setObjectPosition(){
    //サイズ別にセット
    if (m_winSize.height==1136) {
        //4インチ
        yMinus=0;
        
    } else {
        yMinus=44;
        
        NativeManager::closeIconView();
    }
    
    //戻るボタン
    m_p_BackButton = ccp(560, 173);
    
    //Twitterボタン
    m_p_Tw = ccp(317, 173);
    
}

#pragma mark 背景セット
void EvolutionScene::setBackGround(){
    //背景
    //黒
    m_backGroundSprite=GameUtil::makeBlackBg(m_winSize.width, m_winSize.height);
    pos00(m_backGroundSprite);
    this->addChild(m_backGroundSprite);
    
}

#pragma mark メニューアイテムをセット
void EvolutionScene::setMenuItem(){
    
    //メニュー
    //おすすめアプリ
    //MyEasyMenuItem* _rew=MyEasyMenuItem::create("btn_wall.png", m_p_wallButton, this, menu_selector(FriendsScene::tapButton));
    
    //もどる
    MyEasyMenuItem *_backItem = MyEasyMenuItem::create("btn_back.png", m_p_BackButton, this, menu_selector(EvolutionScene::tapButton));
    
    //TW
    MyEasyMenuItem *twMenuItem = MyEasyMenuItem::create("zukan_tw_btn.png", m_p_Tw, this, menu_selector(EvolutionScene::tapTw));
    
    _menuS = CCMenu::create(_backItem,twMenuItem,NULL);
    
	_menuS->setPosition(ccp(0, 0));
    this->addChild(_menuS);

    _menuS->setVisible(false);
}



//毎回呼ばれるメインループ
void EvolutionScene::mainLoop(){
    i_nowSec=floor(GetSecond());
    
    
}


void EvolutionScene::gameStart(){
    //ループ系スタート
    //this->schedule(schedule_selector(EvolutionScene::mainLoop), 1);
    //アニメーション開始
    
    
}

#pragma mark ボタンタップ処理

//もどる
void EvolutionScene::tapButton(CCObject *pSender){
    
}

//TWボタンタップ
void EvolutionScene::tapTw(CCObject *pSender){
    
}



#pragma mark エンター
void EvolutionScene::onEnter(){
    CCLayer::onEnter();
    
    //通知受け取り設定
    My_setNotify(EvolutionScene::onPause, NOTIFICATION_PAUSE)
        My_setNotify(EvolutionScene::onPause, NOTIFICATION_TWEET_DONE)
    
    // !!!:------Google Analytics
    NativeManager::sendName2GA(SCENE_NAME_SETTING);
}

#pragma mark エンターフィニッシュ
void EvolutionScene::onEnterTransitionDidFinish(){
    CCLayer::onEnterTransitionDidFinish();

    this->scheduleOnce(schedule_selector(EvolutionScene::gameStart),1);
}

#pragma mark Exit
void EvolutionScene::onExit(){
    CCLayer::onExit();
    //通知受け取り解放
    My_unSetNotify(NOTIFICATION_PAUSE)
     My_unSetNotify(NOTIFICATION_TWEET_DONE)
    //スケジュール全部止める
    
    
}

#pragma mark Exitスタート
void EvolutionScene::onExitTransitionDidStart(){
    CCLayer::onExitTransitionDidStart();
}



#pragma mark バックグラウンドにまわる時よぶfunc
void EvolutionScene::onPause(){
    CCLOG("onPause");
    //ステージ
    SaveUtil::saveInt(USERDEFAULT_STAGE, nowStageNum);
    
    i_nowSec = floor(GetSecond());
    
    //アプリ終了時の時間
    SaveUtil::saveInt(USERDEFAULT_APP_PAUSE_TIME,i_nowSec);
}



void EvolutionScene::show4komaDialog(int stageNum){
    canTouch=false;
    
    // !!!:自作のviewPagerをadd
    My4SpritePager* _pager=My4SpritePager::create();
    this->addChild(_pager,kGameLayerDialog);
    
    //表示する大きさと座標　　anchor(0,0)
    _pager->prepere(640,583, ccp(0,420));
    
    //plistからPNG名配列返す
    CCArray * animFrames =get4KomaPlistNameAndPng(stageNum);
    for (int x=0; x<4; x++) {
        //必要な分 画像をadd
        CCString* _s=(CCString *)animFrames->objectAtIndex(x);
        _pager->addSpByFilename(_s->getCString());
    }
    
    //------------------------------------初期状態
    _pager->mySetShowPage(0);
    
    //-----下のボタンと、タッチの優先度を合わせる
    _pager->setTouchPriority(kCCMenuHandlerPriority);
    
    _pager->setTag(ADD_LAYER_TAG);
    
    _menuS->setVisible(true);
}




bool EvolutionScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    if (!canTouch) return true;
	
    // タッチ開始時の座標を保存
	CCDirector *pDirector = CCDirector::sharedDirector();
	touchStartPoint = pDirector->convertToGL(pTouch->getLocationInView());
    
    
	return true;
}

void EvolutionScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
    if (!canTouch) return;
    
	// タップポイント取得
	CCDirector *pDirector = CCDirector::sharedDirector();
	CCPoint tpoint = pDirector->convertToGL(pTouch->getLocationInView());
    
    
}

// スワイプ中
void EvolutionScene::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent) {
    CCLog("ccTouchMoved");
    if (!canTouch) return;
    
	// タップポイント取得
	CCDirector *pDirector = CCDirector::sharedDirector();
	CCPoint tpoint = pDirector->convertToGL(pTouch->getLocationInView());
    
    
}
// タップキャンセル時
void EvolutionScene::ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent) {
    CCLog("TouchCancelled");
    if (!canTouch) return;
    
	// タップポイント取得
	CCDirector *pDirector = CCDirector::sharedDirector();
	CCPoint tpoint = pDirector->convertToGL(pTouch->getLocationInView());
    
}


#pragma mark ステージ数で、使うpngの名前4つを返す
CCArray* EvolutionScene::get4KomaPlistNameAndPng(int stage) {
    //使う4コマplist読み込む usePlistName
    m_frameCashe->addSpriteFramesWithFile("koma_1.plist");
    
    CCArray *itemS = CCArray::createWithContentsOfFile("pngname_yonkoma.plist");
    CCArray *item=(CCArray *)itemS->objectAtIndex(stage);
    return item;
}
