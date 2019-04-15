#include "Block.h"
#include<stdio.h>	


VOID Block::InitBlock(LPDIRECT3DDEVICE9 g_Device)
{
	BlockImage.Center = { 0,0,0 };
	BlockImage.Pos = { 1700,900,0 };
	BlockImage.rect = { 0,0,500,500 };
	BlockImage.name = L"Block.png";
	PICTURE::TextureInit(g_Device, &BlockImage);
	return VOID();
}

VOID Block::BlockData(Image* BlockData)
{
	
	if (BlockData->Pos.x+BlockData->rect.right > BlockImage.Pos.x && BlockData->Pos.x+ BlockData->rect.right < BlockImage.Pos.x +BlockImage.rect.right)
	{
		BlockData->Pos = {BlockImage.Pos.x - BlockData->rect.right , BlockData->Pos.y,BlockData->Pos.z };
		printf("PlayerData X : %f, PlayerData Y : %f\n", BlockData->Pos.x, BlockData->Pos.y);
	}
	if (BlockData->Pos.x < BlockImage.Pos.x + BlockImage.rect.right&& BlockData->Pos.x + BlockData->rect.right > BlockImage.Pos.x + BlockImage.rect.right) {
		BlockData->Pos.x = BlockImage.Pos.x + BlockImage.rect.right +1;
	}
	if (BlockData->Pos.y + BlockData->rect.bottom < BlockImage.Pos.y) {
		BlockData->Pos.y = BlockImage.Pos.y - BlockData->rect.bottom;
	}
	return VOID();
}

Image Block::ReturnImage()
{
	return BlockImage;
}
