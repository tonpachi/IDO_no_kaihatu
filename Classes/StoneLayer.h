//
//  StoneLayer.h
//  kyojin
//
//  Created by コトブキ タロウ on 2014/02/21.
//
//

#ifndef __kyojin__StoneLayer__
#define __kyojin__StoneLayer__


#import <vector>
#import "cocos2d.h"
#import "MyEasyMenuItem.h"
#import "Game.h"
#import "SaveUtil.h"



USING_NS_CC;



class StoneLayer :public CCLayer{
    
protected:
    
    CCRect escapeRect;
    
    void createEnemydied(CCSprite* sp);
    
    void endDiedAnim(CCNode* sender);
    
    CCPoint touchStartPoint;

    
    CCSize m_winSize;
    
    const char* userdefault_NUM;
    const char* userdefault_POS;
    const char* userdefault_KIND;
    const char* userdefault_DIRECT;
    
    
    std::list<CCSprite*> enemySpList;
    int i_STONECnt;
    
    int stoneCnt_normal;
    int stoneCnt_gold;
    
    CCLabelTTF* m_Label_enemy;

    
public:
    
    virtual bool init();
    
    StoneLayer();
    virtual ~StoneLayer();
    
    void prepare();
    
    
    void startLoop();
    void stopLoop();
    
    void enemyCreateLoop();
    void createEnemy(int xx,int yy,int kind,int direct);
    
    void deleteSpriteFunc(CCPoint pt);
    
    void saveEnemyPosition();
    
    void createEnemyBySavedPosition();
    
    int getEnemyCount();
    
    void zawazawa();
    
    
    
    CREATE_FUNC(StoneLayer);

    

    
};
#endif /* defined(__kyojin__StoneLayer__) */
