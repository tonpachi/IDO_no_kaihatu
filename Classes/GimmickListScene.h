//
//  GimmickListScene.h
//
//
//  Created by dotchi on 2014/06/02.
//
//

#ifndef __nagure__GimmickListScene__
#define __nagure__GimmickListScene__


#import "cocos2d.h"
#import "MyEasyMenuItem.h"
#import "GameUtil.h"
#import <iostream>
#import <list>

#import <vector>

#import "EnemySprite.h"





#include "cocos-ext.h"
using namespace extension;


USING_NS_CC;


#define LISTCELL_MONGON 9
#define LISTCELL_CHECK 8
#define LISTCELL_NOM 7



// CCTableViewDataSource、CCTableViewDelegateを継承
class GimmickListScene :public CCLayer,public cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate
{
protected:
    
    // !!!:Sp
    //----------------------------------------------
    
    //背景
    CCSprite* m_backGroundSprite;
    
    //

    CCTableView* m_tableView;
    CCSprite* m_tableViewBg;
    
    
    
    CCLabelTTF* m_Label_enemy;
    CCLabelTTF* m_Label_okashi;
    
    // !!!:位置
    //----------------------------------------------
    
    CCPoint m_ToStartBtn_pt;
    
    CCPoint m_pt_tableView;
    
    CCPoint m_pt_arrowBtn_L;
    
    CCPoint m_pt_arrowBtn_R;
    
    
    CCPoint touchStartPoint;
    
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
    
    void showscroll();
    
    
    
    // !!!:変数
    //----------------------------------------------
    bool canDestroy;
    
    
    bool canTouch;
    
    //解放されてるステージ
    int m_max_stage;
    
    int yMinus;
    

    CCArray* mPngNameArr;
    
    
    //使うもの
    //----------------------------------------------
    //画面サイズ
    CCSize m_winSize;
    CCSpriteFrameCache* m_frameCashe;
    //音関係
    GameUtil* m_utils;
    
    
public:
    
    virtual ~GimmickListScene();
    
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
    
    
    /***** テーブル用に以下を追加 *****/
    // CCTableViewDelegateがCCScrollViewDelegateを継承している事情で必要
    virtual void scrollViewDidScroll(CCScrollView* view){}
    virtual void scrollViewDidZoom(CCScrollView* view){}
    // セルのサイズを設定
    virtual CCSize cellSizeForTable(CCTableView *table);
    // セルの内容を設定
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    // セルの数を設定
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    // セルを選択したときの処理
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
    
    
    
    
    // !!!:ボタンタップ処理
    //----------------------------------------------
    void tapBack(CCObject *pSender);
    
    void tapOsusume(CCObject *pSender);
    

    
    //ループ


    
    
    void onPause();
    void onResume();
    
    // implement the "static node()" method manually
    CREATE_FUNC(GimmickListScene);
};




#define PNG_4KOMA_1_1        "koma_1_1.png"
#define PNG_4KOMA_1_2        "koma_1_2.png"
#define PNG_4KOMA_1_3        "koma_1_3.png"
#define PNG_4KOMA_1_4        "koma_1_4.png"




#endif /* defined(__nagure__GimmickListScene__) */
