//
//  GraveScene.cpp
//
//
//  Created by dotchi on 2014/06/02.
//
//
#import "GraveScene.h"

#import "SimpleAudioEngine.h"

#import "Game.h"
#import "GameUtil.h"

#import "NativeManager.h"
#import "SaveUtil.h"
#import "MySoundONOFFMenuItem.h"
#import "MyEasyMenuItem.h"
#import "MyButtonUtil.h"
#import "GraveScene.h"
#import "AndroidUtil.h"

#import "MyAnimationUtil.h"

#import "HowToScene.h"
#import "IdoAnaScene.h"
#import "FriendsScene.h"

#import "GameScene.h"
#import "SettingScene.h"

#import <list>


USING_NS_CC;
using namespace std;

GraveScene::~GraveScene(){
    //デストラクタ
    if (canDestroy) {
        //CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("setting.plist");
        //CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    }
    
}


CCScene* GraveScene::scene(){
    CCScene* scene=CCScene::create();
    GraveScene* layer=GraveScene::create();
    scene->addChild(layer);
    return scene;
}

#pragma mark 変数初期化
void GraveScene::initValue(){
    
	m_winSize = CCDirector::sharedDirector()->getWinSize();
    
    m_utils=GameUtil::create();
    this->addChild(m_utils,kGameLayerBackground0);
    
    m_winSize=CCDirector::sharedDirector()->getWinSize();
    
    m_frameCashe=CCSpriteFrameCache::sharedSpriteFrameCache();
    
    nowStageNum=SaveUtil::getSaveInt(USERDEFAULT_STAGE, 1);
    
    nowHasPoint=SaveUtil::getSaveInt(USERDEFAULT_NOW_HAS_POINT, 0);
    
    canTouch=true;
    
    canDestroy=true;
    
    intLevelState();
    
    /* 乱数系列の変更 */
	srand((unsigned)time(NULL));
    
    // タッチ有効化
	setTouchEnabled(true);
	setTouchMode(kCCTouchesOneByOne);
    
}

        // !!!:init
bool GraveScene::init(){
    //CCLOG("GraveScene::init");
    if (CCLayer::init()) {
        
        initValue();
        
        
        //m_frameCashe->addSpriteFramesWithFile("setting.plist");
        
        
        //画面位置をセット
        setObjectPosition();
        
        //背景をセット
        setBackGround();
        
        //メニューアイテムをセット
        setMenuItem();

        //汚れレイヤー
        m_yogoreLayer=TombLayer::create();
        m_yogoreLayer->prepare();
        this->addChild(m_yogoreLayer,kGameLayerOnBg1);
        
        //敵レイヤー
        m_enemyLayer= EnemyLayer::create();
        m_enemyLayer->setMode(klaunchSceneHaka);
        this->addChild(m_enemyLayer,kGameLayerOnBg2);
        
        //菓子レイヤー
        m_kasiLayer=KashiLayer::create();
        m_kasiLayer->setMode(klaunchSceneHaka);
        this->addChild(m_kasiLayer,kGameLayerOnBg3);
        

        
        
        
        //-------------------デバッグ
        //メーターの数字
        m_Label_enemy = CCLabelTTF::create("0", FONT_NAME_Marker,21);
        m_Label_enemy->setAnchorPoint(ccp(1, 1));
        m_Label_enemy->setPosition(ccp(640,960));
        m_Label_enemy->setColor(ccWHITE);
        CCString* cntS=CCString::createWithFormat("Has point : %d",nowHasPoint);
        m_Label_enemy->setString(cntS->getCString());
        this->addChild(m_Label_enemy,kGameLayerDebugText);
        
        //-------------------

        updateScore(0);
        
        
        if (SaveUtil::getSaveBool(USERDEFAULT_STAGE_FIRST_HAKA, false)==false) {
            //墓に始めてきた チュートリアル出す
            SaveUtil::saveBool(USERDEFAULT_STAGE_FIRST_HAKA, true);
        }
        
        
        
        // !!!:init抜ける
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
void GraveScene::setObjectPosition(){
    //サイズ別にセット
    if (m_winSize.height==1136) {
        //4インチ
        yMinus=0;
        
    } else {
        yMinus=44;
        
        NativeManager::closeIconView();
    }
    
    m_pt_tableView=ccp(0,300);
    
    m_pt_arrowBtn_L=ccp(52,647);
    
    m_pt_arrowBtn_R=ccp(588,647);
    
    //メーター位置
    m_p_meter = ccp(0, 702-yMinus);
    
    m_pt_wall=ccp(340,1000);
    m_pt_okashi=ccp(50, 207);
    m_pt_kumotsu=ccp(174, 207);
    m_pt_friends=ccp(328, 207);
    m_pt_setting=ccp(482, 207);
}

#pragma mark 背景セット
void GraveScene::setBackGround(){
    //背景
    //黒
    m_backGroundSprite=CCSprite::createWithSpriteFrameName("bg_grave.png");
    pos00(m_backGroundSprite);
    this->addChild(m_backGroundSprite,kGameLayerBackground0);
    
    meterSp = MeterLayer::create();

    //メーター全部入りをadd
    this->addChild(meterSp,kGameLayerOnBg3);
    
    tapEffect = TapEffectLayer::create();
    this->addChild(tapEffect,kGameLayerOnBg4);
    
}

#pragma mark メニューアイテムをセット
void GraveScene::setMenuItem(){
    
    m_btnLayer=CommonBtnLayer::create();
    m_btnLayer->prepare(this, menu_selector(GraveScene::onEsaClick), menu_selector(GraveScene::tapItems), menu_selector(GraveScene::tapFriends), menu_selector(GraveScene::tapSetting), menu_selector(GraveScene::tapWallButton));
    this->addChild(m_btnLayer,kGameLayerMenu);
    
    //ひだり
    //MyEasyMenuItem *_arrowLItem = MyEasyMenuItem::create("arrow_l.png", m_pt_arrowBtn_L, this, menu_selector(GraveScene::onArrowLClick));
    //みぎ
    MyEasyMenuItem *_arrowRItem = MyEasyMenuItem::create("btn_arrow_r.png", m_pt_arrowBtn_R, this, menu_selector(GraveScene::onArrowRClick));
    
    CCMenu *_menuS = CCMenu::create(_arrowRItem,NULL);
    
	_menuS->setPosition(ccp(0, 0));
    this->addChild(_menuS,kGameLayerMenu);
    
}

//毎回呼ばれるメインループ
void GraveScene::mainLoop(){
    i_nowSec=floor(GetSecond());
    
    
}


#pragma mark onResume
void GraveScene::onResume(){
    
    nowHasPoint=SaveUtil::getSaveInt(USERDEFAULT_NOW_HAS_POINT);
    
    
    updateScore(0);

    
    //アプリ終了時の時間
    int savedSec=SaveUtil::getSaveInt(USERDEFAULT_HAKA_PAUSE_TIME);
    //終了時間から計算して　オブジェクト生成
    i_nowSec = floor(GetSecond());
    
    //敵
    if (savedSec!=0) {
        int _n=(i_nowSec-savedSec)/TIME_ENEMY_MAKE_SEC;
        CCLOG("jikan kara make suru teki ha = %d",_n);
        for (int i=0; i<_n; i++) {
            m_enemyLayer->enemyCreateLoop();
            if (ENEMY_MAKE_MAX<i)break;
        }
    }
    
    //菓子
    if (savedSec!=0) {
        int _n=(i_nowSec-savedSec)/TIME_KASI_MAKE_SEC;
        CCLOG("-----jikan kara make suru okashi ha = %d",_n);
        for (int i=0; i<_n; i++) {
            m_kasiLayer->okashiCreateLoop();
            if (KASI_MAKE_MAX<i)break;
        }
    }
    
    //汚れ
    if (savedSec!=0) {
        int _n=(i_nowSec-savedSec)/TIME_TOMB_DIRTY;
        CCLOG("-----------jikan kara make suru yogore ha = %d",_n);
        for (int i=0; i<_n; i++) {
            m_yogoreLayer->enemyCreateLoop();
            if (KASI_MAKE_MAX<i)break;
        }
    }
    
    
    //ループ系スタート
    this->schedule(schedule_selector(GraveScene::mainLoop), 1);
    
    m_enemyLayer->startLoop();
    
    m_kasiLayer->startLoop();
    
    m_yogoreLayer->startLoop();
    
}

#pragma mark -----ボタンタップ処理
void GraveScene::tapFriends(CCObject *pSender){
    //シーン移動
    changeSceneFade(FriendsScene::scene())
}
//
void GraveScene::tapWallButton(CCObject *pSender){
    
}
//
void GraveScene::tapItems(CCObject *pSender){
    
}
//
void GraveScene::tapSetting(CCObject *pSender){
    changeSceneFade(SettingScene::scene())
}

void GraveScene::onEsaClick(CCObject *pSender){
    //シーン移動
    changeSceneFade(IdoAnaScene::scene())
}


void GraveScene::onArrowLClick(CCObject *pSender){
    //シーン移動
    CCTransitionSlideInL* _transition=CCTransitionSlideInL::create(FLOAT_SCENE_MOVE_TIME, GraveScene::scene());
    CCDirector::sharedDirector()->replaceScene(_transition);
}

void GraveScene::onArrowRClick(CCObject *pSender){
    //シーン移動
    CCTransitionSlideInR* _transition=CCTransitionSlideInR::create(FLOAT_SCENE_MOVE_TIME, GameScene::scene());
    CCDirector::sharedDirector()->replaceScene(_transition);
}


#pragma mark タッチ処理
bool GraveScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    if (canTouch==false) return false;
	
    // タッチ開始時の座標を保存
	CCDirector *pDirector = CCDirector::sharedDirector();
	touchStartPoint = pDirector->convertToGL(pTouch->getLocationInView());
    
    tapEffect->show(touchStartPoint);
    
	return true;
}

void GraveScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
    if (canTouch==false) return;
    
	// タップポイント取得
	CCDirector *pDirector = CCDirector::sharedDirector();
	CCPoint tpoint = pDirector->convertToGL(pTouch->getLocationInView());
    
    //おかし　排除
    int k=m_kasiLayer->touchOkashiSpFunc(tpoint);
    if(0<=k){
        return;
    }
    
    //敵　排除
    int n=m_enemyLayer->deleteSpriteFunc(tpoint);
    updateScore(n);
    
    //汚れ排除
    m_yogoreLayer->deleteSpriteFunc(tpoint);

}

// スワイプ中
void GraveScene::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent) {
    if (canTouch==false) return;
    
	// タップポイント取得
	CCDirector *pDirector = CCDirector::sharedDirector();
	CCPoint tpoint = pDirector->convertToGL(pTouch->getLocationInView());
    //CCLog("ccTouchMoved x=%f y=%f",tpoint.x,tpoint.y);
    
    int n=m_enemyLayer->deleteSpriteFunc(tpoint);
    updateScore(n);
    
    
}
// タップキャンセル時
void GraveScene::ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent) {
    CCLog("TouchCancelled");
    if (canTouch==false) return;
    
}

#pragma mark エンター
void GraveScene::onEnter(){
    CCLayer::onEnter();
    
    //通知受け取り設定
    My_setNotify(GraveScene::onPause, NOTIFICATION_PAUSE)
    My_setNotify(GraveScene::onResume, NOTIFICATION_RESUME)
    
    // !!!:------Google Analytics
    NativeManager::sendName2GA(SCENE_NAME_SETTING);
    
    onResume();
}

#pragma mark エンターフィニッシュ
void GraveScene::onEnterTransitionDidFinish(){
    CCLayer::onEnterTransitionDidFinish();


}

#pragma mark Exit
void GraveScene::onExit(){
    CCLayer::onExit();
    //通知受け取り解放
    My_unSetNotify(NOTIFICATION_PAUSE)
    My_unSetNotify(NOTIFICATION_RESUME)


    
}

#pragma mark Exitスタート
void GraveScene::onExitTransitionDidStart(){
    CCLayer::onExitTransitionDidStart();
    
    SaveUtil::saveInt(USERDEFAULT_FROM_LAUCH,klaunchSceneHaka);
    
    //Pause
    onPause();
}




#pragma mark onPause
void GraveScene::onPause(){
    CCLOG("onPause");
    
    this->unscheduleAllSelectors();
    
    m_enemyLayer->stopLoop();
    m_enemyLayer->saveEnemyPosition();
    
    
    m_kasiLayer->stopLoop();
    m_kasiLayer->saveKasiPosition();
    
    //所持ポイント
    SaveUtil::saveInt(USERDEFAULT_NOW_HAS_POINT, nowHasPoint);
    
    //ステージ
    SaveUtil::saveInt(USERDEFAULT_STAGE, nowStageNum);
    
    i_nowSec = floor(GetSecond());
    //アプリ終了時の時間
    SaveUtil::saveInt(USERDEFAULT_HAKA_PAUSE_TIME,i_nowSec);
}





    // !!!:数字とかメーター更新
void GraveScene::updateScore(int n){
    nowHasPoint+=n;
    
    //メーターのスケールいじる
    float _wper=nowHasPoint/(float)nowLevelUpLimit;
    //timeMeterSp->setScaleX(_wper);

    CCString* cntS=CCString::createWithFormat("Has point : %d",nowHasPoint);
    m_Label_enemy->setString(cntS->getCString());
    
    meterSp->upDateMeter(_wper);
}




void GraveScene::onTableClose(CCObject *pSender){

}




// !!!:ステージ数から、レベルアップまでのポイント、等を返す
void GraveScene::intLevelState(){
    

    
    if(nowStageNum==1){

		nowLevelUpLimit = INT_EVOLUTION_2;

        
    }else if (nowStageNum==2){

		nowLevelUpLimit = INT_EVOLUTION_3;

        
    }else if (nowStageNum==3){

		nowLevelUpLimit = INT_EVOLUTION_4;

        
    }else if (nowStageNum==4){

		nowLevelUpLimit = INT_EVOLUTION_5;

        
    }else if (nowStageNum==5){

		nowLevelUpLimit = INT_EVOLUTION_6;

        
    }else if (nowStageNum==6){

		nowLevelUpLimit = INT_EVOLUTION_7;

    }else if (nowStageNum==7){

		nowLevelUpLimit = INT_EVOLUTION_8;

    }else if (nowStageNum==8){

		nowLevelUpLimit = INT_EVOLUTION_9;

    }else if (nowStageNum==9){

		nowLevelUpLimit = INT_EVOLUTION_10;

    }else if (nowStageNum==10){

		nowLevelUpLimit = INT_EVOLUTION_10;
        
    }else{
        
		nowLevelUpLimit = INT_EVOLUTION_10;
        
    }

}

