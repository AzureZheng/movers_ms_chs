/*----------------------------
Ѫ��UI
2016-03-01 by Azure Zheng
------------------------------*/

#ifndef __HP_BAR_H__
#define __HP_BAR_H__

#include "cocos2d.h"

USING_NS_CC;

#define MAX_HP_COUNT 3

class HPBar : public Sprite
{
public:
	
	//��ʼ��
	bool init(const std::string & block, const Size & hpBarSize, const Vec2 & hpBlockOffset, const Vec2 & firstBlockPos);

	//����ʵ��
	static HPBar * create(const std::string & block, const Size & hpBarSize, const Vec2 & hpBlockOffset, const Vec2 & firstBlockPos);
	static HPBar * createWithFormat(bool isRed, bool hpBlockReverse);

	//��ȡѪ��
	int getHP();

	//����Ѫ��
	void setHP(int hp);

	//Ѫ����1�������Ƿ�������
	bool cutHP();

	//�ָ�
	void heal();

protected:

	//ˢ����ʾ
	void _refreshView();

	//Ѫ���鴢��
	Vector<Sprite*> m_hpBlocks;

	//Ѫ��
	int m_hp;

	//Ѫ������
	int m_maxHP;

};














#endif



