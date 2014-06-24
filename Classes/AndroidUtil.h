//
//  AndroidUtil.h
//  highandlowrun
//
//  Created by dotchi on 2013/11/06.
//
//
#import <string>

#ifndef __tenchi__AndroidUtil__
#define __tenchi__AndroidUtil__

class AndroidUtil
{
public:
	static void heapLogger();
    
    static int getAndroidAPIVer();
    
    static bool getPrefBoolean(const char* stringkey);
    static bool getPrefBoolean(const char* stringkey , bool bdefvalue);
    
    static int getPrefInt(const char* stringkey,int defValue);
    
    static const char* getPrefString(const char* stringkey);
    static const char* getPrefString(const char* stringkey,const char* defvalue);
    
    static void putPref_void_bool(const char* stringkey,bool bvalue);
    static void putPref_void_int(const char* stringkey,int ivalue);
    static void putPref_void_string(const char* stringkey,const char* svalue);
    
    static void txtviewVisible();
};



#endif
