//
//  HowToScene.h
//  nagure
//
//  Created by dotchi on 2013/09/26.
//
//

#ifndef __nagure__HowToScene__
#define __nagure__HowToScene__

#import <iostream>

#import "cocos2d.h"
#import "MySpritePager.h"
#import "MyPagerCounter.h"



class HowToScene :public cocos2d::CCLayer{
protected:
    
    
    //表示パネル番号
    int m_panelNo;

    MySpritePager* _pager;

    MyEasyMenuItem* backButton;
    
    //位置
    ///////////////////////////////////////////////
    //画面サイズ
    cocos2d::CCSize m_winSize;
    
    //HowToパネル
    cocos2d::CCPoint m_pointHowToSprite;
    
    
    //戻るボタン
    cocos2d::CCPoint m_p_BackButton;
    
    ///////////////////////////////////////////////
    
    //画面位置をセット
    void setObjectPosition();
    
    //背景セット
    void setBackGround();
    //メニューアイテムをセット
    void setMenuItem();
    
    //戻るボタンタップ
    void tapBackButton();

    //viewpagerの移動アニメ終わったとき呼ばれる
    void endSlideAnim();
    
    bool canDestroy;
    
public:
    static cocos2d::CCScene* scene();
    
    virtual ~HowToScene();
    
    virtual bool init();
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    
    // implement the "static node()" method manually
    CREATE_FUNC(HowToScene);
};

#endif /* defined(__nagure__HowToScene__) */
