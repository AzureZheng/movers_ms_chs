#ifndef  _MONEY_MANAGER_H_
#define  _MONEY_MANAGER_H_

#include "cocos2d.h"
USING_NS_CC;


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )

class MoneyManager
{
public:

	static bool isBuyOverAd(){ return true; }

	static int BuyNumberAd(){ return 0; }

	static void playBuyStartAd(){}
	static void playBuyStart2Ad(){}
	static void playBuyStart3Ad(){}
};


#else

class MoneyManager
{
public:

	static bool isBuyOverAd();

	static int BuyNumberAd();

	static void playBuyStartAd();
	static void playBuyStart2Ad();
	static void playBuyStart3Ad();
};

#endif

#endif // _MONEY_MANAGER_H_ 