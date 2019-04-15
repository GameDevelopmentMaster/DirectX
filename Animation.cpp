#include "Animation.h"

VOID Animation::ImageInit(LPDIRECT3DDEVICE9 g_pd3dDevice, Image * data)
{
	Riden = 330;
	Ani(data);
	PICTURE::TextureInit(g_pd3dDevice, &Charater);
	PICTURE::TextureInit(g_pd3dDevice, &Gun);
	BulletInit();
	for (int i = 0; i < Index; i++) {
		PICTURE::TextureInit(g_pd3dDevice, &Bullet[i]);
	}
	return VOID();
}

VOID Animation::Ani(Image * newImgae)
{
	Charater = *newImgae;
	Gun.Pos = { Charater.Pos.x + Charater.rect.right, Charater.Pos.y,0 };
	return VOID();
}

VOID Animation::BulletInit()
{
	for (int i = 0; i < 60; i++) {
		Bullet[i].name = L"Bullet.png";
		Bullet[i].Center = { 0,0,0 };
		Bullet[i].rect = { 0,0,34,20 };
		switch (CharacterList)
		{
		case CharacterCheck::Player:
			Bullet[i].Pos = { 1920,Charater.Pos.y ,0 };
			break;
		case CharacterCheck::Enemy1:
			Bullet[i].Pos = { -100,Charater.Pos.y + Charater.rect.bottom / 2,0 };
			break;
		}
	}
	return VOID();
}

VOID Animation::LeftButton(Animation *CharacteAnimation, Weapon weapon)
{
	CurTIme = clock();
	switch (CharacterList)
	{
	case CharacterCheck::Player:

		if (BulletCheck == false) {
			for (int i = 0; i < Index; i++) {
				if (Bullet[i].Pos.x < 1920 && Charater.Pos.x + Charater.rect.right < Bullet[i].Pos.x || Bullet[i].Pos.y >0) {
					Bullet[i].Pos.x += CharacterData.Speed * cosf(D3DXToRadian(CharacterData.RidenSpeed[i]));
					Bullet[i].Pos.y += CharacterData.Speed * sinf(D3DXToRadian(CharacterData.RidenSpeed[i]));
				}
			}
		}
		if (BulletCheck == true) {
			switch (weapon) {
			case Weapon::Air:
				for (int i = 0; i < Index; i++) {
					if (CurTIme - OldTime > 150) {
						OldTime = clock();
						if (SpaceNum < Index) { SpaceNum++; }
						for (int j = i + 1; j <= SpaceNum; j++) {
							if (Bullet[j].Pos.x + CharacterData.Speed > 1920 || Bullet[j].Pos.y + CharacterData.Speed < 0) {
								Bullet[j].Pos.y = Charater.Pos.y;
								Bullet[j].Pos.x = Gun.Pos.x + Gun.rect.right / 3;
								CharacterData.RidenSpeed[j] = Riden;
								SpaceNum = j;
							}
						}
					}
					Bullet[i].Pos.x += CharacterData.Speed * cosf(D3DXToRadian(CharacterData.RidenSpeed[i]));
					Bullet[i].Pos.y += CharacterData.Speed * sinf(D3DXToRadian(CharacterData.RidenSpeed[i]));
				}
				break;
			case Weapon::Ground:

				break;
			}
		}
		sprintf_s(Test, "%d", SpaceNum);
		CharacterDown();
		break;
	case CharacterCheck::Enemy1:
		if (Riden != 120) {
			Riden = 120;
		}
		for (int i = 0; i < Index; i++) {
			if (CurTIme - OldTime > 250) {
				OldTime = clock();
				if (SpaceNum < Index) { SpaceNum++; }
				for (int j = i + 1; j <= SpaceNum; j++) {
					if (Bullet[j].Pos.x+Bullet[i].rect.right < 0 || Bullet[i].Pos.y+ Bullet[i].rect.bottom > 1080) {
						Bullet[j].Pos.y = Charater.Pos.y + Charater.rect.bottom;
						Bullet[j].Pos.x = Charater.Pos.x + Charater.rect.right / 3;
						CharacterData.RidenSpeed[j] = Riden;
						SpaceNum = j;
					}
				}
			}
			Bullet[i].Pos.x -= CharacterData.Speed * cosf(D3DXToRadian(330));
			Bullet[i].Pos.y -= CharacterData.Speed * sinf(D3DXToRadian(330));
		}
		MovePlayer(ObjectMove);
		break;
	}
	PhysicsBullet(CharacteAnimation);
	if (CharacterData.Hp <= 0) {
		switch (CharacterList)
		{
		case CharacterCheck::Player:
			Charater.rect = { 0,0,0,0 };
			break;
		case CharacterCheck::Enemy1:
			Charater.Pos.x = 1920;
			CharacterData.Hp = 1;
			break;
		default:
			break;
		}
	}


	return VOID();

}

VOID Animation::PhysicsBullet(Animation *CharaterPosData)
{
	SetPos(&CharaterPosData->Charater);
	for (int i = 0; i < Index; i++) {
		if ((Bullet[i].Pos.x > Enemy->Pos.x && Bullet[i].Pos.x < Enemy->Pos.x + Enemy->rect.right) && (Bullet[i].Pos.y > Enemy->Pos.y && Bullet[i].Pos.y < Enemy->Pos.y + Enemy->rect.bottom) && CharaterPosData->CharacterList == Enemy1) {
			if (CharaterPosData->CharacterData.Hp > 0) {
				CharaterPosData->HpCheck = true;
				Bullet[i].Pos.x = 1980;

			}
			break;
		}
		else if ((Bullet[i].Pos.x > Enemy->Pos.x&&Bullet[i].Pos.x<Enemy->Pos.x + Enemy->rect.right&&Bullet[i].Pos.y>Enemy->Pos.y&&Bullet[i].Pos.y < Enemy->rect.bottom + Enemy->Pos.y) && CharaterPosData->CharacterList == Player) {
			if (CharaterPosData->CharacterData.Hp > 0) {
				CharaterPosData->HpCheck = true;
				Bullet[i].Pos.y = -1000;
			}
			break;
		}
	}
	if (HpCheck) {
		CharacterData.Hp--;
		HpCheck = false;

	}

	return VOID();
}

VOID Animation::CharacterDown()
{
	float JumpSpeed = CharacterData.Speed + Charater.Pos.y / 20;
	if (Charater.Pos.y + Charater.rect.bottom < 1000) {
		Charater.Pos.y += JumpSpeed;
	}
	else {

		JumpCount = 50;
	}
	return VOID();
}

VOID Animation::MovePlayer(Move dir)
{
	switch (dir)
	{
	case Move::Left:
		if (Charater.Pos.x > 0) {
			Charater.Pos.x -= CharacterData.Speed;
			Gun.Pos.x -= CharacterData.Speed;
		}
		else {
			ObjectMove = Move::Right;
		}
		break;
	case Move::Right:
		if (Charater.Pos.x + Charater.rect.right < 1920) {
			Charater.Pos.x += CharacterData.Speed;
			Gun.Pos.x += CharacterData.Speed;
		}
		else {
			ObjectMove = Move::Left;
		}
		break;
	case Move::Up:
		if (Charater.Pos.y > 0 && JumpCount > 0) {
			Charater.Pos.y -= CharacterData.Speed + 60;
			Gun.Pos.y -= CharacterData.Speed;
			JumpCount--;
		}
		break;

	case Move::DirUp:
		if (Riden < 330) {
			Riden += 2;
		}
		break;
	case Move::DirDown:
		if (Riden > 270) {
			Riden -= 2;
		}
		break;
	}

	return VOID();
}


VOID Animation::SetItem()
{
	ItemDatas.Curtime = clock();
	if (ItemDatas.ItemImage.Pos.x > Charater.Pos.x && ItemDatas.ItemImage.Pos.x < Charater.Pos.x + Charater.rect.right &&
		ItemDatas.ItemImage.Pos.y > Charater.Pos.y && ItemDatas.ItemImage.Pos.y < Charater.Pos.y + Charater.rect.bottom && CharacterList == CharacterCheck::Player) {
		switch (ItemDatas.ListData)
		{
		case DoubleJump:
			ItemDatas.Oldtime = clock();
			JumpCount = 2;				//일정 시간동안 이 카운트가 유지가 되어야함
			ItemDatas.Itemgain = true;
			break;
		case SpeedItem:
			ItemDatas.Itemgain = true;
			CharacterData.Speed = 15;
			ItemDatas.Oldtime = clock();
			break;
		case Range:
			DistanceRange = 500;
			break;

		case TreepleDir:

			break;
		case Homing:

			break;
		case nucleus:
			if (ItemDatas.NucleusCount < 2) {
				ItemDatas.NucleusCount++;
			}
			/*if (EnemyAni.Charater.Pos.x > 0 && EnemyAni.Charater.Pos.x < 1920 && EnemyAni.CharacterList != CharacterCheck::Player) {
				EnemyAni.CharacterData.Hp = 0;
			}*/
			break;

		}
	}
	if (ItemDatas.Itemgain) {
		if (ItemDatas.Oldtime - ItemDatas.Curtime < 150) {
			ItemDatas.Itemgain = false;
			switch (ItemDatas.ListData)
			{
			case DoubleJump:
				JumpCount = 1;
				break;
			case SpeedItem:
				CharacterData.Speed = 10;
				break;
			case Range:
				DistanceRange = 300;
				break;
			case TreepleDir:

				break;
			}
		}
	}
	return VOID();
}

VOID Animation::ItemUse(Animation * EnemyAni)
{

	return VOID();
}

INT Animation::BulletRadin(int j)
{
	return CharacterData.RidenSpeed[j];
}

VOID Animation::BulletReset(int num)
{
	Gun.Pos.y = Charater.Pos.y - 20;
	Gun.Pos.x = Charater.Pos.x + Charater.rect.right / 2;

	return VOID();
}

IMAGE Animation::ReturnGun()
{
	return Gun;
}

VOID Animation::SetRidian(FLOAT Ridain)
{
	Riden = Ridain;
	return;
}

VOID  Animation::_3DirBullet(Animation * CharacterPosData)
{
	CurTIme = clock();
	if (BulletCheck == false) {
		for (int i = 0; i < 60; i++) {
			if (Bullet[i].Pos.x < 1920 && Charater.Pos.x + Charater.rect.right < Bullet[i].Pos.x || Bullet[i].Pos.y >0) {
				Bullet[i].Pos.x += CharacterData.Speed * cosf(D3DXToRadian(CharacterData.RidenSpeed[i]));
				Bullet[i].Pos.y += CharacterData.Speed * sinf(D3DXToRadian(CharacterData.RidenSpeed[i]));
			}
		}
	}
	if (BulletCheck == true) {
		for (int i = 0; i < 60; i++) {
			if (CurTIme - OldTime > 150) {
				OldTime = clock();
				if (SpaceNum < 60) { SpaceNum++; }
				for (int j = 0; j <= 60; j += 3) {
					if (Bullet[j].Pos.x + CharacterData.Speed > 1920 || Bullet[j].Pos.y + CharacterData.Speed < 0) {
						Bullet[j].Pos.y = Charater.Pos.y;
						Bullet[j].Pos.x = Gun.Pos.x + Gun.rect.right / 6;
						CharacterData.RidenSpeed[j] = Riden - 30;
						Bullet[j + 1].Pos.y = Charater.Pos.y;
						Bullet[j + 1].Pos.x = Gun.Pos.x + Gun.rect.right / 3;
						CharacterData.RidenSpeed[j + 1] = Riden;
						Bullet[j + 2].Pos.y = Charater.Pos.y;
						Bullet[j + 2].Pos.x = Gun.Pos.x + Gun.rect.right / 3;
						CharacterData.RidenSpeed[j + 2] = Riden + 30;
						break;
					}
				}
			}
			Bullet[i].Pos.x += CharacterData.Speed * cosf(D3DXToRadian(CharacterData.RidenSpeed[i]));
			Bullet[i].Pos.y += CharacterData.Speed * sinf(D3DXToRadian(CharacterData.RidenSpeed[i]));
		}
	}
	PhysicsBullet(CharacterPosData);
	return;
}

VOID Animation::SetPos(Image *CharacterPos)
{
	Enemy = new Image;
	*Enemy = *CharacterPos;
	return VOID();
}


Image Animation::ReturnCharacter()
{
	return Charater;
}

Image Animation::ReturnBullet(int num)
{
	return Bullet[num];
}

Move Animation::ReturnMove()
{
	return ObjectMove;
}

INT Animation::HpReturn()
{
	return CharacterData.Hp;
}

VOID Animation::AnimationInit(CharacterCheck Character)
{
	CharacterList = Character;
	switch (CharacterList)
	{
	case CharacterCheck::Player:
		CharacterData.Hp = 3;
		break;
	case CharacterCheck::Enemy1:
		CharacterData.Hp = 1;
		break;
	}
	CharacterData.Speed = 10;
	OldTime = clock();
	SpaceNum = 0;
	Index = 20;
	ObjectMove = Left;
	JumpCount = 1;
	Gun.name = L"Gun.png";
	Gun.rect = { 0,0,100,41 };
	return VOID();
}


