//
//  MyPagerCounter.cpp
//  kyojin
//
//  Created by コトブキ タロウ on 2014/02/27.
//
//

#import "MyPagerCounter.h"

#import "cocos2d.h"
#import "GameUtil.h"

USING_NS_CC;

MyPagerCounter::MyPagerCounter(){
    
}

MyPagerCounter::~MyPagerCounter(){
    //デストラクタ
}

//初期化
bool MyPagerCounter::init(){
    CCLOG("MyPagerCounter::init");
    if (CCLayer::init()) {
        
        // !!!:変数初期化
        contentsNum=0;
        //今表示してるやつ
        nowContentNum=0;

        //ルートのsp
        rootSp = CCSprite::create();
        
        return true;
    } else {
        return false;
    }
}

#pragma mark 初期設定
void MyPagerCounter::prepere(const char* normalPngname,const char* focusPngname,int num,CCPoint position,int _margin){
    rootSp->setAnchorPoint(ccp(0, 0));
    this->addChild(rootSp);
    
    normalPngName=normalPngname;
    focusPngName=focusPngname;
    
    for (int i=0; i<num; i++) {
		//add
		CCSprite *_sp = CCSprite::createWithSpriteFrameName(normalPngName);
		_sp->setTag(i);
		contentW = _sp->getContentSize().width;
		_sp->setPositionX((contentW+_margin)*i);//(_margin * i)
        anc00(_sp)
        //rootSpにaddする
        rootSp->addChild(_sp);
    }
    

    //CCLOG("m_content_w=%f",m_content_w);
    
    rootSp->setPosition(position);
    /*
    //中央に
	CCSize m_winSize = CCDirector::sharedDirector()->getWinSize();
	int _rootW = contentW * num + _margin * (num - 1);
	rootSp->setPositionX((m_winSize.width - _rootW) / 2.0f);
	rootSp->setPositionY(_yposition);
     */
    nowContentNum=0;
    contentsNum=num;
    
    MyUpdateVisible(0);
}


#pragma mark ページ移動終わったら外から呼ぶ
void MyPagerCounter::MyUpdateVisible(int num){
    for (int i=0; i<contentsNum; i++) {
        if(i==num){
            CCSprite *sp1 = ((CCSprite*)rootSp->getChildByTag(i));
            GameUtil::changeSpImage(sp1, focusPngName);
        }else{
            CCSprite *sp1 = ((CCSprite*)rootSp->getChildByTag(i));
            GameUtil::changeSpImage(sp1, normalPngName);
        }
    }

}
