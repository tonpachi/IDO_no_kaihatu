//
//  HorrorEffectLayer.h
//  kyojin
//
//  Created by コトブキ タロウ on 2014/02/21.
//
//

#ifndef __kyojin__HorrorEffectLayer__
#define __kyojin__HorrorEffectLayer__


#import <vector>
#import "cocos2d.h"


USING_NS_CC;


class HorrorEffectLayer :public CCLayer{
    
protected:
    
    int m_mode;
    //画面サイズ
    CCSize m_winSize;
    
    //ゲージ
    CCSprite* allSp;
    
public:
    
    virtual bool init();
    
    void setMode(int mode);
    
    void show();
    
    void stopAnim();

    
    void deleteSelf(CCNode* sender);
    
    HorrorEffectLayer();
    virtual ~HorrorEffectLayer();

    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    
    CREATE_FUNC(HorrorEffectLayer);

};
#endif /* defined(__kyojin__HorrorEffectLayer__) */
