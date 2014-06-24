#include "AppDelegate.h"
#include "SimpleAudioEngine.h"

#include "Game.h"
#include "GameUtil.h"
#include "SaveUtil.h"

#include "GameScene.h"

#include "AndroidUtil.h"
#import "EvolutionScene.h"
#import "HowToScene.h"

#import "NativeManager.h"
#import "TitleScene.h"


USING_NS_CC;

AppDelegate::AppDelegate() {
}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	
    // turn on display FPS
    pDirector->setDisplayStats(false);
    //pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    //ファイルフォルダ
    std::vector<std::string>folderPath1;
    std::vector<std::string>folderPath2;
    
    folderPath1.push_back("for_iOS");
    CCLOG("for_iOS");
    
    //スクリーンサイズ
    CCEGLView* view=pDirector->getOpenGLView();
    CCSize frame=view->getFrameSize();
    
    //画面サイズ判定
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)

    if (frame.width>480) {
        //retina
        pDirector->setContentScaleFactor(1.f);

        if (1136<=frame.height) {
            //4インチ
            folderPath2.push_back("HD");
            CCEGLView::sharedOpenGLView()->setDesignResolutionSize(640, 1136, kResolutionExactFit);
            CCLOG("1136 HD");
        } else {
            folderPath2.push_back("HD");
            CCEGLView::sharedOpenGLView()->setDesignResolutionSize(640, 960, kResolutionNoBorder);
            CCLOG("960 HD");
        }
    } else {
        pDirector->setContentScaleFactor(0.5f);
        folderPath2.push_back("SD");
        CCLOG("small SD");
        CCEGLView::sharedOpenGLView()->setDesignResolutionSize(320, 480, kResolutionNoBorder);
    }

#else
    //それ以外 android
    //スクリーンサイズ /kResolutionNoBorder
    //480/854 720/1280 0.562
    //480/800 0.600
    //800/1280 0.625
    //640/960 0.666
    
    int maxScreenSize=std::max(frame.width, frame.height);
    int minScreenSize=std::min(frame.width, frame.height);
	float sizePer = (float)minScreenSize / maxScreenSize;
    CCLOG("screen %d : %d   aspect=%f",minScreenSize,maxScreenSize,sizePer);
    
    pDirector->setContentScaleFactor(1);
    int _aVer=AndroidUtil::getAndroidAPIVer();
    if(0.61<sizePer){//短め 800/1280(note)
        if (720<=frame.width) {
            //解像度大きめ
            folderPath2.push_back("HD");
            CCEGLView::sharedOpenGLView()->setDesignResolutionSize(640, 960, kResolutionExactFit);
            CCLOG("HD 4:3");
        } else {
            if(11<=_aVer){
                //解像度小さめ多い　だがAPIverが大きい
                folderPath2.push_back("HD");
                CCEGLView::sharedOpenGLView()->setDesignResolutionSize(640, 960, kResolutionExactFit);
                CCLOG("HD 4:3");
            }else{
                //解像度小さめ多い　さらにheapを考慮し小さめの画像
                folderPath2.push_back("common");
                folderPath2.push_back("HD");
                CCLOG("SD?  4:3");
                CCEGLView::sharedOpenGLView()->setDesignResolutionSize(640, 960, kResolutionExactFit);
            }
        }
    }else{//長め
        if(0.6f==sizePer){
            //480:800とか
            folderPath2.push_back("HD");
            CCEGLView::sharedOpenGLView()->setDesignResolutionSize(640, 960, kResolutionExactFit);
            CCLOG("HD 4:3 480x800?");
            
        }else if(0.6f<sizePer){
            if(11<=_aVer){
                folderPath2.push_back("HD");
                CCEGLView::sharedOpenGLView()->setDesignResolutionSize(640, 1136, kResolutionExactFit);
                CCLOG("HD  16:9 high API");
                
            }else{
                //長めだがヒープが弱い端末が多いので小さめの画像を設定する　480x800でver2.3など
                folderPath2.push_back("HD");
                CCEGLView::sharedOpenGLView()->setDesignResolutionSize(640, 960, kResolutionExactFit);
                CCLOG("SD 4:3 because low APIver");
            }
            
        }else{
            folderPath2.push_back("HD");
            CCEGLView::sharedOpenGLView()->setDesignResolutionSize(640, 1136, kResolutionExactFit);
            CCLOG("HD  16:9");
        }
    }
    
    folderPath1.push_back("particle");
    folderPath1.push_back("sound");
    folderPath1.push_back("fonts");

    
#endif
    
    //デバッグ
    //ステージ
    //SaveUtil::saveInt(USERDEFAULT_STAGE, 6);
    //SaveUtil::saveBool(USERDEFAULT_ENDING_FLG,false);
    //SaveUtil::saveInt(USERDEFAULT_DRUGS_NUM, 50);
    
    //フォルダセット
    CCFileUtils::sharedFileUtils()->setSearchPaths(folderPath1);
    CCFileUtils::sharedFileUtils()->setSearchResolutionsOrder(folderPath2);
    
    //画像キャッシュ読み込み
    //loadImageCashe();
    
    //サウンド読み込み
    loadSound();
    
    SaveUtil::saveInt(USERDEFAULT_FROM_LAUCH,klaunchSceneAppDeligate);

    //完全初回起動時
    CCSpriteFrameCache* frameCashe=CCSpriteFrameCache::sharedSpriteFrameCache();
    frameCashe->addSpriteFramesWithFile("top.plist");
    frameCashe->addSpriteFramesWithFile("common.plist");
    frameCashe->addSpriteFramesWithFile("ido.plist");
    
    CCScene* pScene=TitleScene::scene();
    pDirector->runWithScene(pScene);
    
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    //起動後のインタースティシャル
    NativeManager::setRewordAd();
#endif

    return true;
}

// pause
void AppDelegate::applicationDidEnterBackground() {
    CCLOG("AppDelegate::application DidEnterBackground");
    
    //通知する
    CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_PAUSE,NULL);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#endif
    
    CCDirector::sharedDirector()->stopAnimation();
}

// resume
void AppDelegate::applicationWillEnterForeground() {
    CCLOG("AppDelegate::application WillEnterForeground");
    CCDirector::sharedDirector()->startAnimation();
    
    CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_RESUME);
}

#pragma mark custom

//画像キャッシュ読み込み
void AppDelegate::loadImageCashe(){
    CCLOG("AppDelegate::loadImageCashe");
    
    //スクリーンサイズ
    CCEGLView* view=CCDirector::sharedDirector()->getOpenGLView();
    CCSize frame=view->getFrameSize();

}

//サウンドファイル読み込み
void AppDelegate::loadSound(){
    CCLOG("AppDelegate::loadSound");


    //ゲームBGM
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(SOUND_FILE_GAME);

    
    //クリック
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(SOUND_FILE_BUTTON_TAP);
    //スロー
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(SOUND_FILE_THROW);
    
    //ごくごく
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(SOUND_FILE_GOKUGOKU);
    
    //ボリューム
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1.0f);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);
}

