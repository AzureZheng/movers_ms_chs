#include "SpriteButton.h"

USING_NS_CC;

//配置互斥状态
bool SpriteButton::m_mutexStatus = false;


//析构移除精灵帧与监听器
SpriteButton::~SpriteButton()
{
	if (m_normalSpriteFrame)
	{
		m_normalSpriteFrame->release();
	}

	if (m_pressSpriteFrame)
	{
		m_pressSpriteFrame->release();
	}

	if (m_disabledSpriteFrame)
	{
		m_disabledSpriteFrame->release();
	}

	if (m_touchListener)
	{
		m_touchListener->release();
	}
}

//创建触摸监听器
void SpriteButton::_setupTouchListener()
{
	m_touchListener = EventListenerTouchOneByOne::create();
	m_touchListener->retain();

	m_touchListener->setSwallowTouches(true);
	m_touchListener->onTouchBegan = [this](Touch * t, Event * e)
	{
		if (!getParent()) return false;

		if (m_isEnabled == true && m_mutexStatus == false && (m_status == 0 || m_status == 3) && _isAncensterEnabled(this))
		{
			if (getBoundingBox().containsPoint(getParent()->convertToNodeSpace(t->getLocation())))
			{
				switchToPress();
				m_touchBeganCallback(this);
				m_startToBeTouched = true;
				m_mutexStatus = true;
				return true;
			}
		}
		else if (m_isEnabled == false && _isAncensterEnabled(this))
		{
			if (getBoundingBox().containsPoint(getParent()->convertToNodeSpace(t->getLocation())))
			{
				m_disabledCallback(this);
			}
		}

		return false;
	};

	m_touchListener->onTouchMoved = [this](Touch * t, Event * e)
	{
		if (!getParent()) return;

		if (m_status == 0)
		{
			if (getBoundingBox().containsPoint(getParent()->convertToNodeSpace(t->getLocation())))
			{
				switchToPress();
			}
		}
		else if (m_status == 1)
		{
			if (!getBoundingBox().containsPoint(getParent()->convertToNodeSpace(t->getLocation())))
			{
				switchToNormal();
			}
		}

	};

	auto touchEnded = [this](Touch * t, Event * e)
	{
		if (!getParent()) return;

		if (m_status == 3)
		{
			m_status = 0;
		}
		else if (m_status == 0 || m_status == 1)
		{
			if (getBoundingBox().containsPoint(getParent()->convertToNodeSpace(t->getLocation())))
			{
				m_callback(this);
			}
			switchToNormal();
		}

		m_startToBeTouched = false;
		m_mutexStatus = false;
	};

	m_touchListener->onTouchEnded = touchEnded;
	m_touchListener->onTouchCancelled = touchEnded;

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_touchListener,this);
}


//设置触摸吞噬
void SpriteButton::setSwallowTouches(bool needSwallow)
{
	m_touchListener->setSwallowTouches(needSwallow);
}

//初始化
bool SpriteButton::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	m_normalSpriteFrame = nullptr;

	m_pressSpriteFrame = nullptr;

	m_disabledSpriteFrame = nullptr;

	m_status = 0;

	m_isEnabled = false;

	m_scaledRateX = 0;

	m_scaledRateY = 0;

	m_startToBeTouched = false;

	m_callback = [](Ref*){};
	m_touchBeganCallback = [](Ref*){};
	m_disabledCallback = [](Ref*){};

	_setupTouchListener();

	setEnabled(true);

	return true;
}



//带参数创建实例
SpriteButton * SpriteButton::create(const std::string & normalSpriteFrameName, const std::string & pressSpriteFrameName, const std::string & disabledSpriteFrameName)
{
	auto spb = create();

	auto sfc = SpriteFrameCache::getInstance();

	spb->setNormalSpriteFrame(sfc->getSpriteFrameByName(normalSpriteFrameName));
	spb->setPressSpriteFrame(sfc->getSpriteFrameByName(pressSpriteFrameName));
	spb->setDisabledSpriteFrame(sfc->getSpriteFrameByName(disabledSpriteFrameName));

	return spb;
}


SpriteButton * SpriteButton::create(cocos2d::SpriteFrame * normalSpriteFrame, cocos2d::SpriteFrame * pressSpriteFrame, cocos2d::SpriteFrame * disabledSpriteFrame)
{
	auto spb = create();

	auto sfc = SpriteFrameCache::getInstance();
	spb->setNormalSpriteFrame(normalSpriteFrame);
	spb->setPressSpriteFrame(pressSpriteFrame);
	spb->setDisabledSpriteFrame(disabledSpriteFrame);

	return spb;
}


//转换到正常状态
void SpriteButton::switchToNormal()
{
	m_status = 0;

	if (m_normalSpriteFrame)
	{
		setSpriteFrame(m_normalSpriteFrame);
	}
	else
	{
		setTexture(nullptr);
	}

	if (m_scaledRateX != 0 && m_scaledRateY != 0)
	{
		setScale(m_scaledRateX, m_scaledRateY);
	}
}



//转换到按下状态
void SpriteButton::switchToPress()
{
	m_status = 1;

	if (m_pressSpriteFrame)
	{
		setSpriteFrame(m_pressSpriteFrame);
	}
	else
	{
		m_scaledRateX = getScaleX();
		m_scaledRateY = getScaleY();

		setScale(m_scaledRateX + 0.1f, m_scaledRateY + 0.1f);
	}
}


//转换到禁用状态
void SpriteButton::switchToDisabled()
{
	m_status = 2;
	if (m_disabledSpriteFrame)
	{
		setSpriteFrame(m_disabledSpriteFrame);
	}
}



//设置可用状态
void SpriteButton::setEnabled(bool enabled)
{
	if (enabled)
	{
		if (m_isEnabled) return;
		m_isEnabled = true;
		switchToNormal();
	}
	else
	{
		if (!m_isEnabled) return;
		m_isEnabled = false;
		switchToDisabled();
	}
}



//返回可用状态
bool SpriteButton::isEnabled()
{
	return m_isEnabled;
}



//设置回调函数
void SpriteButton::setCallback(const std::function<void(cocos2d::Ref*)> callback)
{
	m_callback = callback;
}



//返回回调函数
const std::function<void(cocos2d::Ref*)> & SpriteButton::getCallback() const
{
	return m_callback;
}



//设置正常状态精灵帧
void SpriteButton::setNormalSpriteFrame(cocos2d::SpriteFrame * sf)
{
	if (m_normalSpriteFrame)
	{
		m_normalSpriteFrame->release();
		m_normalSpriteFrame = nullptr;
	}

	if (sf)
	{
		m_normalSpriteFrame = sf;
		m_normalSpriteFrame->retain();
	}

	if (m_status == 0)
	{
		switchToNormal();
	}
}



//设置按下状态精灵帧
void SpriteButton::setPressSpriteFrame(cocos2d::SpriteFrame * sf)
{
	if (m_pressSpriteFrame)
	{
		m_pressSpriteFrame->release();
		m_pressSpriteFrame = nullptr;
	}

	if (sf)
	{
		m_pressSpriteFrame = sf;
		m_pressSpriteFrame->retain();
	}

	if (m_status == 1)
	{
		switchToPress();
	}
}



//设置禁用状态精灵帧
void SpriteButton::setDisabledSpriteFrame(cocos2d::SpriteFrame * sf)
{
	if (m_disabledSpriteFrame)
	{
		m_disabledSpriteFrame->release();
		m_disabledSpriteFrame = nullptr;
	}

	if (sf)
	{
		m_disabledSpriteFrame = sf;
		m_disabledSpriteFrame->retain();
	}

	if (m_status == 2)
	{
		switchToDisabled();
	}
}



//退出时移除监听器
void SpriteButton::onExit()
{
	Sprite::onExit();
	Director::getInstance()->getEventDispatcher()->removeEventListener(m_touchListener);
}



//触摸取消
void SpriteButton::touchCancel()
{
	if (m_startToBeTouched)
	{
		if (m_status == 1)
		{
			switchToNormal();
		}
		m_status = 3;
	}
}


//设置所有按钮互斥状态
void SpriteButton::setAllButtonsMutexStatus(bool isEnabled)
{
	m_mutexStatus = !isEnabled;
}


//设置刚按下时回调函数
void SpriteButton::setCallbackTouchBegan(const std::function<void(cocos2d::Ref*)> callback)
{
	m_touchBeganCallback = callback;
}


//设置禁用时的回调函数
void SpriteButton::setCallbackDisabled(const std::function<void(cocos2d::Ref*)> callback)
{
	m_disabledCallback = callback;
}


//检查是否父节点可见
bool SpriteButton::_isAncensterEnabled(Node * node)
{
	if (node == nullptr)
	{
		return true;
	}

	if (!node->isVisible())
	{
		return false;
	}

	return _isAncensterEnabled(node->getParent());
}
