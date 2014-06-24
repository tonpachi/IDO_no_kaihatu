//
//  TombLayer.cpp
//  kyojin
//
//  Created by コトブキ タロウ on 2014/02/21.
//
//

#import "TombLayer.h"
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

TombLayer::TombLayer(){
    
}

TombLayer::~TombLayer(){
    //デストラクタ


}

//初期化
bool TombLayer::init(){
    CCLOG("TombLayer::init");
    if (CCLayer::init()) {
        
        m_winSize = CCDirector::sharedDirector()->getWinSize();
        
        totalyogoreCnt=SaveUtil::getSaveInt(USERDEFAULT_TOMB_CLEAN_UP, 0);
        
        return true;
    } else {
        return false;
    }
}


#pragma mark -------------敵を生むループ
void TombLayer::enemyCreateLoop(){
    if (i_enemyCnt<=KASI_MAKE_MAX) {
        //墓にかぶるようにランダム場所
        //種類
        int k = (int)(2 * CCRANDOM_0_1());

        int ranx = hakaX+(int)( CCRANDOM_0_1() * hakaW );
        int rany = hakaY+(int)( CCRANDOM_0_1() * hakaH );
        
        createEnemy(ranx,rany,k);
    }
}


void TombLayer::createEnemy(int xx,int yy,int kind){
    /* 画像の表示 */
	CCSprite *pSprite = CCSprite::createWithSpriteFrameName("grave_yogore.png");
    //タッチ領域
    pSprite->setContentSize(CCSizeMake(65, 65));

    pSprite->setTag(kind);
    
    pSprite->setPosition(ccp(xx, yy));
    
    this->addChild(pSprite);
    //管理配列に入れる
	enemySpList.push_back(pSprite);
    int size=enemySpList.size();
    i_enemyCnt=size+1;
}


#pragma mark 初期設定
void TombLayer::prepare(){
    userdefault_NUM=USERDEFAULT_YOGORE_NUM;
    userdefault_POS=USERDEFAULT_STRING_POINT_YOGORE;
    userdefault_KIND=USERDEFAULT_STRING_KIND_YOGORE;
    
    escapeRect=CCRectMake(170,355, 256, 248);
    hakaX=170;
    hakaY=355;
    hakaW=256;
    hakaH=350;
    
    createEnemyBySavedPosition();
}

// !!!:----------------敵の場所のセーブ
void TombLayer::saveEnemyPosition(){
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
    
    SaveUtil::saveInt(userdefault_NUM,i_enemyCnt);
}


// !!!:-----------敵の場所の復帰 起動後1度だけ
void TombLayer::createEnemyBySavedPosition(){
    
    //数
    i_enemyCnt=SaveUtil::getSaveInt(userdefault_NUM,0);
    CCLOG("fukki i_enemyCnt = %d",i_enemyCnt);
    
    CCString* _ccstrXY=CCString::create( SaveUtil::getSaveString(userdefault_POS) );
    CCString* _ccstrKIND=CCString::create( SaveUtil::getSaveString(userdefault_KIND) );
    
    if (i_enemyCnt!=0 && _ccstrXY->length()!=0) {
        //_esaが0じゃなければcreateSprite
        std::string _str(_ccstrXY->getCString());
        std::string _strK(_ccstrKIND->getCString());
        
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
            
            //x y kind direct
            createEnemy(_ranx,_rany,kindI);
        }
    }else{
        //createSprite();
    }
}


#pragma mark -------------条件で敵EnemySpriteの削除
int TombLayer::deleteSpriteFunc(CCPoint tpoint) {
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
void TombLayer::createEnemydied(CCSprite *pSprite){
    totalyogoreCnt++;
    
    GameUtil::changeSpImage(pSprite, "grave_yogore_on.png");
    //runActionをするspを引数にとる
    CCCallFuncN *_endfunc = CCCallFuncN::create(this,callfuncN_selector(TombLayer::endDiedAnim));
    
    CCFiniteTimeAction *_alp = CCFadeTo::create(1.0f, 0.0f);
    CCSequence *_sc = CCSequence::create(_alp,_endfunc, NULL);
    pSprite->runAction(_sc);
    
    ///-----------友達出現判定
    if (4<=totalyogoreCnt && totalyogoreCnt<5) {
        //2
        zawazawa();
    }else if (15<=totalyogoreCnt && totalyogoreCnt<16){
        //3
        zawazawa();
    }else{
        
    }
    
    SaveUtil::saveInt(USERDEFAULT_TOMB_CLEAN_UP, totalyogoreCnt);
}


void TombLayer::zawazawa(){
    SaveUtil::saveBool(USERDEFAULT_FRIEND_ZAWAZAWA,true);
}


void TombLayer::endDiedAnim(CCNode* sender){
    sender->removeFromParentAndCleanup(true);
}


void TombLayer::startLoop(){
        this->schedule(schedule_selector(TombLayer::enemyCreateLoop), TIME_TOMB_DIRTY);
}



void TombLayer::stopLoop(){
    this->unscheduleAllSelectors();
}

#pragma mark アニメーション終わった


int TombLayer::getEnemyCount(){
    return i_enemyCnt;
}


