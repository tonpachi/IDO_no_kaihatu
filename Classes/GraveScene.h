//
//  GraveScene.h
//
//
//  Created by dotchi on 2014/06/02.
//
//

#ifndef __nagure__GraveScene__
#define __nagure__GraveScene__


#import "cocos2d.h"
#import "MyEasyMenuItem.h"
#import "GameUtil.h"
#import <iostream>
#import <list>
#import <string>
#import <vector>

#import "MeterLayer.h"
#import "TapEffectLayer.h"

#import "EnemyLayer.h"
#import "KashiLayer.h"

#import "TombLayer.h"

#import "CommonBtnLayer.h"

USING_NS_CC;



class GraveScene :public CCLayer
{
protected:
    
    // !!!:Sp
    //----------------------------------------------
    
    //背景
    CCSprite* m_backGroundSprite;
    
    KashiLayer* m_kasiLayer;
    
    TombLayer* m_yogoreLayer;
    
    
    //ゲージ
    MeterLayer* meterSp;
    
        TapEffectLayer* tapEffect;
        EnemyLayer* m_enemyLayer;
    
    //パネル
    CommonBtnLayer* m_btnLayer;
    

    CCSprite* m_tableViewBg;
    CCMenu* m_tbCloseMenu;
    
    
    
    
    CCLabelTTF* m_Label_enemy;
    CCLabelTTF* m_Label_okashi;
    
    // !!!:位置
    //----------------------------------------------
    
    CCPoint m_ToStartBtn_pt;
    
    CCPoint m_pt_tableView;
    
    CCPoint m_pt_arrowBtn_L;
    
    CCPoint m_pt_arrowBtn_R;
    
    //メーター位置
    CCPoint m_p_meter;
    
    CCPoint m_pt_wall;
    CCPoint m_pt_okashi;
    CCPoint m_pt_kumotsu;
    CCPoint m_pt_friends;
    CCPoint m_pt_setting;
    
    // !!!:関数
    //----------------------------------------------
    
    //画面位置をセット
    void setObjectPosition();
    
    //背景セット
    void setBackGround();
    //メニューアイテムをセット
    void setMenuItem();
    
    //変数初期化
    void initValue();
    
    void updateScore(int n);
    
    
    void touchOkashiSpFunc(CCPoint tpoint);
    
    void intLevelState();
    
    
    
    
    void startEvolutionAnim();
    void finishEvolutionAnim();
    
    
    // !!!:変数
    //----------------------------------------------
    bool canDestroy;
    
    int nowStageNum;
    int nowLevelUpLimit;
    int nowHasPoint;
    
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
    
    virtual ~GraveScene();
    
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

    
    
    
    
    // !!!:ボタンタップ処理
    //----------------------------------------------
    void tapButton(CCObject *pSender);
    void tapWallButton(CCObject *pSender);
    void tapItems(CCObject *pSender);
    void tapSetting(CCObject *pSender);
    void tapFriends(CCObject *pSender);
    void onEsaClick(CCObject *pSender);
    
    //テーブルビュー閉じる
    void onTableClose(CCObject *pSender);

    
    void onArrowLClick(CCObject *pSender);
    void onArrowRClick(CCObject *pSender);
    
    
    
    
    
    
    
    
    //ループ
    void mainLoop();
    void enemyCreateLoop();
    void subLoop();
    void okashiCreateLoop();
    
    
    void onPause();
    void onResume();
    
    // implement the "static node()" method manually
    CREATE_FUNC(GraveScene);
};

#endif /* defined(__nagure__GraveScene__) */
