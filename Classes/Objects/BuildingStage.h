/****************************************
¥�����
2016-02-01 by Azure Zheng
*****************************************/

#ifndef __BUILDING_STAGE_H__
#define __BUILDING_STAGE_H__

#include "cocos2d.h"
#include "Objects/StageSide.h"

USING_NS_CC;

class BuildingStage : public Node
{
public:

	//����¥��
	CREATE_FUNC(BuildingStage);

	//��ʼ��¥��
	virtual bool init();

	//��ȡ���
	int getFloorIndex(){ return m_floorIndex; }

	//���ò��
	void setFloorIndex(int index){ m_floorIndex = index; }

	//����һ����ͨ��
	static BuildingStage * createNormalFloor(int floorIndex);

	//����һ����һ��
	static BuildingStage * createFirstFloor(bool noLeft = false);

	//��ȡ��������ʵ��(0:��;1:��)
	RabbitHamal * getSideRabbit(int side);

	//��ȡ¥��ʵ��(0:��;1:��)
	StageSide * getStageSide(int side);

	//��ʼ��һ����ͨ��
	void initNormalStage();

	//��ʼ����һ��
	void initFirstStage(bool noLeft = false);

	//��ȡ¥���С
	virtual Size getStageSize();

	//����¥���С
	virtual void setStageSize(Size stageSize);

	//���¥����
	void addFloorBoard();

	//����¼�¼��
	void addHighFloorMark();

	//������ʾ¥����
	void setFloorBoardVisible(bool visible);

	//���������
	void addFloorLine();

	//������ʾ������
	void setFloorLineVisible(bool visible);

	//����·���
	void addClothLine();

	//��Ӵ�����
	void addBedSheet();

	//�������
	void addBirdLine();

	//��Ǹò�����ұ߳�������
	void signRabbitSide(int side){ m_rabbitSide = side; }

	//��ȡ�ò����ӵ�����
	int getRabbitSide(){ return m_rabbitSide; }

protected:

	//�ڼ���
	int m_floorIndex;

	//������
	Node * m_lines;

	//¥����
	Sprite * m_floorBoard;

	//�¼�¼��
	Sprite * m_highFloorMark;

	//¥���
	StageSide * m_stageSides[2];

	//¥���С
	Size m_stageSize;

	//�����������
	int m_rabbitSide;
};


#endif
