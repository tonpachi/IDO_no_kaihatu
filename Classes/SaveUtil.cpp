//
//  SaveUtil.cpp
//  tenchi
//
//  Created by dotchi on 2013/11/21.
//
//
#include <string>
#include "SaveUtil.h"
#include "cocos2d.h"
#include "AndroidUtil.h"

USING_NS_CC;

//保存int
void SaveUtil::saveInt(const char *keyname, int ivalue) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	CCUserDefault::sharedUserDefault()->setIntegerForKey(keyname, ivalue);
    CCUserDefault::sharedUserDefault()->flush();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	AndroidUtil::putPref_void_int(keyname, ivalue);
#endif
}

//保存bool
void SaveUtil::saveBool(const char *keyname, bool bvalue) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	CCUserDefault::sharedUserDefault()->setBoolForKey(keyname, bvalue);
    CCUserDefault::sharedUserDefault()->flush();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	AndroidUtil::putPref_void_bool(keyname, bvalue);
#endif
}

//保存string
void SaveUtil::saveString(const char* keyname,const char* svalue){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	CCUserDefault::sharedUserDefault()->setStringForKey(keyname, svalue);
    CCUserDefault::sharedUserDefault()->flush();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	AndroidUtil::putPref_void_string(keyname, svalue);
#endif
    
}



//取得bool
bool SaveUtil::getSaveBool(const char *keyname) {
    return SaveUtil::getSaveBool(keyname, false);
}

bool SaveUtil::getSaveBool(const char* keyname,bool bdefvalue) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	return CCUserDefault::sharedUserDefault()->getBoolForKey(keyname, bdefvalue);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	return AndroidUtil::getPrefBoolean(keyname,bdefvalue);
#endif
}


//取得int
int SaveUtil::getSaveInt(const char *keyname) {
    return SaveUtil::getSaveInt(keyname, 0);
}

int SaveUtil::getSaveInt(const char *keyname, int defvalue) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	return CCUserDefault::sharedUserDefault()->getIntegerForKey(keyname, defvalue);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	return AndroidUtil::getPrefInt(keyname, defvalue);
#endif
}


//取得string
const char* SaveUtil::getSaveString(const char* keyname){
    return SaveUtil::getSaveString(keyname,"");
}

const char* SaveUtil::getSaveString(const char* keyname,const char* sdefvalue){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    std::string res=CCUserDefault::sharedUserDefault()->getStringForKey(keyname,sdefvalue);
	return res.c_str();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	return AndroidUtil::getPrefString(keyname,sdefvalue);
#endif
}



//取得int
int SaveUtil::getStageNum() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	return CCUserDefault::sharedUserDefault()->getIntegerForKey(USERDEFAULT_STAGE, 1);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	return AndroidUtil::getPrefInt(USERDEFAULT_STAGE, 1);
#endif
}



int SaveUtil::getPauseTime() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	return CCUserDefault::sharedUserDefault()->getIntegerForKey(USERDEFAULT_APP_PAUSE_TIME, 1);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	return AndroidUtil::getPrefInt(USERDEFAULT_APP_PAUSE_TIME, 1);
#endif
}

void SaveUtil::setPauseTime(int ivalue){
    SaveUtil::saveInt(USERDEFAULT_APP_PAUSE_TIME, ivalue);
}





void SaveUtil::incrimentSave(const char* keyname){
    int _n = SaveUtil::getSaveInt(keyname, 0);
    SaveUtil::saveInt(keyname, _n+1);
}

void SaveUtil::decrimentSave(const char* keyname){
    int _n = SaveUtil::getSaveInt(keyname, 0);
    if(0<_n)SaveUtil::saveInt(keyname, _n-1);
}
