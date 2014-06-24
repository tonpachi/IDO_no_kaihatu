//
//  MySpritePager.h
//  kyojin
//
//  Created by コトブキ タロウ on 2014/02/21.
//
//

#ifndef __kyojin__MySpritePager__
#define __kyojin__MySpritePager__


#import <vector>
#import "cocos2d.h"
#import "MyEasyMenuItem.h"


#define NOTIFY_SP_PAGER "notification_myspritepager"

USING_NS_CC;


enum kpages{
    kpageroot=0,
    kpagebtn=1,
};

class MySpritePager :public CCLayer{
    
protected:
    
    CCRect m_inTouchRect;
    
    CCRect m_size_rect;
    
    std::vector<CCPoint> m_point_vec;
    
    CCPoint m_p_last;
    
    CCSprite* rootSp;

    CCSprite* maskSp;
    
    float m_content_w;
    
    CCClippingNode *m_clippingNode;
    
    int m_flick_w;
    
    CCPoint touchStartPoint;
    
    void onAnimatoinFinished();
    
    bool canTouch;
    
    float m_rootY;

    bool isContainRect;
    
    int lastPageNum;
    
    
    MyEasyMenuItem *leftBtn;
    MyEasyMenuItem *rightBtn;
    
    void onLeft(CCObject *pSender);
        void onRight(CCObject *pSender);
    
public:
    
    virtual bool init();
    
    MySpritePager();
    virtual ~MySpritePager();
    //virtual void onEnterTransitionDidFinish();
    //virtual void onExitTransitionDidStart();
    
    //タップイベント
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent* pEvent);
    
    CREATE_FUNC(MySpritePager);
    
    
    void myInitButton(const char* l_pngname,CCPoint l_position,const char* r_pngname,CCPoint r_position);
    
    
    void addSpByFilename(const char* pngname);
    //spriteを格納するarray
    CCArray* spArray;
    //コンテンツ数
    int contentsNum;
    //今表示してるやつ
    int nowContentNum;
    
    void prepere(int wsize,int hsize,CCPoint _position);
    
    int myGetContentNum();
    
    int myGetNowShowing();
    void mySetFlickWidth(int wid);
    
    void mySetShowPage(int n);
    void mySetLastPage(int n);
};
#endif /* defined(__kyojin__MySpritePager__) */
