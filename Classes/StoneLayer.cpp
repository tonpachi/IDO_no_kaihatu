//
//  StoneLayer.cpp
//  kyojin
//
//  Created by コトブキ タロウ on 2014/02/21.
//
//

#import "StoneLayer.h"
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

StoneLayer::StoneLayer(){
    
}

StoneLayer::~StoneLayer(){
    //デストラクタ


}

//初期化
bool StoneLayer::init(){
    CCLOG("StoneLayer::init");
    if (CCLayer::init()) {
        
        m_winSize = CCDirector::sharedDirector()->getWinSize();
        
        
        stoneCnt_normal=SaveUtil::getSaveInt(USERDEFAULT_STONE_COUNT_NORMAL, 0);
        stoneCnt_gold=SaveUtil::getSaveInt(USERDEFAULT_STONE_COUNT_GOLD, 0);
        
        //-------------------デバッグ
        //メーターの数字
        m_Label_enemy = CCLabelTTF::create("0", FONT_NAME_Marker,21);
        m_Label_enemy->setAnchorPoint(ccp(1, 1));
        m_Label_enemy->setPosition(ccp(640,960));
        m_Label_enemy->setColor(ccWHITE);
        CCString* cntS=CCString::createWithFormat("stone point : %d",stoneCnt_normal);
        m_Label_enemy->setString(cntS->getCString());
        this->addChild(m_Label_enemy,kGameLayerDebugText);
        
        //-------------------
        return true;
    } else {
        return false;
    }
}


#pragma mark -------------石を生むループ
void StoneLayer::enemyCreateLoop(){
    if (i_STONECnt<STONE_MAKE_MAX) {
        //ランダム場所
        int ranx = 150+(int)( CCRANDOM_0_1() * (m_winSize.width-300) );
        int rany = 300+(int)( CCRANDOM_0_1() * 200 );
        
        int k = 2 * CCRANDOM_0_1();
        int d = (2 * CCRANDOM_0_1());
        createEnemy(ranx,rany,k,d);
    }
}
void StoneLayer::createEnemy(int xx,int yy,int kind,int direct){
    /* 画像の表示 */
	CCSprite *pSprite = CCSprite::createWithSpriteFrameName("stone.png");
    CCSprite *_sp=CCSprite::createWithSpriteFrameName("stone_black.png");
    _sp->setOpacity(0);
    _sp->setTag(14);
    anc00(_sp)
    pSprite->addChild(_sp);
    
    pSprite->setPosition(ccp(xx, yy));
    pSprite->setTag(kind);
    
    this->addChild(pSprite,kGameLayerOnBg1);
    //管理配列に入れる
	enemySpList.push_back(pSprite);
    int size=enemySpList.size();
    i_STONECnt=size+1;
    
    //CCLOG("createStone i_STONECnt=%d",i_STONECnt);
}


#pragma mark 初期設定
void StoneLayer::prepare(){
    
    userdefault_NUM=USERDEFAULT_STONE_NUM;
    userdefault_POS=USERDEFAULT_STRING_POINT_STONE;
    userdefault_KIND=USERDEFAULT_STRING_KIND_STONE;
    
    escapeRect=CCRectMake(170,355, 256, 248);
    
    createEnemyBySavedPosition();
}

#pragma mark -------------条件で　石　Spriteの削除
void StoneLayer::deleteSpriteFunc(CCPoint tpoint) {
    // イテレータの取得
	std::list <CCSprite *>::iterator it = enemySpList.begin();
	while (it != enemySpList.end()) {
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
            int size=enemySpList.size();
            i_STONECnt=size-1;
            
            pSprite->stopAllActions();
            // spriteのリストから削除＆削除した要素以降のイテレータの取得
			it = enemySpList.erase(it);
            
            //石の種類によって消すアニメーション
            createEnemydied(pSprite);
            break;
            
            //メーターとかをいじる
            //updateScore();
            break;
        }else{
            it++;
        }
        
    }//end while
    
}

#pragma mark 石の種類によって消すアニメーションをrun
void StoneLayer::createEnemydied(CCSprite *pSprite){
    stoneCnt_normal++;
    /*
     if (pSprite->getTag()==0) {
     //からす
     //runActionをするspを引数にとる
     CCCallFuncN *_endfunc = CCCallFuncN::create(this,callfuncN_selector(LakeScene::endDiedAnim));
     
     CCFiniteTimeAction *_move1 = CCMoveTo::create(4.0f,ccp(0, m_winSize.height));
     CCSequence *_sc = CCSequence::create(_move1,_endfunc, NULL);
     pSprite->runAction(_sc);
     }else{
     //runActionをするspを引数にとる
     CCCallFuncN *_endfunc = CCCallFuncN::create(this,callfuncN_selector(LakeScene::endDiedAnim));
     
     CCFiniteTimeAction *_alp = CCFadeTo::create(3.0f, 0.0f);
     CCSequence *_sc = CCSequence::create(_alp,_endfunc, NULL);
     pSprite->runAction(_sc);
     }
     */
    CCSprite *_isi=(CCSprite*)(pSprite->getChildByTag(14));
    int ranx = 50-(int)( CCRANDOM_0_1() * 100 );
    int rany = 50-(int)( CCRANDOM_0_1() * 100 );
    int ranh = 300+(int)( CCRANDOM_0_1() * 100 );
    float sec = 2+CCRANDOM_0_1();
    //runActionをするspを引数にとる
    CCCallFuncN *_endfunc = CCCallFuncN::create(this,callfuncN_selector(StoneLayer::endDiedAnim));
    
    //アニメ加える
    //CCFiniteTimeAction *_move1 = CCJumpTo::create(sec, ccp(306+ranx, 742+rany), ranh, 1);
    CCJumpTo* _move1 = CCJumpTo::create(sec, ccp(306+ranx, 742+rany), ranh, 1);
    //CCEaseInOut* ease = CCEaseInOut::create(_move1,3);
    
    CCFiniteTimeAction *_scale = CCScaleTo::create(sec, 0.1);
    
    CCSpawn *spa=CCSpawn::createWithTwoActions(CCEaseOut::create(_move1,1.5), _scale);
    
    CCSequence *_sc = CCSequence::create(spa,_endfunc, NULL);
    
    CCFiniteTimeAction *_alp = CCFadeTo::create(sec, 200);
    _isi->runAction(_alp);
    pSprite->runAction(_sc);
    
    ///-----------友達出現判定
    if (40<=stoneCnt_normal && stoneCnt_normal<50) {
        //2
        zawazawa();
    }else if (180<=stoneCnt_normal && stoneCnt_normal<200){
        //3
        zawazawa();
    }else if (450<=stoneCnt_normal && stoneCnt_normal<480){
        //4
        zawazawa();
    }else{

    }
}

void StoneLayer::zawazawa(){
    SaveUtil::saveBool(USERDEFAULT_FRIEND_ZAWAZAWA,true);
}


#pragma mark 飛んだから石消す
void StoneLayer::endDiedAnim(CCNode* sender){
    sender->removeFromParentAndCleanup(true);
    
    CCString* cntS=CCString::createWithFormat("stone point : %d",stoneCnt_normal);
    m_Label_enemy->setString(cntS->getCString());
}



// !!!:-------------石の場所のセーブ
void StoneLayer::saveEnemyPosition(){
    //石の座標を文字列で保存する
    std::string _strXY("");
    //石の種類を文字列で保存
    std::string _strKIND("");
    
    // イテレータの取得
	std::list <CCSprite *>::iterator it = enemySpList.begin();
	while (it != enemySpList.end()) {
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
    
    ///!!!:石の座標を文字列で保存
    SaveUtil::saveString(userdefault_POS,_strXY.c_str());
    //種類
    SaveUtil::saveString(userdefault_KIND,_strKIND.c_str());
    
    SaveUtil::saveInt(userdefault_NUM,i_STONECnt);
}


// !!!:-----------石の場所の復帰
void StoneLayer::createEnemyBySavedPosition(){
    
    //数
    i_STONECnt=SaveUtil::getSaveInt(userdefault_NUM,0);
    
    CCString* _ccstrXY=CCString::create( SaveUtil::getSaveString(userdefault_POS) );
    CCString* _ccstrKIND=CCString::create( SaveUtil::getSaveString(userdefault_KIND) );
    
    if (i_STONECnt!=0 && _ccstrXY->length()!=0) {
        //_esaが0じゃなければcreateSprite
        std::string _str(_ccstrXY->getCString());
        std::string _strK(_ccstrKIND->getCString());
        
        //CCLOG("fukki _str=%s",_str.c_str());
        float _ranx=0;
        float _rany=0;
        
        int _sentou=0;
        //エサの数だけ繰り返し
        for (int i=0; i<i_STONECnt; i++) {
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
            createEnemy(_ranx,_rany,kindI,1);
        }
    }else{
        //createSprite();
    }
}



void StoneLayer::startLoop(){
    this->schedule(schedule_selector(StoneLayer::enemyCreateLoop), TIME_STONE_MAKE_SEC);
}



void StoneLayer::stopLoop(){
    this->unscheduleAllSelectors();
}

#pragma mark アニメーション終わった



