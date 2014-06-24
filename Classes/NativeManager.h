//
//  NativeManager.h
//  balanceTiger
//
//  Created by dotchi on 2013/10/14.
//
//

#ifndef balanceTiger_AdSetting_h
#define balanceTiger_AdSetting_h


#define POST_WORD_STAGE_1 "スマホの歴史上、最狂の育成ゲーム...iPhone/Androidアプリ #人間をポコしてパン [Android] https://play.google.com/store/apps/details?id=jp.co.dotchi.kyojinikusei [iOS]"
#define POST_WORD_STAGE_2 "中毒者続出の最狂変態アプリ...iPhone/Androidアプリ #人間をポコしてパン [Android] https://play.google.com/store/apps/details?id=jp.co.dotchi.kyojinikusei [iOS]"
#define POST_WORD_STAGE_3 "狂い咲き育成ゲーム...iPhone/Androidアプリ #人間をポコしてパン [Android] https://play.google.com/store/apps/details?id=jp.co.dotchi.kyojinikusei [iOS]"
#define POST_WORD_STAGE_4 "君はもうこの変態アプリを体験したか...iPhone/Androidアプリ #人間をポコしてパン [Android] https://play.google.com/store/apps/details?id=jp.co.dotchi.kyojinikusei [iOS]"
#define POST_WORD_STAGE_5 "育成ゲームの向こう側...iPhone/Androidアプリ #人間をポコしてパン [Android] https://play.google.com/store/apps/details?id=jp.co.dotchi.kyojinikusei [iOS]"
#define POST_WORD_STAGE_6 "最狂でも電池の減りは普通の育成ゲーム...iPhone/Androidアプリ #人間をポコしてパン [Android] https://play.google.com/store/apps/details?id=jp.co.dotchi.kyojinikusei [iOS]"
#define POST_WORD_STAGE_7 "もはや常人には理解不能！最狂育成ゲーム...iPhone/Androidアプリ #人間をポコしてパン [Android] https://play.google.com/store/apps/details?id=jp.co.dotchi.kyojinikusei [iOS]"
#define POST_WORD_STAGE_8 "ダウンロードを後悔！最狂の育成ゲーム...iPhone/Androidアプリ #人間をポコしてパン [Android] https://play.google.com/store/apps/details?id=jp.co.dotchi.kyojinikusei [iOS]"
#define POST_WORD_STAGE_9 "早く誰かに言いたい！最狂の育成ゲーム...iPhone/Androidアプリ #人間をポコしてパン [Android] https://play.google.com/store/apps/details?id=jp.co.dotchi.kyojinikusei [iOS]"
#define POST_WORD_STAGE_10 "遊んだ人も共犯！最狂の育成ゲーム...iPhone/Androidアプリ #人間をポコしてパン [Android] https://play.google.com/store/apps/details?id=jp.co.dotchi.kyojinikusei [iOS]"
#define POST_WORD_STAGE_11 "時間の無駄！最狂の育成ゲーム...iPhone/Androidアプリ #人間をポコしてパン [Android] https://play.google.com/store/apps/details?id=jp.co.dotchi.kyojinikusei [ios]"



//ネイティブ機能呼び出し用クラス
//実装部はネイティブ毎に用意する
//iOSはNativeManager.mm
class NativeManager {
public:
    
    //top画面のad設定
    static void setTopAd();
    
    //howTo画面のad設定
    static void setHowToAd();
    
    //おすすめ画面のad設定
    static void setRewordAd();
    
    //渋三あっぷす画面のad設定
    static void setInfoAd();
    
    //キャラ選択画面のad設定
    static void setCharacterAd();
    
    //ゲーム画面のad設定
    static void setGameAd();
    
    
    //結果画面のad設定
    static void setAfterEvolutionAd();
    
    //adをクローズ
    static void closeAd();
    static void openAd();
    
    //人気アプリ　アルバム
    static void callHotApp();
    //おすすめ　設定
    static void callFreeApp();
    //ひとやすみ　ゲーム
    static void callLink();
    
    
    
    //渋三あっぷすwebビュー
    static void showWebView();
    //アイコンビュー閉じる
    static void closeIconView();
    //ストア
    static void callStore();
    
    
    
    //twitter投稿
    //4こま
    static void sendTweet4(int stage);
    //ともだち
    static void sendTweetFriend(int stage);
    //設定から
    static void sendTweetFromSetting();
    
    
    //facebook投稿
    static void sendFacebook(int stage);
    
    //LINE投稿
    static void sendLINE(int stage);
    
    
    //もしもーしのダイアログ消した
    static void resumeMosiMosi();
    
    
    //スコア送信
    static void sendScore(long score);
    //累積スコア送信
    static void sendTotalScore(long totalScore);
    
    //leaderboard表示
    static void showLeaderboard();
    
    //レビュー依頼
    static void requestReview();
    
    static void set960Icon();
    
    static void removeAllData();

    
    //Google Analytics
    static void sendName2GA(const char* scenename);
    static void sendClickEvent2GA(const char* scenename,const char* buttonName);
    
    static void startVibe();
};

#endif
