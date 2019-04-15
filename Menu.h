#pragma once
#include<d3dx9.h>
#include<d3dx9tex.h>
#include"Animation.h"
#include"Block.h"
#define ScreenX 1920
//Animation Player(PICTURE::Player);
//Animation Enemy(PICTURE::Enemy);
//typedef LPDIRECT3DDEVICE9 *Device9;
enum MenuCheck
{
	Main = 0, Option = 1, GameStart = 2
};
class Menu{
public:
	Block BlockCheck;
	Menu();
	VOID MenuInit();
	VOID SetDevice(LPDIRECT3DDEVICE9 Device);
	VOID CharacterInit(LPDIRECT3DDEVICE9 Device);
	VOID MainMenu();
	VOID Option();
	VOID GameStart();
	VOID BulletShot();
	MenuCheck GameCheck;
	Animation Enemy[5];
	Animation Player;
	Move  CharaterMove;
	VOID  BackGroundUpdate();
	VOID  InGameBackGroundIni();
	Weapon weapon;
private:
	Image MenuImage[2];
	Image InGameImage[3];
	//ItemList  ItemList;
};