//
//  TapEffectLayer.h
//  kyojin
//
//  Created by コトブキ タロウ on 2014/02/21.
//
//

#ifndef __kyojin__TapEffectLayer__
#define __kyojin__TapEffectLayer__


#import <vector>
#import "cocos2d.h"


USING_NS_CC;


class TapEffectLayer :public CCLayer{
    
protected:

    
    //画面サイズ
    CCSize m_winSize;
    
    //ゲージ
    CCSprite* meterAllSp;
    CCSprite* meterSp;
    
    CCSprite* createSpTapSign(CCPoint pt,CCObject *target,SEL_CallFuncN func);
    
public:
    
    virtual bool init();
    
    void show(CCPoint pt);
    
    void deleteSelf(CCNode* sender);
    
    TapEffectLayer();
    virtual ~TapEffectLayer();
    

    
    CREATE_FUNC(TapEffectLayer);

};
#endif /* defined(__kyojin__TapEffectLayer__) */
