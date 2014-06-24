//
//  IdoAnaScene.h
//
//
//  Created by dotchi on 2014/06/02.
//
//

#ifndef __nagure__IdoAnaScene__
#define __nagure__IdoAnaScene__


#import "cocos2d.h"
#import "MyEasyMenuItem.h"
#import "GameUtil.h"

#import "BaseSimpleLayer.h"
#import "MeterLayer.h"
USING_NS_CC;

//
#define ADD_LAYER_ESADIALOG 123
#define ADD_LAYER_CONFIRMDIALOG 456


class IdoAnaScene :public CCLayer{
protected:
    
    //Sp
    //----------------------------------------------

    //背景
    CCSprite* m_backGroundSprite;
    
    //
    MyEasyMenuItem* m_esatBtn;
    MyEasyMenuItem* m_backtBtn;

    BaseSimpleLayer* dialogLayer;
    BaseSimpleLayer* confirmdialogLayer;

    
    //ゲージ
    MeterLayer* meterSp;
    
    
    CCLabelTTF* m_Label_enemy;
    
    
    
    
    //位置
    //----------------------------------------------

    
    CCPoint m_esatBtn_pt;
    CCPoint m_backtBtn_pt;

CCPoint m_esadialog_pt;
    
    CCPoint m_confirmdialog_pt;
    
    
    
    //関数
    //----------------------------------------------
    
    //画面位置をセット
    void setObjectPosition();
    
    //背景セット
    void setBackGround();
    //メニューアイテムをセット
    void setMenuItem();

    //変数初期化
    void initValue();
    
    void randomAnimStart();
    
    void startAgeruAnim();
    
    
    void updateScore();
    
    
    
    void startEvolutionAnim();
    void finishEvolutionAnim();
    
    
    
    //変数
    //----------------------------------------------
    bool canDestroy;
    
    int nowStageNum;
    int nowLevelUpLimit;
    int nowHasPoint;
    
    bool canTouch;
    
    int i_nowSec;
    
    int i_lastOkashiTime;
    
    int yMinus;
    
    CCPoint touchStartPoint;
    
    int nowSelectedOkasi;
        
    
    
    //使うもの
    //----------------------------------------------
    //画面サイズ
    CCSize m_winSize;
    CCSpriteFrameCache* m_frameCashe;
    //音関係
    GameUtil* m_utils;
    
    
public:
    
    virtual ~IdoAnaScene();
    
    static CCScene* scene();
    
    void onBtn_in_Setting(CCObject *pSender);

    
    
    virtual bool init();
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    virtual void onExitTransitionDidStart();

    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent * pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent);
    virtual void ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent);
    
    
    //ボタンタップ処理
    //----------------------------------------------
    void tapEsaButton(CCObject *pSender);
    
    void tapBack(CCObject *pSender);
    
    void tapAgeru(CCObject *pSender);
    
    
    void closeAddLayer(CCObject *pSender);
    
    
    void tapEsaCancel(CCObject *pSender);
    
    void tapEsaYes(CCObject *pSender);
    
    
    //ループ
    void mainLoop();
    void animLoop();
    void subLoop(float time);
    
    
    void onPause();
    void onResume();
    
    // implement the "static node()" method manually
    CREATE_FUNC(IdoAnaScene);
};

#endif /* defined(__nagure__IdoAnaScene__) */
