#pragma once
#include "Sprite.h"

enum ItemList
{
	DoubleJump = 0, SpeedItem, Range, TreepleDir, Homing, nucleus		//0 : �������� , ���ǵ� ����, ��Ÿ� ����, 3����, ȣ�ֹ̻���, ��
};


struct ItemData {
	ItemList ListData;
	Image	ItemImage;   //������ �̹���
	time_t	Oldtime;
	time_t	Curtime;
	BOOL   Itemgain;     //�������� �Ծ����� Ȯ���ϴ� ����
	INT		NucleusCount;//������ �� ����
};
