#pragma once


#include<d3dx9.h>	
#include<d3d9.h>
#include<string>
#include<d3dx9tex.h>
#include<time.h>
#include<math.h>
typedef struct IMAGE {
RECT rect;
LPCWSTR name;
D3DXVECTOR3 Pos;
D3DXVECTOR3 Center;
LPDIRECT3DTEXTURE9 texture;
}Image;

enum Move {
	Left = 0, Right = 1, Up = 2, Down = 3, DirUp = 4, DirDown = 5
};

class PICTURE {
public:
	static LPD3DXSPRITE picture;
	static LPD3DXFONT font;


	static VOID Draw(Image Data);
	static VOID TextureInit(LPDIRECT3DDEVICE9 Device,Image * Data);
};




