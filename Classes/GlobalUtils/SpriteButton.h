/****************************************
精灵按键
2016-01-13 by Azure Zheng
*****************************************/


#ifndef __SPRITE_BUTTON_H__
#define __SPRITE_BUTTON_H__


#include "cocos2d.h"

class SpriteButton : public cocos2d::Sprite
{
public:

	//析构移除精灵帧与监听器
	virtual ~SpriteButton();

	//创建实例
	CREATE_FUNC(SpriteButton);

	//带参数创建实例
	static SpriteButton * create(const std::string & normalSpriteFrameName, const std::string & pressSpriteFrameName = "", const std::string & disabledSpriteFrameName = "");
	static SpriteButton * create(cocos2d::SpriteFrame * normalSpriteFrame, cocos2d::SpriteFrame * pressSpriteFrame = nullptr, cocos2d::SpriteFrame * disabledSpriteFrame = nullptr);

	//设置所有按钮互斥状态
	static void setAllButtonsMutexStatus(bool isEnabled);

	//转换到按下状态
	void switchToPress();

	//转换到正常状态
	void switchToNormal();

	//转换到禁用状态
	void switchToDisabled();

	//设置可用状态
	void setEnabled(bool enabled);

	//返回可用状态
	bool isEnabled();

	//设置回调函数
	void setCallback(const std::function<void(cocos2d::Ref*)> callback);

	//设置刚按下时回调函数
	void setCallbackTouchBegan(const std::function<void(cocos2d::Ref*)> callback);

	//设置禁用时的回调函数
	void setCallbackDisabled(const std::function<void(cocos2d::Ref*)> callback);

	//返回回调函数
	const std::function<void(cocos2d::Ref*)> & getCallback() const;

	//设置正常状态精灵帧
	void setNormalSpriteFrame(cocos2d::SpriteFrame * sf);

	//设置按下状态精灵帧
	void setPressSpriteFrame(cocos2d::SpriteFrame * sf);

	//设置禁用状态精灵帧
	void setDisabledSpriteFrame(cocos2d::SpriteFrame * sf);

	//设置触摸吞噬
	void setSwallowTouches(bool needSwallow);

	//触摸取消
	void touchCancel();

	//退出时移除监听器
	virtual void onExit();

protected:

	//初始化(请勿手动调用)
	virtual bool init();

	//创建触摸监听器
	void _setupTouchListener();

	//检查是否父节点可见
	bool _isAncensterEnabled(Node * node);

	//-------------------------------------------------------------------

	//互斥状态
	static bool m_mutexStatus;

	//当前状态(0:正常，1:按下，2:禁用，3:触摸取消)
	short m_status;

	//触摸监听器
	cocos2d::EventListenerTouchOneByOne * m_touchListener;

	//正常状态精灵帧
	cocos2d::SpriteFrame * m_normalSpriteFrame;

	//按下状态精灵帧
	cocos2d::SpriteFrame * m_pressSpriteFrame;

	//禁用状态精灵帧
	cocos2d::SpriteFrame * m_disabledSpriteFrame;

	//按下回调函数
	std::function<void(cocos2d::Ref*)> m_callback;

	//刚按时回调函数
	std::function<void(cocos2d::Ref*)> m_touchBeganCallback;

	//禁用时回调函数
	std::function<void(cocos2d::Ref*)> m_disabledCallback;

	//可用状态
	bool m_isEnabled;

	//缩放状态
	float m_scaledRateX;
	float m_scaledRateY;

	//开始触摸状态
	bool m_startToBeTouched;
};

















#endif
