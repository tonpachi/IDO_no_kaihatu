//
//  MyAnimationUtil.cpp
//  highandlowrun
//
//  Created by コトブキ タロウ on 2013/10/21.
//
//

#import "MyAnimationUtil.h"
#import <cstdarg>


USING_NS_CC;



CCAnimation *MyAnimationUtil::setKomaAniByFileName2(const char *fileName1, const char *fileName2, float sec, int loop) {
	//テクスチャアトラス使う前提
	CCSpriteFrameCache *_cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    
	CCArray *animFrameArr = CCArray::createWithCapacity(2);
	CCSpriteFrame *frame0 = _cache->spriteFrameByName(fileName1);
	CCSpriteFrame *frame1 = _cache->spriteFrameByName(fileName2);
	animFrameArr->addObject(frame0);
	animFrameArr->addObject(frame1);
	CCAnimation *animFrames = CCAnimation::createWithSpriteFrames(animFrameArr, sec);
	animFrames->setLoops(loop);
	return animFrames;
}



//引数の画像ファイルに変更する
#pragma mark 画像変更
void MyAnimationUtil::changeImage(CCSprite* itemImage,const char* imageFile){
    CCSpriteFrame* imageSpriteFrame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(imageFile);
    CCLOG("imageFile = %s",imageFile);
    itemImage->setTexture(imageSpriteFrame->getTexture());
    itemImage->setTextureRect(imageSpriteFrame->getRect());
    itemImage->setDisplayFrame(imageSpriteFrame);
}



CCRepeatForever* MyAnimationUtil::setGiantAnim(CCSprite* sp){
    //Y軸移動アニメ
	CCMoveTo *cMove1 = CCMoveTo::create(5, ccp(sp->getPositionX(),sp->getPositionY()+200));
    CCMoveTo *cMove2 = CCMoveTo::create(5, ccp(sp->getPositionX(),sp->getPositionY()));
    CCSequence *squence = CCSequence::create(cMove1, cMove2, NULL);
    CCRepeatForever *action = CCRepeatForever::create(squence);
    return action;
}


CCRepeatForever* MyAnimationUtil::getFadeInOutAnim(float time){
    
    CCFiniteTimeAction *_alpha1 = CCFadeTo::create(time, 128);
    CCFiniteTimeAction *_alpha2 = CCFadeTo::create(time, 255);
    CCFiniteTimeAction *_alpha3 = CCFadeTo::create(time, 128);
    CCFiniteTimeAction *_alpha4 = CCFadeTo::create(time, 255);
    
    CCSequence *_squences = CCSequence::create(_alpha1,_alpha2,_alpha3,_alpha4, NULL);
    
    return CCRepeatForever::create(_squences);
}


CCRepeatForever* MyAnimationUtil::fuwafuwaAnim(float time,float toScale){
CCFiniteTimeAction *_scale1 = CCScaleTo::create(time, toScale);
CCFiniteTimeAction *_scale2 = CCScaleTo::create(time, 1.0f);
CCSequence *_squences = CCSequence::create(_scale1,_scale2, NULL);
return CCRepeatForever::create(_squences);
}


CCAnimate* MyAnimationUtil::mirrorBallAnim(){
    return CCAnimate::create(MyAnimationUtil::setKomaAniByFileName2("mirabo-ru1.png", "mirabo-ru2.png", 0.2, -1));
}

CCAnimate* MyAnimationUtil::touyakuAnim(){
    return CCAnimate::create(MyAnimationUtil::setKomaAniByFileName2("kusuri_me-ta-1.png", "kusuri_me-ta-2.png", 0.5, -1));
}



CCSprite* MyAnimationUtil::createSpNewSign(CCPoint pt){
    //newと出す　アイモバイル用
    CCSprite *onew = CCSprite::createWithSpriteFrameName("sign_new.png");
    onew->setAnchorPoint(ccp(0.5, 0.5));
    onew->setPosition(pt);
    CCFiniteTimeAction *_scale1 = CCScaleTo::create(1.0f, 1.5f);
    CCFiniteTimeAction *_scale2 = CCScaleTo::create(1.0f, 1.0f);
    CCSequence *_squences = CCSequence::create(_scale1,_scale2, NULL);
    onew->runAction(CCRepeatForever::create(_squences));
    return onew;
}





