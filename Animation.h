#pragma once

#include"Sprite.h"
#include"Item.h"


struct Data {
	INT Hp;						// 체력
	INT Speed;					// 속도
	FLOAT RidenSpeed[20];		//각도 저장할 공간
};

enum CharacterCheck
{
	Player = 0, Enemy1 = 1, Enemy2
};

enum Weapon {
	Air, Ground
};

class Animation{
public:
	VOID ImageInit(LPDIRECT3DDEVICE9 g_pd3dDevice,Image*data);
	VOID LeftButton(Animation *CharacterData,Weapon weapon);
	VOID MovePlayer(Move dir);
	BOOL HpCheck;
	BOOL BulletCheck;
	VOID AnimationInit(CharacterCheck Character);
	Image ReturnCharacter();
	Image ReturnBullet(int num);
	Move ReturnMove();
	INT HpReturn();
	CHAR Test[10];	
	INT JumpCount;
	VOID SetItem();
	VOID ItemUse(Animation *EnemyAni);
	D3DXMATRIX Matrix;
	INT BulletRadin(int num);
	VOID BulletReset(int num);
	IMAGE ReturnGun();
	VOID SetRidian(FLOAT Ridain);
	Image Charater;				//메인 캐릭터 이미지
	VOID _3DirBullet(Animation* CharacterPosData);
	BOOL _3DirCheck;
protected:
	VOID SetPos(Image *CharacterPos);
	VOID Ani(Image* newImgae);
	VOID BulletInit();
	VOID PhysicsBullet(Animation *CharacterData);
	VOID CharacterDown();
	CharacterCheck CharacterList;			// 캐릭터 구분
	Move	ObjectMove;			//움직이는 방향
	clock_t OldTime;
	clock_t CurTIme;
	INT Index;					// 최대 총알수
	INT SpaceNum;				// 현재 나온 총알 수
	Image Bullet[60];			// 총알 이미지
	Image *Enemy;				//적 캐릭터 이미지
	Data CharacterData;			//캐릭터 내부 데이터
	ItemData ItemDatas;			//아이템 데이터
	INT   DistanceRange;		//사거리 변수
	FLOAT PrePosX[60];			//총알 처음 쐈을때	
	FLOAT Riden;				//이동한 각도
	Image Gun;					//총
};
