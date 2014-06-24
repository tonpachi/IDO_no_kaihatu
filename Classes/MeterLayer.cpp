//
//  MeterLayer.cpp
//  kyojin
//
//  Created by コトブキ タロウ on 2014/02/21.
//
//

#import "MeterLayer.h"
#import "Game.h"
#import "GameUtil.h"

#import "SaveUtil.h"


#import "MyEasyMenuItem.h"

#import "cocos2d.h"


USING_NS_CC;

MeterLayer::MeterLayer(){
    
}

MeterLayer::~MeterLayer(){

}

//初期化
bool MeterLayer::init(){
    if (CCLayer::init()) {
        
        m_winSize = CCDirector::sharedDirector()->getWinSize();
        
        int yMinus;
        //サイズ別にセット
        if (m_winSize.height==1136) {
            //4インチ
            yMinus=0;
            
        } else {
            yMinus=44;
        }
        //メーター位置
        CCPoint m_p_meter = ccp(0, 902-yMinus);
        show(m_p_meter);

        
        return true;
    } else {
        return false;
    }
}
void MeterLayer::show(CCPoint pt){
    //メーター親
    meterAllSp= CCSprite::create();
    meterAllSp->setAnchorPoint(ccp(0, 0));
    meterAllSp->setPosition(pt);
    
    //メーター
    meterSp = CCSprite::createWithSpriteFrameName("meter.png");
    meterSp->setAnchorPoint(ccp(0, 0));
    meterSp->setPosition(ccp(20,0));
    meterAllSp->addChild(meterSp);
    
    //メーターwaku
    CCSprite *gaugebgSp = CCSprite::createWithSpriteFrameName("waku.png");
    gaugebgSp->setAnchorPoint(ccp(0, 0));
	gaugebgSp->setPosition(ccp(0,0));
	meterAllSp->addChild(gaugebgSp);
    
    
    
    //メーター全部入りをadd
    this->addChild(meterAllSp,kGameLayerMenu);
}

void MeterLayer::upDateMeter(float scale){
    meterSp->setScaleX(scale);
}

void MeterLayer::startGetAnim(){
    
}