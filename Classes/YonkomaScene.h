//
//  YonkomaScene.h
//
//
//  Created by dotchi on 2014/06/02.
//
//

#ifndef __nagure__YonkomaScene__
#define __nagure__YonkomaScene__


#import "cocos2d.h"
#import "MyEasyMenuItem.h"
#import "GameUtil.h"
#import <iostream>
#import <list>

#import <vector>

#import "EnemySprite.h"

#import "My4ListSpritePager.h"


#import <list>

#include "cocos-ext.h"
using namespace extension;
using namespace std;

USING_NS_CC;

#define ADD_LAYER_4KOMA 999


// CCTableViewDataSource、CCTableViewDelegateを継承
class YonkomaScene :public CCLayer
{
protected:
    
    // !!!:Sp
    //----------------------------------------------
    
    //背景
    CCSprite* m_backGroundSprite;
    
    //

    My4ListSpritePager* m_pager;
    
    CCSprite* m_tableViewBg;
    CCMenu* m_tbCloseMenu;
    
    
    CCLabelTTF* m_Label_enemy;
    CCLabelTTF* m_Label_okashi;
    
    
    // !!!:位置
    //----------------------------------------------
    
    CCPoint m_wall_pt;
    CCPoint m_back_pt;
    
    CCPoint m_pt_tableView;
    
    CCPoint m_pt_arrowBtn_L;
    
    CCPoint m_pt_arrowBtn_R;
    
    
        CCPoint touchStartPoint;
    
    CCSize m_scrollViewSize;
    
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
    
    void show4komaDialog(int stageNum);
    
    
    void closeAddLayer();
    
    void showscroll();
    //テーブルビュー閉じる
    void closeScroll();
    
    
    CCArray* getPanelFilename(int stage);
    
    
    
    void readPlistNameByStage(int stage);

    
    // !!!:変数
    //----------------------------------------------
    bool canDestroy;
    
    
    bool canTouch;
    
    //解放されてるステージ
    int m_max_stage;
    
    int yMinus;
    

    list<CCSprite*> cellSpList;
    
    
    //使うもの
    //----------------------------------------------
    //画面サイズ
    CCSize m_winSize;
    CCSpriteFrameCache* m_frameCashe;
    //音関係
    GameUtil* m_utils;
    
    
public:
    
    virtual ~YonkomaScene();
    
    static CCScene* scene();
    
    
    
    
    virtual bool init();
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent * pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    //virtual void ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent);
    //virtual void ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent);
    
    
    
    
    // !!!:ボタンタップ処理
    //----------------------------------------------
    void tapBack(CCObject *pSender);
    
    void tapOsusume(CCObject *pSender);
    
    void tapTwinList(CCObject *pSender);
    
    void tapCell(CCObject *pSender);
    
    
    
    //ループ

    void onPause();
    void onResume();
    
    // implement the "static node()" method manually
    CREATE_FUNC(YonkomaScene);
};



#endif /* defined(__nagure__YonkomaScene__) */
