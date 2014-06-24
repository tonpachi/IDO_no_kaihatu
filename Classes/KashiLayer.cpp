//
//  KashiLayer.cpp
//  kyojin
//
//  Created by コトブキ タロウ on 2014/02/21.
//
//

#import "KashiLayer.h"
#include "SaveUtil.h"
#import "GameUtil.h"

#import "cocos2d.h"

#import <iostream>
#import <list>
#import <string>
#import <vector>
#import "MyAnimationUtil.h"
#import "KasiGetLayer.h"

USING_NS_CC;
using namespace std;

KashiLayer::KashiLayer(){
    
}

KashiLayer::~KashiLayer(){
    //デストラクタ


}

//初期化
bool KashiLayer::init(){
    CCLOG("KashiLayer::init");
    if (CCLayer::init()) {
        
        m_winSize = CCDirector::sharedDirector()->getWinSize();
        
        return true;
    } else {
        return false;
    }
}

#pragma mark おかしを生むループ
void KashiLayer::okashiCreateLoop(){
    CCLOG("60sec KashiLayer::okashiCreateLoop    i_kashiCnt = %d",i_kashiCnt);
    if (i_kashiCnt<KASI_MAKE_MAX) {
        //井戸にかぶらないようにランダム場所
        int ranx;
        int rany;
        while (true) {
            ranx = 150+(int)( CCRANDOM_0_1() * (m_winSize.width-300) );
            rany = 300+(int)( CCRANDOM_0_1() * 200 );
            if (escapeRect.containsPoint(ccp(ranx, rany))) {
                
            }else{
                break;
            }
        }
        //種類
        int k = (int)(3 * CCRANDOM_0_1());
        createOkashi(ranx,rany,k);
    }
}
void KashiLayer::createOkashi(int xx,int yy,int kind){
    /* 画像の表示 */
	CCSprite *pSprite = CCSprite::create();
    //CCLOG("createOkashi x=%d  y=%d   kind=%d",xx,yy,kind);
    //1コマの時間をランダムにして
    CCAnimation* ani;
    if (kind==0) {
        //
        ani=MyAnimationUtil::setKomaAniByFileName2("okashi1.png", "okashi1.png", 0.5+0.5 * CCRANDOM_0_1(), -1);
        pSprite->runAction(CCAnimate::create(ani));
    }else if(kind==1){
        ani=MyAnimationUtil::setKomaAniByFileName2("okashi2.png", "okashi2.png", 0.5+0.5 * CCRANDOM_0_1(), -1);
        pSprite->runAction(CCAnimate::create(ani));
    }else{
        ani=MyAnimationUtil::setKomaAniByFileName2("okashi3.png", "okashi3.png", 0.5+0.5 * CCRANDOM_0_1(), -1);
        pSprite->runAction(CCAnimate::create(ani));
    }
    
    pSprite->setPosition(ccp(xx, yy));
    pSprite->setTag(kind);
    
    this->addChild(pSprite,kGameLayerOnBg2);
    //管理配列に入れる
	kashiSpList.push_back(pSprite);
    i_kashiCnt++;
}

// !!!:菓子ゲットのダイアログ
void KashiLayer::showGetOkashiDialog(int kind){
    
    KasiGetLayer* okashiGetDialogLayer=KasiGetLayer::create();
    okashiGetDialogLayer->show(kind, this, menu_selector(KashiLayer::closeAddLayer));
    okashiGetDialogLayer->setTag(109);
    
    this->addChild(okashiGetDialogLayer,kGameLayerDialog);
    
}
void KashiLayer::closeAddLayer(){
    this->getChildByTag(109)->removeFromParentAndCleanup(true);
}


#pragma mark 初期設定
void KashiLayer::setMode(klaunchScene scene){
    if (scene==klaunchSceneIdo) {
        //井戸
        userdefault_NUM=USERDEFAULT_KASHI_NUM_IDO;
        userdefault_POS=USERDEFAULT_STRING_POINT_KASI_IDO;
        userdefault_KIND=USERDEFAULT_STRING_KIND_KASI_IDO;

    }else if(scene==klaunchSceneHaka){
        //墓
        userdefault_NUM=USERDEFAULT_KASHI_NUM_HAKA;
        userdefault_POS=USERDEFAULT_STRING_POINT_KASI_HAKA;
        userdefault_KIND=USERDEFAULT_STRING_KIND_KASI_HAKA;

    }else{
        //池
        userdefault_NUM=USERDEFAULT_KASHI_NUM_IKE;
        userdefault_POS=USERDEFAULT_STRING_POINT_KASI_IKE;
        userdefault_KIND=USERDEFAULT_STRING_KIND_KASI_IKE;
    }
    
    escapeRect=CCRectMake(170,355, 256, 248);
    
    createKasiBySavedPosition();
}

// !!!:-----------菓子の場所保存
void KashiLayer::saveKasiPosition(){
    //菓子の座標を文字列で保存する
    std::string _strXY("");
    //菓子の種類を文字列で保存
    std::string _strKIND("");
    
    // イテレータの取得
	std::list <CCSprite *>::iterator it = kashiSpList.begin();
	while (it != kashiSpList.end()) {
		// spriteの取得
		CCSprite *pSprite = *it;
		// spriteの位置の取得
		float pssx = pSprite->getPositionX();
        float pssy = pSprite->getPositionY();
        
        CCString* _ccstrx=CCString::createWithFormat("%.1f",pssx);
        _strXY.append(_ccstrx->getCString());
        
        _strXY.append(",");
        
        CCString* _ccstry=CCString::createWithFormat("%.1f",pssy);
        _strXY.append(_ccstry->getCString());
        
        _strXY.append(",");
        
        //種類
        int _kind=pSprite->getTag();
        CCString* _ccstrk=CCString::createWithFormat("%d",_kind);
        _strKIND.append(_ccstrk->getCString());
        
        // イテレータを進める
        it++;
    }
    //CCLOG("_str=%s",_str.c_str());
    
    //菓子の座標を文字列で保存
    SaveUtil::saveString(userdefault_POS,_strXY.c_str());
    //種類
    SaveUtil::saveString(userdefault_KIND,_strKIND.c_str());
    
    if(3<i_kashiCnt)i_kashiCnt=3;
    SaveUtil::saveInt(userdefault_NUM,i_kashiCnt);
    CCLOG("save i_kashiCnt = %d",i_kashiCnt);
}
// !!!:-----------菓子の場所復帰
void KashiLayer::createKasiBySavedPosition(){
    //数
    i_kashiCnt=SaveUtil::getSaveInt(userdefault_NUM,0);
    if(3<i_kashiCnt)i_kashiCnt=3;
    CCLOG("fukki i_kashiCnt = %d",i_kashiCnt);
    CCString* _ccstrXY=CCString::create( SaveUtil::getSaveString(userdefault_POS) );
    CCString* _ccstrKIND=CCString::create( SaveUtil::getSaveString(userdefault_KIND) );
    
    if (i_kashiCnt!=0 && _ccstrXY->length()!=0) {
        //が0じゃなければcreateSprite
        std::string _str(_ccstrXY->getCString());
        std::string _strK(_ccstrKIND->getCString());
        
        //CCLOG("fukki _str=%s",_str.c_str());
        float _ranx=0;
        float _rany=0;
        
        int _sentou=0;
        //菓子の数だけ繰り返し
        for (int i=0; i<i_kashiCnt; i++) {
            //xを出す
			int _firstComma = _str.find(",");
            
			if (_firstComma == string::npos) {
				continue;
			}else {
                CCString* _stx=CCString::create(_str.substr(_sentou,_firstComma));
                //xが出た
                //CCLOG("substr x = %s",_stx->getCString());
                _str.erase(_sentou,_firstComma+1);
                _ranx = _stx->floatValue();
			}
            
            //yを出す
            _firstComma = _str.find(",");
            
			if (_firstComma == string::npos) {
				continue;
			}else {
                CCString* _sty=CCString::create(_str.substr(_sentou,_firstComma));
                //yが出た
                //CCLOG("substr y = %s",_sty->getCString());
                _str.erase(_sentou,_firstComma+1);
                _rany = _sty->floatValue();
			}
            
            //CCLOG("sprite x = %f   y = %f",_ranx,_rany);
            char _knum=_strK.at( i );
            int kindI=atoi( &_knum );
            CCLOG("fukki KashiLayer::createKasiBySavedPosition i_kashiCnt = %d",i_kashiCnt);
            //x y kind direct
            createOkashi(_ranx,_rany,kindI);
        }//end for
    }else{
        
    }
}


#pragma mark 条件でおかしの削除
int KashiLayer::touchOkashiSpFunc(CCPoint tpoint){
    // イテレータの取得
	std::list <CCSprite *>::iterator it = kashiSpList.begin();
	while (it != kashiSpList.end()) {
		// spriteの取得
		CCSprite *pSprite = *it;
		// spriteの位置の取得
		//float pssx = pSprite->getPositionX();
        //float pssy = pSprite->getPositionY();
        bool isHit=false;
        //タッチ座標の下にspがいるか
        CCRect _rect = pSprite->boundingBox();
        if(_rect.containsPoint(tpoint)){
            isHit=true;
        }
        
        if (isHit) {
            int _shurui=pSprite->getTag();
            pSprite->removeFromParentAndCleanup(true);
            
            // spriteのリストから削除＆削除した要素以降のイテレータの取得
			it = kashiSpList.erase(it);
            i_kashiCnt=kashiSpList.size();
            CCLOG("delete okasi i_kashiCnt=%d",i_kashiCnt);
            //おかしの種類によって消すダイアログ
            showGetOkashiDialog(_shurui);
            return _shurui;
            break;
        }else{
            it++;
        }
        
    }//end while
    return -1;
}




void KashiLayer::startLoop(){
    this->schedule(schedule_selector(KashiLayer::okashiCreateLoop), TIME_KASI_MAKE_SEC);
}



void KashiLayer::stopLoop(){
    this->unscheduleAllSelectors();
}


/*
void KashiLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {

}

// スワイプ中
void KashiLayer::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent) {
    
	// タップポイント取得
	CCDirector *pDirector = CCDirector::sharedDirector();
	CCPoint tpoint = pDirector->convertToGL(pTouch->getLocationInView());
    //CCLog("ccTouchMoved x=%f y=%f",tpoint.x,tpoint.y);
    
}
// タップキャンセル時
void KashiLayer::ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent) {

    
}
*/


