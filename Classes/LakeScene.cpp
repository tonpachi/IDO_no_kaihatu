//
//  LakeScene.cpp
//
//
//  Created by dotchi on 2014/06/02.
//
//
#import "LakeScene.h"

#import "SimpleAudioEngine.h"

#import "Game.h"
#import "GameUtil.h"

#import "NativeManager.h"
#import "SaveUtil.h"
#import "MySoundONOFFMenuItem.h"
#import "MyEasyMenuItem.h"
#import "MyButtonUtil.h"
#import "LakeScene.h"
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

LakeScene::~LakeScene(){
    //デストラクタ
    if (canDestroy) {
        //CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("setting.plist");
        //CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    }
    
}


CCScene* LakeScene::scene(){
    CCScene* scene=CCScene::create();
    LakeScene* layer=LakeScene::create();
    scene->addChild(layer);
    return scene;
}

#pragma mark 変数初期化
void LakeScene::initValue(){
    
	m_winSize = CCDirector::sharedDirector()->getWinSize();
    
    m_utils=GameUtil::create();
    this->addChild(m_utils,kGameLayerBackground0);
    
    m_winSize=CCDirector::sharedDirector()->getWinSize();
    
    m_frameCashe=CCSpriteFrameCache::sharedSpriteFrameCache();
    
    nowStageNum=SaveUtil::getSaveInt(USERDEFAULT_STAGE, 1);
    
    nowHasPoint=SaveUtil::getSaveInt(USERDEFAULT_NOW_HAS_POINT, 0);
    
    canTouch=true;
    
    canDestroy=true;
    
    nowLevelUpLimit=GameUtil::getStageMaxLevel(nowStageNum);
    
    
    /* 乱数系列の変更 */
	srand((unsigned)time(NULL));
    
    // タッチ有効化
	setTouchEnabled(true);
	setTouchMode(kCCTouchesOneByOne);
    
}

        // !!!:init
bool LakeScene::init(){
    //CCLOG("LakeScene::init");
    if (CCLayer::init()) {
        
        initValue();
        
        
        //m_frameCashe->addSpriteFramesWithFile("setting.plist");
        
        
        //画面位置をセット
        setObjectPosition();
        
        //背景をセット
        setBackGround();
        
        //メニューアイテムをセット
        setMenuItem();

        
        //復帰
        m_stoneLayer=StoneLayer::create();
        m_stoneLayer->prepare();
        this->addChild(m_stoneLayer,kGameLayerOnBg1);
        
        m_kasiLayer=KashiLayer::create();
        m_kasiLayer->setMode(klaunchSceneIke);
        this->addChild(m_kasiLayer,kGameLayerOnBg2);

        
        updateScore();
        
        
        if (SaveUtil::getSaveBool(USERDEFAULT_STAGE_FIRST_IKE, false)==false) {
            //池に始めてきた チュートリアル出す
            SaveUtil::saveBool(USERDEFAULT_STAGE_FIRST_IKE, true);
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
void LakeScene::setObjectPosition(){
    //サイズ別にセット
    if (m_winSize.height==1136) {
        //4インチ
        yMinus=0;
        
    } else {
        yMinus=44;
        
        NativeManager::closeIconView();
    }
    
    m_pt_arrowBtn_L=ccp(52,647);
    
    m_pt_arrowBtn_R=ccp(588,647);
    
    //メーター位置
    m_p_meter = ccp(0, 902-yMinus);
    
    
    m_pt_wall=ccp(340,1000);
    
    m_pt_okashi=ccp(50, 207);
    m_pt_kumotsu=ccp(174, 207);
    m_pt_friends=ccp(328, 207);
    m_pt_setting=ccp(482, 207);
}

#pragma mark 背景セット
void LakeScene::setBackGround(){
    //背景
    //黒
    m_backGroundSprite=CCSprite::createWithSpriteFrameName("bg_lake.png");
    pos00(m_backGroundSprite);
    this->addChild(m_backGroundSprite,kGameLayerBackground0);
    
    meterSp = MeterLayer::create();
    
    //メーター全部入りをadd
    this->addChild(meterSp,kGameLayerOnBg3);
    
    tapEffect = TapEffectLayer::create();
    this->addChild(tapEffect,kGameLayerOnBg4);
}

#pragma mark メニューアイテムをセット
void LakeScene::setMenuItem(){
    
    m_btnLayer=CommonBtnLayer::create();
    m_btnLayer->prepare(this, menu_selector(LakeScene::onEsaClick), menu_selector(LakeScene::tapItems), menu_selector(LakeScene::tapFriends), menu_selector(LakeScene::tapSetting), menu_selector(LakeScene::tapWallButton));
    this->addChild(m_btnLayer,kGameLayerMenu);
    
    //ひだり
    MyEasyMenuItem *_arrowLItem = MyEasyMenuItem::create("btn_arrow_l.png", m_pt_arrowBtn_L, this, menu_selector(LakeScene::onArrowLClick));
    
    
    CCMenu *_menuS = CCMenu::create(_arrowLItem,NULL);
    
	_menuS->setPosition(ccp(0, 0));
    this->addChild(_menuS,kGameLayerMenu);

}

//毎回呼ばれるメインループ
void LakeScene::mainLoop(){
    i_nowSec=floor(GetSecond());
    
    
}


#pragma mark onResume
void LakeScene::onResume(){
    
    nowHasPoint=SaveUtil::getSaveInt(USERDEFAULT_NOW_HAS_POINT);
    
    
    updateScore();

    
    //アプリ終了時の時間
    int savedSec=SaveUtil::getSaveInt(USERDEFAULT_IKE_PAUSE_TIME);
    
    i_nowSec = floor(GetSecond());
    
    //終了時間から計算して　オブジェクト生成
    
    if (savedSec!=0) {
        int _n=(i_nowSec-savedSec)/TIME_STONE_MAKE_SEC;
        CCLOG("jikan kara make suru teki ha = %d",_n);
        for (int i=0; i<_n; i++) {
            m_stoneLayer->enemyCreateLoop();
            if (STONE_MAKE_MAX<i)break;
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
    this->schedule(schedule_selector(LakeScene::mainLoop), 1);
    
    m_stoneLayer->startLoop();
    m_kasiLayer->startLoop();
    m_stoneLayer->startLoop();
}

#pragma mark -----ボタンタップ処理
void LakeScene::tapFriends(CCObject *pSender){
    //シーン移動
    changeSceneFade(FriendsScene::scene())
}
//
void LakeScene::tapWallButton(CCObject *pSender){
    
}
//
void LakeScene::tapItems(CCObject *pSender){
    
}
//
void LakeScene::tapSetting(CCObject *pSender){
    changeSceneFade(SettingScene::scene())
}

void LakeScene::onEsaClick(CCObject *pSender){
    //シーン移動
    changeSceneFade(IdoAnaScene::scene())
}


void LakeScene::onArrowLClick(CCObject *pSender){
    //シーン移動
    CCTransitionSlideInL* _transition=CCTransitionSlideInL::create(FLOAT_SCENE_MOVE_TIME, GameScene::scene());
    CCDirector::sharedDirector()->replaceScene(_transition);
}

void LakeScene::onArrowRClick(CCObject *pSender){

}


#pragma mark エンター
void LakeScene::onEnter(){
    CCLayer::onEnter();
    
    //通知受け取り設定
    My_setNotify(LakeScene::onPause, NOTIFICATION_PAUSE)
    My_setNotify(LakeScene::onResume, NOTIFICATION_RESUME)
    
    // !!!:------Google Analytics
    NativeManager::sendName2GA(SCENE_NAME_SETTING);
    
        onResume();
}

#pragma mark エンターフィニッシュ
void LakeScene::onEnterTransitionDidFinish(){
    CCLayer::onEnterTransitionDidFinish();
    

}

#pragma mark Exit
void LakeScene::onExit(){
    CCLayer::onExit();
    //通知受け取り解放
    My_unSetNotify(NOTIFICATION_PAUSE)
    My_unSetNotify(NOTIFICATION_RESUME)

    

}

#pragma mark Exitスタート
void LakeScene::onExitTransitionDidStart(){
    CCLayer::onExitTransitionDidStart();
    
    SaveUtil::saveInt(USERDEFAULT_FROM_LAUCH,klaunchSceneIke);
    
    //ようするに保存
    onPause();
}




#pragma mark onPause
void LakeScene::onPause(){
    CCLOG("onPause");
    
    this->unscheduleAllSelectors();
    
    m_stoneLayer->stopLoop();
    m_stoneLayer->saveEnemyPosition();
    
    m_kasiLayer->stopLoop();
    m_kasiLayer->saveKasiPosition();
    
    //所持ポイント
    SaveUtil::saveInt(USERDEFAULT_NOW_HAS_POINT, nowHasPoint);
    
    //ステージ
    SaveUtil::saveInt(USERDEFAULT_STAGE, nowStageNum);
    
    i_nowSec = floor(GetSecond());
    //アプリ終了時の時間
    SaveUtil::saveInt(USERDEFAULT_IKE_PAUSE_TIME,i_nowSec);
}


#pragma mark タッチ処理
bool LakeScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    if (canTouch==false) return false;
	
    // タッチ開始時の座標を保存
	CCDirector *pDirector = CCDirector::sharedDirector();
	touchStartPoint = pDirector->convertToGL(pTouch->getLocationInView());
    
    tapEffect->show(touchStartPoint);
    
	return true;
}

void LakeScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
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
    //m_stoneLayer->deleteSpriteFunc(tpoint);
    //updateScore(n);
    
}

// スワイプ中
void LakeScene::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent) {
    if (canTouch==false) return;
    
	// タップポイント取得
	CCDirector *pDirector = CCDirector::sharedDirector();
	CCPoint tpoint = pDirector->convertToGL(pTouch->getLocationInView());
    //CCLog("ccTouchMoved x=%f y=%f",tpoint.x,tpoint.y);
    
    m_stoneLayer->deleteSpriteFunc(tpoint);
    //updateScore(n);
    
}
// タップキャンセル時
void LakeScene::ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent) {
    CCLog("TouchCancelled");
    if (canTouch==false) return;
    
}


    // !!!:数字とかメーター更新
void LakeScene::updateScore(){
    //nowHasPoint++;
    
    //メーターのスケールいじる
    float _wper=nowHasPoint/(float)nowLevelUpLimit;

    //CCString* cntS=CCString::createWithFormat("stone point : %d",nowHasPoint);
    //m_Label_enemy->setString(cntS->getCString());
    
    meterSp->upDateMeter(_wper);
}



void LakeScene::onTableClose(CCObject *pSender){

}


// !!!:ステージ数から、レベルアップまでのポイント、等を返す
void LakeScene::intLevelState(){
    

    
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

