#include "StageSide.h"
#include "Info/GameInfo.h"

//��ʼ��
bool StageSide::init()
{
	if (!Node::init())
	{
		return false;
	}

	//λ��(0:��1:��)
	m_side = 0;

	//�Ƿ�ת
	m_isFlipped = false;

	//����ʵ��
	m_rabbit = nullptr;

	//����
	m_rail = nullptr;

	//ǽ��
	m_wall = nullptr;

	//�����Ƿ�����
	m_hideRabbit = false;

	return true;
};

//��ȡ����ʵ��
RabbitHamal * StageSide::getRabbit()
{
	return m_rabbit;
}

//��������ʵ��
void StageSide::setRabbit(RabbitHamal * rabbit)
{
	if (m_rabbit)
	{
		m_rabbit->removeFromParent();
	}

	m_rabbit = rabbit;
	m_rabbit->setCascadeOpacityEnabled(true);
	addChild(rabbit, 2);

	if (m_hideRabbit)
	{
		m_rabbit->setOpacity(0);
	}
}


//�������
void StageSide::clearRabbit()
{
	if (m_rabbit)
	{
		m_rabbit->removeFromParent();
		m_rabbit = nullptr;
	}
}


//��������
void StageSide::setSide(int side, bool flipped)
{
	m_side = side;
	if (flipped)
	{
		if (side == 0)
		{
			setBuildingFlipped(false);
		}
		else
		{
			setBuildingFlipped(true);
		}
	}
}

//���ý�����ת
void StageSide::setBuildingFlipped(bool flipped)
{
	if (m_rail)
	{
		m_rail->setFlippedX(flipped);
	}

	if (m_wall)
	{
		m_wall->setFlippedX(flipped);
	}

	m_isFlipped = flipped;
}

//��������ͼ��
void StageSide::setRail(Sprite * rail)
{
	if (m_rail)
	{
		m_rail->removeFromParent();
	}

	m_rail = rail;
	addChild(m_rail, 5);
}

//����ǽ��ͼ��
void StageSide::setWall(Sprite * wall)
{
	if (m_wall)
	{
		m_wall->removeFromParent();
	}

	m_wall = wall;
	m_wallSize = m_wall->getContentSize();
	addChild(m_wall, 1);
}

//���ӳ���
void StageSide::showRabbit(float dt)
{
	if (!m_hideRabbit) return;

	//if (m_side == 0)
	//{
	//	m_rabbit->runAction(MoveBy::create(0.2f, Vec2(-220, 0)));
	//}
	//else
	//{
	//	m_rabbit->runAction(MoveBy::create(0.2f, Vec2(220, 0)));
	//}
	m_rabbit->setKO(false);
	m_rabbit->setVisible(true);

	if (dt == 0)
	{
		m_rabbit->setOpacity(255);
	}
	else
	{
		m_rabbit->runAction(FadeIn::create(dt));
	}

	m_hideRabbit = false;
}

//��������
void StageSide::hideRabbit()
{
	if (m_hideRabbit) return;

	/*if (m_side == 0)*/
	//{
	//	m_rabbit->setPositionX(m_rabbit->getPositionX() + 220);
	//}
	//else
	//{
	//	m_rabbit->setPositionX(m_rabbit->getPositionX() - 220);
	//}

	/*m_rabbit->runAction(FadeOut::create(0.5f));*/
	m_rabbit->setVisible(false);
	m_rabbit->setKO(true);
	m_rabbit->setOpacity(0);

	m_hideRabbit = true;
}


//��ģ��������ʵ��(0:��˫��;1:��˫��;2:��һ��;3:��һ��;4:�ҵ���;5:����)
StageSide * StageSide::createWithType(int type)
{
	auto ss = StageSide::create();

	if (type == 0)
	{
		ss->setWall(Sprite::createWithSpriteFrameName("building_wall.png"));
		ss->setRail(Sprite::createWithSpriteFrameName("building_yangtai.png"));
		ss->addChild(Sprite::createWithSpriteFrameName("building_windows.png"),1);
		ss->setRabbit(RabbitHamal::create());
	}

	if (type == 1)
	{
		ss->setWall(Sprite::createWithSpriteFrameName("building_wall.png"));
		ss->setRail(Sprite::createWithSpriteFrameName("building_yangtai.png"));
		ss->addChild(Sprite::createWithSpriteFrameName("building_windows.png"), 1);
		ss->setRabbit(RabbitHamal::create());
		ss->setSide(1);
	}

	if (type == 2)
	{
		ss->setRabbit(RabbitHamalBoss::create());
	}

	if (type == 3)
	{
		ss->setRabbit(RabbitHamalBoss::create());
		ss->setSide(1);
	}

	if (type == 4)
	{
		ss->setWall(Sprite::createWithSpriteFrameName("building_wall.png"));
		ss->setRail(Sprite::createWithSpriteFrameName("building_yangtai.png"));

		auto wall2 = Sprite::createWithSpriteFrameName("building_wall.png");
		wall2->setPosition(345,0);
		wall2->setFlippedX(true);
		ss->addChild(wall2,1);

		auto wd = Sprite::createWithSpriteFrameName("building_windows.png");
		ss->addChild(wd, 1);

		wd = Sprite::createWithSpriteFrameName("building_windows.png");
		wd->setPosition(173,0);
		ss->addChild(wd, 1);

		wd = Sprite::createWithSpriteFrameName("building_windows.png");
		wd->setPosition(347, 0);
		ss->addChild(wd, 1);

		ss->setRabbit(RabbitHamal::create());
	}

	if (type == 5)
	{
		ss->setWall(Sprite::createWithSpriteFrameName("building_wall.png"));
		ss->setRail(Sprite::createWithSpriteFrameName("building_yangtai.png"));

		auto wall2 = Sprite::createWithSpriteFrameName("building_wall.png");
		wall2->setPosition(-345, 0);
		ss->addChild(wall2, 1);

		auto wd = Sprite::createWithSpriteFrameName("building_windows.png");
		ss->addChild(wd, 1);

		wd = Sprite::createWithSpriteFrameName("building_windows.png");
		wd->setPosition(-173, 0);
		ss->addChild(wd, 1);

		wd = Sprite::createWithSpriteFrameName("building_windows.png");
		wd->setPosition(-347, 0);
		ss->addChild(wd, 1);

		ss->setRabbit(RabbitHamal::create());
		ss->setSide(1);
	}

	ss->refreshRabbitPos();
	ss->hideRabbit();
	return ss;
}


//�������ӷ�λ
void StageSide::refreshRabbitPos()
{
	if (m_side == 0)
	{
		m_rabbit->setPosition(Vec2(-110, -123));
	}
	else
	{
		m_rabbit->setPosition(Vec2(110, -123));
	}
}


//��ȡǽ�ڸ߶�
Size StageSide::getWallSize()
{
	return m_wallSize;
}

//��ʾ��
void StageSide::showYou(bool fourPlayer)
{
	auto _you = dynamic_cast<Sprite*>(getChildByName("YouMark"));
	if (_you) return;

	if (GameInfo::getInstance()->getModeCode() == "A1")
	{
		return;
	}
	else if (GameInfo::getInstance()->getModeCode() == "M1")
	{
		if (m_side == 1)
		{
			_you = Sprite::createWithSpriteFrameName("ui_p1.png");
		}
		else
		{
			_you = Sprite::createWithSpriteFrameName("ui_p2.png");
		}

		_you->setScale(0.6f);
	}
	else if (GameInfo::getInstance()->getModeCode() == "A2")
	{
		if (fourPlayer)
		{
			if (m_side == 1)
			{
				_you = Sprite::createWithSpriteFrameName("ui_p3.png");
			}
			else
			{
				_you = Sprite::createWithSpriteFrameName("ui_p4.png");
			}
		}
		else
		{
			if (m_side == 1)
			{
				_you = Sprite::createWithSpriteFrameName("ui_p1.png");
			}
			else
			{
				_you = Sprite::createWithSpriteFrameName("ui_p2_red.png");
			}
		}

		_you->setScale(0.6f);
	}
	else
	{
		_you = Sprite::createWithSpriteFrameName("building_obj_player_mark.png");
	}

	addChild(_you, 6, "YouMark");

	auto x = m_rabbit->getPosition().x;

	_you->setPosition(x, m_rabbit->getPosition().y - 96);
	_you->runAction(RepeatForever::create(Sequence::create(
		FadeTo::create(0.4, 64),
		FadeTo::create(0.4, 255),
		FadeTo::create(0.4, 255),
		NULL
		)));
}


//������
void StageSide::hideYou()
{
	auto _you = getChildByName("YouMark");
	if (!_you) return;
	_you->stopAllActions();
	_you->runAction(Sequence::create(
		FadeTo::create(0.2f, 0),
		RemoveSelf::create(),
		nullptr
		));
}
