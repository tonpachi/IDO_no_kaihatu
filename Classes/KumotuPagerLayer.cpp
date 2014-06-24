//
//  KumotuPagerLayer.cpp
//  kyojin
//
//  Created by コトブキ タロウ on 2014/02/21.
//
//

#import "KumotuPagerLayer.h"
#import "MyEasyMenuItem.h"
#import "GameUtil.h"

#import "cocos2d.h"


USING_NS_CC;

KumotuPagerLayer::KumotuPagerLayer(){
    
}

KumotuPagerLayer::~KumotuPagerLayer(){
    //デストラクタ
    spArray->release();
        m_point_vec.clear();
}

//初期化
bool KumotuPagerLayer::init(){
    CCLOG("KumotuPagerLayer::init");
    if (CCLayer::init()) {
        // タッチ有効化
        setTouchEnabled(true);
        setTouchMode(kCCTouchesOneByOne);
                this->setTouchPriority(kModalLayerPriority_b);
        
        
        // !!!:変数初期化
        spArray= CCArray::create();
        spArray->retain();
        m_flick_w=100;
        contentsNum=0;
        //今表示してるやつ
        nowContentNum=0;
        canTouch=true;
        
        
        CCSize m_winSize=CCDirector::sharedDirector()->getWinSize();
        
        
        
        //黒
        CCSprite* m_blackBg = GameUtil::makeBlackBg(m_winSize.width, m_winSize.height);
        pos00(m_blackBg)
        this->addChild(m_blackBg,kGameLayerBackground0);
        
        
        
        //最初ゼロ
        m_p_last=CCPointZero;
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
void KumotuPagerLayer::prepere(int wsize,int hsize,CCPoint _position){
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
    
    this->addChild(m_clippingNode,kGameLayerOnBg1);
    nowContentNum=0;
    m_rootY=0;
    
    CCRect _re1 = m_clippingNode->boundingBox();
    CCRect _re2 = maskSp->boundingBox();

    m_inTouchRect=CCRectMake(_re1.getMinX(),_re1.getMinY(),_re2.getMaxX(),_re2.getMaxY());
    
    
    myInitButton("btn_arrow_l.png", ccp(52,647), "btn_arrow_r.png", ccp(588,647));
    
    
    //閉じるボタンもadd
    MyEasyMenuItem *_backItem = MyEasyMenuItem::create("ok_btn.png", ccp(320,200), this, menu_selector(KumotuPagerLayer::closeAddLayer));
    
    CCMenu *_menuS = CCMenu::create(_backItem,NULL);
	_menuS->setPosition(ccp(0, 0));
    _menuS->setTouchPriority(kModalLayerPriority_b_menu);
    this->addChild(_menuS);
    
    
    //ここでadd sprite 5種類
    
    
}


#pragma mark add_array
void KumotuPagerLayer::addSpByFilename(const char* pngname){
    //テクスチャアトラス使う前提
    //spriteをaddChild
    CCSprite *_sp = CCSprite::createWithSpriteFrameName(pngname);
    _sp->setAnchorPoint(CCPointZero);
    
    int _spw=_sp->getContentSize().width;
    
	_sp->setPosition(ccp(m_p_last.x+(m_content_w-_spw)/2,m_p_last.y));
    //rootSpにaddする
	rootSp->addChild(_sp);
    //管理配列にもadd
    spArray->addObject(_sp);
    
    float _x=m_p_last.x+m_content_w;
    m_p_last=ccp(_x, m_p_last.y);
    
    m_point_vec.push_back(m_p_last);
    
    contentsNum++;
    
    lastPageNum=contentsNum;
}

void KumotuPagerLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
    
}

bool KumotuPagerLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    CCLOG("KumotuPagerLayer::ccTouchBegan");
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

void KumotuPagerLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
    CCLOG("KumotuPagerLayer::ccTouchEnded");
    if(!isContainRect)return;
    
    
    // 離した時の座標を保存
	CCDirector *pDirector = CCDirector::sharedDirector();
	CCPoint touchEndPoint = pDirector->convertToGL(pTouch->getLocationInView());
    //どっちに動いたか　1=右　-1=左
	int _direct = (touchStartPoint.x < touchEndPoint.x) ? 1 : -1;
	//どんだけ動いたか
    float _movew = (_direct==1)?(touchEndPoint.x - touchStartPoint.x) : (touchStartPoint.x - touchEndPoint.x);
	if (m_flick_w <= _movew) {
        CCCallFunc *actionDone = CCCallFunc::create(this, callfunc_selector(KumotuPagerLayer::onAnimatoinFinished));
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
void KumotuPagerLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent* pEvent){
    
}

#pragma mark アニメーション終わった
void KumotuPagerLayer::onAnimatoinFinished(){
    canTouch=true;
    //m_p_last=rootSp->getPosition();

    
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

int KumotuPagerLayer::myGetNowShowing(){
    return nowContentNum;
}
void KumotuPagerLayer::mySetFlickWidth(int wid){
    m_flick_w=wid;
}
int KumotuPagerLayer::myGetContentNum(){
    return contentsNum;
}
void KumotuPagerLayer::mySetShowPage(int n){
    
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
void KumotuPagerLayer::mySetLastPage(int n){
    lastPageNum=n;
}


void KumotuPagerLayer::myInitButton(const char* l_pngname,CCPoint l_position,const char* r_pngname,CCPoint r_position){
    
    leftBtn = MyEasyMenuItem::create(l_pngname, l_position, this, menu_selector(KumotuPagerLayer::onLeft));
    
    rightBtn = MyEasyMenuItem::create(r_pngname, r_position, this, menu_selector(KumotuPagerLayer::onRight));
    
	CCMenu *menuS = CCMenu::create(leftBtn, rightBtn,NULL);
	menuS->setPosition(ccp(0, 0));
    menuS->setTouchPriority(kModalLayerPriority_a);
    
	this->addChild(menuS,kGameLayerOnBg2);
    
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


void KumotuPagerLayer::onLeft(CCObject *pSender){
    if (!canTouch) return;
    //右へ動かす　つまり左が出る
    if(nowContentNum<=0)return;
    CCLOG("migi");
    
    canTouch=false;
    nowContentNum--;
    
    CCCallFunc *actionDone = CCCallFunc::create(this, callfunc_selector(KumotuPagerLayer::onAnimatoinFinished));
    
    CCMoveTo* _ani=CCMoveTo::create(0.5f, ccp(rootSp->getPositionX()+m_content_w,m_rootY));
    CCEaseOut* _ease=CCEaseOut::create(_ani,2);
    CCSequence *squence2 = CCSequence::create(_ease, actionDone, NULL);
    rootSp->runAction(squence2);
}
void KumotuPagerLayer::onRight(CCObject *pSender){
    if (!canTouch) return;
    //左へ動かす　つまり右が出る
    if(nowContentNum==contentsNum-1)return;
    CCLOG("hidari");
    
    canTouch=false;
    nowContentNum++;
    
    CCCallFunc *actionDone = CCCallFunc::create(this, callfunc_selector(KumotuPagerLayer::onAnimatoinFinished));
    
    CCMoveTo *_ani = CCMoveTo::create(0.5f, ccp(rootSp->getPositionX()-m_content_w, m_rootY));
    CCEaseOut* _ease=CCEaseOut::create(_ani,2);
    CCSequence *squence2 = CCSequence::create(_ease, actionDone, NULL);
    rootSp->runAction(squence2);
}


void KumotuPagerLayer::closeAddLayer(CCObject *pSender){
    this->removeFromParentAndCleanup(true);
}