#include "Sprite.h"

LPD3DXSPRITE PICTURE::picture = NULL;
LPD3DXFONT PICTURE::font = NULL;

VOID PICTURE::Draw(Image Data)
{
	picture->Draw(Data.texture, &Data.rect, &Data.Center, &Data.Pos, 0xffffffff);
	return VOID();
}

VOID PICTURE::TextureInit(LPDIRECT3DDEVICE9 Device,Image * Data)
{
	D3DXCreateTextureFromFileEx(Device, Data->name, 0, 0, 0, 0,D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, 0, 0, &Data->texture);
	return VOID();
}
