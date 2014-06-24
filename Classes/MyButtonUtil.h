//
//  MyButtonUtil.h
//  highandlowrun
//
//  Created by コトブキ タロウ on 2013/10/24.
//
//  押しても音出したりしない

#ifndef __highandlowrun__MyButtonUtil__
#define __highandlowrun__MyButtonUtil__

#import "MyToggleMenuItem.h"

#import "cocos2d.h"

USING_NS_CC;

class MyButtonUtil
{
public:
    
    static CCMenuItemImage* makeCCMenuItemImage(const char* pngName,CCPoint pnt,CCLayer *target,SEL_MenuHandler selector);
    
    static CCMenuItemLabel* makeCCMenuItemLabel(const char* buttontext,CCPoint pnt,CCLayer *target,SEL_MenuHandler selector);
};

#endif /* defined(__highandlowrun__MyButtonUtil__) */
