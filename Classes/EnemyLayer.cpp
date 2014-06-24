//
//  EnemyLayer.cpp
//  kyojin
//
//  Created by コトブキ タロウ on 2014/02/21.
//
//

#import "EnemyLayer.h"
#include "SaveUtil.h"
#import "GameUtil.h"

#import "cocos2d.h"

#import <iostream>
#import <list>
#import <string>
#import <vector>
#import "MyAnimationUtil.h"

USING_NS_CC;
using namespace std;

EnemyLayer::EnemyLayer(){
    
}

EnemyLayer::~EnemyLayer(){
    //デストラクタ


}

//初期化
bool EnemyLayer::init(){
    CCLOG("EnemyLayer::init");
    if (CCLayer::init()) {
        
        m_winSize = CCDirector::sharedDirector()->getWinSize();
        
        return true;
    } else {
        return false;
    }
}


#pragma mark -------------敵を生むループ
void EnemyLayer::enemyCreateLoop(){
    
    if (i_enemyCnt<=ENEMY_MAKE_MAX) {
        //井戸にかぶらないようにランダム場所
        //種類
        int k = (int)(2 * CCRANDOM_0_1());
        
        int ranx;
        int rany;
        while (true) {
            ranx = 150+(int)( CCRANDOM_0_1() * (m_winSize.width-300) );
            if(k==0)rany = 300+(int)( CCRANDOM_0_1() * 300 );
            else rany = 300+(int)( CCRANDOM_0_1() * 100 );

            if (escapeRect.containsPoint(ccp(ranx, rany))) {
                
            }else{
                break;
            }
        }
        
        //向き
        int d = (int)(2 * CCRANDOM_0_1());
        
        createEnemy(ranx,rany,k,(d==0)?-1:1);
    }
}


void EnemyLayer::createEnemy(int xx,int yy,int kind,int direct){
    /* 画像の表示 */
	CCSprite *pSprite = CCSprite::create();
    
    CCSprite *inSprite = CCSprite::create();
    inSprite->setTag(direct);
    inSprite->setAnchorPoint(ccp(0, 0));
    
    //CCLOG("createEnemy i_enemyCnt=%d",i_enemyCnt);
    //1コマの時間をランダムにして
    CCAnimation* ani;
    if (kind==0) {
        //からす
        ani=MyAnimationUtil::setKomaAniByFileName2("enemy_1.png", "enemy_1.png", 0.5+0.5 * CCRANDOM_0_1(), -1);
        inSprite->runAction(CCAnimate::create(ani));
        
        //タッチ領域
        pSprite->setContentSize(CCSizeMake(76, 162));
    }else{
        //ねこ
        ani=MyAnimationUtil::setKomaAniByFileName2("enemy_2.png", "enemy_2.png", 0.5+0.5 * CCRANDOM_0_1(), -1);
        inSprite->runAction(CCAnimate::create(ani));
        
        //タッチ領域
        pSprite->setContentSize(CCSizeMake(162, 76));
    }
    pSprite->setTag(kind);
    pSprite->addChild(inSprite);
    
    pSprite->setPosition(ccp(xx, yy));
    
    inSprite->setTag(direct);
    
    if (kind==1) {
        //ねこは左右に動く
        int desX;
        
        if (direct==1) {
            desX=xx+(int)( CCRANDOM_0_1() * 200 );
        }else{
            desX=xx-(int)( CCRANDOM_0_1() * 50 );
        }
        //runActionをするspを引数にとる
        CCCallFuncN *_endfunc = CCCallFuncN::create(this,callfuncN_selector(EnemyLayer::onCatAnimFnished));
        CCFiniteTimeAction *_move1 = CCMoveTo::create(10.0f,ccp(desX, yy));
        CCSequence *_sc = CCSequence::create(_move1,_endfunc, NULL);
        pSprite->runAction(_sc);
    }
    
    this->addChild(pSprite,kGameLayerOnBg1);
    //管理配列に入れる
	enemySpList.push_back(pSprite);
    int size=enemySpList.size();
    i_enemyCnt=size+1;
}

#pragma mark --onCatAnimFnished
void EnemyLayer::onCatAnimFnished(CCNode* sender){
    CCSprite *pSprite=(CCSprite*)sender;
    CCArray* inArr=pSprite->getChildren();
    CCSprite* inSp=(CCSprite*)inArr->objectAtIndex(0);
    
    //ねこは左右に動く
    int _d=inSp->getTag();
    
    int desX;
    
    if (_d==1) {
        desX=100+(int)( CCRANDOM_0_1() * 50 );
        //反転
        inSp->setFlipX(false);
    }else{
        desX=400+(int)( CCRANDOM_0_1() * 200 );
        inSp->setFlipX(true);
    }
    //CCLOG("_d= %d",_d);
    _d=_d*-1;
    inSp->setTag(_d);
    //runActionをするspを引数にとる
    CCCallFuncN *_endfunc = CCCallFuncN::create(this,callfuncN_selector(EnemyLayer::onCatAnimFnished));
    CCFiniteTimeAction *_move1 = CCMoveTo::create(10.0f,ccp(desX, pSprite->getPositionY()));
    CCSequence *_sc = CCSequence::create(_move1,_endfunc, NULL);
    pSprite->runAction(_sc);
}


#pragma mark 初期設定
void EnemyLayer::setMode(klaunchScene scene){
    if (scene==klaunchSceneIdo) {
        //井戸
        userdefault_NUM=USERDEFAULT_ENEMY_NUM_IDO;
        userdefault_POS=USERDEFAULT_STRING_POINT_ENEMY_IDO;
        userdefault_KIND=USERDEFAULT_STRING_KIND_ENEMY_IDO;
        userdefault_DIRECT=USERDEFAULT_STRING_DIREC_ENEMY_IDO;
    }else{
        //墓
        userdefault_NUM=USERDEFAULT_ENEMY_NUM_HAKA;
        userdefault_POS=USERDEFAULT_STRING_POINT_ENEMY_HAKA;
        userdefault_KIND=USERDEFAULT_STRING_KIND_ENEMY_HAKA;
        userdefault_DIRECT=USERDEFAULT_STRING_DIREC_ENEMY_HAKA;
    }
    
    escapeRect=CCRectMake(170,355, 256, 248);
    
    createEnemyBySavedPosition();
}

// !!!:----------------敵の場所のセーブ
void EnemyLayer::saveEnemyPosition(){
    //敵の座標を文字列で保存する
    std::string _strXY("");
    //敵の種類を文字列で保存
    std::string _strKIND("");
    //敵の向きを文字列で保存
    std::string _strDIRECT("");
    
    // イテレータの取得
	std::list <CCSprite *>::iterator it = enemySpList.begin();
	while (it != enemySpList.end()) {
		// spriteの取得
		CCSprite *pSprite = *it;
        
        CCArray* inArr=pSprite->getChildren();
        CCSprite* inSp=(CCSprite*)inArr->objectAtIndex(0);
        
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
        
        //向き左右
        int _dr=inSp->getTag();
        CCString* _ccstrD=CCString::createWithFormat("%d",_dr);
        _strDIRECT.append(_ccstrD->getCString());
        
        // イテレータを進める
        it++;
    }
    //CCLOG("_str=%s",_str.c_str());
    //敵の座標を文字列で保存
    SaveUtil::saveString(userdefault_POS,_strXY.c_str());
    //種類
    SaveUtil::saveString(userdefault_KIND,_strKIND.c_str());
    //向き
    SaveUtil::saveString(userdefault_DIRECT,_strDIRECT.c_str());
    
    SaveUtil::saveInt(userdefault_NUM,i_enemyCnt);
}


// !!!:-----------敵の場所の復帰 起動後1度だけ
void EnemyLayer::createEnemyBySavedPosition(){
    
    //数
    i_enemyCnt=SaveUtil::getSaveInt(userdefault_NUM,0);
    CCLOG("fukki i_enemyCnt = %d",i_enemyCnt);
    
    CCString* _ccstrXY=CCString::create( SaveUtil::getSaveString(userdefault_POS) );
    CCString* _ccstrKIND=CCString::create( SaveUtil::getSaveString(userdefault_KIND) );
    CCString* _ccstrDIRECT=CCString::create( SaveUtil::getSaveString(userdefault_DIRECT) );
    
    if (i_enemyCnt!=0 && _ccstrXY->length()!=0) {
        //_esaが0じゃなければcreateSprite
        std::string _str(_ccstrXY->getCString());
        std::string _strK(_ccstrKIND->getCString());
        std::string _strD(_ccstrDIRECT->getCString());
        
        //CCLOG("fukki _str=%s",_str.c_str());
        float _ranx=0;
        float _rany=0;
        
        int _sentou=0;
        //敵の数だけ繰り返し
        for (int i=0; i<i_enemyCnt; i++) {
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
            
            char _dnum=_strD.at( i );
            int DrI=atoi( &_dnum );
            
            //x y kind direct
            createEnemy(_ranx,_rany,kindI,DrI);
        }
    }else{
        //createSprite();
    }
}


#pragma mark -------------条件で敵EnemySpriteの削除
int EnemyLayer::deleteSpriteFunc(CCPoint tpoint) {
    // イテレータの取得
	std::list <CCSprite *>::iterator it = enemySpList.begin();
	while (it != enemySpList.end()) {
		// spriteの取得
		CCSprite *pSprite = *it;

        bool isHit=false;
        //タッチ座標の下にspがいるか
        CCRect _rect = pSprite->boundingBox();
        if(_rect.containsPoint(tpoint)){
            isHit=true;
        }
        
        if (isHit) {
            int size=enemySpList.size();
            i_enemyCnt=size-1;
            
            CCLOG("deleteEnemy i_enemyCnt=%d",i_enemyCnt);
            pSprite->stopAllActions();
            // spriteのリストから削除＆削除した要素以降のイテレータの取得
			it = enemySpList.erase(it);
            
            //敵の種類によって消すアニメーション
            createEnemydied(pSprite);
            return PT_ENEMY;
            break;
        }else{
            it++;
        }
        
    }//end while

    return 0;
}

//敵の種類によって消すアニメーション
void EnemyLayer::createEnemydied(CCSprite *pSprite){
    
    CCArray* inArr=pSprite->getChildren();
    CCSprite* inSp=(CCSprite*)inArr->objectAtIndex(0);
    
    if (pSprite->getTag()==0) {
        //からす
        //runActionをするspを引数にとる
        CCCallFuncN *_endfunc = CCCallFuncN::create(this,callfuncN_selector(EnemyLayer::endDiedAnim));
        
        CCFiniteTimeAction *_move1 = CCMoveTo::create(4.0f,ccp(0, m_winSize.height));
        CCSequence *_sc = CCSequence::create(_move1,_endfunc, NULL);
        pSprite->runAction(_sc);
    }else{
        inSp->stopAllActions();
        inSp->removeFromParentAndCleanup(true);
        
        GameUtil::changeSpImage(pSprite, "enemy_2_dead.png");
        //runActionをするspを引数にとる
        CCCallFuncN *_endfunc = CCCallFuncN::create(this,callfuncN_selector(EnemyLayer::endDiedAnim));
        
        CCFiniteTimeAction *_alp = CCFadeTo::create(1.0f, 0.0f);
        CCSequence *_sc = CCSequence::create(_alp,_endfunc, NULL);
        pSprite->runAction(_sc);
    }
}
void EnemyLayer::endDiedAnim(CCNode* sender){
    sender->removeFromParentAndCleanup(true);
}


void EnemyLayer::startLoop(){
        this->schedule(schedule_selector(EnemyLayer::enemyCreateLoop), TIME_ENEMY_MAKE_SEC);
}



void EnemyLayer::stopLoop(){
    this->unscheduleAllSelectors();
}

#pragma mark アニメーション終わった


int EnemyLayer::getEnemyCount(){
    return i_enemyCnt;
}


