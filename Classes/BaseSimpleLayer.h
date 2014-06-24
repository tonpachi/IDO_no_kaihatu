//
//  BaseSimpleLayer.h
//  kyojin
//
//  Created by コトブキ タロウ on 2014/02/21.
//
//

#ifndef __kyojin__BaseSimpleLayer__
#define __kyojin__BaseSimpleLayer__


#import <vector>
#import "cocos2d.h"


USING_NS_CC;


class BaseSimpleLayer :public CCLayer{
    
protected:

    
public:
    
    virtual bool init();
    
    BaseSimpleLayer();
    virtual ~BaseSimpleLayer();
    
    //タップイベント
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent* pEvent);
    
    CREATE_FUNC(BaseSimpleLayer);

};
#endif /* defined(__kyojin__BaseSimpleLayer__) */
