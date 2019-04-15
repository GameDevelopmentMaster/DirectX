#include "Menu.h"
Menu::Menu()
{
	Player.AnimationInit(CharacterCheck::Player);
	for (int i = 0; i < 5; i++) {
		Enemy[i].AnimationInit(CharacterCheck::Enemy1);
	}
	MenuInit();
}


VOID Menu::MenuInit()
{
	Image newImage;
	GameCheck = MenuCheck::Main;
	newImage = { {0,0,1920,1080}, L"Main.png",{0,0,0}, {0,0,0} };
	MenuImage[0] = newImage;
	newImage = { {0,0,1920,1080}, L"Option.png",{0,0,0}, {0,0,0} };
	MenuImage[1] = newImage;

	return VOID();
}

VOID Menu::SetDevice(LPDIRECT3DDEVICE9 Device)
{
	BlockCheck.InitBlock(Device);
	CharacterInit(Device);
	InGameBackGroundIni();
	for (int i = 0; i < 3; i++) {
		PICTURE::TextureInit(Device, &MenuImage[i]);
		PICTURE::TextureInit(Device, &InGameImage[i]);
	}
	return VOID();
}

VOID Menu::CharacterInit(LPDIRECT3DDEVICE9 Device)
{
	Image temporaryImage = { {0,0,500,254},L"Player.png" ,{ 100,700,0}, { 0,0,0} };
	Player.ImageInit(Device, &temporaryImage);
	temporaryImage.name = L"Enemy.jpg";
	for (int i = 0; i < 1; i++) {
		temporaryImage.Pos = { (float)100 * i,(float)200 * i,0 };
		Enemy[i].ImageInit(Device, &temporaryImage);
	}

	return VOID();
}

VOID Menu::MainMenu()
{
	PICTURE::Draw(MenuImage[GameCheck]);
	return VOID();
}

VOID Menu::Option()
{
	PICTURE::Draw(MenuImage[GameCheck]);
	return VOID();
}

VOID Menu::GameStart()
{
	for (int i = 0; i < 3; i++) {
		PICTURE::Draw(InGameImage[i]);
	}
	PICTURE::Draw(BlockCheck.ReturnImage());
	PICTURE::Draw(Player.ReturnCharacter());
	PICTURE::Draw(Player.ReturnGun());
	PICTURE::Draw(Enemy[0].ReturnCharacter());
	for (int j = 0; j < 20; j++) {
		D3DXMatrixTransformation2D(&Player.Matrix, NULL, NULL, NULL, &((D3DXVECTOR2)Player.ReturnBullet(j).Pos), D3DXToRadian(Player.BulletRadin(j)), NULL);
		PICTURE::picture->SetTransform(&Player.Matrix);
		Player.BulletReset(j);
		PICTURE::Draw(Player.ReturnBullet(j));

		D3DXMatrixTransformation2D(&Player.Matrix, NULL, NULL, NULL, NULL, NULL, NULL);
		PICTURE::picture->SetTransform(&Player.Matrix);
		D3DXMatrixTransformation2D(&Enemy[0].Matrix, NULL, NULL, NULL, &(D3DXVECTOR2)Enemy[0].ReturnBullet(j).Pos, D3DXToRadian(Enemy[0].BulletRadin(j)), NULL);
		PICTURE::picture->SetTransform(&Enemy[0].Matrix);
		PICTURE::Draw(Enemy[0].ReturnBullet(j));
		D3DXMatrixTransformation2D(&Enemy[0].Matrix, NULL, NULL, NULL, NULL, NULL, NULL);
		PICTURE::picture->SetTransform(&Enemy[0].Matrix);
	}
	Enemy[0].MovePlayer(Enemy[0].ReturnMove());
	return VOID();
}

VOID Menu::BulletShot()
{
	BackGroundUpdate();
	if (Player._3DirCheck) {
		Player._3DirBullet(&Enemy[0]);
	}
	else {

		for (int i = 0; i < 1; i++) {
			Player.LeftButton(&Enemy[i], Weapon::Air);
			Enemy[i].LeftButton(&Player,Weapon::Air);
		}
	}
	return VOID();
}

VOID Menu::BackGroundUpdate()
{

	Image Test = Player.Charater;
	Image A = Player.ReturnCharacter();
	BlockCheck.BlockData(&A);
	//.BlockData(&Player.Charater);

	return VOID();
}

VOID Menu::InGameBackGroundIni()
{
	Image newImage = { {0,0,2000,1080},L"InGameBackGround1.png",{0,0,0},{0,0,0} };
	InGameImage[0] = newImage;
	newImage = { {0,0,1986,516},L"InGameBackGround2.png",{0,564,0},{0,0,0} };
	InGameImage[1] = newImage;
	newImage = { {0,0,1999,241},L"InGameBackGround3.png",{0,839,0},{0,0,0} };
	InGameImage[2] = newImage;
	return VOID();
}


