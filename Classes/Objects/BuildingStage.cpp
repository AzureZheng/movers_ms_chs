#include "BuildingStage.h"
#include "FilePathDefine.h"
#include "Info/GameInfo.h"

#define SET_CLOTH_TYPE_B( _sprite ) switch( random( 0 , 3 ) ){ default: break; case 0: _sprite = Sprite::createWithSpriteFrameName( "building_obj_cloth_01.png" );break; case 1: _sprite = Sprite::createWithSpriteFrameName( "building_obj_cloth_02.png" );break; case 2: _sprite = Sprite::createWithSpriteFrameName( "building_obj_cloth_03.png" );break; case 3: _sprite = Sprite::createWithSpriteFrameName( "building_obj_cloth_04.png" );break; }

#define SET_CLOTH_MOTION_B( _sprite ) _sprite->runAction( RepeatForever::create( Sequence::create( RotateTo::create( ((float)random( 10 , 20 ))/10.0f , random( 5 , 10 ) ), RotateTo::create( ((float)random( 10 , 20 ))/10.0f , -random( 2 , 5 ) ), NULL ) ) )

//��ʼ��¥��
bool BuildingStage::init()
{
	if (!Node::init())
	{
		return false;
	}

	//�ڼ���
	m_floorIndex = 0;

	//������
	m_lines = nullptr;

	//¥����
	m_floorBoard = nullptr;

	//¥���
	m_stageSides[0] = nullptr;
	m_stageSides[1] = nullptr;

	//���ӳ��ֵ�λ��
	m_rabbitSide = 0;

	return true;
}


//����һ����ͨ��
BuildingStage * BuildingStage::createNormalFloor(int floorIndex)
{
	auto bs = BuildingStage::create();

	bs->m_floorIndex = floorIndex;
	bs->initNormalStage();
	return bs;
}

//����һ����һ��
BuildingStage * BuildingStage::createFirstFloor(bool noLeft)
{
	auto bs = BuildingStage::create();

	bs->m_floorIndex = 1;
	bs->initFirstStage(noLeft);
	return bs;
}

//��ȡ��������ʵ��(0:��;1:��)
RabbitHamal * BuildingStage::getSideRabbit(int side)
{
	return m_stageSides[side]->getRabbit();
}


//��ȡ¥��ʵ��(0:��;1:��)
StageSide * BuildingStage::getStageSide(int side)
{
	return m_stageSides[side];
}


//��ȡ¥��߶�
Size BuildingStage::getStageSize()
{
	return m_stageSize;
}


//��ʼ��һ����ͨ��
void BuildingStage::initNormalStage()
{
	//����¥���
	if (GameInfo::getInstance()->getModeCode() == "A1" || GameInfo::getInstance()->getModeCode() == "A2")
	{
		m_stageSides[0] = StageSide::createWithType(0);
		m_stageSides[1] = StageSide::createWithType(1);
	}
	else
	{
		m_stageSides[0] = StageSide::createWithType(4);
		m_stageSides[1] = StageSide::createWithType(5);
	}

	m_stageSides[0]->setPositionX(313);
	m_stageSides[1]->setPositionX(-313);

	addChild(m_stageSides[0], 0);
	addChild(m_stageSides[1], 0);

	m_stageSize = m_stageSides[0]->getWallSize();
	m_stageSize.height = BUILDING_STAGE_H;

	addFloorBoard();
	addFloorLine();

	if (GameInfo::getInstance()->getHighFloor() == m_floorIndex)
	{
		addHighFloorMark();
	}
}


//��ʼ����һ��
void BuildingStage::initFirstStage(bool noLeft)
{
	//����¥���
	m_stageSides[0] = StageSide::createWithType(2);
	m_stageSides[1] = StageSide::createWithType(3);
	m_stageSides[0]->setPositionX(313+173);
	m_stageSides[1]->setPositionX(-313 - 173);
	m_stageSides[0]->addChild(Sprite::createWithSpriteFrameName("building_first_floor.png"), 0);
	if (!noLeft) m_stageSides[1]->addChild(Sprite::createWithSpriteFrameName("building_first_floor.png"), 0);
	addChild(m_stageSides[0], 0);
	addChild(m_stageSides[1], 0);

	m_stageSize.height = 476;
}


//����¥���С
void BuildingStage::setStageSize(Size stageHeight)
{
	m_stageSize = stageHeight;
}


//���¥����
void BuildingStage::addFloorBoard()
{
	m_floorBoard = Sprite::createWithSpriteFrameName("building_obj_floor.png");
	m_floorBoard->setPosition(-12,-30);
	addChild(m_floorBoard,1);

	auto floor = LabelAtlas::create("0123456789:", NUMBER_BUILDING_FLOOR, 20, 28, '0');
	floor->setString(Value(m_floorIndex).asString() + ":");
	floor->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	floor->setPosition(465, 408);

	m_floorBoard->addChild(floor, 1);
}


//����¼�¼��
void BuildingStage::addHighFloorMark()
{
	auto mark = Sprite::createWithSpriteFrameName("building_obj_floor_mark.png");
	m_floorBoard->addChild(mark, 2);
	mark->setPosition(465, 408 + 36);
}


//������ʾ¥����
void BuildingStage::setFloorBoardVisible(bool visible)
{
	m_floorBoard->setVisible(visible);
}


//���������
void BuildingStage::addFloorLine()
{
	std::string fileName;
	auto tc = Director::getInstance()->getTextureCache();
	m_lines = Node::create();
	addChild(m_lines,-1);

	switch (m_floorIndex)
	{
	case 2:
		//������
		fileName = "object_tips.png";
		break;
	case 6:
		//ը����
		fileName = "movers_object_warning.png";
		break;
	default:
		if (m_floorIndex%5 == 0)
		{
			addClothLine();
		}
		else
		{
			auto rand = cocos2d::random(0, 5);
			if (rand < 3)
			{
				//������
				addBedSheet();
			}
			else if (rand == 3)
			{
				//�·���
				addClothLine();
			}
		}
		return;
	}

	auto _line = Sprite::createWithSpriteFrameName(fileName);
	m_lines->addChild(_line, 1);
}


//������ʾ������
void BuildingStage::setFloorLineVisible(bool visible)
{
	m_lines->setVisible(visible);
}


//����·���
void BuildingStage::addClothLine()
{
	auto _line = Sprite::createWithSpriteFrameName("building_obj_line_cloth.png");
	m_lines->addChild(_line, 1);
	Sprite * _cloth;
	if (random(0, 3) > 0)
	{
		SET_CLOTH_TYPE_B(_cloth);
		_line->addChild(_cloth, random(0, 3));
		_cloth->setPosition(157, 277);
		SET_CLOTH_MOTION_B(_cloth);
	}
	if (random(0, 3) > 0)
	{
		SET_CLOTH_TYPE_B(_cloth);
		_line->addChild(_cloth, random(0, 3));
		_cloth->setPosition(248, 267);
		SET_CLOTH_MOTION_B(_cloth);
	}
	if (random(0, 3) > 0)
	{
		SET_CLOTH_TYPE_B(_cloth);
		_line->addChild(_cloth, random(0, 3));
		_cloth->setPosition(342, 265);
		SET_CLOTH_MOTION_B(_cloth);
	}
	if (random(0, 3) > 0)
	{
		SET_CLOTH_TYPE_B(_cloth);
		_line->addChild(_cloth, random(0, 3));
		_cloth->setPosition(461, 274);
		SET_CLOTH_MOTION_B(_cloth);
	}
}


//��Ӵ�����
void BuildingStage::addBedSheet()
{
	auto _sheet = Sprite::createWithSpriteFrameName(
		StringUtils::format("building_obj_bedsheet_0%d.png", cocos2d::random(1, 4))
		);
	m_lines->addChild(_sheet,1);
}


//�������
void BuildingStage::addBirdLine()
{
	auto _line = Sprite::createWithSpriteFrameName("building_obj_line_bird.png");
	m_lines->addChild(_line, 1);
	int _bx = 156;
	HeadShaker * bird;
	for (auto i = 0; i < 7; i++)
	{
		if (random(0, 1) == 1)
		{
			switch (random(0, 3))
			{
			default: break;
			case 0: bird = HeadShaker::create(); bird->setHead("building_obj_bird_01_head.png"); bird->setBody("building_obj_bird_01_body.png"); break;
			case 1: bird = HeadShaker::create(); bird->setHead("building_obj_bird_02_head.png"); bird->setBody("building_obj_bird_02_body.png"); break;
			case 2: bird = HeadShaker::create(); bird->setHead("building_obj_bird_03_head.png"); bird->setBody("building_obj_bird_03_body.png"); break;
			case 3: bird = HeadShaker::create(); bird->setHead("building_obj_bird_04_head.png", 0); bird->setBody("building_obj_bird_04_body.png"); break;
			}
			if (random(0, 1) == 1) bird->flipX();
			bird->setPosition(_bx + i * 54, 305);
			_line->addChild(bird);
		}
	}
}
