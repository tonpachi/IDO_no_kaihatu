//
//  GameScene.cpp
//
//
//  Created by dotchi on 2014/06/02.
//
//
#import "GameScene.h"

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

#import "MyAnimationUtil.h"

#import "HowToScene.h"
#import "IdoAnaScene.h"
#import "FriendsScene.h"

#import "GraveScene.h"
#import "LakeScene.h"

#import "EvolutionScene.h"

#import "SettingScene.h"

#import "My4SpritePager.h"

#import <list>


USING_NS_CC;
using namespace std;

GameScene::~GameScene(){
    //デストラクタ
    if (canDestroy) {
        //CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("setting.plist");
        //CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    }
    
}


CCScene* GameScene::scene(){
    CCScene* scene=CCScene::create();
    GameScene* layer=GameScene::create();
    scene->addChild(layer);
    return scene;
}

#pragma mark 変数初期化
void GameScene::initValue(){
    
	m_winSize = CCDirector::sharedDirector()->getWinSize();
    
    m_utils=GameUtil::create();
    this->addChild(m_utils,kGameLayerBackground0);
    
    
    m_frameCashe=CCSpriteFrameCache::sharedSpriteFrameCache();
    
    nowStageNum=SaveUtil::getSaveInt(USERDEFAULT_STAGE, 1);
    
    nowHasPoint=SaveUtil::getSaveInt(USERDEFAULT_NOW_HAS_POINT, 0);
    
    canTouch=true;
    
    canDestroy=true;
    
    nowLevelUpLimit=GameUtil::getStageMaxLevel(nowStageNum);
    
    escapeRect=CCRectMake(170,355, 256, 248);
    
    /* 乱数系列の変更 */
	srand((unsigned)time(NULL));
    
    // タッチ有効化
	setTouchEnabled(true);
	setTouchMode(kCCTouchesOneByOne);

}

        // !!!:init
bool GameScene::init(){
    //CCLOG("GameScene::init");
    if (CCLayer::init()) {
        
        initValue();
        
        
        //m_frameCashe->addSpriteFramesWithFile("setting.plist");
        
        
        //画面位置をセット
        setObjectPosition();
        
        //背景をセット
        setBackGround();
        
        //メニューアイテムをセット
        setMenuItem();
        
        //敵レイヤー
        m_enemyLayer= EnemyLayer::create();
        m_enemyLayer->setMode(klaunchSceneIdo);
        this->addChild(m_enemyLayer,kGameLayerOnBg1);
        
        m_kasiLayer=KashiLayer::create();
        m_kasiLayer->setMode(klaunchSceneIdo);
        this->addChild(m_kasiLayer,kGameLayerOnBg2);
        
        //-------------------デバッグ
        //メーターの数字
        m_Label_enemy = CCLabelTTF::create("0", FONT_NAME_Marker,21);
        m_Label_enemy->setAnchorPoint(ccp(1, 1));
        m_Label_enemy->setPosition(ccp(640,960));
        m_Label_enemy->setColor(ccWHITE);
        CCString* cntS=CCString::createWithFormat("Has point : %d",nowHasPoint);
        m_Label_enemy->setString(cntS->getCString());
        this->addChild(m_Label_enemy,kGameLayerDebugText);
        
        
        updateScore(0);
        //-------------------

        
        
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
void GameScene::setObjectPosition(){
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
    m_p_meter = ccp(0, 902-yMinus);
    
}

#pragma mark 背景セット
void GameScene::setBackGround(){
    //背景
    m_backGroundSprite=CCSprite::createWithSpriteFrameName("bg_ido.png");
    pos00(m_backGroundSprite);
    this->addChild(m_backGroundSprite,kGameLayerBackground0);
    
    meterSp = MeterLayer::create();    
    //メーター全部入りをadd
    this->addChild(meterSp,kGameLayerMenu);
    
    tapEffect = TapEffectLayer::create();
    this->addChild(tapEffect,kGameLayerOnBg4);
}

#pragma mark メニューアイテムをセット
void GameScene::setMenuItem(){

    
    m_btnLayer=CommonBtnLayer::create();
    m_btnLayer->prepare(this, menu_selector(GameScene::onEsaClick), menu_selector(GameScene::tapItems), menu_selector(GameScene::tapFriends), menu_selector(GameScene::tapSetting), menu_selector(GameScene::tapWallButton));
    this->addChild(m_btnLayer,kGameLayerMenu);
    
    
    //ひだり
    MyEasyMenuItem *_arrowLItem = MyEasyMenuItem::create("btn_arrow_l.png", m_pt_arrowBtn_L, this, menu_selector(GameScene::onArrowLClick));
    //みぎ
    MyEasyMenuItem *_arrowRItem = MyEasyMenuItem::create("btn_arrow_r.png", m_pt_arrowBtn_R, this, menu_selector(GameScene::onArrowRClick));
    
    /*
    if (nowStageNum<3) {
        //池いけない
        _arrowRItem->setOpacity(126);
        _arrowRItem->setEnabled(false);
    }

    if (nowStageNum<5) {
        //墓いけない
        _arrowLItem->setOpacity(126);
        _arrowLItem->setEnabled(false);
    }
    */
    
    CCMenu *_menuS = CCMenu::create(_arrowLItem,_arrowRItem,NULL);
    
	_menuS->setPosition(ccp(0, 0));
    this->addChild(_menuS,kGameLayerMenu);
    
}

//1秒毎　呼ばれるメインループ
void GameScene::mainLoop(){
    i_nowSec=floor(GetSecond());
    
    if( (i_nowSec-i_lastOkashiTime)>300 ){
        //5分経ってて　もし空腹サイン出してなければ出す
    }
    
    ///!!!:fog ランダム生成
    float rdm =CCRANDOM_0_1();
    if (rdm<0.1f) {
        CCSprite *fog=CCSprite::createWithSpriteFrameName("fog.png");
        //初期値
        fog->setScale(1.0+CCRANDOM_0_1());
        
        float _sec=4+CCRANDOM_0_1()*6;
        
        int _sx=(int)(CCRANDOM_0_1()*m_winSize.width);
        int _sy=(int)(CCRANDOM_0_1()*m_winSize.height);
        fog->setPosition(ccp(_sx, _sy));
        fog->setOpacity(0);
        
        int _dx=_sx+(int)(CCRANDOM_0_1()*m_winSize.width);
        //runActionをするspを引数にとる
        CCCallFuncN *_endfunc = CCCallFuncN::create(this,callfuncN_selector(GameScene::onFogAnimFinished));
        
        //アニメ加える
        CCFiniteTimeAction *_move1 = CCMoveTo::create(_sec,ccp(_dx, _sy));
        
        CCFiniteTimeAction *_fadeIn = CCFadeTo::create(_sec/4, 255);
        CCDelayTime* delay = CCDelayTime::create(_sec/2);
        CCFiniteTimeAction *_fadeOut = CCFadeTo::create(_sec/4, 0);
        
        CCSequence* fadeSeq = CCSequence::create(_fadeIn, delay, _fadeOut, NULL);
        
        CCSpawn *spa=CCSpawn::createWithTwoActions(_move1, fadeSeq);
        
        CCSequence *_sc = CCSequence::create(spa,_endfunc, NULL);
        
        this->addChild(fog,kGameLayerOnBg3);
        fog->runAction(_sc);
    }
}

void GameScene::onFogAnimFinished(CCNode* sender){
    CCSprite *pSprite=(CCSprite*)sender;
    pSprite->removeFromParentAndCleanup(true);
}



#pragma mark onResume
void GameScene::onResume(){
    i_nowSec = floor(GetSecond());
    
    nowHasPoint = SaveUtil::getSaveInt(USERDEFAULT_NOW_HAS_POINT);
    
    i_lastOkashiTime = SaveUtil::getSaveInt(USERDEFAULT_LAST_EAT_TIME, i_nowSec);
    
    updateScore(0);

    
    //アプリ終了時の時間
    int savedSec=SaveUtil::getSaveInt(USERDEFAULT_IDO_PAUSE_TIME);
    
    //終了時間から計算して　オブジェクト生成
    
    if (savedSec!=0) {
        int _n=(i_nowSec-savedSec)/TIME_ENEMY_MAKE_SEC;
        CCLOG("-----jikan kara make suru teki ha = %d",_n);
        for (int i=0; i<_n; i++) {
            m_enemyLayer->enemyCreateLoop();
            if (ENEMY_MAKE_MAX<i)break;
        }
    }
    
    if (savedSec!=0) {
        int _n=(i_nowSec-savedSec)/TIME_KASI_MAKE_SEC;
        CCLOG("-----jikan kara make suru okashi ha = %d",_n);
        for (int i=0; i<_n; i++) {
            m_kasiLayer->okashiCreateLoop();
            if (KASI_MAKE_MAX<i)break;
        }
    }
    
    //ループ系スタート
    this->schedule(schedule_selector(GameScene::mainLoop), 1);
    
    m_enemyLayer->startLoop();
    
    m_kasiLayer->startLoop();
}

#pragma mark -----ボタンタップ処理
void GameScene::tapFriends(CCObject *pSender){
    //シーン移動
    changeSceneFade(FriendsScene::scene())
}
//
void GameScene::tapWallButton(CCObject *pSender){
    
}
//
void GameScene::tapItems(CCObject *pSender){
    
}
//
void GameScene::tapSetting(CCObject *pSender){
    changeSceneFade(SettingScene::scene())
}

void GameScene::onEsaClick(CCObject *pSender){
    //シーン移動
    changeSceneFade(IdoAnaScene::scene())
}


void GameScene::onArrowLClick(CCObject *pSender){
    //シーン移動
    CCTransitionSlideInL* _transition=CCTransitionSlideInL::create(FLOAT_SCENE_MOVE_TIME, GraveScene::scene());
    CCDirector::sharedDirector()->replaceScene(_transition);
}

void GameScene::onArrowRClick(CCObject *pSender){
    //シーン移動
    CCTransitionSlideInR* _transition=CCTransitionSlideInR::create(FLOAT_SCENE_MOVE_TIME, LakeScene::scene());
    CCDirector::sharedDirector()->replaceScene(_transition);
}



#pragma mark タッチ処理
bool GameScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    if (canTouch==false) return false;
	
    // タッチ開始時の座標を保存
	CCDirector *pDirector = CCDirector::sharedDirector();
	touchStartPoint = pDirector->convertToGL(pTouch->getLocationInView());
    
    tapEffect->show(touchStartPoint);
    
	return true;
}

void GameScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
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
    

}

// スワイプ中
void GameScene::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent) {
    if (canTouch==false) return;
    
	// タップポイント取得
	CCDirector *pDirector = CCDirector::sharedDirector();
	CCPoint tpoint = pDirector->convertToGL(pTouch->getLocationInView());
    //CCLog("ccTouchMoved x=%f y=%f",tpoint.x,tpoint.y);
    
    int n=m_enemyLayer->deleteSpriteFunc(tpoint);
    updateScore(n);
    
    
}
// タップキャンセル時
void GameScene::ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent) {
    CCLog("TouchCancelled");
    if (canTouch==false) return;
    
	// タップポイント取得
	CCDirector *pDirector = CCDirector::sharedDirector();
	CCPoint tpoint = pDirector->convertToGL(pTouch->getLocationInView());
    
}



#pragma mark エンター
void GameScene::onEnter(){
    CCLayer::onEnter();
    
    //通知受け取り設定
    My_setNotify(GameScene::onPause, NOTIFICATION_PAUSE)
    My_setNotify(GameScene::onResume, NOTIFICATION_RESUME)
    
    // !!!:------Google Analytics
    NativeManager::sendName2GA(SCENE_NAME_SETTING);
    
        onResume();
}

#pragma mark エンターフィニッシュ
void GameScene::onEnterTransitionDidFinish(){
    CCLayer::onEnterTransitionDidFinish();
    
}

#pragma mark Exit
void GameScene::onExit(){
    CCLayer::onExit();
    //通知受け取り解放
    My_unSetNotify(NOTIFICATION_PAUSE)
    My_unSetNotify(NOTIFICATION_RESUME)

    
    //スケジュール全部止める
    
    
}

#pragma mark Exitスタート
void GameScene::onExitTransitionDidStart(){
    CCLayer::onExitTransitionDidStart();
    
    SaveUtil::saveInt(USERDEFAULT_FROM_LAUCH,klaunchSceneIdo);
    
    
    //Pause
    onPause();
}




#pragma mark onPause
void GameScene::onPause(){
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
    SaveUtil::saveInt(USERDEFAULT_IDO_PAUSE_TIME,i_nowSec);
}





    // !!!:数字とかメーター更新
void GameScene::updateScore(int n){
    
    nowHasPoint+=n;
    
    //メーターのスケールいじる
    float _wper=nowHasPoint/(float)nowLevelUpLimit;
    //timeMeterSp->setScaleX(_wper);

    CCString* cntS=CCString::createWithFormat("Has point : %d",nowHasPoint);
    m_Label_enemy->setString(cntS->getCString());
    
    
    meterSp->upDateMeter(_wper);
    
    //リミット
    if(nowLevelUpLimit<=nowStageNum){
        //進化
        startEvolutionAnim();
    }
    
}





void GameScene::startEvolutionAnim(){
    //所持ポイント
    SaveUtil::saveInt(USERDEFAULT_NOW_HAS_POINT, 0);
    
    //ステージ
    SaveUtil::saveInt(USERDEFAULT_STAGE, nowStageNum+1);
    
    //黒い雲
}
void GameScene::finishEvolutionAnim(){
    changeSceneFade(EvolutionScene::scene())
}


void GameScene::endDiedAnim(CCNode* sender){
    sender->removeFromParentAndCleanup(true);
}
void GameScene::deleteSelf(CCNode* sender){
    sender->removeFromParentAndCleanup(true);
}


#pragma mark ステージ数で、使うpngの名前4つを返す
CCArray* GameScene::getPanelFilename(int stage) {
    //使う4コマplist読み込む
    m_frameCashe->addSpriteFramesWithFile("koma_1.plist");
    
    CCArray *itemS = CCArray::createWithContentsOfFile("pngname_yonkoma.plist");
    CCArray *item=(CCArray *)itemS->objectAtIndex(stage);
    return item;
}



// !!!:ステージ数から、レベルアップまでのポイント、等を返す
void GameScene::intLevelState(){

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

