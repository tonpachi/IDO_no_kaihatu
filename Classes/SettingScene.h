//
//  SettingScene.h
//
//
//  Created by dotchi on 2014/06/02.
//
//

#ifndef __nagure__SettingScene__
#define __nagure__SettingScene__


#import "cocos2d.h"
#import "MyEasyMenuItem.h"
#import "GameUtil.h"

USING_NS_CC;

//画像ファイル


class SettingScene :public CCLayer{
protected:
    
    //Sp
    //----------------------------------------------
    
    //背景
    CCSprite* m_backGroundSprite;
    
    //
    MyEasyMenuItem* m_WallBtn;
    
    
    MyEasyMenuItem* m_revBtn;
    
    //位置
    //----------------------------------------------
    
    CCPoint m_pt_back;
    
    CCPoint m_pt_4koma;
    
    CCPoint m_pt_rev;
    
    CCPoint m_pt_friends;
    
    CCPoint m_pt_gimic;
    
    CCPoint m_pt_howto;
    
    CCPoint m_pt_sound;
    
    CCPoint m_pt_vibe;
    
    CCPoint m_pt_lobi;
    
    CCPoint m_pt_tw;
    
    CCPoint m_pt_wall;
    
    
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
    
    void tweetDone();
    
    
    
    //変数
    //----------------------------------------------
    bool canDestroy;

    
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
    
    virtual ~SettingScene();
    
    static CCScene* scene();
    
    
    
    
    virtual bool init();
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    
    
    //ボタンタップ処理
    //----------------------------------------------
    void onBack(CCObject *pSender);
    void on4koma(CCObject *pSender);
    void onFriends(CCObject *pSender);
    void onGimic(CCObject *pSender);
    void onHowTo(CCObject *pSender);
    void onSound(CCObject *pSender);
    void onVibe(CCObject *pSender);
    void onLobi(CCObject *pSender);
    void onTw(CCObject *pSender);

    void onWall(CCObject *pSender);
    void onRev(CCObject *pSender);

    
    // implement the "static node()" method manually
    CREATE_FUNC(SettingScene);
};

#endif /* defined(__nagure__SettingScene__) */
