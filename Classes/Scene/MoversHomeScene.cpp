#include "MoversHomeScene.h"
#include "Scene/BuildingScene.h"
#include "ui/CocosGUI.h"
#include "GlobalUtils/UIPC_Loader.h"
using namespace ui;

// there's no 'id' in cpp, so we recommend returning the class instance pointer
Scene* MoversHomeScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MoversHomeScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

void MoversHomeScene::swapCloud(float dt)
{
	auto cloud = Sprite::create();
	cloud->setSpriteFrame("world_home_cloud.png");
	if (random(0, 1) == 1) cloud->setFlippedX(true);
	cloud->setPosition(10 * random(-32, 192), 10 * random(0, 110));
	addChild(cloud, 2);
	cloud->setOpacity(0);
	cloud->runAction(FadeTo::create(4, 255));
	cloud->runAction(Sequence::create(
		MoveBy::create(random(28, 36), Vec2(2340, 0)),
		RemoveSelf::create(),
		NULL
		));
}

void moversVoidStartGame(void *obj)
{
	((MoversHomeScene*)obj)->goToGame(1);
}

void buttonShowAbout(void *obj)
{
	((MoversHomeScene*)obj)->showAbout();
}

void buttonShowRecoed(void *obj)
{
	((MoversHomeScene*)obj)->showRecord();
}

// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
bool MoversHomeScene::init()
{
	if (!Layer::init()) return false;

	GameInfo::loadMoney();
	GameInfo::loadModeUnlock();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile(WORLD_MOVERS_CAR_PLI, createTexture(WORLD_MOVERS_CAR_BIG));
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile(WORLD_MOVERS_HWORLD_PLI, createTexture(WORLD_MOVERS_HWORLD_BIG));


	addBackWorld();


	////////////////////
	inOption = false;
	inMenu = true;
	_bv = 0.3f;
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_EFFECT_BUTTON);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_EFFECT_ZOOM_IN);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_EFFECT_ZOOM_OUT);

	uiHolder = Node::create();
	uiHolder->setContentSize(visibleSize);
	addChild(uiHolder, 40);

	//检查MiniStation库加载情况
	if (!UIPC_Loader::loader_open_finished)
	{
		auto warnning = Label::create();
		warnning->setString("Compatible Mode");
		warnning->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
		warnning->setPosition(Vec2(visibleSize.width,0));
		addChild(warnning,39);
	}

	auto about = Sprite::createWithSpriteFrameName("home_aboutxq.png");
	about->setScale(1.8f);
	about->setPosition(visibleSize.width + 1010, 532);
	uiHolder->addChild(about);

	auto title = Sprite::createWithSpriteFrameName("home_logo.png");
	title->setPosition(1369, 832);
	uiHolder->addChild(title);

	buttonGame = PushButtonZoomimng::createByFrameName("home_bt_single.png");
	buttonGame->setPosition(Vec2(1165, 469));
	uiHolder->addChild(buttonGame, 2);
	buttonGame->setPressReleaseCallBack(std::bind(&MoversHomeScene::goToGame, this, 1));

	/*---by Azure-------------------*/
	buttonGame2 = PushButtonZoomimng::createByFrameName("home_bt_double.png");
	buttonGame2->setPosition(Vec2(1596, 469));
	uiHolder->addChild(buttonGame2, 2);
	buttonGame2->setPressReleaseCallBack(std::bind(&MoversHomeScene::goToGame, this, 2));


	buttonBack = PushButton::createByFrameName("home_bt_return.png");
	buttonBack->setPosition(1373, 183);
	uiHolder->addChild(buttonBack, 1);
	buttonBack->setPressReleaseCallBack(std::bind(&MoversHomeScene::backHome, this));
	buttonBack->lockButton();
	buttonBack->setScale(0);


	buttonMod1 = PushButtonZoomimng::createByFrameName("home_bt_match.png");
	buttonMod1->setPosition(Vec2(1373, 469));
	uiHolder->addChild(buttonMod1, 1);
	buttonMod1->setPressReleaseCallBack([this](){BuildingScene::setGameMode(0); popConnectUI(); });
	buttonMod1->lockButton();
	buttonMod1->setScale(0);

	buttonMod2 = PushButtonZoomimng::createByFrameName("home_bt_multi.png");
	buttonMod2->setPressReleaseCallBack([this](){BuildingScene::setGameMode(1); popConnectUI(); });
	buttonMod2->setPosition(Vec2(1023, 469));
	uiHolder->addChild(buttonMod2, 1);
	buttonMod2->lockButton();
	buttonMod2->setScale(0);

	buttonMod3 = PushButtonZoomimng::createByFrameName("home_bt_four.png");
	buttonMod3->setPressReleaseCallBack([this](){BuildingScene::setGameMode(2); popConnectUI(); });
	buttonMod3->setPosition(Vec2(1727, 469));
	uiHolder->addChild(buttonMod3, 1);
	buttonMod3->lockButton();
	buttonMod3->setScale(0);

	buttonAbout = PushButton::createByFrameName("home_bt_about.png");
	buttonAbout->setPosition(593, 891);
	uiHolder->addChild(buttonAbout, 2);
	buttonAbout->setPressReleaseCallBack(std::bind(&MoversHomeScene::showAbout, this));

	buttonRecord = PushButton::createByFrameName("home_bt_record.png");
	buttonRecord->setPosition(262, 871);
	uiHolder->addChild(buttonRecord, 2);
	buttonRecord->setPressReleaseCallBack(std::bind(&MoversHomeScene::showRecord, this));

	addHighScoreUI();
	addConnectUI();

	/**/
	_listener = EventListenerTouchOneByOne::create();
	// 注册触摸监听
	_listener = EventListenerTouchOneByOne::create();
	_listener->onTouchBegan = CC_CALLBACK_2(MoversHomeScene::onTouchBegan, this);
	_listener->onTouchEnded = CC_CALLBACK_2(MoversHomeScene::onTouchEnded, this);
	_listener->setSwallowTouches(true);//不向下传递触摸
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listener, this);

	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.3f);
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(movers_bgm_home, true);

	auto ourInfo = Sprite::create("xchange_soft_ltd.pvr.ccz");
	ourInfo->setPosition(Vec2(960, 12));
	addChild(ourInfo, 9);

	auto curVersion = Sprite::create("version_code_current.pvr.ccz");
	curVersion->setPosition(origin + Vec2(4 + curVersion->getContentSize().width / 2, visibleSize.height - 4 - curVersion->getContentSize().height / 2));
	addChild(curVersion, 9);

	return true;
}


//添加背景图
void MoversHomeScene::addBackWorld()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();


	//天空背景
	auto _sky = Sprite::createWithSpriteFrameName("home_sky_bg1.png");
	_sky->setAnchorPoint(Vec2::ZERO);
	_sky->setScale(visibleSize.width / _sky->getContentSize().width, visibleSize.height / _sky->getContentSize().height);
	addChild(_sky, 1);

	//背景圈
	auto _circle = Sprite::create(WORLD_SKY_CIRCLE_BIG);
	_circle->setPosition(Vec2(visibleSize.width / 2, visibleSize.height + 200));
	_circle->setScale(1.25f);
	addChild(_circle, 2);
	_circle->runAction(RepeatForever::create(RotateBy::create(1.0, Vec3(0, 0, -60))));

	//公路背景承载
	downHolder = Node::create();
	addChild(downHolder, 3);

	//公路背景
	auto glbg1 = Sprite::createWithSpriteFrameName("home_gonglu_bg1.png");
	glbg1->setAnchorPoint(Vec2::ZERO);
	glbg1->setScaleX(visibleSize.width / glbg1->getContentSize().width);
	downHolder->addChild(glbg1, 0);

	//卡车
	_car = MoversTruck::create();
	addChild(_car, 5);
	_car->setPosition(511, 261);


	//背景草树云的移动
	for (int i = -500; i <= 4000; i += 400)
	{
		landGrass1(i);
	}

	for (int i = -500; i <= 4000; i += 800)
	{
		landGrass2(i);
	}

	for (int i = -1000; i <= 4000; i += 800)
	{
		landMountain(i);
	}

	swapCloud();
	swapCloud();
	swapCloud();
	swapCloud();
	swapCloud();
	swapCloud();

	schedule(schedule_selector(MoversHomeScene::loodGrass1), 0.75f);
	schedule(schedule_selector(MoversHomeScene::loodGrass2), 1);
	schedule(schedule_selector(MoversHomeScene::loodMountain), 5);
	schedule(schedule_selector(MoversHomeScene::swapCloud), 2);

}

//添加高分计数面板UI
void MoversHomeScene::addHighScoreUI()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto ui = Layer::create();
	ui->setContentSize(visibleSize);
	ui->setPosition(uiHolder->convertToNodeSpace(Vec2(-visibleSize.width, 0)));
	uiHolder->addChild(ui);

	Vector<Sprite*> panelList;

	panelList.pushBack(Sprite::createWithSpriteFrameName("history_single_panel.png"));
	panelList.back()->setPosition(Vec2(328 + 300, 568));
	ui->addChild(panelList.back());

	//panelList.pushBack(Sprite::createWithSpriteFrameName("history_match_panel.png"));
	//panelList.back()->setPosition(Vec2(957, 568));
	//ui->addChild(panelList.back());

	panelList.pushBack(Sprite::createWithSpriteFrameName("history_multi_panel.png"));
	panelList.back()->setPosition(Vec2(1592 - 300, 568));
	ui->addChild(panelList.back());


	Vector<LabelAtlas*> tempAtlas;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			tempAtlas.pushBack(LabelAtlas::create("0123456789", MOVERS_HOME_PAGE_ATLAS, 29, 37, '0'));
			tempAtlas.back()->setAnchorPoint(Vec2::ZERO);
			tempAtlas.back()->setScale(1.7f);
			panelList.at(i)->addChild(tempAtlas.back());
		}
	}

	auto ud = UserDefault::getInstance();

	tempAtlas.at(0)->setString(Value(ud->getIntegerForKey("MOVERS_HIGH_FLOOR", 0)).asString());
	tempAtlas.at(1)->setString(Value(ud->getIntegerForKey("MOVERS_HIGH_GOODS", 0)).asString());
	tempAtlas.at(2)->setString(Value(ud->getIntegerForKey("MOVERS_HIGH_BOMB", 0)).asString());
	tempAtlas.at(3)->setString(Value(ud->getIntegerForKey("MOVERS_HIGH_SCORE", 0)).asString());

	tempAtlas.at(0)->setPosition(Vec2(72, 574));
	tempAtlas.at(1)->setPosition(Vec2(72, 402));
	tempAtlas.at(2)->setPosition(Vec2(72, 228));
	tempAtlas.at(3)->setPosition(Vec2(72, 53));


	tempAtlas.at(4)->setString(Value(ud->getIntegerForKey("M1MOVERS_HIGH_FLOOR", 0)).asString());
	tempAtlas.at(5)->setString(Value(ud->getIntegerForKey("M1MOVERS_HIGH_GOODS", 0)).asString());
	tempAtlas.at(6)->setString(Value(ud->getIntegerForKey("M1MOVERS_HIGH_BOMB", 0)).asString());
	tempAtlas.at(7)->setString(Value(ud->getIntegerForKey("M1MOVERS_HIGH_SCORE", 0)).asString());

	tempAtlas.at(4)->setPosition(Vec2(72, 574));
	tempAtlas.at(5)->setPosition(Vec2(72, 402));
	tempAtlas.at(6)->setPosition(Vec2(72, 228));
	tempAtlas.at(7)->setPosition(Vec2(72, 53));
}


void MoversHomeScene::unlockMode()
{
	GameInfo::unlockMode(1);
	buttonMod2->setFrameNormal("home_bt_mode2.png");
	buttonMod2->setFrameNormal("home_bt_mode2.png");
	buttonMod2->setPressDownCallBack(std::bind(&MoversHomeScene::goToGame2, this));

	auto visibleSize = Director::getInstance()->getVisibleSize();

	//auto flag = Sprite::createWithSpriteFrameName( "cd_gmcg.png" );
	//addChild( flag , 20 );
	//flag->setPosition( visibleSize.width / 2  , -100 );
	//flag->runAction( Sequence::create( 
	//	EaseSineOut::create( MoveBy::create( 0.4 , Vec2( 0 , visibleSize.height / 2 + 100 ) ) ) ,
	//	MoveBy::create( 0.2 , Vec2( 0 , 0 ) ) ,
	//	EaseSineIn::create( MoveBy::create( 0.4 , Vec2( 0 , visibleSize.height / 2 + 100 ) ) ) ,
	//	CallFunc::create( std::bind( &Node::removeChild , this , flag , true ) ) ,
	//	NULL ) );
}

void MoversHomeScene::intoGame()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

	doIntoGame();
}

void MoversHomeScene::intoMod1()
{
	if (_playerCount > 1)
	{
		if (BuildingScene::getGameMode() == 2)
		{
			GameInfo::getInstance()->switchGameMode(3);
		}
		else
		{
			GameInfo::getInstance()->switchGameMode(2);
		}
	}
	else
	{
		GameInfo::getInstance()->switchGameMode(0);
	}


	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, BuildingScene::createSceneWithStory(_playerCount)));
}

void MoversHomeScene::intoMod2()
{
	GameInfo::getInstance()->switchGameMode(1);
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, BuildingScene::createSceneWithStory(1)));
}

void MoversHomeScene::blackScreen()
{
	schedule(schedule_selector(MoversHomeScene::subBgmV));
	auto _black = LayerColor::create();
	addChild(_black, 20);
	_black->setOpacity(0);
	_black->runAction(Sequence::create(
		FadeTo::create(0.25, 255),
		FadeTo::create(0.05, 255),
		CallFuncN::create(CC_CALLBACK_0(MoversHomeScene::intoGame, this)),
		NULL
		));
}

void MoversHomeScene::goToGame(int playerCount)
{
	buttonGame->lockButton();
	buttonGame2->lockButton();
	buttonAbout->lockButton();
	buttonRecord->lockButton();
	buttonBack->lockButton();
	buttonMod1->lockButton();
	buttonMod2->lockButton();
	buttonMod3->lockButton();

	if (playerCount == 1)
	{
		_playerCount = 1;
		runAction(Sequence::create(CallFunc::create(std::bind(&MoversHomeScene::goToGame1, this)), nullptr));
		return;
	}

	_playerCount = 2;

	buttonBack->runAction(Sequence::create(
		ScaleTo::create(0.2f, 1),
		CallFuncN::create(CC_CALLBACK_0(PushButton::unlockButton, buttonBack)),
		NULL));

	buttonMod1->runAction(Sequence::create(
		ScaleTo::create(0.2f, 1),
		CallFuncN::create(CC_CALLBACK_0(PushButton::unlockButton, buttonMod1)),
		NULL));

	buttonMod2->runAction(Sequence::create(
		ScaleTo::create(0.2f, 1),
		CallFuncN::create(CC_CALLBACK_0(PushButton::unlockButton, buttonMod2)),
		NULL));

	buttonMod3->runAction(Sequence::create(
		ScaleTo::create(0.2f, 1),
		CallFuncN::create(CC_CALLBACK_0(PushButton::unlockButton, buttonMod3)),
		NULL));

	buttonGame->runAction(ScaleTo::create(0.2f, 0));
	((PushButtonZoomimng*)buttonGame2)->_isNoGoNormal = true;
	buttonGame2->runAction(ScaleTo::create(0.2f, 0));
	buttonAbout->runAction(ScaleTo::create(0.2f, 0));
	buttonRecord->runAction(ScaleTo::create(0.2f, 0));
}

void MoversHomeScene::goToGame1()
{
	BuildingScene::setGameMode(0);
	buttonBack->lockButton();
	buttonMod1->lockButton();
	buttonMod2->lockButton();
	buttonMod3->lockButton();

	doIntoGame = std::bind(&MoversHomeScene::intoMod1, this);

	uiHolder->runAction(MoveBy::create(0.2f, Vec2(0, 1080)));
	_car->runAction(Sequence::create(
		//EaseElasticInOut::create( MoveBy::create( 3.0 , Vec2( -640 , 0 ) ) ) ,
		MoveBy::create(1.0f, Vec2(-1920, 0)),
		CallFunc::create(CC_CALLBACK_0(MoversHomeScene::blackScreen, this)),
		NULL
		));
}

void MoversHomeScene::goToGame2()
{
	BuildingScene::setGameMode(1);
	buttonBack->lockButton();
	buttonMod1->lockButton();
	buttonMod2->lockButton();
	buttonMod3->lockButton();
	doIntoGame = std::bind(&MoversHomeScene::intoMod2, this);
	uiHolder->runAction(MoveBy::create(0.2f, Vec2(0, 1080)));
	_car->runAction(Sequence::create(
		//EaseElasticInOut::create( MoveBy::create( 3.0 , Vec2( -640 , 0 ) ) ) ,
		MoveBy::create(1.0f, Vec2(-1920, 0)),
		CallFunc::create(CC_CALLBACK_0(MoversHomeScene::blackScreen, this)),
		NULL
		));
}


void MoversHomeScene::goToGame3()
{
	BuildingScene::setGameMode(2);
	buttonBack->lockButton();
	buttonMod1->lockButton();
	buttonMod2->lockButton();
	buttonMod3->lockButton();
	doIntoGame = std::bind(&MoversHomeScene::intoMod1, this);
	uiHolder->runAction(MoveBy::create(0.2f, Vec2(0, 1080)));
	_car->runAction(Sequence::create(
		//EaseElasticInOut::create( MoveBy::create( 3.0 , Vec2( -640 , 0 ) ) ) ,
		MoveBy::create(1.0f, Vec2(-1920, 0)),
		CallFunc::create(CC_CALLBACK_0(MoversHomeScene::blackScreen, this)),
		NULL
		));
}

void MoversHomeScene::backHome()
{
	buttonGame->lockButton();
	buttonGame2->lockButton();
	buttonAbout->lockButton();
	buttonRecord->lockButton();
	buttonBack->lockButton();
	buttonMod1->lockButton();
	buttonMod2->lockButton();
	buttonMod3->lockButton();

	buttonGame->runAction(Sequence::create(
		ScaleTo::create(0.2f, 1),
		CallFuncN::create(CC_CALLBACK_0(PushButton::unlockButton, buttonGame)),
		NULL));

	buttonGame2->runAction(Sequence::create(
		ScaleTo::create(0.2f, 1),
		CallFuncN::create(CC_CALLBACK_0(PushButton::unlockButton, buttonGame2)),
		NULL));

	buttonAbout->runAction(Sequence::create(
		ScaleTo::create(0.2f, 1),
		CallFuncN::create(CC_CALLBACK_0(PushButton::unlockButton, buttonAbout)),
		NULL));

	buttonRecord->runAction(Sequence::create(
		ScaleTo::create(0.2f, 1),
		CallFuncN::create(CC_CALLBACK_0(PushButton::unlockButton, buttonRecord)),
		NULL));

	buttonBack->runAction(ScaleTo::create(0.2f, 0));
	buttonMod1->runAction(ScaleTo::create(0.2f, 0));
	buttonMod2->runAction(ScaleTo::create(0.2f, 0));
	buttonMod3->runAction(ScaleTo::create(0.2f, 0));
}
void MoversHomeScene::loodGrass1(float dt)
{
	landGrass1(-300);
}

void MoversHomeScene::landGrass1(float PX)
{
	auto grass = Sprite::create();//Sprite::createWithSpriteFrameName( "home_guanmu1.png" );
	grass->setSpriteFrame("home_guanmu1.png");

	grass->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	grass->setPositionY(230);

	grass->setPositionX(PX - random(950, 1040));
	if (random(0, 1) == 1) grass->setFlippedX(true);
	if (random(0, 1) == 0)
	{
		auto tree = Sprite::create();
		tree->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		tree->setPositionY(230);
		downHolder->addChild(tree, 5);
		if (random(0, 1) == 0) tree->setSpriteFrame("home_shu1a.png");
		else tree->setSpriteFrame("home_shu1b.png");
		tree->setPositionX(PX - random(880, 1160));
		tree->runAction(Sequence::create(
			MoveBy::create(9, Vec2(5000, 0)),
			RemoveSelf::create(),
			NULL
			));
	}

	downHolder->addChild(grass, 5);
	grass->runAction(Sequence::create(
		MoveBy::create(9, Vec2(5000, 0)),
		RemoveSelf::create(),
		NULL
		));
}

///////////////////////////////////////////////////////////////////

void MoversHomeScene::loodGrass2(float dt)
{
	landGrass2(-300);
}

void MoversHomeScene::landGrass2(float PX)
{
	auto grass = Sprite::create();//Sprite::createWithSpriteFrameName( "home_guanmu1.png" );
	grass->setSpriteFrame("home_guanmu2.png");

	grass->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	grass->setPositionY(267);

	grass->setPositionX(PX - random(950, 1040));
	if (random(0, 1) == 1) grass->setFlippedX(true);
	if (random(0, 1) == 0)
	{
		auto tree = Sprite::create();
		tree->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		tree->setPositionY(267);
		downHolder->addChild(tree, 3);
		if (random(0, 1) == 0) tree->setSpriteFrame("home_shu2a.png");
		else tree->setSpriteFrame("home_shu2b.png");
		tree->setPositionX(PX - random(880, 1160));
		tree->runAction(Sequence::create(
			MoveBy::create(18, Vec2(5000, 0)),
			RemoveSelf::create(),
			NULL
			));
	}


	downHolder->addChild(grass, 4);
	grass->runAction(Sequence::create(
		MoveBy::create(18, Vec2(5000, 0)),
		RemoveSelf::create(),
		NULL
		));
}

///////////////////////////////////////////

void MoversHomeScene::loodMountain(float dt)
{
	landMountain(-400);
}

void MoversHomeScene::landMountain(float PX)
{
	auto mt = Sprite::create();
	mt->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	mt->setPositionY(230);

	switch (random(0, 2))
	{
	default: break;
	case 0: mt->setSpriteFrame("home_shan1a.png"); break;
	case 1: mt->setSpriteFrame("home_shan1b.png"); break;
	case 2: mt->setSpriteFrame("home_shan1c.png"); break;
	}
	if (random(0, 1) == 1) mt->setFlippedX(true);
	mt->setPositionX(PX - random(928, 1184));
	downHolder->addChild(mt, 2);
	mt->runAction(Sequence::create(
		MoveBy::create(38, Vec2(4000, 0)),
		RemoveSelf::create(),
		NULL
		));

	//////////////////////

	mt = Sprite::create();
	mt->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	mt->setPositionY(230);
	switch (random(0, 1))
	{
	default: break;
	case 0: mt->setSpriteFrame("home_shan2a.png"); break;
	case 1: mt->setSpriteFrame("home_shan2b.png"); break;
	}
	if (random(0, 1) == 1) mt->setFlippedX(true);
	mt->setPositionX(PX - random(928, 1184));
	downHolder->addChild(mt, 1);
	mt->runAction(Sequence::create(
		MoveBy::create(48, Vec2(4000, 0)),
		RemoveSelf::create(),
		NULL
		));
}

void MoversHomeScene::subBgmV(float dt)
{
	_bv -= 0.03;
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(_bv);
}

bool MoversHomeScene::onTouchBegan(Touch *touch, Event *event)
{
	return true;
}

void MoversHomeScene::onTouchEnded(Touch *touch, Event *event)
{
	hideOptions();
}

void MoversHomeScene::onExit()
{
	Layer::onExit();
	Director::getInstance()->getEventDispatcher()->removeEventListener(_listener);
	TextureCache::getInstance()->removeUnusedTextures();
}

void MoversHomeScene::showRecord()
{
	if (inMenu)
	{
		inMenu = false;
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SOUND_EFFECT_ZOOM_IN);
		uiHolder->runAction(Sequence::create(
			MoveBy::create(0.1, Vec2(1920, 0)),
			CallFunc::create(CC_CALLBACK_0(MoversHomeScene::confirmAbout, this)),
			NULL
			));
	}
}

void MoversHomeScene::showAbout()
{
	if (inMenu)
	{
		inMenu = false;
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SOUND_EFFECT_ZOOM_IN);
		uiHolder->runAction(Sequence::create(
			MoveBy::create(0.1, Vec2(-1920, 0)),
			CallFunc::create(CC_CALLBACK_0(MoversHomeScene::confirmAbout, this)),
			NULL
			));
	}
}

void MoversHomeScene::hideOptions()
{
	if (inOption)
	{
		inOption = false;
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SOUND_EFFECT_ZOOM_OUT);
		int px = 1920;
		if (uiHolder->getPositionX() > 1920 / 2) px = -px;
		uiHolder->runAction(Sequence::create(
			MoveBy::create(0.1, Vec2(px, 0)),
			CallFunc::create(CC_CALLBACK_0(MoversHomeScene::confirmMenu, this)),
			NULL
			));
	}
}


//添加连接UI
void MoversHomeScene::addConnectUI()
{
	_connectUI_2 = ConnectUI::create();
	_connectUI_2->initWithDoublePlayers();
	_connectUI_2->setVisible(false);
	_connectUI_2->setBlackBackVisible(false);

	_connectUI_2->setCloseButtonCallback(std::bind(&MoversHomeScene::closeConnectUI, this, std::placeholders::_1));
	_connectUI_2->setStartButtonCallback(std::bind(&MoversHomeScene::startGameButtonCallback, this, std::placeholders::_1));
	_connectUI_2->setReconnectButtonCallback(std::bind(&MoversHomeScene::reconnectForConnectUI, this, std::placeholders::_1));
	_connectUI_2->setTriggerConnectCallback(std::bind(&MoversHomeScene::connectListener, this, std::placeholders::_1, std::placeholders::_2));

	uiHolder->addChild(_connectUI_2,60);

	_connectUI_4 = ConnectUI::create();
	_connectUI_4->initWithFourPlayers();
	_connectUI_4->setVisible(false);
	_connectUI_4->setBlackBackVisible(false);

	_connectUI_4->setCloseButtonCallback(std::bind(&MoversHomeScene::closeConnectUI, this, std::placeholders::_1));
	_connectUI_4->setStartButtonCallback(std::bind(&MoversHomeScene::startGameButtonCallback, this, std::placeholders::_1));
	_connectUI_4->setReconnectButtonCallback(std::bind(&MoversHomeScene::reconnectForConnectUI, this, std::placeholders::_1));
	_connectUI_4->setTriggerConnectCallback(std::bind(&MoversHomeScene::connectListener, this, std::placeholders::_1, std::placeholders::_2));

	uiHolder->addChild(_connectUI_4, 60);

	_connectUI = _connectUI_2;
}



//弹出连接界面
void MoversHomeScene::popConnectUI()
{
	clearListenerBuffer();

	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SOUND_EFFECT_ZOOM_IN);

	BuildingScene::getPlayersIDMap()->clear();

	buttonBack->lockButton();
	buttonMod1->lockButton();
	buttonMod2->lockButton();
	buttonMod3->lockButton();

	buttonBack->runAction(ScaleTo::create(0.2f, 0));
	buttonMod1->runAction(ScaleTo::create(0.2f, 0));
	
	buttonMod2->runAction(ScaleTo::create(0.2f, 0));
	
	buttonMod3->runAction(ScaleTo::create(0.2f, 0));
	

	if (BuildingScene::getGameMode() == 2)
	{
		_connectUI = _connectUI_4;
		((PushButtonZoomimng*)buttonMod3)->_isNoGoNormal = true;
	}
	else
	{
		_connectUI = _connectUI_2;

		if (BuildingScene::getGameMode() == 1)
		{
			((PushButtonZoomimng*)buttonMod2)->_isNoGoNormal = true;
		}
		else
		{
			((PushButtonZoomimng*)buttonMod1)->_isNoGoNormal = true;
		}
	}

	_connectUI->activeConnectingListenerAndShow(true);
}


//关闭连接界面
void MoversHomeScene::closeConnectUI(Ref * ref)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SOUND_EFFECT_ZOOM_OUT);

	_connectUI->activeConnectingListenerAndShow(false);

	buttonBack->runAction(Sequence::create(
		ScaleTo::create(0.2f, 1),
		CallFuncN::create(CC_CALLBACK_0(PushButton::unlockButton, buttonBack)),
		NULL));

	buttonMod1->runAction(Sequence::create(
		ScaleTo::create(0.2f, 1),
		CallFuncN::create(CC_CALLBACK_0(PushButton::unlockButton, buttonMod1)),
		NULL));

	buttonMod2->runAction(Sequence::create(
		ScaleTo::create(0.2f, 1),
		CallFuncN::create(CC_CALLBACK_0(PushButton::unlockButton, buttonMod2)),
		NULL));

	buttonMod3->runAction(Sequence::create(
		ScaleTo::create(0.2f, 1),
		CallFuncN::create(CC_CALLBACK_0(PushButton::unlockButton, buttonMod3)),
		NULL));
}


//开始游戏回调
void MoversHomeScene::startGameButtonCallback(Ref * ref)
{
	_connectUI->activeConnectingListenerAndShow(false);

	if (BuildingScene::getGameMode() == 0)
	{
		goToGame1();
	}

	if (BuildingScene::getGameMode() == 1)
	{
		goToGame2();
	}

	if (BuildingScene::getGameMode() == 2)
	{
		goToGame3();
	}
	
}


//重新连接回调
void MoversHomeScene::reconnectForConnectUI(Ref * ref)
{
	BuildingScene::getPlayersIDMap()->clear();

	_connectUI->reconnect();
}


//连接侦听回调
int MoversHomeScene::connectListener(int playerID,bool isEmptyLoops)
{
	auto m = BuildingScene::getPlayersIDMap();

	static int out_player_id = -1;
	static int out_dev_id = -1;
	static int out_type_id = -1;
	static const int out_buff_size = 512;
	static int out_buff[out_buff_size];

	if (UIPC_Loader::uipc_receiver_poll_event(&out_dev_id, &out_type_id, out_buff, out_buff_size) != -1)
	{
		if (isEmptyLoops)
		{
			return false;
		}
		if (((out_type_id == 0x8003 || out_type_id == 0x8002) && *out_buff == 0) || ((out_type_id == 0x8012 && out_buff[0] == 0) || (out_type_id == 0x8012 && out_buff[0] == 0xffffffff && out_buff[1] == 0)))
		{
			auto iter = m->find(out_dev_id);
			if (iter == m->end())
			{
				m->insert(std::make_pair(out_dev_id,playerID));
				return -1;
			}
			else
			{
				return iter->second;
			}
		}
	}

	return -2;
}


//清除侦听Buffer
void MoversHomeScene::clearListenerBuffer()
{
	static int out_dev_id = -1;
	static int out_type_id = -1;
	static int out_buff[512];

	for (int i = 0; i <= 255;i++)
	{
		UIPC_Loader::uipc_receiver_poll_event(&out_dev_id, &out_type_id, out_buff, 512);
	}
}
