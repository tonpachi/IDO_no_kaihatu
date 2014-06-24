//
//  EvolutionScene.h
//
//
//  Created by dotchi on 2014/06/02.
//
//

#ifndef __nagure__EvolutionScene__
#define __nagure__EvolutionScene__


#import "cocos2d.h"
#import "MyEasyMenuItem.h"
#import "GameUtil.h"

USING_NS_CC;

//画像ファイル


class EvolutionScene :public CCLayer{
protected:
    
    //Sp
    //----------------------------------------------
    
    //背景
    CCSprite* m_backGroundSprite;
    
    //パネル
    MyEasyMenuItem* m_ToStartBtn;
    
    
    
    CCMenu *_menuS;
    
    
    
    
    
    //位置
    //----------------------------------------------
    
    
    CCPoint m_ToStartBtn_pt;
    
    //戻るボタン
    CCPoint m_p_BackButton;

    CCPoint m_p_name;
    
    
    //Twitterボタン
    CCPoint m_p_Tw;
    
    
    
    
    
    
    
    
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
    
    void onPause();
    
    
    void show4komaDialog(int stageNum);
    
    CCArray* get4KomaPlistNameAndPng(int stage);
    
    
    //変数
    //----------------------------------------------
    bool canDestroy;
    
    int nowStageNum;
    
    bool canTouch;
    
    int i_nowSec;
    
    int yMinus;
    
    CCPoint touchStartPoint;
    
    const char* usePlistName;
    
    
    
    
    
    
    //使うもの
    //----------------------------------------------
    //画面サイズ
    CCSize m_winSize;
    CCSpriteFrameCache* m_frameCashe;
    //音関係
    GameUtil* m_utils;
    
    
public:
    
    virtual ~EvolutionScene();
    
    static CCScene* scene();
    

    
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
    void tapButton(CCObject *pSender);
    
    //TWボタンタップ
    void tapTw(CCObject *pSender);
    
    
    
    
    //ループ
    void mainLoop();
    void animLoop();
    void subLoop();
    
    
    void gameStart();
    
    // implement the "static node()" method manually
    CREATE_FUNC(EvolutionScene);
};

#endif /* defined(__nagure__EvolutionScene__) */
