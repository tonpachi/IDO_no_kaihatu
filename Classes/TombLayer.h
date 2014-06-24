//
//  TombLayer.h
//  kyojin
//
//  Created by コトブキ タロウ on 2014/02/21.
//
//

#ifndef __kyojin__TombLayer__
#define __kyojin__TombLayer__


#import <vector>
#import "cocos2d.h"
#import "MyEasyMenuItem.h"
#import "Game.h"
#import "SaveUtil.h"



USING_NS_CC;



class TombLayer :public CCLayer{
    
protected:

    
    std::list<CCSprite*> enemySpList;

    int i_enemyCnt;
    
    int totalyogoreCnt;
    
    CCRect escapeRect;
    
    void createEnemydied(CCSprite* sp);
    
    void endDiedAnim(CCNode* sender);
    
    CCSize m_winSize;
    
    const char* userdefault_NUM;
    const char* userdefault_POS;
    const char* userdefault_KIND;
    
    int hakaX;
    int hakaY;
    int hakaW;
    int hakaH;
    
public:
    
    virtual bool init();
    
    TombLayer();
    virtual ~TombLayer();
    
    void prepare();
    
    
    void startLoop();
    void stopLoop();
    
    void enemyCreateLoop();
    void createEnemy(int xx,int yy,int kind);
    
    int deleteSpriteFunc(CCPoint pt);
    
    void saveEnemyPosition();
    
    void createEnemyBySavedPosition();
    
    int getEnemyCount();
    
    void zawazawa();
    
    CREATE_FUNC(TombLayer);

    

    
};
#endif /* defined(__kyojin__TombLayer__) */
