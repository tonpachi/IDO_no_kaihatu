//
//  BaseSimpleLayer.cpp
//  kyojin
//
//  Created by コトブキ タロウ on 2014/02/21.
//
//

#import "BaseSimpleLayer.h"

#import "cocos2d.h"


USING_NS_CC;

BaseSimpleLayer::BaseSimpleLayer(){
    
}

BaseSimpleLayer::~BaseSimpleLayer(){

}

//初期化
bool BaseSimpleLayer::init(){
    if (CCLayer::init()) {
        // タッチ有効化
        setTouchEnabled(true);
        setTouchMode(kCCTouchesOneByOne);
        
        return true;
    } else {
        return false;
    }
}

void BaseSimpleLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
}

bool BaseSimpleLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
	return true;
}

void BaseSimpleLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
 }
void BaseSimpleLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent* pEvent){
}
