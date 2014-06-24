//
//  KasiGetLayer.h
//  kyojin
//
//  Created by コトブキ タロウ on 2014/02/21.
//
//

#ifndef __kyojin__KasiGetLayer__
#define __kyojin__KasiGetLayer__


#import <vector>
#import "cocos2d.h"


USING_NS_CC;


class KasiGetLayer :public CCLayer{
    
protected:

    
    //画面サイズ
    CCSize m_winSize;
    

    
public:
    
    virtual bool init();
    
    void show(int kind,CCObject *target,SEL_MenuHandler selector);
    
    KasiGetLayer();
    virtual ~KasiGetLayer();
    
        void onClose(CCObject *pSender);
    
    
    
    
    //タップイベント
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
    CREATE_FUNC(KasiGetLayer);

};
#endif /* defined(__kyojin__KasiGetLayer__) */
