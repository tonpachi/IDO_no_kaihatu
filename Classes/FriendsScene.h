//
//  FriendsScene.h
//
//
//  Created by dotchi on 2014/06/02.
//
//

#ifndef __nagure__FriendsScene__
#define __nagure__FriendsScene__


#import "cocos2d.h"
#import "MyEasyMenuItem.h"
#import "GameUtil.h"

#import "FriendPagerLayer.h"

#import "TapEffectLayer.h"

USING_NS_CC;



//画像ファイル
#define PNG_ALBUM_CHARACTER_NONE        "zentai_quest.png"
#define PNG_ALBUM_PANEL_NONE        "word_none.png"






class FriendsScene :public CCLayer{
protected:
    
    //Sp
    //----------------------------------------------
    
    //背景
    CCSprite* m_backGroundSprite;
    
    
    //文言パネル
    CCSprite *m_panelSp;
    
    
    FriendPagerLayer* m_pager;
    
    MyEasyMenuItem *lnMenuItem;
    
    	    TapEffectLayer* tapEffect;
    
    //位置
    //----------------------------------------------
    
    
    CCPoint m_ToStartBtn_pt;
    //戻るボタン
    CCPoint m_p_BackButton;
    
    //人気アプリボタン
    CCPoint m_p_wallButton;
    
    CCPoint m_p_title;
    CCPoint m_p_name;
    
    
    
    CCPoint m_p_chara;
    CCPoint m_p_panel;
    
    CCPoint m_p_maru;
    
    CCPoint m_p_zukan;
    
    
    
    
    
    
    
    
    
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

    
    
    //変数
    //----------------------------------------------
    bool canDestroy;
    
    bool canTouch;
    
    int i_nowSec;
    
    int yMinus;
    
    CCPoint touchStartPoint;
    
    //現在表示中
    int m_fr_num;
    

    //使うもの
    //----------------------------------------------
    //画面サイズ
    CCSize m_winSize;
    CCSpriteFrameCache* m_frameCashe;
    //音関係
    GameUtil* m_utils;
    
    
public:
    
    virtual ~FriendsScene();
    
    static CCScene* scene();
    
    void onBtn_in_Setting(CCObject *pSender);
    
    
    
    virtual bool init();
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    

    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent * pEvent);
    /*
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent);
    virtual void ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent);
    */
    
    //ボタンタップ処理
    //----------------------------------------------
    void tapButton(CCObject *pSender);

    
    //ループ
    void mainLoop();
    void animLoop();
    void subLoop();
    
    
    void gameStart();
    
    // implement the "static node()" method manually
    CREATE_FUNC(FriendsScene);
};

#endif /* defined(__nagure__FriendsScene__) */
