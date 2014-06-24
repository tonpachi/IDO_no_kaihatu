//
//  IdoAnaScene.cpp
//
//
//  Created by dotchi on 2014/06/02.
//
//
#import "IdoAnaScene.h"

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

#import "LakeScene.h"
#import "GraveScene.h"

#import "EvolutionScene.h"

USING_NS_CC;


IdoAnaScene::~IdoAnaScene(){
    //デストラクタ
    if (canDestroy) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("idoana.plist");
        CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    }

}


CCScene* IdoAnaScene::scene(){
    CCScene* scene=CCScene::create();
    IdoAnaScene* layer=IdoAnaScene::create();
    scene->addChild(layer);
    return scene;
}

#pragma mark 変数初期化
void IdoAnaScene::initValue(){
    
	m_winSize = CCDirector::sharedDirector()->getWinSize();
    
    m_utils=GameUtil::create();
    this->addChild(m_utils,kGameLayerBackground0);
    
    m_winSize=CCDirector::sharedDirector()->getWinSize();
    
    m_frameCashe=CCSpriteFrameCache::sharedSpriteFrameCache();
    
    nowStageNum=SaveUtil::getSaveInt(USERDEFAULT_STAGE, 1);
    
    nowHasPoint=SaveUtil::getSaveInt(USERDEFAULT_NOW_HAS_POINT, 0);
    
    i_nowSec=floor(GetSecond());
    i_lastOkashiTime=SaveUtil::getSaveInt(USERDEFAULT_LAST_EAT_TIME, i_nowSec);
    
    
    canTouch=true;
    
    canDestroy=true;
    
    nowSelectedOkasi=0;
    
    
    nowLevelUpLimit=GameUtil::getStageMaxLevel(nowStageNum);
    
    
    /* 乱数系列の変更 */
	srand((unsigned)time(NULL));
    
    // タッチ有効化
	setTouchEnabled(true);
	setTouchMode(kCCTouchesOneByOne);
}

//初期化
bool IdoAnaScene::init(){
    //CCLOG("IdoAnaScene::init");
    if (CCLayer::init()) {
        
        initValue();

        m_frameCashe->addSpriteFramesWithFile("idoana.plist");

        //画面位置をセット
        setObjectPosition();
        
        //背景をセット
        setBackGround();
        
        //メニューアイテムをセット
        setMenuItem();
        
        
        updateScore();
        
        
        
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        AndroidUtil::heapLogger();
        AndroidUtil::txtviewVisible();
#endif
        return true;
    } else {
        return false;
    }
}

// !!!:数字とかメーター更新
void IdoAnaScene::updateScore(){
    //メーターのスケールいじる
    float _wper=nowHasPoint/(float)nowLevelUpLimit;
    //timeMeterSp->setScaleX(_wper);
    
    //CCString* cntS=CCString::createWithFormat("stone point : %d",stoneCnt_normal);
    //m_Label_enemy->setString(cntS->getCString());
    
    
    meterSp->upDateMeter(_wper);
}


#pragma mark 位置設定
//画面位置をセット
void IdoAnaScene::setObjectPosition(){
    //サイズ別にセット
    if (m_winSize.height==1136) {
        //4インチ
        yMinus=0;

    } else {
        yMinus=44;
        
        NativeManager::closeIconView();
    }
    
    
    m_esadialog_pt=ccp(20,400);
    
    m_confirmdialog_pt=ccp(100,500);
    

    
}

#pragma mark 背景セット
void IdoAnaScene::setBackGround(){
    //背景
    m_backGroundSprite=CCSprite::createWithSpriteFrameName("bg_idoana.png");
    pos00(m_backGroundSprite);
    this->addChild(m_backGroundSprite,kGameLayerBackground0);
    
    meterSp = MeterLayer::create();
    
    //メーター全部入りをadd
    this->addChild(meterSp,kGameLayerOnBg3);
}

#pragma mark メニューアイテムをセット
void IdoAnaScene::setMenuItem(){
    
    //
    m_esatBtn= MyEasyMenuItem::create("btn_setting.png", ccp(220, 210), this, menu_selector(IdoAnaScene::tapEsaButton));
    
    m_backtBtn = MyEasyMenuItem::create("btn_back.png", ccp(500, 210), this, menu_selector(IdoAnaScene::tapBack));


    
    
    CCMenu *_menuS = CCMenu::create(m_backtBtn,m_esatBtn,NULL);

	_menuS->setPosition(ccp(0, 0));
    this->addChild(_menuS,kGameLayerOnBg1);

    
}

//10秒毎　呼ばれるメインループ
void IdoAnaScene::mainLoop(){
    CCLOG("IdoAnaScene::mainLoop");
    float rdm=CCRANDOM_0_1();
    if (0.2<rdm) return;
    
    //ステージごとに怖がらせるアニメ
    int aniRdm;
    switch (nowStageNum) {
        case 1:
            aniRdm=(int)(CCRANDOM_0_1()*2);
            break;
        case 2:
            aniRdm=(int)(CCRANDOM_0_1()*2);
            break;
        default:
            break;
    }
}



//1秒毎　呼ばれるメインループ
void IdoAnaScene::subLoop(float time){
    i_nowSec = floor(GetSecond());
    if( (i_nowSec-i_lastOkashiTime)>300 ){
        //5分経った
        
    }
}


#pragma mark onPause
void IdoAnaScene::onPause(){
    CCLOG("onPause");
    //ループ系ストップ
    this->unscheduleAllSelectors();
    //ステージ
    SaveUtil::saveInt(USERDEFAULT_STAGE, nowStageNum);
    
    i_nowSec = floor(GetSecond());
    
    //アプリ終了時の時間
    SaveUtil::saveInt(USERDEFAULT_APP_PAUSE_TIME,i_nowSec);
    
}

#pragma mark onResume
void IdoAnaScene::onResume(){
    CCLOG("onResume");
    //ループ系スタート
    this->schedule(schedule_selector(IdoAnaScene::mainLoop), 10);
    
    this->schedule(schedule_selector(IdoAnaScene::subLoop), 1);

}

#pragma mark ボタンタップ処理
#pragma mark 菓子選択
void IdoAnaScene::tapEsaButton(CCObject *pSender){
    //おかし選択ダイアログ表示
    dialogLayer=BaseSimpleLayer::create();
    
    //うすい黒
    CCSprite* m_blackBg = GameUtil::makeBlackBg(m_winSize.width, m_winSize.height);
    pos00(m_blackBg)
    dialogLayer->addChild(m_blackBg);
    
    
    //ダイアログbg m_esadialog_pt
    CCSprite *_spbg = CCSprite::createWithSpriteFrameName("okasi_dialog_bg.png");
    anc00(_spbg)
    _spbg->setPosition(m_esadialog_pt);
    dialogLayer->addChild(_spbg);

    
    //------ダイアログにあげるボタン　add child 7個
    int tagCnt=0;
    for (int n=2;0<n; n--) {
        for (int m=0;m<4; m++) {
            int xx=m*110+100;
            int yy=n*300+250;
            //おかし　サムネイル
            CCSprite *thumb = CCSprite::createWithSpriteFrameName("okasi_1.png");
            anc00(thumb)
            thumb->setPosition(ccp(xx, yy));
            dialogLayer->addChild(thumb);
            
            
            //文言
            int has=GameUtil::getHasOkashiNum(tagCnt+1);
            char s_buf[32];
            snprintf(s_buf , sizeof(s_buf) , "所持数:%2d" , has);
            CCLabelTTF* label = CCLabelTTF::create(s_buf, "Arial", 20);
            label->setAnchorPoint(ccp(0, 0));
            label->setPosition(ccp(xx, yy-50));
            dialogLayer->addChild(label);
            
            
            //あげるボタン
            MyEasyMenuItem *_okasi_1 = MyEasyMenuItem::createAnc00("ok_btn.png", ccp(xx, yy-120), this, menu_selector(IdoAnaScene::tapAgeru));
            //ボタンにタグ
            _okasi_1->setTag(tagCnt+1);
            
            CCMenu *_menu7 = CCMenu::create(_okasi_1,NULL);
            _menu7->setPosition(ccp(0, 0));
            _menu7->setTouchPriority(kModalLayerPriority_a_menu);
            
            //0個は押せない
            if (has==0) _okasi_1->setEnabled(false);
            
            dialogLayer->addChild(_menu7);
            
            
            tagCnt++;
            if (7<=tagCnt) break;
        }
    }

    //-----
    
    //閉じる
    MyEasyMenuItem *_close = MyEasyMenuItem::create("close_btn.png", ccp(420,250), this, menu_selector(IdoAnaScene::closeAddLayer));
    
    CCMenu *_menuS = CCMenu::create(_close,NULL);
	_menuS->setPosition(ccp(0, 0));
    _menuS->setTouchPriority(kModalLayerPriority_a_menu);
    dialogLayer->addChild(_menuS);
    
    this->addChild(dialogLayer,kGameLayerMenu);
    //タッチの優先順位上げる
    dialogLayer->setTouchEnabled(true);
    dialogLayer->setTouchMode(kCCTouchesOneByOne);
    dialogLayer->setTouchPriority(kModalLayerPriority_a);
}

//戻るボタン
void IdoAnaScene::tapBack(CCObject *pSender){
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
        default:
            transition=CCTransitionFade::create(FLOAT_SCENE_MOVE_TIME, GameScene::scene());
            break;
    }
    CCDirector::sharedDirector()->replaceScene(transition);
}


#pragma mark あげるを押した
void IdoAnaScene::tapAgeru(CCObject *pSender){
    //押したボタンによる
    int _tag=((MyEasyMenuItem*)pSender)->getTag();
    CCLOG("tapAgeru _tag = %d",_tag);
    
    nowSelectedOkasi=_tag;
    
    //--------確認のダイアログ表示
    confirmdialogLayer=BaseSimpleLayer::create();
    
    //うすい黒
    CCSprite* m_blackBg = GameUtil::makeBlackBg(m_winSize.width, m_winSize.height);
    pos00(m_blackBg)
    confirmdialogLayer->addChild(m_blackBg);
    
    CCSprite *_spbg = CCSprite::createWithSpriteFrameName("confirmdialog_bg.png");
    anc00(_spbg)
    _spbg->setPosition(m_confirmdialog_pt);
    confirmdialogLayer->addChild(_spbg);
    
    
    //おかし　サムネイル 選択されたものによって変える
    switch (nowSelectedOkasi) {
        case 1:
            //
            break;
            
        default:
            break;
    }
    
    CCSprite *thumb = CCSprite::createWithSpriteFrameName(GameUtil::getPngNameFromPlist("",nowSelectedOkasi-1));
    anc00(thumb)
    thumb->setPosition(ccp(150, 700));
    confirmdialogLayer->addChild(thumb);
    
    
    //文言
    CCLabelTTF* label = CCLabelTTF::create("このおかしをあげますか？", "Arial", 30);
    label->setAnchorPoint(ccp(0, 0));
    label->setPosition(ccp(250, 700));
    confirmdialogLayer->addChild(label);
    
    
    //はい　いいえ　ボタン
    MyEasyMenuItem *noBtn = MyEasyMenuItem::createAnc00("btn_no.png", ccp(200, 550), this, menu_selector(IdoAnaScene::tapEsaCancel));
    MyEasyMenuItem *yesBtn = MyEasyMenuItem::createAnc00("btn_yes.png", ccp(400, 550), this, menu_selector(IdoAnaScene::tapEsaYes));
    
    CCMenu *_menu2 = CCMenu::create(noBtn,yesBtn,NULL);
    _menu2->setPosition(ccp(0, 0));
    _menu2->setTouchPriority(kModalLayerPriority_b_menu);
    confirmdialogLayer->addChild(_menu2);
    this->addChild(confirmdialogLayer,kGameLayerMenu);
    //タッチの優先順位上げる
    confirmdialogLayer->setTouchEnabled(true);
    confirmdialogLayer->setTouchMode(kCCTouchesOneByOne);
    confirmdialogLayer->setTouchPriority(kModalLayerPriority_b);
}

void IdoAnaScene::closeAddLayer(CCObject *pSender){
    //
    dialogLayer->removeFromParentAndCleanup(true);
}


#pragma mark あげるー＞はい　を押した
void IdoAnaScene::tapEsaYes(CCObject *pSender){
    dialogLayer->removeFromParentAndCleanup(true);
    confirmdialogLayer->removeFromParentAndCleanup(true);
    //あげるアニメーション
    switch (nowSelectedOkasi) {
        case 1:
            //
            nowHasPoint+=PT_COOKIE;
            //個数減らす
            SaveUtil::decrimentSave(USERDEFAULT_HAS_COOKIE);
            break;
        case 2:
            //
            nowHasPoint+=PT_AME;
            //個数減らす
            SaveUtil::decrimentSave(USERDEFAULT_HAS_AME);
            break;
        case 3:
            //
            nowHasPoint+=PT_CAKE;
            //個数減らす
            SaveUtil::decrimentSave(USERDEFAULT_HAS_PAN);
            break;
        case 4:
            //
            nowHasPoint+=PT_CHOCO;
            //個数減らす
            SaveUtil::decrimentSave(USERDEFAULT_HAS_CHOCO);
            break;
        case 5:
            //
            nowHasPoint+=PT_SPECIAL_SWEEETS;
            //個数減らす
            SaveUtil::decrimentSave(USERDEFAULT_HAS_SHOE);
            break;
        case 6:
            //
            nowHasPoint+=PT_SPECIAL_SWEEETS;
            //個数減らす
            SaveUtil::decrimentSave(USERDEFAULT_HAS_CAKE);
            break;
        case 7:
            //
            nowHasPoint+=PT_SPECIAL_SWEEETS;
            //個数減らす
            SaveUtil::decrimentSave(USERDEFAULT_HAS_PUDDING);
            break;
        default:
            break;
    }
    //ポイント加算
    SaveUtil::saveInt(USERDEFAULT_NOW_HAS_POINT, nowHasPoint);
    
    //菓子あげるアニメ
    startAgeruAnim();
    
    //アニメーション終了3秒後
    this->scheduleOnce(schedule_selector(IdoAnaScene::randomAnimStart), 3000);
}

#pragma mark あげるアニメーション　スタート
void IdoAnaScene::startAgeruAnim(){
    
    updateScore();
    
    //最後に菓子あげた時間
    i_lastOkashiTime=floor(GetSecond());
    SaveUtil::saveInt(USERDEFAULT_LAST_EAT_TIME, i_lastOkashiTime);
}



void IdoAnaScene::tapEsaCancel(CCObject *pSender){
    confirmdialogLayer->removeFromParentAndCleanup(true);
}


void IdoAnaScene::randomAnimStart(){
    //反応ランダム
}

void IdoAnaScene::startEvolutionAnim(){
    //所持ポイント
    SaveUtil::saveInt(USERDEFAULT_NOW_HAS_POINT, 0);
    
    //ステージ
    SaveUtil::saveInt(USERDEFAULT_STAGE, nowStageNum+1);
    
    //黒い雲
}
void IdoAnaScene::finishEvolutionAnim(){
    changeSceneFade(EvolutionScene::scene())
}



#pragma mark エンター
void IdoAnaScene::onEnter(){
    CCLayer::onEnter();
    //通知受け取り設定
    My_setNotify(IdoAnaScene::onPause, NOTIFICATION_PAUSE)
    My_setNotify(IdoAnaScene::onResume, NOTIFICATION_RESUME)
    
    
    // !!!:------Google Analytics
    NativeManager::sendName2GA(SCENE_NAME_SETTING);
}

#pragma mark エンターフィニッシュ
void IdoAnaScene::onEnterTransitionDidFinish(){
    CCLayer::onEnterTransitionDidFinish();
    
    onResume();
}

#pragma mark Exit
void IdoAnaScene::onExit(){
    CCLayer::onExit();
    //通知受け取り解放
    My_unSetNotify(NOTIFICATION_PAUSE)
    My_unSetNotify(NOTIFICATION_RESUME)
    
    //スケジュール全部止める

    
}

#pragma mark Exitスタート
void IdoAnaScene::onExitTransitionDidStart(){
    CCLayer::onExitTransitionDidStart();
}












bool IdoAnaScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    if (canTouch==false) return true;
	
    // タッチ開始時の座標を保存
	CCDirector *pDirector = CCDirector::sharedDirector();
	touchStartPoint = pDirector->convertToGL(pTouch->getLocationInView());

    
	return true;
}

void IdoAnaScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
    if (canTouch==false) return;
    
	// タップポイント取得
	CCDirector *pDirector = CCDirector::sharedDirector();
	CCPoint tpoint = pDirector->convertToGL(pTouch->getLocationInView());

    
}

// スワイプ中
void IdoAnaScene::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent) {
    CCLog("ccTouchMoved");
    if (canTouch==false) return;
    
	// タップポイント取得
	CCDirector *pDirector = CCDirector::sharedDirector();
	CCPoint tpoint = pDirector->convertToGL(pTouch->getLocationInView());
    
    
}
// タップキャンセル時
void IdoAnaScene::ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent) {
    CCLog("TouchCancelled");
    if (canTouch==false) return;
    
	// タップポイント取得
	CCDirector *pDirector = CCDirector::sharedDirector();
	CCPoint tpoint = pDirector->convertToGL(pTouch->getLocationInView());
    
}

