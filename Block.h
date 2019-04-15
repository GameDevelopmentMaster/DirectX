#pragma once

#include"Sprite.h"

class Block {
	Image BlockImage;


public :
	VOID InitBlock(LPDIRECT3DDEVICE9 g_Device);
	VOID BlockData(Image *BlockData);
	Image ReturnImage();

};