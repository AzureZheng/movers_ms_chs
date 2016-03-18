#include "HPBar.h"


//��ʼ��
bool HPBar::init(const std::string & block, const Size & hpBarSize, const Vec2 & hpBlockOffset, const Vec2 & firstBlockPos)
{
	if (!Sprite::init())
	{
		return false;
	}

	setContentSize(hpBarSize);

	m_maxHP = MAX_HP_COUNT;

	m_hp = m_maxHP;

	//��������
	Sprite * hpBlock = nullptr;

	for (int i = 0; i < m_maxHP;i++)
	{
		hpBlock = Sprite::createWithSpriteFrameName(block);
		hpBlock->setPosition(firstBlockPos + (hpBlockOffset * i));
		hpBlock->setTag(1);
		addChild(hpBlock);
		m_hpBlocks.pushBack(hpBlock);
	}

	return true;
}


//����ʵ��
HPBar * HPBar::create(const std::string & block, const Size & hpBarSize, const Vec2 & hpBlockOffset, const Vec2 & firstBlockPos)
{
	auto ret = new (std::nothrow) HPBar();
	
	if (ret->init(block, hpBarSize, hpBlockOffset, firstBlockPos))
	{
		ret->autorelease();
	}
	else
	{
		return nullptr;
	}

	return ret;
}


HPBar * HPBar::createWithFormat(bool isRed, bool hpBlockReverse)
{
	HPBar * ret = nullptr;
	if (isRed)
	{
		if (hpBlockReverse)
		{
			ret = create("ui_hp_block_red.png", Size(165, 44), Vec2(-56, 0), Vec2(138.5f, 22));
		}
		else
		{
			ret = create("ui_hp_block_red.png", Size(165, 44), Vec2(56, 0), Vec2(26.5f, 22));
		}
	}
	else
	{
		if (hpBlockReverse)
		{
			ret = create("ui_hp_block_green.png", Size(165, 44), Vec2(-56, 0), Vec2(138.5f, 22));
		}
		else
		{
			ret = create("ui_hp_block_green.png", Size(165, 44), Vec2(56, 0), Vec2(26.5f, 22));
		}
	}

	return ret;
}


//��ȡѪ��
int HPBar::getHP()
{
	return m_hp;
}


//����Ѫ��
void HPBar::setHP(int hp)
{
	if (hp > m_maxHP)
	{
		hp = m_maxHP;
	}
	else if (hp < 0)
	{
		hp = 0;
	}

	m_hp = hp;
	_refreshView();
}

//�ָ�
void HPBar::heal()
{
	m_hp = m_maxHP;
	_refreshView();
}

//Ѫ����1�������Ƿ�������
bool HPBar::cutHP()
{
	m_hp--;
	if (m_hp<=0)
	{
		m_hp = 0;
	}

	_refreshView();

	if (!m_hp)
	{
		return true;
	}

	return false;
}


//ˢ����ʾ
void HPBar::_refreshView()
{
	Sprite * block = nullptr;

	for (int i = 0; i < m_maxHP;i++)
	{
		block = m_hpBlocks.at(i);
		if (i < m_hp)
		{
			if (!block->getTag())
			{
				block->setTag(1);
				block->stopAllActions();
				block->runAction(ScaleTo::create(0.1f, 0));
			}
		}
		else
		{
			if (block->getTag())
			{
				block->setTag(0);
				block->stopAllActions();
				block->runAction(ScaleTo::create(0.1f, 0));
			}
		}
	}
}
