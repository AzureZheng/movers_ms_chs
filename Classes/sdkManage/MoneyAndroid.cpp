#include "MoneyManager.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )

#include "platform/android/jni/JniHelper.h" //vem do projeto principal - pasta cocos2dx  

#include <jni.h>  

//using namespace cocos2d;

#define CLASS_PATH "com.sdk.money/SdkManageMoney"


extern "C"
{
	void playBuyStartJNI()
	{
		JniMethodInfo t;
		if (JniHelper::getStaticMethodInfo(t, CLASS_PATH
			, "gameStart1"
			, "()V"))
		{
			t.env->CallStaticVoidMethod(t.classID, t.methodID);
		}
	}
	void playBuyStart2JNI()
	{
		JniMethodInfo t;
		if (JniHelper::getStaticMethodInfo(t, CLASS_PATH
			, "gameStart2"
			, "()V"))
		{
			t.env->CallStaticVoidMethod(t.classID, t.methodID);
		}
	}
	void playBuyStart3JNI()
	{
		JniMethodInfo t;
		if (JniHelper::getStaticMethodInfo(t, CLASS_PATH
			, "gameStart3"
			, "()V"))
		{
			t.env->CallStaticVoidMethod(t.classID, t.methodID);
		}
	}

	bool isBuyOverJNI()
	{
		bool _result = false;
		JniMethodInfo t;
		if (JniHelper::getStaticMethodInfo(t, CLASS_PATH
			, "getBuyState"
			, "()Z"))
		{
			jboolean _RESULT = t.env->CallStaticBooleanMethod(t.classID, t.methodID);
			if (_RESULT == JNI_TRUE) _result = true;
		}

		return _result;
	}

	int BuyNumberJNI()
	{
		int _number = 0;
		JniMethodInfo t;
		if (JniHelper::getStaticMethodInfo(t, CLASS_PATH
			, "getBuyNumber"
			, "()I"))
		{
			jboolean _NUMBER = t.env->CallStaticIntMethod(t.classID, t.methodID);
			_number = _NUMBER;
		}
		return _number;
	}
}

void MoneyManager::playBuyStartAd()
{
	playBuyStartJNI();
}

void MoneyManager::playBuyStart2Ad()
{
	playBuyStart2JNI();
}

void MoneyManager::playBuyStart3Ad()
{
	playBuyStart3JNI();
}

bool MoneyManager::isBuyOverAd()
{
	return isBuyOverJNI();
}

int MoneyManager::BuyNumberAd()
{
	return BuyNumberJNI();
}

#endif
