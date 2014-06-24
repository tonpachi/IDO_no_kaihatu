//
//  EnemySprite.cpp
//  kyojin
//
//  Created by コトブキ タロウ on 2014/01/24.
//
//

#import "EnemySprite.h"
#import "Box2D/Box2D.h"

USING_NS_CC;


enum {
	kTagParentNode = 1,
};

EnemySprite::EnemySprite() {
    isChange=false;
    isEnding=false;
}


// this method will only get called if the sprite is batched.
// return YES if the physics values (angles, position ) changed
// If you return NO, then nodeToParentTransform won't be called.
bool EnemySprite::isDirty(void) {
	return true;
}



void EnemySprite::setKind(int n){
    m_kind=n;
}
bool EnemySprite::getKind(){
    return m_kind;
}
void EnemySprite::setDirection(bool n){
    m_direction=n;
}
bool EnemySprite::getDirection(){
    return m_direction;
}

EnemySprite* EnemySprite::createSp(){
    EnemySprite *pSprite = new EnemySprite();
    if (pSprite && pSprite->init())
    {
        // Set to autorelease
        pSprite->autorelease();
        
        return pSprite;
    }
    CC_SAFE_DELETE(pSprite);
    return NULL;
}
