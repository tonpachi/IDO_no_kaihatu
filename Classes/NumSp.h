//
//  NumSp.h
//  tenchi
//
//  Created by コトブキ タロウ on 2013/12/10.
//
//

#ifndef __tenchi__NumSp__
#define __tenchi__NumSp__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class NumSp{
public:
    
    static CCSprite* getNumberBmpSp(int num);
    static CCSprite* getNumberBmpSp2Result(int num);
    static const char* getPngName(int n);
};

#endif /* defined(__tenchi__NumSp__) */
