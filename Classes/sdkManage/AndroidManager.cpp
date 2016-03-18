#include "AndroidManager.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )

#include "platform/android/jni/JniHelper.h" //vem do projeto principal - pasta cocos2dx  
 
#include <jni.h>  

using namespace cocos2d;

#define CLASS_PATH "org.cocos2dx.cpp/AppActivity"


extern "C"  
{
	bool isVersionHighJNI(){
		bool result = false;
        JniMethodInfo t;  
        if (JniHelper::getStaticMethodInfo(t, CLASS_PATH  
                        ,"isVersionHighJNI"  
                        ,"()Z"))  
        {  
            jboolean javaResult = t.env->CallStaticBooleanMethod(t.classID,t.methodID);
			if( javaResult == JNI_TRUE ) result = true;
			else log( "versionCodeUnpon5JIN() is lower than 5" );
        } 

		return result;
    }
}

bool AndroidManager::systemVersionCodeUpon5()
{
	return isVersionHighJNI();
}


#endif