//
//  EnemySprite.h
//  kyojin
//
//  Created by コトブキ タロウ on 2014/01/24.
//
//

#ifndef __kyojin__EnemySprite__
#define __kyojin__EnemySprite__

#define PTM_RATIO 32

#import "cocos2d.h"


USING_NS_CC;

class EnemySprite : public CCSprite
{
public:
	EnemySprite();

	virtual bool isDirty(void);
    
    void setKind(int n);
    bool getKind();
    
    void setDirection(bool n);
    bool getDirection();
    
    static EnemySprite* createSp();
    
private:

    int m_kind;
    bool m_direction;
    
    bool isChange;
    bool isEnding;

};

#endif /* defined(__kyojin__EnemySprite__) */
