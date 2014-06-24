//
//  GimmickListScene.cpp
//
//
//  Created by dotchi on 2014/06/02.
//
//
#import "GimmickListScene.h"

#import "SimpleAudioEngine.h"

#import "Game.h"
#import "GameUtil.h"

#import "NativeManager.h"
#import "SaveUtil.h"
#import "MySoundONOFFMenuItem.h"
#import "MyEasyMenuItem.h"
#import "MyButtonUtil.h"
#import "GimmickListScene.h"
#import "AndroidUtil.h"

#import "MyAnimationUtil.h"

#import "GameScene.h"
#import "SettingScene.h"

#import <list>


USING_NS_CC;
using namespace std;

GimmickListScene::~GimmickListScene(){
    //デストラクタ
    if (canDestroy) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("gimmick.plist");
        CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    }
    mPngNameArr->release();
}


CCScene* GimmickListScene::scene(){
    CCScene* scene=CCScene::create();
    GimmickListScene* layer=GimmickListScene::create();
    scene->addChild(layer);
    return scene;
}

#pragma mark 変数初期化
void GimmickListScene::initValue(){
    
	m_winSize = CCDirector::sharedDirector()->getWinSize();
    
    m_utils=GameUtil::create();
    this->addChild(m_utils,kGameLayerBackground0);
    
    m_winSize=CCDirector::sharedDirector()->getWinSize();
    
    m_frameCashe=CCSpriteFrameCache::sharedSpriteFrameCache();
    
    canTouch=true;
    
    canDestroy=true;
    
    
    mPngNameArr = CCArray::createWithContentsOfFile("pngname_gimmick.plist");
    mPngNameArr->retain();
    
    /* 乱数系列の変更 */
	srand((unsigned)time(NULL));
    
    // タッチ有効化
	setTouchEnabled(true);
	setTouchMode(kCCTouchesOneByOne);
}

        // !!!:init
bool GimmickListScene::init(){
    //CCLOG("GimmickListScene::init");
    if (CCLayer::init()) {
        
        initValue();
        
        
        m_frameCashe->addSpriteFramesWithFile("gimmick.plist");
        
        
        //画面位置をセット
        setObjectPosition();
        
        //背景をセット
        setBackGround();
        
        //メニューアイテムをセット
        setMenuItem();

        
        showscroll();
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
void GimmickListScene::setObjectPosition(){
    //サイズ別にセット
    if (m_winSize.height==1136) {
        //4インチ
        yMinus=0;
        
    } else {
        yMinus=44;
        
        NativeManager::closeIconView();
    }
    
    m_pt_tableView=ccp(50,300);
    
    m_pt_arrowBtn_L=ccp(52,647);
    
    m_pt_arrowBtn_R=ccp(588,647);
}

#pragma mark 背景セット
void GimmickListScene::setBackGround(){
    //背景
    //黒
    m_backGroundSprite=CCSprite::createWithSpriteFrameName("gimmick_bg.png");
    pos00(m_backGroundSprite);
    this->addChild(m_backGroundSprite,kGameLayerBackground0);
    
}

#pragma mark メニューアイテムをセット
void GimmickListScene::setMenuItem(){
    
    // wall
    MyEasyMenuItem* _rew=MyEasyMenuItem::create("btn_wall.png", ccp(482, 207), this, menu_selector(GimmickListScene::tapOsusume));
    
    
    // back
    MyEasyMenuItem *_backItem = MyEasyMenuItem::create("btn_back.png", ccp(174, 207), this, menu_selector(GimmickListScene::tapBack));
    
    
    
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
void GimmickListScene::onResume(){


}

#pragma mark ボタンタップ処理

//
void GimmickListScene::tapBack(CCObject *pSender){
    changeSceneFade(SettingScene::scene())
}

void GimmickListScene::tapOsusume(CCObject *pSender){
    
}






/// !!!:テーブルビュー表示
void GimmickListScene::showscroll(){
    
    //bg waku
    m_tableViewBg=CCSprite::createWithSpriteFrameName("gimmick_waku.png");
    anc00(m_tableViewBg)
    m_tableViewBg->setPosition(m_pt_tableView);
    this->addChild(m_tableViewBg,kGameLayerDialog);
    
    //-----------------テーブルビュー
    m_tableView = CCTableView::create(this, CCSizeMake(m_tableViewBg->getContentSize().width, m_tableViewBg->getContentSize().height));
    m_tableView->setPosition(m_pt_tableView);
    

    //方向（縦）
    m_tableView->setDirection(kCCScrollViewDirectionVertical);
    
    //セルの表示順（上から下）
    m_tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    
    //表示
    m_tableView->setDelegate(this);
    this->addChild(m_tableView,kGameLayerDialog);
    //m_tableView->setVisible(false);

}


#pragma mark エンター
void GimmickListScene::onEnter(){
    CCLayer::onEnter();
    
    // !!!:------Google Analytics
    NativeManager::sendName2GA(SCENE_NAME_SETTING);
}

#pragma mark エンターフィニッシュ
void GimmickListScene::onEnterTransitionDidFinish(){
    CCLayer::onEnterTransitionDidFinish();
    
    
    onResume();
}

#pragma mark Exit
void GimmickListScene::onExit(){
    CCLayer::onExit();
}

#pragma mark Exitスタート
void GimmickListScene::onExitTransitionDidStart(){
    CCLayer::onExitTransitionDidStart();
}




#pragma mark onPause
void GimmickListScene::onPause(){
    CCLOG("onPause");

}




#pragma mark リスとビュー
//セルのサイズを設定（横：画面いっぱい / 縦：ここでは画像サイズに合わせて100に設定）
CCSize GimmickListScene::cellSizeForTable(CCTableView *table){
    return CCSizeMake(table->getContentSize().width, 140);
}

// セルの内容を設定　リストビュー1個1個 idxでif分岐しないといけないのか
CCTableViewCell* GimmickListScene::tableCellAtIndex(CCTableView *table, unsigned int idx){
    
    char s_buf[32];
    snprintf(s_buf , sizeof(s_buf) , "No.%2d",idx);
    
    CCTableViewCell *cell = table->dequeueCell();
    CCLOG("tableCellAtIndex idx = %d",idx);
    
    CCString* _s=(CCString *)mPngNameArr->objectAtIndex(idx);
    const char* _png1=_s->getCString();
    
    if(!cell){
        cell = new CCTableViewCell();
        cell->autorelease();
        
        // 文字画像の部分
        CCSprite* mongon = CCSprite::createWithSpriteFrameName("gimmick_list_1.png");
        anc00(mongon)
        mongon->setPosition(ccp(190, 5));
        mongon->setTag(LISTCELL_MONGON);
        cell->addChild(mongon);
        
        
        // チェック画像の部分
        CCSprite* chk = CCSprite::createWithSpriteFrameName("yet.png");
        anc00(chk)
        chk->setPosition(ccp(100, 5));
        chk->setTag(LISTCELL_CHECK);
        cell->addChild(chk);
        
        
        // テキストの部分（ccp(130, 35)->画像サイズに合わせて位置を調整してます）
        CCLabelTTF *label = CCLabelTTF::create(s_buf, "Arial", 40);
        label->setAnchorPoint(ccp(0,0));
        label->setPosition(ccp(10, 10));
        label->setTag(119);
        cell->addChild(label);
    }else{
        CCLabelTTF *label = (CCLabelTTF*) cell->getChildByTag(119);
        label->setString(s_buf);
        
        CCSprite* _mongon=(CCSprite*)cell->getChildByTag(LISTCELL_MONGON);
        
        CCSprite* _chk=(CCSprite*)cell->getChildByTag(LISTCELL_CHECK);
    }
    
    return cell;
}

// セルの数を設定。インデックスは0から始まる
unsigned int GimmickListScene::numberOfCellsInTableView(CCTableView *table){
    return GIMMICK_MAX_NUM;
}

// セルを選択したときの処理。
void GimmickListScene::tableCellTouched(CCTableView* table, CCTableViewCell* cell){
    CCLOG("%i番目が選択されました", cell->getIdx());
    

}



#pragma mark タッチ
bool GimmickListScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    if (canTouch==false) return true;
	
    // タッチ開始時の座標を保存
	CCDirector *pDirector = CCDirector::sharedDirector();
	touchStartPoint = pDirector->convertToGL(pTouch->getLocationInView());
    
    
	return true;
}

void GimmickListScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
    if (canTouch==false) return;
    
	// タップポイント取得
	CCDirector *pDirector = CCDirector::sharedDirector();
	CCPoint tpoint = pDirector->convertToGL(pTouch->getLocationInView());
    
}

// スワイプ中
void GimmickListScene::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent) {
    if (canTouch==false) return;
    
	// タップポイント取得
	CCDirector *pDirector = CCDirector::sharedDirector();
	CCPoint tpoint = pDirector->convertToGL(pTouch->getLocationInView());
    //CCLog("ccTouchMoved x=%f y=%f",tpoint.x,tpoint.y);
    
}
// タップキャンセル時
void GimmickListScene::ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent) {
    CCLog("TouchCancelled");
    if (canTouch==false) return;
    
	// タップポイント取得
	CCDirector *pDirector = CCDirector::sharedDirector();
	CCPoint tpoint = pDirector->convertToGL(pTouch->getLocationInView());
    
}


