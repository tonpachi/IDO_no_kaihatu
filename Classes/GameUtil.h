//
//
//

#ifndef __Res__
#define __Res__

#import <iostream>

#import "cocos2d.h"

#import "Game.h"

#define GetSecond()                     ( gettimeofday_sec() )



#define SOUND_FILE_GAME "bgm.mp3"

#define SOUND_FILE_BUTTON_TAP "button_tap.mp3"

#define SOUND_FILE_THROW "poyo.mp3"

#define SOUND_FILE_GOKUGOKU "gokun.mp3"

#define SOUND_FILE_HOERU "roar.mp3"

#define SOUND_FILE_PYORO "pyoro.mp3"

#define SOUND_FILE_BOMB "bomb.mp3"

#define SOUND_FILE_EVO "evo.mp3"






USING_NS_CC;

//SNS名
enum kSNS{
    k_facebook=1,
    k_twitter=2,
    k_line=3,
};

inline double gettimeofday_sec()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    //現在時間long型みたいなのでミリ秒まで返ってくる
    return tv.tv_sec + tv.tv_usec * 1e-6;
}

class GameUtil : public cocos2d::CCLayer{
public:
    virtual bool init();
    virtual ~GameUtil();


    //サウンドフラグ
    bool m_soundFlg;
    //CC_SYNTHESIZE(bool, m_soundFlg, SoundFlg);

    
    //引数のサウンドをならす
    unsigned int startSoundEffect(const char* soundFile);
    //引数のサウンドを止める
    void stopSoundEffect(unsigned int soundId);
    //引数のBGMをならす
    void startBGM(const char* soundFile,bool loop);
    //BGMを止める
    void stopBGM();
    
    void pauseALLSound();
    
    void pauseBGM();
    void resumeBGM();

    void stopALLSound();

    void resumeALLSound();
    
    void setSoundFlg(bool flg);
    bool getSounFlg();
    
    unsigned int startButtonTapEffect();
    
    static void changeSpImage(cocos2d::CCSprite* itemImage,const char* imageFile);
    
    
    static CCSprite* makeBlackBg(int w,int h);
    
    static CCSprite* makeColorSp(int w,int h);
    
    static unsigned int tapButtonEffect(bool isSound);
    
    
    static bool getAppStatus();
    
    //SNS POSTしてるかを返す
    static bool getBoolSNSPosted_Stage(int stagenum);
    //SNS POSTしたのを保存
    static void setBoolSNSPosted_Stage(int stagenum);
    
    //SNS POSTしてるかを返す
    static bool getBoolSNSPosted_Friend(int stagenum);
    //SNS POSTしたのを保存
    static void setBoolSNSPosted_Friend(int stagenum);
    
    
    
    //ギミック　発見したのを保存
    static void setBoolGimmickFlag(int num);
    //ギミック　発見したかを返す
    static bool getBoolGimmickFlag(int num);
    
    
    //友達　発見したのを保存
    static void setBoolFriendFlag(int num);
    //友達　発見したかを返す
    static bool getBoolFriendFlag(int num);
    //友達　発見した回数
    static int getFriendFindCount(int kind);
    //友達　tweetしたか
    static bool isFriendTweeted(int n);
    
    static void incrementFriendFindCount(int kind);
    
    
    //plist から　画像ファイル名　を返す
    static const char* getPngNameFromPlist(const char* filename,int num);
    
    
    
    
    static const char* getSNSPostWord(int stagenum);
    
    
    //数字からエサ所持数を返す
    static int getHasOkashiNum(int kind);

    
    static unsigned int SimpleStartEffect(const char* soundFile);
    //引数のサウンドを止める
    static void SimpleStopEffect(unsigned int soundId);
    
    
    static void readPlist(int stageNum);
    static void delPlist(int stageNum);
    
    static CCLabelTTF* getTextSp(const char* moji);
    
    //投稿する画像ファイル名
    static const char* getSNSPostFriendImageName(int num);
    
    //投稿する画像ファイル名
    static const char* getSNSPost4komaImageName(int num);
    
    //投稿する画像ファイル名
    static const char* getSNSPostImageNameFromSetting(int num);
    
    
    //CCArrayからcharに変換
    static const char* changeChar(CCObject* obj);
    
    static int getStageMaxLevel(int nowStageNum);
    
    
    CREATE_FUNC(GameUtil);
};


#endif /*  */
