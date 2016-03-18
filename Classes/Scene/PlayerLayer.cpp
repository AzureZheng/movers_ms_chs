#include "PlayerLayer.h"
#include "FilePathDefine.h"


//��ʼ��
bool PlayerLayer::init()
{
	if (!ClippingRectangleNode::init())
	{
		return false;
	}

	//������
	m_playerID = 0;

	//¥�����
	m_stageCount = 0;

	//¥��
	m_objectsHolder = nullptr;
	m_building = nullptr;

	//��ҷ���
	m_viewScore = 0;
	m_score = 0;

	setClippingEnabled(false);

	setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	//���û������
	m_isOver = false;

	//���û����������
	m_lockControl = false;
	m_lockControl2 = false;

	return true;
}


//������ʼ¥��
void PlayerLayer::initBuilding()
{
	m_objectsHolder = Node::create();
	addChild(m_objectsHolder,0);
	m_building = Building::create();
	m_building->setPlayerFlag(m_playerID);
	m_objectsHolder->addChild(m_building, 0);
	m_building->setPositionY(-200);


	addBuildingStage();
	addBuildingStage();
	addBuildingStage();
	addBuildingStage();
}


//���һ��¥��
void PlayerLayer::addBuildingStage()
{
	m_building->addStage();
}


//���òü���С
void PlayerLayer::setClippingArea(const Size & size)
{
	setContentSize(size);
	setClippingRegion(Rect(0,0,size.width,size.height));
	setClippingEnabled(true);
}


//��ʱ���Ӳ㼶
void PlayerLayer::delayUpFloor(float dt)
{
	auto act1 = EaseElasticInOut::create(MoveBy::create(1.0, Vec2(0, -BUILDING_STAGE_H)));
	auto act2 = CallFunc::create([](){Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("UpFloorFinished"); });
	auto act = Sequence::create(act1,act2,nullptr);

	m_objectsHolder->runAction(act);
}


//���Ӳ㼶
void PlayerLayer::upFloor()
{
	gainStageCount();
	scheduleOnce(schedule_selector(PlayerLayer::delayUpFloor), 0.5f);
}


//ˢ����Ұ
void PlayerLayer::refreshView()
{
	auto bottomStage = m_building->getBuildingStages().at(0);
	if (bottomStage->getPosition().y >= BUILDING_STAGE_H)
	{
		m_building->moveAllFloors(-BUILDING_STAGE_H);
		m_objectsHolder->setPositionY(m_objectsHolder->getPositionY() + BUILDING_STAGE_H);
	}
}


//�㼶�������
void PlayerLayer::upFloorFinish()
{
	m_building->addStage();
	refreshView();
}


//����¥���ӽ�λ��
void PlayerLayer::setFloorCameraPos(const Vec2 & pos)
{
	m_objectsHolder->setPosition(pos);
}


//��ȡ¥���ӽ�λ��
const Vec2 & PlayerLayer::getFloorCameraPos() const
{
	return m_objectsHolder->getPosition();
}


//����¥���ӽ�ƫ��
void PlayerLayer::setFloorCameraOffset(const Vec2 & offset)
{
	m_objectsHolder->setPosition(m_objectsHolder->getPosition() + offset);
}


