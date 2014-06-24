//
//  SaveUtil.h
//  tenchi
//
//  Created by dotchi on 2013/11/21.
//
//

#ifndef __tenchi__SaveUtil__
#define __tenchi__SaveUtil__

#import <string>
#import "cocos2d.h"


// !!!:データ保存

//完全初回起動
#define USERDEFAULT_END_TUTO     "endtutorial"

#define USERDEFAULT_APP_STATUS       "appstatus"
#define USERDEFAULT_WALL_STATUS       "wallstatus"




//アプリ落としたときの時間(秒)
#define USERDEFAULT_APP_PAUSE_TIME    "apppausetime"


#define USERDEFAULT_IDO_PAUSE_TIME    "idopausetime"

#define USERDEFAULT_HAKA_PAUSE_TIME    "hakapausetime"

#define USERDEFAULT_IKE_PAUSE_TIME    "ikepausetime"



//最後におかし食った時間(秒)
#define USERDEFAULT_LAST_EAT_TIME    "latesteattime"




//現在のステージ
#define USERDEFAULT_STAGE           "stagenumber"

#define USERDEFAULT_NOW_HAS_POINT      "nowhaspoint"



//石数
#define USERDEFAULT_STONE_NUM       "isinokazu"


///!!!:おかしの所持数----------------------------------------------
#define USERDEFAULT_HAS_COOKIE      "okashi1"
#define USERDEFAULT_HAS_AME      "okashi2"
#define USERDEFAULT_HAS_PAN      "okashi3"
#define USERDEFAULT_HAS_CHOCO      "okashi4"
#define USERDEFAULT_HAS_SHOE      "okashi5"
#define USERDEFAULT_HAS_CAKE      "okashi6"
#define USERDEFAULT_HAS_PUDDING      "okashi7"




//
#define USERDEFAULT_SOUND_ON_OFF    "soundOnOff"

#define USERDEFAULT_VIBE_ON_OFF    "vibeOnOff"



//敵の場所を保存----------------------------------------------
//井戸シーン
//敵の座標
#define USERDEFAULT_STRING_POINT_ENEMY_IDO     "enemypointxyido"
//敵の種類保存
#define USERDEFAULT_STRING_KIND_ENEMY_IDO     "enemykindido"
//敵の向き保存
#define USERDEFAULT_STRING_DIREC_ENEMY_IDO     "enemydirectionido"

//墓シーン
//敵の座標
#define USERDEFAULT_STRING_POINT_ENEMY_HAKA     "enemypointxyhaka"
//敵の種類保存
#define USERDEFAULT_STRING_KIND_ENEMY_HAKA     "enemykindhaka"
//敵の向き保存
#define USERDEFAULT_STRING_DIREC_ENEMY_HAKA     "enemydirectionhaka"

//池シーン
//敵の座標
#define USERDEFAULT_STRING_POINT_ENEMY_IKE     "enemypointxyike"
//敵の種類保存
#define USERDEFAULT_STRING_KIND_ENEMY_IKE     "enemykindike"
//敵の向き保存
#define USERDEFAULT_STRING_DIREC_ENEMY_IKE     "enemydirectionike"


//井戸の敵　数
#define USERDEFAULT_ENEMY_NUM_IDO       "idonoteki"
//墓の敵　数
#define USERDEFAULT_ENEMY_NUM_HAKA       "hakanoteki"
//池の菓子　数
#define USERDEFAULT_ENEMY_NUM_IKE       "ikenokasi"




//菓子の場所と種類を保存----------------------------------------------
//井戸
#define USERDEFAULT_STRING_POINT_KASI_IDO     "kasiidopointxy"

#define USERDEFAULT_STRING_KIND_KASI_IDO     "kasiidokind"

//墓
#define USERDEFAULT_STRING_POINT_KASI_HAKA     "kasihakapointxy"

#define USERDEFAULT_STRING_KIND_KASI_HAKA     "kasihakakind"

//池
#define USERDEFAULT_STRING_POINT_KASI_IKE     "kasiikepointxy"

#define USERDEFAULT_STRING_KIND_KASI_IKE     "kasiikekind"


//井戸の菓子　数を保存----
#define USERDEFAULT_KASHI_NUM_IDO       "deteru_idonokasi"
//墓の菓子　数
#define USERDEFAULT_KASHI_NUM_HAKA       "deteru_hakanokasi"
//池の菓子　数
#define USERDEFAULT_KASHI_NUM_IKE       "deteru_ikenokasi"



//石の場所を保存----------------------------------------------
#define USERDEFAULT_STRING_POINT_STONE     "stonepointxy"
//石の種類保存
#define USERDEFAULT_STRING_KIND_STONE     "stonekind"

//石入れた数　normal
#define USERDEFAULT_STONE_COUNT_NORMAL     "stonecountnormal"
//石入れた数　gold
#define USERDEFAULT_STONE_COUNT_GOLD     "stonecountgold"


//どこからcreatesceneされたか
#define USERDEFAULT_FROM_LAUCH     "launchfrom"



//墓をきれいにした回数
#define USERDEFAULT_TOMB_CLEAN_UP     "hakawofuitakazu"

//墓に供物を置いた回数
#define USERDEFAULT_TOMB_PUT_ON     "hakanikumotuwooitakazu"



//墓の汚れ　数
#define USERDEFAULT_YOGORE_NUM     "hakanonoyogorenokazu"
//墓の汚れ　場所
#define USERDEFAULT_STRING_POINT_YOGORE     "yogorenoichi"
//墓の汚れ　種類
#define USERDEFAULT_STRING_KIND_YOGORE     "yogorenosyurui"







//ギミック----------------------------------------------


//池　初遷移
#define USERDEFAULT_STAGE_FIRST_IKE     "ikehajimete"
//墓　初遷移
#define USERDEFAULT_STAGE_FIRST_HAKA     "hakahajimete"



//友達----------------------------------------------
///!!!:友達　発見済みか
#define USERDEFAULT_FRIEND_1	"friend1"
#define USERDEFAULT_FRIEND_2	"friend2"
#define USERDEFAULT_FRIEND_3	"friend3"
#define USERDEFAULT_FRIEND_4	"friend4"
#define USERDEFAULT_FRIEND_5	"friend5"
#define USERDEFAULT_FRIEND_6	"friend6"
#define USERDEFAULT_FRIEND_7	"friend7"
#define USERDEFAULT_FRIEND_8	"friend8"
#define USERDEFAULT_FRIEND_9	"friend9"
#define USERDEFAULT_FRIEND_10	"friend10"

#define USERDEFAULT_NEWFRIEND	"newfriend"

///!!!:友達　発見カウント
#define USERDEFAULT_FRIEND_COUNT_1	"friend1count"
#define USERDEFAULT_FRIEND_COUNT_2	"friend2count"
#define USERDEFAULT_FRIEND_COUNT_3	"friend3count"
#define USERDEFAULT_FRIEND_COUNT_4	"friend4count"
#define USERDEFAULT_FRIEND_COUNT_5	"friend5count"
#define USERDEFAULT_FRIEND_COUNT_6	"friend6count"
#define USERDEFAULT_FRIEND_COUNT_7	"friend7count"
#define USERDEFAULT_FRIEND_COUNT_8	"friend8count"
#define USERDEFAULT_FRIEND_COUNT_9	"friend9count"
#define USERDEFAULT_FRIEND_COUNT_10	"friend10count"

///!!!:友達　tweet フラグ
#define USERDEFAULT_FRIEND_TWEET_1	"friend1tweet"
#define USERDEFAULT_FRIEND_TWEET_2	"friend2tweet"
#define USERDEFAULT_FRIEND_TWEET_3	"friend3tweet"
#define USERDEFAULT_FRIEND_TWEET_4	"friend4tweet"
#define USERDEFAULT_FRIEND_TWEET_5	"friend5tweet"
#define USERDEFAULT_FRIEND_TWEET_6	"friend6tweet"
#define USERDEFAULT_FRIEND_TWEET_7	"friend7tweet"
#define USERDEFAULT_FRIEND_TWEET_8	"friend8tweet"
#define USERDEFAULT_FRIEND_TWEET_9	"friend9tweet"
#define USERDEFAULT_FRIEND_TWEET_10	"friend10tweet"

#define USERDEFAULT_FRIEND_ZAWAZAWA	"tomodachinokehai"



///!!!:供物　発見済みか
#define USERDEFAULT_KUMOTU_FINDFLAG_1	"kumotufingflg1"
#define USERDEFAULT_KUMOTU_FINDFLAG_2	"kumotufingflg2"
#define USERDEFAULT_KUMOTU_FINDFLAG_3	"kumotufingflg3"
#define USERDEFAULT_KUMOTU_FINDFLAG_4	"kumotufingflg4"
#define USERDEFAULT_KUMOTU_FINDFLAG_5	"kumotufingflg5"
///!!!:供物　数
#define USERDEFAULT_KUMOTU_COUNT_1	"kumotucount1"
#define USERDEFAULT_KUMOTU_COUNT_2	"kumotucount2"
#define USERDEFAULT_KUMOTU_COUNT_3	"kumotucount3"
#define USERDEFAULT_KUMOTU_COUNT_4	"kumotucount4"
#define USERDEFAULT_KUMOTU_COUNT_5	"kumotucount5"


//----------------------------------------------





///!!!:SNS投稿済みか
#define POST_TW_STAGE_1   "twitter_post_stage_1"
#define POST_TW_STAGE_2   "twitter_post_stage_2"
#define POST_TW_STAGE_3   "twitter_post_stage_3"
#define POST_TW_STAGE_4   "twitter_post_stage_4"
#define POST_TW_STAGE_5   "twitter_post_stage_5"
#define POST_TW_STAGE_6   "twitter_post_stage_6"
#define POST_TW_STAGE_7   "twitter_post_stage_7"
#define POST_TW_STAGE_8   "twitter_post_stage_8"
#define POST_TW_STAGE_9   "twitter_post_stage_9"
#define POST_TW_STAGE_10   "twitter_post_stage_10"
#define POST_TW_STAGE_11   "twitter_post_stage_11"
#define POST_TW_STAGE_12   "twitter_post_stage_12"


#define POST_TW_FRIEND_1   "twitter_post_friend_1"
#define POST_TW_FRIEND_2   "twitter_post_friend_2"
#define POST_TW_FRIEND_3   "twitter_post_friend_3"
#define POST_TW_FRIEND_4   "twitter_post_friend_4"
#define POST_TW_FRIEND_5   "twitter_post_friend_5"
#define POST_TW_FRIEND_6   "twitter_post_friend_6"
#define POST_TW_FRIEND_7   "twitter_post_friend_7"
#define POST_TW_FRIEND_8   "twitter_post_friend_8"
#define POST_TW_FRIEND_9   "twitter_post_friend_9"
#define POST_TW_FRIEND_10   "twitter_post_friend_10"
#define POST_TW_FRIEND_11   "twitter_post_friend_11"


///!!!:ギミック　20　発見済みか
#define GIMMICK_CHECK_1   "gimmick_checked_1"
#define GIMMICK_CHECK_2   "gimmick_checked_2"
#define GIMMICK_CHECK_3   "gimmick_checked_3"
#define GIMMICK_CHECK_4   "gimmick_checked_4"
#define GIMMICK_CHECK_5   "gimmick_checked_5"
#define GIMMICK_CHECK_6   "gimmick_checked_6"
#define GIMMICK_CHECK_7   "gimmick_checked_7"
#define GIMMICK_CHECK_8   "gimmick_checked_8"
#define GIMMICK_CHECK_9   "gimmick_checked_9"
#define GIMMICK_CHECK_10   "gimmick_checked_10"
#define GIMMICK_CHECK_11   "gimmick_checked_11"
#define GIMMICK_CHECK_12   "gimmick_checked_12"
#define GIMMICK_CHECK_13   "gimmick_checked_13"
#define GIMMICK_CHECK_14   "gimmick_checked_14"
#define GIMMICK_CHECK_15   "gimmick_checked_15"
#define GIMMICK_CHECK_16   "gimmick_checked_16"
#define GIMMICK_CHECK_17   "gimmick_checked_17"
#define GIMMICK_CHECK_18   "gimmick_checked_18"
#define GIMMICK_CHECK_19   "gimmick_checked_19"
#define GIMMICK_CHECK_20   "gimmick_checked_20"


//最後にtweetした時間　秒
#define LATEST_TWEET_TIME   "saigonitweetsita"

#define BOOST_START_FLAG   "hastostartboost"

#define BOOST_START_TIME    "boostsitajikan"


//レビュー投稿済みか
#define POST_REVIEW   "reviewposted"



enum klaunchScene{
    klaunchSceneNone=0,
    klaunchSceneAppDeligate=1,
    klaunchSceneAlbumAScene=2,
    klaunchSceneIdo=3,
    klaunchSceneIke=4,
    klaunchSceneHaka=5,
    klaunchSceneSetting=6,
};

//SNS　何ボタン押したか　POST後呼ばれる関数内で使う
#define USERDEFAULT_WHAT_KIND_SNS_BUTTON     "whatkindofsnstap"




//結果画面フラグ
#define USERDEFAULT_RESULT_FLG      "resultFlg"

#define INT_PAUSE_FLG_ON            1
#define INT_PAUSE_FLG_OFF           0


class SaveUtil{
public:
    
    //util
    static int getStageNum();
    
    static int getPauseTime();
    
    static void setPauseTime(int ivalue);
    
    
    
    //保存int
    static void saveInt(const char* keyname,int ivalue);
    //保存bool
    static void saveBool(const char* keyname,bool bvalue);
    //保存string
    static void saveString(const char* keyname,const char* svalue);
    
    
    //取得int
    static int getSaveInt(const char* keyname,int defvalue);
    static int getSaveInt(const char* keyname);
    
    //取得bool
    static bool getSaveBool(const char* keyname);
    static bool getSaveBool(const char* keyname,bool bdefvalue);
    
    //取得string
    static const char* getSaveString(const char* keyname);
    static const char* getSaveString(const char* keyname,const char* sdefvalue);
    
    //インクリメントしてセーブ
    static void incrimentSave(const char* keyname);
    
    //デクリメントしてセーブ
    static void decrimentSave(const char* keyname);
};
#endif /* defined(__tenchi__SaveUtil__) */
