//
//  MeterLayer.h
//  kyojin
//
//  Created by コトブキ タロウ on 2014/02/21.
//
//

#ifndef __kyojin__MeterLayer__
#define __kyojin__MeterLayer__


#import <vector>
#import "cocos2d.h"


USING_NS_CC;


class MeterLayer :public CCLayer{
    
protected:

    
    //画面サイズ
    CCSize m_winSize;
    
    //ゲージ
    CCSprite* meterAllSp;
    CCSprite* meterSp;
    
    
public:
    
    virtual bool init();
    
    void show(CCPoint pt);
    
    void upDateMeter(float scale);
    
    void startGetAnim();
    
    
    MeterLayer();
    virtual ~MeterLayer();
    

    
    CREATE_FUNC(MeterLayer);

};
#endif /* defined(__kyojin__MeterLayer__) */
