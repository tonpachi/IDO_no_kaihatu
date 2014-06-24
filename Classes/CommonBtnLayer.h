//
//  CommonBtnLayer.h
//  kyojin
//
//  Created by コトブキ タロウ on 2014/02/21.
//
//

#ifndef __kyojin__CommonBtnLayer__
#define __kyojin__CommonBtnLayer__


#import <vector>
#import "cocos2d.h"
#import "MyEasyMenuItem.h"
#import "Game.h"
#import "SaveUtil.h"
#import "KasiGetLayer.h"


USING_NS_CC;



class CommonBtnLayer :public CCLayer{
    
protected:
    
    CCSize m_winSize;
    
    
    CCPoint m_pt_wall;
    CCPoint m_pt_okashi;
    CCPoint m_pt_kumotsu;
    CCPoint m_pt_friends;
    CCPoint m_pt_setting;
    
public:
    
    virtual bool init();
    
    CommonBtnLayer();
    virtual ~CommonBtnLayer();
    
    void prepare(CCObject *target,SEL_MenuHandler Okasoselector,SEL_MenuHandler Kumotuselector,SEL_MenuHandler Friendselector,SEL_MenuHandler Settingselector,SEL_MenuHandler wallselector);
    
    
    void setNewSignFriend();
    
    
    CREATE_FUNC(CommonBtnLayer);

    

    
};
#endif /* defined(__kyojin__CommonBtnLayer__) */
