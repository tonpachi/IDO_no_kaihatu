//
//  MySoundONOFFMenuItem.h
//  kyojin
//
//  Created by コトブキ タロウ on 2014/02/28.
//
//

#ifndef __kyojin__MySoundONOFFMenuItem__
#define __kyojin__MySoundONOFFMenuItem__

#import "cocos2d.h"


USING_NS_CC;

class MySoundONOFFMenuItem : public CCMenuItemToggle
{
public:
    
    MySoundONOFFMenuItem();
    virtual ~MySoundONOFFMenuItem();
    
    bool isOn;
    
    CCMenuItemToggle* prepar(const char* pngName1,const char* pngName2,CCPoint pnt,CCObject *target,SEL_MenuHandler selector);
    
	static MySoundONOFFMenuItem* create(const char* pngName1,const char* pngName2, CCPoint pnt,CCObject *target,SEL_MenuHandler selector);
    // このボタンをタップした時の処理
    void onTapThis(CCObject* sender);
    
private:
    
    // 元のセレクタ
    cocos2d::CCObject* m_orgTarget;
    cocos2d::SEL_MenuHandler m_orgSelector;
};


#endif /* defined(__kyojin__MySoundONOFFMenuItem__) */
