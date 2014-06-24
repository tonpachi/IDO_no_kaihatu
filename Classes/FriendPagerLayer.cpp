//
//  FriendPagerLayer.cpp
//  kyojin
//
//  Created by コトブキ タロウ on 2014/02/21.
//
//

#import "FriendPagerLayer.h"
#import "MyEasyMenuItem.h"
#import "GameUtil.h"
#import "FriendsScene.h"

#import "cocos2d.h"


USING_NS_CC;

FriendPagerLayer::FriendPagerLayer(){
    
}

FriendPagerLayer::~FriendPagerLayer(){
    //デストラクタ
    spArray->release();
    m_point_vec.clear();
}

//初期化
bool FriendPagerLayer::init(){
    CCLOG("FriendPagerLayer::init");
    if (CCLayer::init()) {
        // タッチ有効化
        setTouchEnabled(true);
        setTouchMode(kCCTouchesOneByOne);
        
        // !!!:変数初期化
        spArray= CCArray::create();
        spArray->retain();
        m_flick_w=100;
        contentsNum=0;
        //今表示してるやつ
        nowContentNum=0;
        canTouch=true;
        
        ///!!!:何個？
        ALLNUM=10;
        
        //最初ゼロ
        m_p_last=CCPointZero;
        //ページの範囲
        m_size_rect=CCRectMake(0,0,640,456);
        
        m_content_w=640;
        
        
        //ルートのsp
        rootSp = CCSprite::create();
        
        //マスク用
        maskSp = CCSprite::create();
        
        
        return true;
    } else {
        return false;
    }
}

#pragma mark 初期設定
void FriendPagerLayer::prepere(int wsize,int hsize,CCPoint _position){
    m_size_rect=CCRectMake(0,0, wsize, hsize);
    //m_p_last=_position;
	m_content_w = wsize;
    //CCLOG("m_content_w=%f",m_content_w);
    
    rootSp->setAnchorPoint(ccp(0, 0));
    rootSp->setPosition(ccp(0, 0));
    //this->addChild(rootSp);
    

    maskSp->setTextureRect(m_size_rect);
    maskSp->setColor(ccBLACK);
    maskSp->setAnchorPoint(ccp(0, 0));
    maskSp->setPosition(ccp(0, 0));
    
    // ルートをマスクする
    m_clippingNode = CCClippingNode::create();
    // マスクするノードを設定
    m_clippingNode->setStencil(maskSp);
    // マスクの閾値の設定
    //m_clippingNode->setAlphaThreshold(0.01f);
    // マスクされるノードを設定
    m_clippingNode->addChild(rootSp);
    
    // マスクしたノードを表示する
    m_clippingNode->setPosition(_position);
    
    this->addChild(m_clippingNode,0);
    nowContentNum=0;
    m_rootY=0;
    
    CCRect _re1 = m_clippingNode->boundingBox();
    CCRect _re2 = maskSp->boundingBox();

    m_inTouchRect=CCRectMake(_re1.getMinX(),_re1.getMinY(),_re2.getMaxX(),_re2.getMaxY());
    
    CCArray *pngName_CharaArr=CCArray::createWithContentsOfFile("pngname_chara.plist");
    CCArray *pngName_WordArr=CCArray::createWithContentsOfFile("pngname_word.plist");
    ///!!!:10個add
    for (int i=0;i<ALLNUM;i++) {
        CCString* _s1=(CCString *)(pngName_CharaArr->objectAtIndex(i));
        CCString* _s2=(CCString *)(pngName_WordArr->objectAtIndex(i));

        int num=GameUtil::getFriendFindCount(i+1);
        bool b=GameUtil::isFriendTweeted(i+1);
        addSpByFilename(getCharaFilename(_s1,i),getPanelFilename(_s2,i),num,b);
    }
    
    
    // !!!:自作のMyPagerCounterをadd m_p_maru
    _pagerCntr=MyPagerCounter::create();
    _pagerCntr->prepere("gater_off.png", "gater_on.png", ALLNUM, m_p_maru,5);
    this->addChild(_pagerCntr);
    
    
    
    //------------------------------------初期状態
    mySetShowPage(0);
    //pagerCounterの表示更新
    _pagerCntr->MyUpdateVisible(0);
}


#pragma mark add_array
void FriendPagerLayer::addSpByFilename(const char* pngname,const char* mongonpngname,int kaisu,bool isTweet){
    //背景
    CCSprite *_sbgp = CCSprite::createWithSpriteFrameName("warabanshi");
    _sbgp->setAnchorPoint(CCPointZero);
    
    //絵sprite
    CCSprite *_sp = CCSprite::createWithSpriteFrameName(pngname);
    _sp->setAnchorPoint(CCPointZero);
    _sp->setPosition(ccp(0,0));
    _sbgp->addChild(_sp);
    
    //文言sprite
    CCSprite *_mongonsp = CCSprite::createWithSpriteFrameName(mongonpngname);
    _mongonsp->setAnchorPoint(CCPointZero);
    _mongonsp->setPosition(ccp(0,0));
    _sbgp->addChild(_mongonsp);
    
    //TW
    MyEasyMenuItem *twMenuItem = MyEasyMenuItem::create("zukan_tw_btn.png", ccp(0,0), this, menu_selector(FriendPagerLayer::tapTw));
    CCMenu *_menuS = CCMenu::create(twMenuItem,NULL);
    _sbgp->addChild(_menuS);
    
    if (isTweet==true) {
        //tweet check sprite
        CCSprite *_twsp = CCSprite::createWithSpriteFrameName("");
        _twsp->setAnchorPoint(CCPointZero);
        _twsp->setPosition(ccp(0,0));
        _sbgp->addChild(_twsp);
    }

    
    

    
    
    int _spw=640;//_sp->getContentSize().width;
    
	_sp->setPosition(ccp(m_p_last.x+(m_content_w-_spw)/2,m_p_last.y));
    
    //rootSpにaddする
	rootSp->addChild(_sbgp);
    //管理配列にもadd
    spArray->addObject(_sbgp);
    
    float _x=m_p_last.x+m_content_w;
    m_p_last=ccp(_x, m_p_last.y);
    
    m_point_vec.push_back(m_p_last);
    
    contentsNum++;
    
    lastPageNum=contentsNum;
}


void FriendPagerLayer::tapTw(CCObject *pSender){
    // nowContentNum
    
}

void FriendPagerLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
    
}

bool FriendPagerLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    CCLOG("FriendPagerLayer::ccTouchBegan");
    CCDirector *pDirector = CCDirector::sharedDirector();
    touchStartPoint = pDirector->convertToGL(pTouch->getLocationInView());

    // タッチ開始時の座標を保存
	if (canTouch && m_inTouchRect.containsPoint(touchStartPoint)) {
		if (nowContentNum < lastPageNum) {
			isContainRect = true;
		}else {
			isContainRect = false;
		}
	}else {
		isContainRect = false;
    }
	return true;
}

void FriendPagerLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
    CCLOG("FriendPagerLayer::ccTouchEnded");
    if(!isContainRect)return;
    
    
    // 離した時の座標を保存
	CCDirector *pDirector = CCDirector::sharedDirector();
	CCPoint touchEndPoint = pDirector->convertToGL(pTouch->getLocationInView());
    //どっちに動いたか　1=右　-1=左
	int _direct = (touchStartPoint.x < touchEndPoint.x) ? 1 : -1;
	//どんだけ動いたか
    float _movew = (_direct==1)?(touchEndPoint.x - touchStartPoint.x) : (touchStartPoint.x - touchEndPoint.x);
	if (m_flick_w <= _movew) {
        CCCallFunc *actionDone = CCCallFunc::create(this, callfunc_selector(FriendPagerLayer::onAnimatoinFinished));
        //CCLOG("flicked nowContentNum=%d  contentsNum=%d",nowContentNum,contentsNum);
        //しきい値より動いてたらanimation
        if(_direct==1){//右にフリック
            //右へ動かす　つまり左が出る
            if(nowContentNum<=0)return;
            CCLOG("migi");
            nowContentNum--;
            
            CCMoveTo* _ani=CCMoveTo::create(0.5f, ccp(rootSp->getPositionX()+m_content_w,m_rootY));
            CCEaseOut* _ease=CCEaseOut::create(_ani,2);
            CCSequence *squence2 = CCSequence::create(_ease, actionDone, NULL);
            rootSp->runAction(squence2);
        }else{
            //左へ動かす　つまり右が出る
            if(nowContentNum==contentsNum-1)return;
            CCLOG("hidari");
			nowContentNum++;

			CCMoveTo *_ani = CCMoveTo::create(0.5f, ccp(rootSp->getPositionX()-m_content_w, m_rootY));
            CCEaseOut* _ease=CCEaseOut::create(_ani,2);
			CCSequence *squence2 = CCSequence::create(_ease, actionDone, NULL);
			rootSp->runAction(squence2);
        }
        canTouch=false;
	}
}
void FriendPagerLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent* pEvent){
    
}

#pragma mark アニメーション終わった
void FriendPagerLayer::onAnimatoinFinished(){
    canTouch=true;
    //m_p_last=rootSp->getPosition();
    //通知する
    //CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFY_SP_PAGER);
    
    if (leftBtn!=NULL && rightBtn!=NULL) {
        if (nowContentNum==0) {
            leftBtn->setVisible(false);
        }else if(nowContentNum==contentsNum-1){
            rightBtn->setVisible(false);
        }else{
            leftBtn->setVisible(true);
            rightBtn->setVisible(true);
        }
    }
    
    
    //pagerCounterの表示更新
	_pagerCntr->MyUpdateVisible(nowContentNum);
}

int FriendPagerLayer::myGetNowShowing(){
    return nowContentNum;
}
void FriendPagerLayer::mySetFlickWidth(int wid){
    m_flick_w=wid;
}
int FriendPagerLayer::myGetContentNum(){
    return contentsNum;
}
void FriendPagerLayer::mySetShowPage(int n){
    
    nowContentNum=n;
    rootSp->setPositionX(m_content_w*n*-1);
    
    if (leftBtn!=NULL && rightBtn!=NULL) {
        if (nowContentNum==0) {
            leftBtn->setVisible(false);
        }else if(nowContentNum==contentsNum-1){
            rightBtn->setVisible(false);
        }else{
            leftBtn->setVisible(true);
            rightBtn->setVisible(true);
        }
    }
}
void FriendPagerLayer::mySetLastPage(int n){
    lastPageNum=n;
}


void FriendPagerLayer::myInitButton(const char* l_pngname,CCPoint l_position,const char* r_pngname,CCPoint r_position){
    
    leftBtn = MyEasyMenuItem::create(l_pngname, l_position, this, menu_selector(FriendPagerLayer::onLeft));
    
    rightBtn = MyEasyMenuItem::create(r_pngname, r_position, this, menu_selector(FriendPagerLayer::onRight));
    
	CCMenu *menuS = CCMenu::create(leftBtn, rightBtn,NULL);
	menuS->setPosition(ccp(0, 0));
    
	this->addChild(menuS,1);
    
    if (leftBtn!=NULL && rightBtn!=NULL) {
        if (nowContentNum==0) {
            leftBtn->setVisible(false);
        }else if(nowContentNum==contentsNum-1){
            rightBtn->setVisible(false);
        }else{
            leftBtn->setVisible(true);
            rightBtn->setVisible(true);
        }
    }
}


void FriendPagerLayer::onLeft(CCObject *pSender){
    if (!canTouch) return;
    //右へ動かす　つまり左が出る
    if(nowContentNum<=0)return;
    CCLOG("migi");
    
    canTouch=false;
    nowContentNum--;
    
    CCCallFunc *actionDone = CCCallFunc::create(this, callfunc_selector(FriendPagerLayer::onAnimatoinFinished));
    
    CCMoveTo* _ani=CCMoveTo::create(0.5f, ccp(rootSp->getPositionX()+m_content_w,m_rootY));
    CCEaseOut* _ease=CCEaseOut::create(_ani,2);
    CCSequence *squence2 = CCSequence::create(_ease, actionDone, NULL);
    rootSp->runAction(squence2);
}
void FriendPagerLayer::onRight(CCObject *pSender){
    if (!canTouch) return;
    //左へ動かす　つまり右が出る
    if(nowContentNum==contentsNum-1)return;
    CCLOG("hidari");
    
    canTouch=false;
    nowContentNum++;
    
    CCCallFunc *actionDone = CCCallFunc::create(this, callfunc_selector(FriendPagerLayer::onAnimatoinFinished));
    
    CCMoveTo *_ani = CCMoveTo::create(0.5f, ccp(rootSp->getPositionX()-m_content_w, m_rootY));
    CCEaseOut* _ease=CCEaseOut::create(_ani,2);
    CCSequence *squence2 = CCSequence::create(_ease, actionDone, NULL);
    rootSp->runAction(squence2);
}



const char* FriendPagerLayer::getCharaFilename(CCString* str,int level){
    if (GameUtil::getBoolFriendFlag(level+1)==true) {
        CCLOG("pngname_chara.plist kara yonda %s",str->getCString());
        return str->getCString();
    }else{
        CCLOG("getCharaFilename false");
        return PNG_ALBUM_CHARACTER_NONE;
    }
}

const char* FriendPagerLayer::getPanelFilename(CCString* str,int level) {
    if (GameUtil::getBoolFriendFlag(level+1)==true) {
        CCLOG("pngname_word.plist kara yonda %s",str->getCString());
        return str->getCString();
    }else{
        CCLOG("getPanelFilename false");
        return PNG_ALBUM_PANEL_NONE;
    }
}
