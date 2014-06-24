//
//  GameUtil.cpp
//

#import "GameUtil.h"

#import "AndroidUtil.h"

#import "SimpleAudioEngine.h"
#import "SaveUtil.h"

#import "NativeManager.h"
#import "GameScene.h"


using namespace cocos2d;
using namespace std;

USING_NS_CC;

GameUtil::~GameUtil(){
    
}

bool GameUtil::getAppStatus(){
    
    return SaveUtil::getSaveBool(USERDEFAULT_APP_STATUS,false);

}

//初期化
bool GameUtil::init() {
	if (CCLayer::init()) {
		//サウンドフラグ
        m_soundFlg =SaveUtil::getSaveBool(USERDEFAULT_SOUND_ON_OFF,true);
        SaveUtil::saveBool(USERDEFAULT_SOUND_ON_OFF, m_soundFlg);
        
        
		return true;
	} else {
		return false;
	}
}

CCLabelTTF* GameUtil::getTextSp(const char* moji){
    CCLabelTTF* pLabel;
    pLabel = CCLabelTTF::create("0", FONT_NAME_TREBUCHET,50);
    pLabel->setAnchorPoint(ccp(0, 0.5));
    //pLabel->setPosition(ccp(265,225));
    //pLabel->setColor(ccc3(229, 204, 182));
    pLabel->setColor(ccWHITE);
    CCString* cntS=CCString::create(moji);
    pLabel->setString(cntS->getCString());
    return pLabel;
}



//ポーズ状態
void GameUtil::pauseALLSound() {
	//サウンド
	if (m_soundFlg) {
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseAllEffects();
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}
}

//ゲーム再開
void GameUtil::resumeALLSound() {
	//サウンド
	if (m_soundFlg) {
		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeAllEffects();
		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	}
}

#pragma mark サウンド

//引数のサウンドをならす
unsigned int GameUtil::startSoundEffect(const char *soundFile) {
	if (m_soundFlg) {
		return CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(soundFile);
	}
	else {
		return 0;
	}
}

//引数のサウンドを止める
void GameUtil::stopSoundEffect(unsigned int soundId) {
	if (m_soundFlg) {
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopEffect(soundId);
	}
}
//サウンドを全部止める
void GameUtil::stopALLSound() {
	if (m_soundFlg) {
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
	}
}
//引数のBGMをならす
void GameUtil::startBGM(const char *soundFile, bool loop) {
	if (m_soundFlg) {
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(soundFile, loop);
	}
}

//BGMを止める
void GameUtil::pauseBGM() {
	if (m_soundFlg) {
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}
}

//BGMを止める
void GameUtil::stopBGM() {
	if (m_soundFlg) {
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	}
}
void GameUtil::resumeBGM() {
	if (m_soundFlg) {
		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	}
}
void GameUtil::setSoundFlg(bool flg){
    m_soundFlg=flg;
    //保存
    CCUserDefault::sharedUserDefault()->setBoolForKey(USERDEFAULT_SOUND_ON_OFF, m_soundFlg);
    CCUserDefault::sharedUserDefault()->flush();
}
bool GameUtil::getSounFlg(){
    return m_soundFlg;
}


//引数のサウンドをならす
unsigned int GameUtil::startButtonTapEffect() {
	if (m_soundFlg) {
		return CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(SOUND_FILE_BUTTON_TAP);
	}
	else {
		return 0;
	}
}


unsigned int GameUtil::tapButtonEffect(bool isSound){
    if (isSound) {
		return CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(SOUND_FILE_BUTTON_TAP);
	}
	else {
		return 0;
	}
}

unsigned int GameUtil::SimpleStartEffect(const char* soundFile){
    if(SaveUtil::getSaveBool(USERDEFAULT_SOUND_ON_OFF,true)){
        return CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(soundFile);
    }else{
        return -1;
    }
}

//引数のサウンドを止める
void GameUtil::SimpleStopEffect(unsigned int soundId){
    if(SaveUtil::getSaveBool(USERDEFAULT_SOUND_ON_OFF,true) && soundId!=-1){
        CocosDenshion::SimpleAudioEngine::sharedEngine()->stopEffect(soundId);
    }
}


//引数の画像ファイルに変更する
void GameUtil::changeSpImage(CCSprite* itemImage,const char* imageFile){
    CCSpriteFrame* imageSpriteFrame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(imageFile);
    itemImage->setTexture(imageSpriteFrame->getTexture());
    itemImage->setTextureRect(imageSpriteFrame->getRect());
    itemImage->setDisplayFrame(imageSpriteFrame);
}


//黒
CCSprite* GameUtil::makeBlackBg(int w,int h){
    CCRect rect = CCRectMake(0, 0, w, h);
    CCSprite* m_blackBg = CCSprite::create();
    m_blackBg->setTextureRect(rect);
    m_blackBg->setColor(ccBLACK);
    m_blackBg->setOpacity(180);
    return m_blackBg;
}
CCSprite* GameUtil::makeColorSp(int w,int h){
    CCRect rect = CCRectMake(0, 0, w, h);
    CCSprite* m_blackBg = CCSprite::create();
    m_blackBg->setTextureRect(rect);
    m_blackBg->setColor(ccRED);
    m_blackBg->setOpacity(128);
    return m_blackBg;
}

const char* GameUtil::changeChar(CCObject* obj){
    CCString* _s=(CCString *)obj;
    return _s->getCString();
}


void GameUtil::setBoolSNSPosted_Stage(int stagenum){
    const char* _name;
    switch (stagenum) {
        case 1:
            _name = POST_TW_STAGE_1;
            break;
        case 2:
            _name = POST_TW_STAGE_2;
            break;
        case 3:
            _name = POST_TW_STAGE_3;
            break;
        case 4:
            _name = POST_TW_STAGE_4;
            break;
        case 5:
            _name = POST_TW_STAGE_5;
            break;
        case 6:
            _name = POST_TW_STAGE_6;
            break;
        case 7:
            _name = POST_TW_STAGE_7;
            break;
        case 8:
            _name = POST_TW_STAGE_8;
            break;
        case 9:
            _name = POST_TW_STAGE_9;
            break;
        case 10:
            _name = POST_TW_STAGE_10;
            break;
        default:
            break;
    }
    SaveUtil::saveBool(_name,true);
    CCLOG("SaveUtil::saveBool(_name,true)");
}


bool GameUtil::getBoolSNSPosted_Stage(int stagenum){
    const char* _name;
    switch (stagenum) {
        case 1:
            _name = POST_TW_STAGE_1;
            break;
        case 2:
            _name = POST_TW_STAGE_2;
            break;
        case 3:
            _name = POST_TW_STAGE_3;
            break;
        case 4:
            _name = POST_TW_STAGE_4;
            break;
        case 5:
            _name = POST_TW_STAGE_5;
            break;
        case 6:
            _name = POST_TW_STAGE_6;
            break;
        case 7:
            _name = POST_TW_STAGE_7;
            break;
        case 8:
            _name = POST_TW_STAGE_8;
            break;
        case 9:
            _name = POST_TW_STAGE_9;
            break;
        case 10:
            _name = POST_TW_STAGE_10;
            break;
        case 11:
            _name = POST_TW_STAGE_11;
            break;

        default:
            _name = POST_TW_STAGE_12;
            break;
    }

    return SaveUtil::getSaveBool(_name);
}



void GameUtil::setBoolSNSPosted_Friend(int stagenum){
    const char* _name;
    switch (stagenum) {
        case 1:
            _name = POST_TW_FRIEND_1;
            break;
        case 2:
            _name = POST_TW_FRIEND_2;
            break;
        case 3:
            _name = POST_TW_FRIEND_3;
            break;
        case 4:
            _name = POST_TW_FRIEND_4;
            break;
        case 5:
            _name = POST_TW_FRIEND_5;
            break;
        case 6:
            _name = POST_TW_FRIEND_6;
            break;
        case 7:
            _name = POST_TW_FRIEND_7;
            break;
        case 8:
            _name = POST_TW_FRIEND_8;
            break;
        case 9:
            _name = POST_TW_FRIEND_9;
            break;
        case 10:
            _name = POST_TW_FRIEND_10;
            break;
        default:
            break;
    }
    SaveUtil::saveBool(_name,true);
    CCLOG("SaveUtil::saveBool(_name,true)");
}


bool GameUtil::getBoolSNSPosted_Friend(int stagenum){
    const char* _name;
    switch (stagenum) {
        case 1:
            _name = POST_TW_FRIEND_1;
            break;
        case 2:
            _name = POST_TW_FRIEND_2;
            break;
        case 3:
            _name = POST_TW_FRIEND_3;
            break;
        case 4:
            _name = POST_TW_FRIEND_4;
            break;
        case 5:
            _name = POST_TW_FRIEND_5;
            break;
        case 6:
            _name = POST_TW_FRIEND_6;
            break;
        case 7:
            _name = POST_TW_FRIEND_7;
            break;
        case 8:
            _name = POST_TW_FRIEND_8;
            break;
        case 9:
            _name = POST_TW_FRIEND_9;
            break;
        case 10:
            _name = POST_TW_FRIEND_10;
            break;
        case 11:
            _name = POST_TW_FRIEND_11;
            break;
        default:
            break;
    }
    
    return SaveUtil::getSaveBool(_name);
}







//シェアで送るときの文言を返す
const char *GameUtil::getSNSPostWord(int stagenum) {
	switch (stagenum) {
		case 1:
			return POST_WORD_STAGE_1;
			break;
            
		case 2:
			return POST_WORD_STAGE_2;
			break;
            
		case 3:
			return POST_WORD_STAGE_3;
			break;
            
		case 4:
			return POST_WORD_STAGE_4;
			break;
            
		case 5:
			return POST_WORD_STAGE_5;
			break;
            
		case 6:
			return POST_WORD_STAGE_6;
			break;
            
		case 7:
			return POST_WORD_STAGE_7;
			break;
            
		case 8:
			return POST_WORD_STAGE_8;
			break;
            
		case 9:
			return POST_WORD_STAGE_9;
			break;
            
		case 10:
			return POST_WORD_STAGE_10;
			break;
        case 11:
			return POST_WORD_STAGE_11;
			break;
		default:
			return "エラーです";
			break;
	}
}

//ギミック発見されたのフラグ
void GameUtil::setBoolGimmickFlag(int num){
    const char* _name;
    switch (num) {
        case 1:
            _name = GIMMICK_CHECK_1;
            break;
        case 2:
            _name = GIMMICK_CHECK_2;
            break;
        case 3:
            _name = GIMMICK_CHECK_3;
            break;
        case 4:
            _name = GIMMICK_CHECK_4;
            break;
        case 5:
            _name = GIMMICK_CHECK_5;
            break;
        case 6:
            _name = GIMMICK_CHECK_6;
            break;
        case 7:
            _name = GIMMICK_CHECK_7;
            break;
        case 8:
            _name = GIMMICK_CHECK_8;
            break;
        case 9:
            _name = GIMMICK_CHECK_9;
            break;
        case 10:
            _name = GIMMICK_CHECK_10;
            break;
        case 11:
            _name = GIMMICK_CHECK_11;
            break;
        case 12:
            _name = GIMMICK_CHECK_12;
            break;
        case 13:
            _name = GIMMICK_CHECK_13;
            break;
        case 14:
            _name = GIMMICK_CHECK_14;
            break;
        case 15:
            _name = GIMMICK_CHECK_15;
            break;
        case 16:
            _name = GIMMICK_CHECK_16;
            break;
        case 17:
            _name = GIMMICK_CHECK_17;
            break;
        case 18:
            _name = GIMMICK_CHECK_18;
            break;
        case 19:
            _name = GIMMICK_CHECK_19;
            break;
        case 20:
            _name = GIMMICK_CHECK_20;
            break;
            
        default:
            break;
    }
    SaveUtil::saveBool(_name,true);
}

//ギミック発見されたのフラグ
bool GameUtil::getBoolGimmickFlag(int num){
    const char* _name;
    switch (num) {
        case 1:
            _name = GIMMICK_CHECK_1;
            break;
        case 2:
            _name = GIMMICK_CHECK_2;
            break;
        case 3:
            _name = GIMMICK_CHECK_3;
            break;
        case 4:
            _name = GIMMICK_CHECK_4;
            break;
        case 5:
            _name = GIMMICK_CHECK_5;
            break;
        case 6:
            _name = GIMMICK_CHECK_6;
            break;
        case 7:
            _name = GIMMICK_CHECK_7;
            break;
        case 8:
            _name = GIMMICK_CHECK_8;
            break;
        case 9:
            _name = GIMMICK_CHECK_9;
            break;
        case 10:
            _name = GIMMICK_CHECK_10;
            break;
        case 11:
            _name = GIMMICK_CHECK_11;
            break;
        case 12:
            _name = GIMMICK_CHECK_12;
            break;
        case 13:
            _name = GIMMICK_CHECK_13;
            break;
        case 14:
            _name = GIMMICK_CHECK_14;
            break;
        case 15:
            _name = GIMMICK_CHECK_15;
            break;
        case 16:
            _name = GIMMICK_CHECK_16;
            break;
        case 17:
            _name = GIMMICK_CHECK_17;
            break;
        case 18:
            _name = GIMMICK_CHECK_18;
            break;
        case 19:
            _name = GIMMICK_CHECK_19;
            break;
        case 20:
            _name = GIMMICK_CHECK_20;
            break;
            
        default:
            break;
    }
    return SaveUtil::getSaveBool(_name);
}

//友達　発見したのを保存
void GameUtil::setBoolFriendFlag(int num){
    const char* _name;
    switch (num) {
        case 1:
            _name = USERDEFAULT_FRIEND_1;
            break;
        case 2:
            _name = USERDEFAULT_FRIEND_2;
            break;
        case 3:
            _name = USERDEFAULT_FRIEND_3;
            break;
        case 4:
            _name = USERDEFAULT_FRIEND_4;
            break;
        case 5:
            _name = USERDEFAULT_FRIEND_5;
            break;
        case 6:
            _name = USERDEFAULT_FRIEND_6;
            break;
        case 7:
            _name = USERDEFAULT_FRIEND_7;
            break;
        case 8:
            _name = USERDEFAULT_FRIEND_8;
            break;
        case 9:
            _name = USERDEFAULT_FRIEND_9;
            break;
        case 10:
            _name = USERDEFAULT_FRIEND_10;
            break;
            
        default:
            break;
    }
    SaveUtil::saveBool(_name,true);
}

//友達　発見されてるかを返す
bool GameUtil::getBoolFriendFlag(int num){
    const char* _name;
    switch (num) {
        case 1:
            _name = USERDEFAULT_FRIEND_1;
            break;
        case 2:
            _name = USERDEFAULT_FRIEND_2;
            break;
        case 3:
            _name = USERDEFAULT_FRIEND_3;
            break;
        case 4:
            _name = USERDEFAULT_FRIEND_4;
            break;
        case 5:
            _name = USERDEFAULT_FRIEND_5;
            break;
        case 6:
            _name = USERDEFAULT_FRIEND_6;
            break;
        case 7:
            _name = USERDEFAULT_FRIEND_7;
            break;
        case 8:
            _name = USERDEFAULT_FRIEND_8;
            break;
        case 9:
            _name = USERDEFAULT_FRIEND_9;
            break;
        case 10:
            _name = USERDEFAULT_FRIEND_10;
            break;
            
        default:
            _name = USERDEFAULT_FRIEND_1;
            break;
    }
    return SaveUtil::getSaveBool(_name);
}

int GameUtil::getFriendFindCount(int kind){
    const char* _name;
    switch (kind) {
        case 1:
            _name = USERDEFAULT_FRIEND_COUNT_1;
            break;
        case 2:
            _name = USERDEFAULT_FRIEND_COUNT_2;
            break;
        case 3:
            _name = USERDEFAULT_FRIEND_COUNT_3;
            break;
        case 4:
            _name = USERDEFAULT_FRIEND_COUNT_4;
            break;
        case 5:
            _name = USERDEFAULT_FRIEND_COUNT_5;
            break;
        case 6:
            _name = USERDEFAULT_FRIEND_COUNT_6;
            break;
        case 7:
            _name = USERDEFAULT_FRIEND_COUNT_7;
            break;
        case 8:
            _name = USERDEFAULT_FRIEND_COUNT_8;
            break;
        case 9:
            _name = USERDEFAULT_FRIEND_COUNT_9;
            break;
        case 10:
            _name = USERDEFAULT_FRIEND_COUNT_10;
            break;
            
        default:
            _name = USERDEFAULT_FRIEND_COUNT_1;
            break;
    }
    return SaveUtil::getSaveBool(_name);
}

void GameUtil::incrementFriendFindCount(int kind){
    const char* _name;
    switch (kind) {
        case 1:
            _name = USERDEFAULT_FRIEND_COUNT_1;
            break;
        case 2:
            _name = USERDEFAULT_FRIEND_COUNT_2;
            break;
        case 3:
            _name = USERDEFAULT_FRIEND_COUNT_3;
            break;
        case 4:
            _name = USERDEFAULT_FRIEND_COUNT_4;
            break;
        case 5:
            _name = USERDEFAULT_FRIEND_COUNT_5;
            break;
        case 6:
            _name = USERDEFAULT_FRIEND_COUNT_6;
            break;
        case 7:
            _name = USERDEFAULT_FRIEND_COUNT_7;
            break;
        case 8:
            _name = USERDEFAULT_FRIEND_COUNT_8;
            break;
        case 9:
            _name = USERDEFAULT_FRIEND_COUNT_9;
            break;
        case 10:
            _name = USERDEFAULT_FRIEND_COUNT_10;
            break;
            
        default:
            _name = USERDEFAULT_FRIEND_COUNT_1;
            break;
    }
    int n = 1 + SaveUtil::getSaveInt(_name, 0);
    SaveUtil::saveInt(_name,n);
}



int GameUtil::getHasOkashiNum(int kind){
    const char* _name;
    switch (kind) {
        case 1:
            _name = USERDEFAULT_HAS_COOKIE;
            break;
        case 2:
            _name = USERDEFAULT_HAS_AME;
            break;
        case 3:
            _name = USERDEFAULT_HAS_PAN;
            break;
        case 4:
            _name = USERDEFAULT_HAS_CHOCO;
            break;
        case 5:
            _name = USERDEFAULT_HAS_SHOE;
            break;
        case 6:
            _name = USERDEFAULT_HAS_CAKE;
            break;
        case 7:
            _name = USERDEFAULT_HAS_PUDDING;
            break;
            
        default:
            _name = USERDEFAULT_HAS_COOKIE;
            break;
    }
    return SaveUtil::getSaveInt(_name);
}



// !!!:ステージ数から、レベルアップまでのポイント、等を返す
int GameUtil::getStageMaxLevel(int nowStageNum){
    int re;
    switch (nowStageNum) {
        case 1:
            re = INT_EVOLUTION_2;
            break;
        case 2:
            re = INT_EVOLUTION_3;
            break;
        case 3:
            re = INT_EVOLUTION_4;
            break;
        case 4:
            re = INT_EVOLUTION_5;
            break;
        case 5:
            re = INT_EVOLUTION_6;
            break;
        case 6:
            re = INT_EVOLUTION_7;
            break;
        case 7:
            re = INT_EVOLUTION_8;
            break;
        case 8:
            re = INT_EVOLUTION_9;
            break;
        case 9:
            re = INT_EVOLUTION_10;
            break;
        case 10:
            re = INT_EVOLUTION_10;
            break;
        default:
            re = INT_EVOLUTION_10;
            break;
    }
    return re;
}

bool GameUtil::isFriendTweeted(int n){
    const char* _name;
    switch (n) {
        case 1:
            _name = USERDEFAULT_FRIEND_TWEET_1;
            break;
        case 2:
            _name = USERDEFAULT_FRIEND_TWEET_2;
            break;
        case 3:
            _name = USERDEFAULT_FRIEND_TWEET_3;
            break;
        case 4:
            _name = USERDEFAULT_FRIEND_TWEET_4;
            break;
        case 5:
            _name = USERDEFAULT_FRIEND_TWEET_5;
            break;
        case 6:
            _name = USERDEFAULT_FRIEND_TWEET_6;
            break;
        case 7:
            _name = USERDEFAULT_FRIEND_TWEET_7;
            break;
        case 8:
            _name = USERDEFAULT_FRIEND_TWEET_8;
            break;
        case 9:
            _name = USERDEFAULT_FRIEND_TWEET_9;
            break;
        case 10:
            _name = USERDEFAULT_FRIEND_TWEET_10;
            break;
        default:
            _name = USERDEFAULT_FRIEND_TWEET_1;
            break;
    }
    return SaveUtil::getSaveBool(_name,false);
}

const char* GameUtil::getPngNameFromPlist(const char* filename,int num){
    CCArray *pngNameArr=CCArray::createWithContentsOfFile(filename);
    CCString* str=(CCString *)(pngNameArr->objectAtIndex(num));
    return str->getCString();
}




#pragma mark そのステージで必要なplistを設定する
void GameUtil::readPlist(int n){

}

void GameUtil::delPlist(int n){

}


//TWで送る友達の画像ファイル名
const char* GameUtil::getSNSPostFriendImageName(int num){
    CCString* _strng=CCString::createWithFormat("friend%d.png",num);
    return _strng->getCString();
}
const char* GameUtil::getSNSPost4komaImageName(int num){
    CCString* _strng=CCString::createWithFormat("image%d.png",num);
    return _strng->getCString();
}

const char* GameUtil::getSNSPostImageNameFromSetting(int num){
    CCString* _strng=CCString::createWithFormat("image%d.png",num);
    return _strng->getCString();
}
