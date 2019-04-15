#pragma once

#include"Sprite.h"
#include"Item.h"


struct Data {
	INT Hp;						// ü��
	INT Speed;					// �ӵ�
	FLOAT RidenSpeed[20];		//���� ������ ����
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
	Image Charater;				//���� ĳ���� �̹���
	VOID _3DirBullet(Animation* CharacterPosData);
	BOOL _3DirCheck;
protected:
	VOID SetPos(Image *CharacterPos);
	VOID Ani(Image* newImgae);
	VOID BulletInit();
	VOID PhysicsBullet(Animation *CharacterData);
	VOID CharacterDown();
	CharacterCheck CharacterList;			// ĳ���� ����
	Move	ObjectMove;			//�����̴� ����
	clock_t OldTime;
	clock_t CurTIme;
	INT Index;					// �ִ� �Ѿ˼�
	INT SpaceNum;				// ���� ���� �Ѿ� ��
	Image Bullet[60];			// �Ѿ� �̹���
	Image *Enemy;				//�� ĳ���� �̹���
	Data CharacterData;			//ĳ���� ���� ������
	ItemData ItemDatas;			//������ ������
	INT   DistanceRange;		//��Ÿ� ����
	FLOAT PrePosX[60];			//�Ѿ� ó�� ������	
	FLOAT Riden;				//�̵��� ����
	Image Gun;					//��
};
