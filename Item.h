#pragma once
#include "Sprite.h"

enum ItemList
{
	DoubleJump = 0, SpeedItem, Range, TreepleDir, Homing, nucleus		//0 : 더블점프 , 스피드 증가, 사거리 증가, 3방향, 호밍미사일, 핵
};


struct ItemData {
	ItemList ListData;
	Image	ItemImage;   //아이템 이미지
	time_t	Oldtime;
	time_t	Curtime;
	BOOL   Itemgain;     //아이템을 먹었는지 확인하는 변수
	INT		NucleusCount;//아이템 핵 갯수
};
