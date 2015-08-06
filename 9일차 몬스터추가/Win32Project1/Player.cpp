#include "Player.h"

CPlayer::CPlayer()
	:moving(false), left(false)
{
	normalAni = new CAnimation(5.0f);
	this->PushScene(normalAni);
	normalAni->pushSprite("resource/player/stand.png");

	moveAni = new CAnimation(7.0f);
	this->PushScene(moveAni);
	for (int i = 0; i < 7; i++)
	{
		char path[7][100];
		sprintf_s(path[i], 100, "resource/player/walking%d.png", i + 1);
		moveAni->pushSprite(path[i]);
	}

	this->scalingCenter = D3DXVECTOR2(normalAni->width / 2, normalAni->height / 2);
}

CPlayer::~CPlayer(){}

void CPlayer::Update(float eTime)
{
	IScene::Update(eTime);
}

void CPlayer::Render()
{
	IScene::Render();

	if (left)
	{
		this->scale.x = -1.0f;
	}
	else
	{
		this->scale.x = 1.0f;
	}

	if (moving)
	{
		moveAni->Render();
		moving = false;
	}
	else
	{
		normalAni->Render();
	}
}

void CPlayer::Move(float dx)
{
	left = (bool)(dx <= 0);
	this->pos.x += dx;
	moving = true;
}
