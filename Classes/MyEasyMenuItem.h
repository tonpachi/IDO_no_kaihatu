//
//  MyEasyMenuItem.h
//  kyojin
//
//  Created by コトブキ タロウ on 2014/02/28.
//  音鳴らしたり勝手にしてくれる
//

#ifndef __kyojin__MyEasyMenuItem__
#define __kyojin__MyEasyMenuItem__

#import "cocos2d.h"


USING_NS_CC;

class MyEasyMenuItem : public CCMenuItemImage
{
public:
    
    MyEasyMenuItem();
    virtual ~MyEasyMenuItem();
    
    bool isOn;
    
    bool isGA;
    
    bool prepar(const char* pngName,CCPoint pnt,CCObject *target,SEL_MenuHandler selector);
    
	static MyEasyMenuItem *create(const char* pngName, CCPoint pnt,CCObject *target,SEL_MenuHandler selector);
    
    static MyEasyMenuItem *createAnc00(const char* pngName, CCPoint pnt,CCObject *target,SEL_MenuHandler selector);
    
    // このボタンをタップした時の処理
    void onTapThis(CCObject* sender);
    
    void setButtonGA(const char* scenename,const char* buttonname);
    
private:
    // 元のセレクタ
    cocos2d::CCObject* m_orgTarget;
    cocos2d::SEL_MenuHandler m_orgSelector;
    
    const char* GAscenename;
    const char* GAbuttonname;
};


#endif /* defined(__kyojin__MyEasyMenuItem__) */
