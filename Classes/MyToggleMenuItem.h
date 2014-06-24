//
//  MyToggleMenuItem.h
//  kyojin
//
//  Created by コトブキ タロウ on 2014/02/28.
//
//

#ifndef __kyojin__MyToggleMenuItem__
#define __kyojin__MyToggleMenuItem__

#import "cocos2d.h"


USING_NS_CC;

class MyToggleMenuItem : public CCMenuItemImage
{
public:
    
    MyToggleMenuItem();
    virtual ~MyToggleMenuItem();
    
    bool isOn;
    
    bool prepar(const char* pngName,CCPoint pnt,CCObject *target,SEL_MenuHandler selector);
    
	static MyToggleMenuItem *create(const char* pngName, CCPoint pnt,CCObject *target,SEL_MenuHandler selector);
    // このボタンをタップした時の処理
    void onTapThis(CCObject* sender);
    
private:
    // 元のセレクタ
    cocos2d::CCObject* m_orgTarget;
    cocos2d::SEL_MenuHandler m_orgSelector;
};


#endif /* defined(__kyojin__MyToggleMenuItem__) */
