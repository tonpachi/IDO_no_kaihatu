//
//  EnemyLayer.h
//  kyojin
//
//  Created by コトブキ タロウ on 2014/02/21.
//
//

#ifndef __kyojin__EnemyLayer__
#define __kyojin__EnemyLayer__


#import <vector>
#import "cocos2d.h"
#import "MyEasyMenuItem.h"
#import "Game.h"
#import "SaveUtil.h"



USING_NS_CC;



class EnemyLayer :public CCLayer{
    
protected:

    
    std::list<CCSprite*> enemySpList;

    int i_enemyCnt;
    
    CCRect escapeRect;
    
    void createEnemydied(CCSprite* sp);
    
    void endDiedAnim(CCNode* sender);
    
        void onCatAnimFnished(CCNode* sender);
    
        CCPoint touchStartPoint;
    
        CCSize m_winSize;
    
    const char* userdefault_NUM;
    const char* userdefault_POS;
    const char* userdefault_KIND;
    const char* userdefault_DIRECT;
    
public:
    
    virtual bool init();
    
    EnemyLayer();
    virtual ~EnemyLayer();
    
    void setMode(klaunchScene scene);
    
    
    void startLoop();
    void stopLoop();
    
    void enemyCreateLoop();
    void createEnemy(int xx,int yy,int kind,int direct);
    
    int deleteSpriteFunc(CCPoint pt);
    
    void saveEnemyPosition();
    
    void createEnemyBySavedPosition();
    
    int getEnemyCount();
    
    
    CREATE_FUNC(EnemyLayer);

    

    
};
#endif /* defined(__kyojin__EnemyLayer__) */
