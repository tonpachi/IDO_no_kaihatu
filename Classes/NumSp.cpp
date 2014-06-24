//
//  NumSp.cpp
//  tenchi
//
//  Created by コトブキ タロウ on 2013/12/10.
//
//
#include <string>
#include "NumSp.h"
#include "cocos2d.h"
#include <sstream>

USING_NS_CC;
using namespace std;

CCSprite* NumSp::getNumberBmpSp(int num){
    CCSprite* basesp=CCSprite::create();
    stringstream ss;
    ss<<num;
    //stringに変換できた
    string str(ss.str());
    
    int calNum=num;
    int cnt=str.length();
    CCSprite *Sp = CCSprite::createWithSpriteFrameName(getPngName(-1));
    Sp->setAnchorPoint(ccp(1, 0.5));
    Sp->setPosition(ccp(0, 0));//pngの幅
    basesp->addChild(Sp);
    for (int i=0; i<cnt; i++) {
        //int n=(int)(str.substr(i,i+1));
        int n=calNum%10;
        calNum=calNum/10;
        CCSprite *Sp = CCSprite::createWithSpriteFrameName(getPngName(n));
        Sp->setAnchorPoint(ccp(1, 0.5));
        Sp->setPosition(ccp(-35*(i+1)-20, 0));//pngの幅
        basesp->addChild(Sp);
    }
    return basesp;
}

CCSprite* NumSp::getNumberBmpSp2Result(int num){
    CCSprite* basesp=CCSprite::create();
    stringstream ss;
    ss<<num;
    //stringに変換できた
    string str(ss.str());
    int calNum=num;
    int cnt=str.length();
    for (int i=0; i<cnt; i++) {
        //int n=(int)(str.substr(i,i+1));
        int n=calNum%10;
        calNum=calNum/10;
        CCSprite *Sp = CCSprite::createWithSpriteFrameName(getPngName(n));
        Sp->setAnchorPoint(ccp(1, 0.5));
        Sp->setPosition(ccp(-35*i, 0));//pngの幅
        basesp->addChild(Sp);
    }
    return basesp;
}


const char* NumSp::getPngName(int n){
    switch (n) {
        case 0:
            return "n0.png";
            break;
        case 1:
            return "n1.png";
            break;
        case 2:
            return "n2.png";
            break;
        case 3:
            return "n3.png";
            break;
        case 4:
            return "n4.png";
            break;
        case 5:
            return "n5.png";
            break;
        case 6:
            return "n6.png";
            break;
        case 7:
            return "n7.png";
            break;
        case 8:
            return "n8.png";
            break;
        case 9:
            return "n9.png";
            break;
        default:
            return "ri.png";
            break;
    }
}