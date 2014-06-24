//
//  YonkomaScene.cpp
//
//
//  Created by dotchi on 2014/06/02.
//
//
#import "YonkomaScene.h"

#import "SimpleAudioEngine.h"

#import "Game.h"
#import "GameUtil.h"

#import "NativeManager.h"
#import "SaveUtil.h"
#import "MySoundONOFFMenuItem.h"
#import "MyEasyMenuItem.h"
#import "MyButtonUtil.h"
#import "YonkomaScene.h"
#import "AndroidUtil.h"

#import "MyAnimationUtil.h"

#import "SettingScene.h"
#import <list>

#import "My4SpritePager.h"

USING_NS_CC;
using namespace std;

YonkomaScene::~YonkomaScene(){
    
    cellSpList.clear();
    
    //デストラクタ
    if (canDestroy) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("yonkoma.plist");
        CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    }
    
}


CCScene* YonkomaScene::scene(){
    CCScene* scene=CCScene::create();
    YonkomaScene* layer=YonkomaScene::create();
    scene->addChild(layer);
    return scene;
}

#pragma mark 変数初期化
void YonkomaScene::initValue(){
    
	m_winSize = CCDirector::sharedDirector()->getWinSize();
    
    m_utils=GameUtil::create();
    this->addChild(m_utils,kGameLayerBackground0);
    
    m_winSize=CCDirector::sharedDirector()->getWinSize();
    
    m_frameCashe=CCSpriteFrameCache::sharedSpriteFrameCache();
    
    canTouch=true;
    
    canDestroy=true;
    
    /* 乱数系列の変更 */
	srand((unsigned)time(NULL));
    
    // タッチ有効化
	setTouchEnabled(true);
	setTouchMode(kCCTouchesOneByOne);
}

        // !!!:init
bool YonkomaScene::init(){
    //CCLOG("YonkomaScene::init");
    if (CCLayer::init()) {
        
        initValue();
        
        
        m_frameCashe->addSpriteFramesWithFile("yonkoma.plist");
        
        
        //画面位置をセット
        setObjectPosition();
        
        //背景をセット
        setBackGround();
        
        //メニューアイテムをセット
        setMenuItem();

        
        
        //-------------------デバッグ

        
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
void YonkomaScene::setObjectPosition(){
    //サイズ別にセット
    if (m_winSize.height==1136) {
        //4インチ
        yMinus=0;
        
    } else {
        yMinus=44;
        
        NativeManager::closeIconView();
    }
    
    m_back_pt=ccp(174, 200);
    
    m_wall_pt=ccp(482, 200);
    
    m_pt_tableView=ccp(0,200);
    
    m_pt_arrowBtn_L=ccp(52,647);
    
    m_pt_arrowBtn_R=ccp(588,647);
}

#pragma mark 背景セット
void YonkomaScene::setBackGround(){
    //背景
    //黒
    m_backGroundSprite=CCSprite::createWithSpriteFrameName("yonkoma_bg.png");
    pos00(m_backGroundSprite);
    this->addChild(m_backGroundSprite,kGameLayerBackground0);
    
}

#pragma mark メニューアイテムをセット
void YonkomaScene::setMenuItem(){
    
    showscroll();
    
    // wall
    MyEasyMenuItem* _rew=MyEasyMenuItem::create("top_set_btn.png", m_wall_pt, this, menu_selector(YonkomaScene::tapOsusume));
    
    
    // back
    MyEasyMenuItem *_backItem = MyEasyMenuItem::create("top_set_btn.png", m_back_pt, this, menu_selector(YonkomaScene::tapBack));

    CCMenu *_menuS = CCMenu::create(_rew,_backItem,NULL);
    
	_menuS->setPosition(ccp(0, 0));
    this->addChild(_menuS,kGameLayerMenu);
    
    //newと出す　アイモバイル用
    //CCSprite *onew =MyAnimationUtil::createSpNewSign(ccp(482+50, 307+55));
    //this->addChild(onew,kGameLayerMenu);

    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    /*
    _rew->setVisible(GameUtil::getAppStatus());
    //レビュー消すか出すか
    _rev->setVisible(GameUtil::getAppStatus());
    m_revSprite->setVisible(GameUtil::getAppStatus());
    
    onew->setVisible(GameUtil::getAppStatus());
    */
#endif
    
    
    
    
}



#pragma mark onResume
void YonkomaScene::onResume(){


}

#pragma mark ボタンタップ処理

//
void YonkomaScene::tapBack(CCObject *pSender){
    changeSceneFade(SettingScene::scene())
}

void YonkomaScene::tapOsusume(CCObject *pSender){

}

void YonkomaScene::tapCell(CCObject *pSender){//CCObject *pSender
    //セルタップでダイアログ表示
        int _tag=((MyEasyMenuItem*)pSender)->getTag();
    show4komaDialog(_tag);
}

void YonkomaScene::tapTwinList(CCObject *pSender){
    //押したボタンによる twitter
    int _tag=((MyEasyMenuItem*)pSender)->getTag();
    NativeManager::sendTweet4(_tag);
}




/// !!!:リストページャービュー表示
void YonkomaScene::showscroll(){
    int listNum=10;
    int cellYSize=150;
    int viewH=cellYSize*listNum;
    
    //viewPager の　bg waku
    m_tableViewBg=CCSprite::createWithSpriteFrameName("yonkoma_bg_table.png");
    anc00(m_tableViewBg)
    m_tableViewBg->setPosition(m_pt_tableView);
    this->addChild(m_tableViewBg,kGameLayerOnBg1);
    
    // !!!:自作のviewPagerをadd
    m_pager=My4ListSpritePager::create();
    this->addChild(m_pager,kGameLayerOnBg1);
    
    //表示する大きさ WH と 座標　　anchor(0,0)で
    m_pager->prepere(640,m_tableViewBg->getContentSize().height, m_pt_tableView);

    //-----------------リストビュー中身
    int tagCnt=0;
    for (int n=0;n<3; n++) {
        CCSprite* _innnerSp=CCSprite::create();
        _innnerSp->setContentSize(m_tableViewBg->getContentSize());
        for (int m=0;m<4; m++) {
            char s_buf[32];
            snprintf(s_buf , sizeof(s_buf) , "4コマ : %d" , tagCnt);
            
            int _yy=cellYSize*(3-m);
            //CCPoint _PT=ccp(0,viewH-_yy);
            CCLOG("cell _yy = %d",_yy);
            //ボタン
            /*
             CCSprite* sprite=CCSprite::createWithSpriteFrameName("bg_cell.png");
             anc00(sprite)
             sprite->setPosition(ccp(10, _yy));
             sprite->setTag(n);
             _innnerLayer->addChild(sprite);
             
             cellSpList.push_back(sprite);
             
             */
            CCArray *menuItemsArr = CCArray::create();
            CCArray *twMenuItemsArr = CCArray::create();
            
            MyEasyMenuItem* sprite=MyEasyMenuItem::createAnc00("bg_cell.png", ccp(10, _yy), this, menu_selector(YonkomaScene::tapCell));
            sprite->setTag(tagCnt);
            menuItemsArr->addObject(sprite);
            
            
            //Twitterボタン
            MyEasyMenuItem* _tweet=MyEasyMenuItem::createAnc00("cell_btn_tw.png", ccp(500, _yy+10), this, menu_selector(YonkomaScene::tapTwinList));
            _tweet->setTag(tagCnt);
            twMenuItemsArr->addObject(_tweet);
            
            
            // メニューを作成
            CCMenu *menu = CCMenu::createWithArray(menuItemsArr);
            menu->setPosition(CCPointZero);
            _innnerSp->addChild(menu);
            
            CCMenu *_menuS = CCMenu::createWithArray(twMenuItemsArr);
            _menuS->setPosition(CCPointZero);
            _innnerSp->addChild(_menuS);
            
            //チェックマークSp
            CCSprite* _chk=CCSprite::createWithSpriteFrameName("check_tw.png");
            _chk->setPosition(ccp(500, _yy+10));
            _innnerSp->addChild(_chk);
            _chk->setVisible(GameUtil::getBoolSNSPosted_Stage(tagCnt+1));
            
            
            //ガイド
            CCLabelTTF* label = CCLabelTTF::create(s_buf, "Arial", 80);
            label->setAnchorPoint(ccp(0, 0));
            label->setPosition(ccp(10, _yy+44));
            //label->setHorizontalAlignment(kCCTextAlignmentLeft);
            _innnerSp->addChild(label);
            
            //インクリメント
            tagCnt++;
        }

        //4行のspをadd
        m_pager->addSp(_innnerSp);

    }

    //-----------------
    //左右のボタン使う
    m_pager->myInitButton("btn_arrow_l.png", ccp(52,647), "btn_arrow_r.png", ccp(588,647));
    
}


#pragma mark エンター
void YonkomaScene::onEnter(){
    CCLayer::onEnter();
    
    // !!!:------Google Analytics
    NativeManager::sendName2GA(SCENE_NAME_SETTING);
}

#pragma mark エンターフィニッシュ
void YonkomaScene::onEnterTransitionDidFinish(){
    CCLayer::onEnterTransitionDidFinish();
    
    onResume();
}

#pragma mark Exit
void YonkomaScene::onExit(){
    CCLayer::onExit();

}

#pragma mark Exitスタート
void YonkomaScene::onExitTransitionDidStart(){
    CCLayer::onExitTransitionDidStart();
}




#pragma mark onPause
void YonkomaScene::onPause(){
    CCLOG("onPause");

}


// !!!:4コマ　ダイアログ表示
void YonkomaScene::show4komaDialog(int stageNum){
    canTouch=false;
    
    // !!!:自作のviewPagerをadd
    My4SpritePager* _pager=My4SpritePager::create();
    this->addChild(_pager,kGameLayerDialog);
    
    //表示する大きさと座標　　anchor(0,0)
    _pager->prepere(640,583, ccp(0,420));
    
    //plistからPNG名配列返す
    CCArray * animFrames =getPanelFilename(stageNum);
    for (int x=0; x<4; x++) {
        //必要な分 画像をadd
        CCString* _s=(CCString *)animFrames->objectAtIndex(x);
        _pager->addSpByFilename(_s->getCString());
    }
    
    //------------------------------------初期状態
    _pager->mySetShowPage(0);
    
    //-----下のボタンと、タッチの優先度を上げる処理らしい　閉じるとき元に戻すこと
    //_pager->setTouchPriority(kCCMenuHandlerPriority);
    //CCDirector* pDirector = CCDirector::sharedDirector();
    //pDirector->getTouchDispatcher()->addTargetedDelegate(_pager, kCCMenuHandlerPriority, true);
    
    
    
    
    _pager->setTag(ADD_LAYER_4KOMA);
    
}
void YonkomaScene::closeAddLayer(){
    this->removeChildByTag(ADD_LAYER_4KOMA);
    canTouch=true;
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
    
}







void YonkomaScene::closeScroll(){
    //非表示
    this->removeChild(m_tableViewBg);
    this->removeChild(m_tbCloseMenu);
}

#pragma mark タッチ
bool YonkomaScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    if (canTouch==false) return true;
	
    // タッチ開始時の座標を保存
	CCDirector *pDirector = CCDirector::sharedDirector();
	touchStartPoint = pDirector->convertToGL(pTouch->getLocationInView());
    
    
	return true;
}

void YonkomaScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
    if (canTouch==false) return;
    
	// タップポイント取得
	CCDirector *pDirector = CCDirector::sharedDirector();
	CCPoint tpoint = pDirector->convertToGL(pTouch->getLocationInView());
    
}
/*
// スワイプ中
void YonkomaScene::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent) {
    if (canTouch==false) return;
    
	// タップポイント取得
	CCDirector *pDirector = CCDirector::sharedDirector();
	CCPoint tpoint = pDirector->convertToGL(pTouch->getLocationInView());
    CCLog("ccTouchMoved x=%f y=%f",tpoint.x,tpoint.y);
    
}
// タップキャンセル時
void YonkomaScene::ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent) {
    CCLog("TouchCancelled");
    if (canTouch==false) return;
    
	// タップポイント取得
	CCDirector *pDirector = CCDirector::sharedDirector();
	CCPoint tpoint = pDirector->convertToGL(pTouch->getLocationInView());
    
}
*/

#pragma mark ステージ数で、使うpngの名前4つを返す
CCArray* YonkomaScene::getPanelFilename(int stage) {
    //使う4コマplist読み込む
    m_frameCashe->addSpriteFramesWithFile("koma_1.plist");
    
    CCArray *itemS = CCArray::createWithContentsOfFile("pngname_yonkoma.plist");
    CCArray *item=(CCArray *)itemS->objectAtIndex(stage);
    return item;
}




void YonkomaScene::readPlistNameByStage(int stage){
    string str[]={"MON","TUE","WED"};
    CCSpriteFrameCache* frameCashe=CCSpriteFrameCache::sharedSpriteFrameCache();
    frameCashe->addSpriteFramesWithFile(str[stage].c_str());
}


