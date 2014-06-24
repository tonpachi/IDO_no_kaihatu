//
//  Game.h
//  nagure
//
//  Created by dotchi on 2013/10/03.
//
//

#ifndef nagure_Game_h
#define nagure_Game_h



#define ISDEBUGING true



#pragma mark リソース関連

//フォント名
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)


#define FONT_NAME_TREBUCHET         "Trebuchet MS"
#define FONT_NAME_TREBUCHET_BOLD    "TrebuchetMS-Bold"

#define FNT_TESTFONT                "testfont.fnt"

#define FONT_NAME_Marker                "Felt"


#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)


#define FONT_NAME_TREBUCHET         "Trebuchet-Ms.ttf"
#define FONT_NAME_TREBUCHET_BOLD    "TrebuchetMS-Bold"

#define FNT_TESTFONT                "testfont.fnt"

#define FONT_NAME_Marker                "Marker Felt.ttf"


#endif





//結果画面フラグ
#define USERDEFAULT_RESULT_FLG      "resultFlg"

//通知
#define NOTIFICATION_GAME_START     "gameStart"

#define NOTIFICATION_PAUSE          "pauseGame"
#define NOTIFICATION_RESUME         "resumeGame"

#define NOTIFICATION_TWEET_DONE     "tweetdone"


#pragma mark しきい値　など------------------------------
#if (ISDEBUGING == true)

    #define INT_EVOLUTION_2     500
    #define INT_EVOLUTION_3     500
    #define INT_EVOLUTION_4     500
    #define INT_EVOLUTION_5     500
    #define INT_EVOLUTION_6     500 //
    #define INT_EVOLUTION_7     500 //
    #define INT_EVOLUTION_8     500 //
    #define INT_EVOLUTION_9     500 //
    #define INT_EVOLUTION_10    500 //


#else


    #define INT_EVOLUTION_2     10
    #define INT_EVOLUTION_3     10
    #define INT_EVOLUTION_4     10
    #define INT_EVOLUTION_5     10
    #define INT_EVOLUTION_6     10 //
    #define INT_EVOLUTION_7     10 //
    #define INT_EVOLUTION_8     10 //
    #define INT_EVOLUTION_9     10 //
    #define INT_EVOLUTION_10    10 //



#endif


#pragma mark ------時間的なものの定義

//空腹になる　秒
#define TIME_HUNGRY 300
//えさ食える回数
#define EAT_COUNT_MAX 3


//菓子時間　秒
#define TIME_KASI_MAKE_SEC 60

//菓子MAX
#define KASI_MAKE_MAX 3




//敵make時間　秒
#define TIME_ENEMY_MAKE_SEC 10
//敵make時間　秒 ブースト時
#define TIME_ENEMY_MAKE_SEC_BOOST 3

//敵MAX
#define ENEMY_MAKE_MAX 20

//石　時間　秒
#define TIME_STONE_MAKE_SEC 3
//敵MAX
#define STONE_MAKE_MAX 20



//ブースト時間
#define TIME_BOOST 300

//ブースト間隔
#define TIME_BOOST_WAIT 10800



//墓が汚れる時間 10分
#define TIME_TOMB_DIRTY 60








//---------エサポイント関係
#define PT_ENEMY 1

#define PT_COOKIE 10

#define PT_AME 20

#define PT_CAKE 30

#define PT_CHOCO 100

#define PT_SPECIAL_SWEEETS 250

#pragma mark ------------------------------


// !!!:ゲーム画面レイヤー重ね順 kGameLayer
enum kGameLayer{
    kGameLayerBackground_3=-3,
    kGameLayerBackground_2=-2,
    kGameLayerBackground_1=-1,
    kGameLayerBackground0=0,
    kGameLayerOnBg1=5,
    kGameLayerOnBg2=6,
    kGameLayerOnBg3=7,
    kGameLayerOnBg4=8,
    kGameLayerOnBg5=9,
    kGameLayerMenu=10,
    kGameLayerDialog=15,
    kGameLayerEffectSmall=16,
    kGameLayerEffect=17,
    kGameLayerDebugText=20,
};

//シーン移動時間
#define FLOAT_SCENE_MOVE_TIME           0.5f
#define PI 3.14159265258979


//サウンドID初期値
#define UNSIGNED_INT_SOUND_ID_INIT  99999


#pragma mark Google Analytics------------------------------------
//Google Analytics
//シーン名
#define SCENE_NAME_GAME1  "Game Scene stage 1"
#define SCENE_NAME_GAME2  "Game Scene stage 2"
#define SCENE_NAME_GAME3  "Game Scene stage 3"
#define SCENE_NAME_GAME4  "Game Scene stage 4"
#define SCENE_NAME_GAME5  "Game Scene stage 5"
#define SCENE_NAME_GAME6  "Game Scene stage 6"
#define SCENE_NAME_GAME7  "Game Scene stage 7"
#define SCENE_NAME_GAME8  "Game Scene stage 8"
#define SCENE_NAME_GAME9  "Game Scene stage 9"
#define SCENE_NAME_GAME10  "Game Scene stage 10"
#define SCENE_NAME_GAME11  "Game Scene stage 11"

#define SCENE_NAME_ZUKAN_KYOJIN  "Kyojin Zukan Scene"
#define SCENE_NAME_ZUKAN_ESA  "Esa Zukan Scene"
#define SCENE_NAME_SETTING  "Setting Scene"
#define SCENE_NAME_EVO  "Evolution Scene"
#define SCENE_NAME_ENDING  "Ending Scene"
#define SCENE_NAME_HOWTO  "HowTo Scene"

//ボタン
#define GA_BUTTON_2HOME_ZUKAN  "to Game Button in Zukan Scene"
#define GA_BUTTON_2HOME_SETTING  "to Game Button in Setting Scene"
#define GA_BUTTON_2HOME_ESAZUKAN  "to Game Button in ESAZukan Secen"
#define GA_BUTTON_2HOME_EVO  "to Game Button in Evolition Scene"

#define GA_BUTTON_BOOST  "booster Button"
#define GA_BUTTON_BOOST_YES  "booster Button YES"
#define GA_BUTTON_BOOST_NO  "booster Button NO"

#define GA_BUTTON_WALL_GAME  "to Wall Button in Game Scene"
#define GA_BUTTON_WALL_ZUKAN  "to Wall Button in Zukan Scene"
#define GA_BUTTON_WALL_ESAZUKAN  "to Wall Button in EsaZukan Scene"
#define GA_BUTTON_WALL_SETTING  "to Wall Button in Setting Scene"


#define GA_BUTTON_ZUKAN  "to Zukan Button in Game Button"
#define GA_BUTTON_KYOJINZUKAN  "to KyojinZukan Button in EsaZukan Button"
#define GA_BUTTON_ESAZUKAN  "to EsaZukan Button in KyojinZukan Button"

#define GA_BUTTON_SETTING  "to Setting Button"

#define GA_BUTTON_HOWTO  "to HowTo Button"

#define GA_BUTTON_REVIEW  "to Review Button"

#define GA_BUTTON_SOUND_TURN_OFF  "sound turn off Button"
#define GA_BUTTON_SOUND_TURN_ON  "sound turn on Button"


#define GA_BUTTON_FB_EVO  "facebook Button in Evolution Scene"
#define GA_BUTTON_TW_EVO  "twitter Button in Evolution Scene"
#define GA_BUTTON_LN_EVO  "LINE Button in Evolution Scene"

#define GA_BUTTON_FB  "facebook Button in Zukan Scene"
#define GA_BUTTON_TW  "twitter Button in Zukan Scene"
#define GA_BUTTON_LN  "LINE Button in Zukan Scene"


#pragma mark Google Analytics------------------------------------







#pragma mark ゲームシステム

#define ADD_LAYER_TAG 999

#define GIMMICK_MAX_NUM 20



#pragma mark Defineまとめ------------------------------------

#define kModalLayerPriority_a kCCMenuHandlerPriority-1
#define kModalLayerPriority_a_menu kCCMenuHandlerPriority-2
#define kModalLayerPriority_b kCCMenuHandlerPriority-3
#define kModalLayerPriority_b_menu kCCMenuHandlerPriority-4
#define kModalLayerPriority_c kCCMenuHandlerPriority-5
#define kModalLayerPriority_c_menu kCCMenuHandlerPriority-6



#define My_setNotify(classmethod,tuuchi) CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(classmethod), tuuchi, NULL);

#define My_unSetNotify(tuuchi)     CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, tuuchi);


#define posWinCenter  ccp(m_winSize.width*0.5, m_winSize.height*0.5)

#define posCenter( obj )  obj->setAnchorPoint(CCPointMake(0.5f, 0.5f));obj->setPosition(posWinCenter);


#define anc00( obj ) obj->setAnchorPoint(CCPointMake(0.f, 0.f));
#define anc55( obj ) obj->setAnchorPoint(CCPointMake(0.5f, 0.5f));

#define pos00( obj ) obj->setAnchorPoint(CCPointMake(0.f, 0.f));obj->setPosition(CCPointMake(0.f, 0.f));

#define posTop( obj ) obj->setAnchorPoint(CCPointMake(0,1));obj->setPosition(CCPointMake(0,m_winSize.height));


#define changeSceneFade( obj )  	CCTransitionFade *transition=CCTransitionFade::create(FLOAT_SCENE_MOVE_TIME, obj);CCDirector::sharedDirector()->replaceScene(transition);



#endif
