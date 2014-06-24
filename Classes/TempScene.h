//
//  TempScene.h
//
//
//  Created by dotchi on 2014/06/02.
//
//

#ifndef __nagure__TempScene__
#define __nagure__TempScene__


#import "cocos2d.h"
#import "MyEasyMenuItem.h"
#import "GameUtil.h"

USING_NS_CC;

//画像ファイル


class TempScene :public CCLayer{
protected:
    
    //Sp
    //----------------------------------------------

    //背景
    CCSprite* m_backGroundSprite;
    
    //パネル
    MyEasyMenuItem* m_ToStartBtn;
    

    
    
    //位置
    //----------------------------------------------

    
    CCPoint m_ToStartBtn_pt;
    


    
    
    
    
    
    
    
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
    

    
    
    
    //変数
    //----------------------------------------------
    bool canDestroy;
    
    int i_nowStageNum;
    
    bool canTouch;
    
    int i_nowSec;
    
    int yMinus;
    
    CCPoint touchStartPoint;
    
    
    
    
    
    
    
    
    //使うもの
    //----------------------------------------------
    //画面サイズ
    CCSize m_winSize;
    CCSpriteFrameCache* m_frameCashe;
    //音関係
    GameUtil* m_utils;
    
    
public:
    
    virtual ~TempScene();
    
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
    void tapButton(CCObject *pSender);
    
    
    
    
    
    
    //ループ
    void mainLoop();
    void animLoop();
    void subLoop();
    
    
    void onPause();
    void onResume();
    
    // implement the "static node()" method manually
    CREATE_FUNC(TempScene);
};

#endif /* defined(__nagure__TempScene__) */
