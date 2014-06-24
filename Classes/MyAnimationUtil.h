//
//  ManAnimation.h
//  highandlowrun
//
//  Created by コトブキ タロウ on 2013/10/21.
//
//

#ifndef __MANANIMATION__
#define __MANANIMATION__

#import "cocos2d.h"


USING_NS_CC;

class MyAnimationUtil
{
public:
    static CCAnimation* setKomaAniByFileName2(const char* fileName1,const char* fileName2,float sec,int loop);
    
    static CCRepeatForever* setGiantAnim(CCSprite* sp);
    
    static void changeImage(CCSprite* itemImage,const char* imageFile);
    
    
    static CCRepeatForever* getFadeInOutAnim(float time);
    
    static CCAnimate* mirrorBallAnim();
    
    static CCAnimate* touyakuAnim();
    
    static CCRepeatForever* fuwafuwaAnim(float time,float toScale);
    
    
    static CCSprite* createSpNewSign(CCPoint pt);
    

};

#endif // __MANANIMATION__
