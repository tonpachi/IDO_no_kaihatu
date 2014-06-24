//
//  KashiLayer.h
//  kyojin
//
//  Created by コトブキ タロウ on 2014/02/21.
//
//

#ifndef __kyojin__KashiLayer__
#define __kyojin__KashiLayer__


#import <vector>
#import "cocos2d.h"
#import "MyEasyMenuItem.h"
#import "Game.h"
#import "SaveUtil.h"
#import "KasiGetLayer.h"

#define NOTIFY_SP_PAGER_KASI "notification_KashiLayer"

USING_NS_CC;



class KashiLayer :public CCLayer{
    
protected:
    
    std::list<CCSprite*> kashiSpList;

    int i_kashiCnt;
    
    CCRect escapeRect;
    
    
    
        CCSize m_winSize;
    
    const char* userdefault_NUM;
    const char* userdefault_POS;
    const char* userdefault_KIND;
    const char* userdefault_DIRECT;
    

        void createKasiBySavedPosition();
    
    CCPoint touchStartPoint;
    
public:
    
    virtual bool init();
    
    KashiLayer();
    virtual ~KashiLayer();
    
        void closeAddLayer();
    
        void showGetOkashiDialog(int kind);
    
    void setMode(klaunchScene scene);
    
    
    void startLoop();
    void stopLoop();
    

    void createOkashi(int xx,int yy,int kind,int direct);
            void okashiCreateLoop();

    
    void saveKasiPosition();

    
    int touchOkashiSpFunc(CCPoint tpoint);
    
    void createOkashi(int xx,int yy,int kind);
    
    CREATE_FUNC(KashiLayer);

    

    
};
#endif /* defined(__kyojin__KashiLayer__) */
