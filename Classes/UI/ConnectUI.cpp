#include "ConnectUI.h"
#include "SimpleAudioEngine.h"
#include "FilePathDefine.h"

using namespace ui;

bool ConnectUI::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//触发连接侦听的接口函数
	m_triggerConnectCallback = [](int, bool){return -2; };

	//玩家人数
	m_playerCount = 2;

	//已连接的玩家人数
	m_connectedPlayerCount = 0;

	//暂时关闭侦听
	m_isPauseConnectListener = true;

	//创建遮罩层
	m_blackBack = Layout::create();
	m_blackBack->setContentSize(Director::getInstance()->getVisibleSize());
	m_blackBack->setBackGroundColorType(ui::Layout::BackGroundColorType::SOLID);
	m_blackBack->setBackGroundColor(Color3B::BLACK);
	m_blackBack->setBackGroundColorOpacity(255 * 6 / 10);
	m_blackBack->setTouchEnabled(true);
	addChild(m_blackBack, 0);

	//创建UI层
	m_uiLayer = Layer::create();
	m_uiLayer->setContentSize(Director::getInstance()->getVisibleSize());
	//m_uiLayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	//m_uiLayer->setPosition(Director::getInstance()->getVisibleSize() / 2);
	addChild(m_uiLayer, 1);

	//创建面板
	auto backPanel = Sprite::createWithSpriteFrameName("ui_connect_panel.png");
	backPanel->setPosition(Vec2(960, 540));
	m_uiLayer->addChild(backPanel, 0);

	//加载WiFi动画缓存
	auto sfc = SpriteFrameCache::getInstance();
	auto ac = AnimationCache::getInstance();
	auto anim = Animation::create();
	anim->addSpriteFrame(sfc->getSpriteFrameByName("ui_wifi_1.png"));
	anim->addSpriteFrame(sfc->getSpriteFrameByName("ui_wifi_2.png"));
	anim->addSpriteFrame(sfc->getSpriteFrameByName("ui_wifi_3.png"));
	anim->addSpriteFrame(sfc->getSpriteFrameByName("ui_wifi_4.png"));
	anim->setDelayPerUnit(0.1f);
	ac->addAnimation(anim, "WiFiConnect");


	//-------------------------------------- 添加按钮 ------------------------------------------
	//添加关闭按钮
	m_closeButton = SpriteButton::create("ui_bt_close.png");
	m_closeButton->setPosition(Vec2(1360, 932));
	m_closeButton->setCallbackTouchBegan([](Ref*){PLAY_EFFECT(SOUND_EFFECT_BUTTON); });
	m_uiLayer->addChild(m_closeButton, 3);

	//添加开始按钮
	m_startButton = SpriteButton::create("ui_bt_start_game_enable.png", "", "ui_bt_start_game_disable.png");
	m_startButton->setPosition(Vec2(802, 344));
	m_startButton->setCallbackTouchBegan([](Ref*){PLAY_EFFECT(SOUND_EFFECT_BUTTON); });
	m_uiLayer->addChild(m_startButton, 3);

	//添加重新连接按钮
	m_reconnectButton = SpriteButton::create("ui_bt_reconnect.png");
	m_reconnectButton->setPosition(Vec2(1116, 344));
	m_reconnectButton->setCallbackTouchBegan([](Ref*){PLAY_EFFECT(SOUND_EFFECT_BUTTON); });
	m_uiLayer->addChild(m_reconnectButton, 3);

	return true;
}

//初始化两人UI
void ConnectUI::initWithDoublePlayers()
{
	m_playerCount = 2;

	Layout * layout = nullptr;

	//添加连接图
	for (int i = 0; i < 2; i++)
	{
		layout = _createConnectPlayerLayout(i);

		switch (i)
		{
		case 0:
			layout->setPositionX(802);
			break;
		case 1:
			layout->setPositionX(1116);
			break;
		}

		layout->setPositionY(658);
		m_uiLayer->addChild(layout, 2);
		m_connectPlayerLayouts.pushBack(layout);
	}

	m_blackBack->addTouchEventListener([this](Ref*, ui::Widget::TouchEventType t)
	{
		if (t == ui::Widget::TouchEventType::BEGAN)
		{
			shakePlayer(0);
		}
	});
}


//初始化四人UI
void ConnectUI::initWithFourPlayers()
{
	m_playerCount = 4;

	Layout * layout = nullptr;

	//添加连接图
	for (int i = 0; i < 4; i++)
	{
		layout = _createConnectPlayerLayout(i);

		switch (i)
		{
		case 0:
			layout->setPositionX(666);
			break;
		case 1:
			layout->setPositionX(860);
			break;
		case 2:
			layout->setPositionX(1057);
			break;
		case 3:
			layout->setPositionX(1253);
			break;
		}

		layout->setPositionY(658);
		m_uiLayer->addChild(layout, 2);
		m_connectPlayerLayouts.pushBack(layout);
	}

	m_blackBack->addTouchEventListener([this](Ref*, ui::Widget::TouchEventType t)
	{
		if (t == ui::Widget::TouchEventType::BEGAN)
		{
			shakePlayer(0);
		}
	});
}


//第几个玩家显示为已连接状态(0~3)
void ConnectUI::connectPlayer(int playerID)
{
	auto layout = m_connectPlayerLayouts.at(playerID);
	auto playerTip = dynamic_cast<Sprite*>(layout->getChildByName("PlayerTip"));
	auto wifi = dynamic_cast<Sprite*>(layout->getChildByName("WiFi"));
	auto textTip = dynamic_cast<Sprite*>(layout->getChildByName("TextTip"));
	auto tapTip = dynamic_cast<Sprite*>(layout->getChildByName("TapTip"));
	auto backColor = dynamic_cast<Sprite*>(layout->getChildByName("BackColor"));

	m_isPauseConnectListener = true;

	tapTip->setVisible(false);

	auto act1 = Animate::create(AnimationCache::getInstance()->getAnimation("WiFiConnect"));
	auto act2 = CallFunc::create([this, playerTip, wifi, textTip, playerID, backColor]()
	{
		if ((m_playerCount == 4 && playerID < 2) || (m_playerCount == 2 && playerID < 1))
		{
			backColor->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ui_connect_backcolor_red.png"));
		}
		else
		{
			backColor->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ui_connect_backcolor_green.png"));
		}

		textTip->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ui_text_tips_connected.png"));
		wifi->setVisible(false);
		m_connectedPlayerCount++;
		waitConnectPlayer(m_connectedPlayerCount);
		m_isPauseConnectListener = false;
		playerTip->stopAllActions();
		playerTip->runAction(ScaleTo::create(0.2f, 1));
	});

	wifi->stopAllActions();
	wifi->runAction(Sequence::create(act1, act2, nullptr));
}


//第几个玩家显示为未连接状态(0~3)
void ConnectUI::disconnectPlayer(int playerID)
{
	auto layout = m_connectPlayerLayouts.at(playerID);
	auto playerTip = dynamic_cast<Sprite*>(layout->getChildByName("PlayerTip"));
	auto wifi = dynamic_cast<Sprite*>(layout->getChildByName("WiFi"));
	auto textTip = dynamic_cast<Sprite*>(layout->getChildByName("TextTip"));

	textTip->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ui_text_tips_unconnected.png"));

	playerTip->stopAllActions();
	playerTip->runAction(ScaleTo::create(0.2f, 0));

	wifi->stopAllActions();
	wifi->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ui_wifi_1.png"));
	wifi->setVisible(true);

	m_connectedPlayerCount--;
}


//第几个玩家显示为等待连接状态(0~3)
void ConnectUI::waitConnectPlayer(int playerID, bool cancelWait)
{
	if (playerID >= m_playerCount)
	{
		m_startButton->setEnabled(true);
		return;
	}

	auto layout = m_connectPlayerLayouts.at(playerID);
	auto backColor = dynamic_cast<Sprite*>(layout->getChildByName("BackColor"));
	auto wifi = dynamic_cast<Sprite*>(layout->getChildByName("WiFi"));
	auto textTip = dynamic_cast<Sprite*>(layout->getChildByName("TextTip"));
	auto tapTip = dynamic_cast<Sprite*>(layout->getChildByName("TapTip"));

	if (!cancelWait)
	{
		textTip->setVisible(true);
		if (playerID != 0) tapTip->setVisible(true);

	}
	else
	{
		textTip->setVisible(false);
		tapTip->setVisible(false);

		if ((m_playerCount == 4 && playerID < 2) || (m_playerCount == 2 && playerID < 1))
		{
			backColor->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ui_connect_backcolor_red_gray.png"));
		}
		else
		{
			backColor->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ui_connect_backcolor_green_gray.png"));
		}
	}
}


//所有玩家显示为未连接状态
void ConnectUI::disconnectAllPlayers()
{
	for (int i = 0; i < m_playerCount; i++)
	{
		disconnectPlayer(i);
		waitConnectPlayer(i, true);
	}
	m_connectedPlayerCount = 0;
	m_isPauseConnectListener = true;
}


//创建一个玩家连接图
ui::Layout * ConnectUI::_createConnectPlayerLayout(int playerID)
{
	auto layout = Layout::create();
	layout->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	auto backColor = Sprite::createWithSpriteFrameName("ui_connect_backcolor_red_gray.png");
	backColor->setName("BackColor");
	backColor->setPosition(backColor->getContentSize()/2);
	layout->addChild(backColor, 0);
	layout->setContentSize(backColor->getContentSize());


	auto wifi = Sprite::createWithSpriteFrameName("ui_wifi_1.png");
	wifi->setName("WiFi");
	wifi->setPosition(Vec2(84, 84));
	layout->addChild(wifi, 1);

	auto textTip = Sprite::createWithSpriteFrameName("ui_text_tips_unconnected.png");
	textTip->setName("TextTip");
	textTip->setPosition(Vec2(84, -31));
	layout->addChild(textTip, 2);

	auto tapTip = Sprite::createWithSpriteFrameName("ui_tap_tips.png");
	tapTip->setName("TapTip");
	tapTip->setPosition(Vec2(84, 84));
	layout->addChild(tapTip, 2);

	Sprite * playerTip = nullptr;

	if (playerID == 1 && m_playerCount == 4)
	{
		playerTip = Sprite::createWithSpriteFrameName("ui_p2_red.png");
	}
	else
	{
		playerTip = Sprite::createWithSpriteFrameName(StringUtils::format("ui_p%d.png", playerID + 1));
	}

	playerTip->setName("PlayerTip");
	playerTip->setPosition(Vec2(85, 79));
	playerTip->setScale(0);
	layout->addChild(playerTip, 2);

	return layout;
}


//是否激活连接侦听与显示
void ConnectUI::activeConnectingListenerAndShow(bool active)
{
	if (active)
	{
		m_startButton->setEnabled(false);
		setVisible(true);

		disconnectAllPlayers();
		waitConnectPlayer(0);

		m_uiLayer->setScale(0);
		auto act1 = EaseElasticOut::create(ScaleTo::create(0.5f, 1));
		auto act2 = CallFunc::create([this]()
		{
			m_reconnectButton->setEnabled(true);
			m_closeButton->setEnabled(true);
			connectPlayer(0);
			scheduleUpdate();
		});
		m_uiLayer->runAction(Sequence::create(act1, act2, nullptr));
	}
	else
	{
		unscheduleUpdate();
		m_startButton->setEnabled(false);
		m_reconnectButton->setEnabled(false);
		m_closeButton->setEnabled(false);

		auto act1 = ScaleTo::create(0.2f, 0);
		auto act2 = CallFunc::create([this]()
		{
			disconnectAllPlayers();
			setVisible(false);
		});
		m_uiLayer->runAction(Sequence::create(act1, act2, nullptr));
	}
}


//设置关闭按钮回调
void ConnectUI::setCloseButtonCallback(const std::function<void(Ref*)> & callback)
{
	m_closeButton->setCallback(callback);
}


//设置开始按钮回调
void ConnectUI::setStartButtonCallback(const std::function<void(Ref*)> & callback)
{
	m_startButton->setCallback(callback);
}


//设置重新连接的回调
void ConnectUI::setReconnectButtonCallback(const std::function<void(Ref*)> & callback)
{
	m_reconnectButton->setCallback(callback);
}

//设置触发连接侦听的函数(玩家ID，是否执行空循环）
void ConnectUI::setTriggerConnectCallback(const std::function<int(int, bool)> & callback)
{
	m_triggerConnectCallback = callback;
}


//连接侦听
void ConnectUI::update(float dt)
{
	if (m_connectedPlayerCount >= m_playerCount)
	{
		m_isPauseConnectListener = true;
		return;
	}

	auto listenerResult = m_triggerConnectCallback(m_connectedPlayerCount, (m_isPauseConnectListener || m_connectedPlayerCount >= m_playerCount));

	if (listenerResult == -1)
	{
		connectPlayer(m_connectedPlayerCount);
	}
	else if (listenerResult > 0)
	{
		shakePlayer(listenerResult);
	}
}


//是否显示遮罩层
void ConnectUI::setBlackBackVisible(bool visible)
{
	if (visible)
	{
		m_blackBack->setOpacity(255);
	}
	else
	{
		m_blackBack->setOpacity(0);
	}
}


//重新连接的回调
void ConnectUI::reconnect()
{
	m_startButton->setEnabled(false);
	disconnectAllPlayers();
	waitConnectPlayer(0);
	runAction(Sequence::create(DelayTime::create(0.2f), CallFunc::create([this](){connectPlayer(0); }), nullptr));
}


//震动玩家
void ConnectUI::shakePlayer(int playerID)
{
	if (m_isPauseConnectListener)
	{
		return;
	}

	auto playerLayout = m_connectPlayerLayouts.at(playerID);

	auto backColor = playerLayout->getChildByName("BackColor");

	auto palyerTip = playerLayout->getChildByName("PlayerTip");

	auto oriPos = Vec2(84.5f,84.5f);

	backColor->stopAllActions();
	backColor->runAction(Sequence::create(
		MoveTo::create(0.05f, oriPos + Vec2(0, random(-20, 20))),
		MoveTo::create(0.05f, oriPos + Vec2(0, 0)),
		MoveTo::create(0.05f, oriPos + Vec2(0, random(-15, 15))),
		MoveTo::create(0.05f, oriPos + Vec2(0, 0)),
		MoveTo::create(0.05f, oriPos + Vec2(0, random(-10, 10))),
		MoveTo::create(0.05f, oriPos + Vec2(0, 0)),
		MoveTo::create(0.05f, oriPos + Vec2(0, random(-5, 5))),
		MoveTo::create(0.05f, oriPos + Vec2(0, 0)),
		nullptr
		));
	backColor->runAction(Sequence::create(
		ScaleTo::create(0.05f, 1.15),
		ScaleTo::create(0.05f, 1),
		ScaleTo::create(0.05f, 1.08),
		ScaleTo::create(0.05f, 1),
		nullptr
		));

	palyerTip->runAction(Sequence::create(
		ScaleTo::create(0.05f, 1.15),
		ScaleTo::create(0.05f, 1),
		ScaleTo::create(0.05f, 1.08),
		ScaleTo::create(0.05f, 1),
		nullptr
		));
}
