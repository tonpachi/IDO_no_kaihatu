//
//  MyPagerCounter.h
//  kyojin
//
//  Created by コトブキ タロウ on 2014/02/27.
//
//

#ifndef __kyojin__MyPagerCounter__
#define __kyojin__MyPagerCounter__

#import <vector>
#import "cocos2d.h"


USING_NS_CC;

class MyPagerCounter :public CCLayer{
    
protected:
    
    CCSprite* rootSp;

    int contentW;
    void onAnimatoinFinished();
    
    const char* normalPngName;
    const char* focusPngName;
public:
    
    virtual bool init();
    
    MyPagerCounter();
    virtual ~MyPagerCounter();
    //virtual void onEnterTransitionDidFinish();
    //virtual void onExitTransitionDidStart();
    
    //タップイベント
//    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
//    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
//    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
//    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent* pEvent);
    
    CREATE_FUNC(MyPagerCounter);

    //コンテンツ数
    int contentsNum;
    //今表示してるやつ
    int nowContentNum;
    
    void prepere(const char* normalPngname,const char* focusPngname,int num,CCPoint position,int _margin);
    
    void MyUpdateVisible(int num);
};



#endif /* defined(__kyojin__MyPagerCounter__) */
