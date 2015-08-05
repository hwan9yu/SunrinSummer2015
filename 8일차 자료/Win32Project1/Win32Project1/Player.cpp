#include "Player.h"
#include "App.h"

CPlayer::CPlayer()
{
	normalAni = new CAnimation(7.0f);
	moveAni = new CAnimation(7.0f);

	normalAni->pushSprite("resource/player/stand.png");
	moveAni->pushSprite("resource/player/walking1.png");
	moveAni->pushSprite("resource/player/walking2.png");
	moveAni->pushSprite("resource/player/walking3.png");
	moveAni->pushSprite("resource/player/walking4.png");
	moveAni->pushSprite("resource/player/walking5.png");
	moveAni->pushSprite("resource/player/walking6.png");
	moveAni->pushSprite("resource/player/walking7.png");

	PushScene(normalAni);
	PushScene(moveAni);

	this->scalingCenter = D3DXVECTOR2(normalAni->width / 2, normalAni->height / 2);
	this->rotatingCenter = D3DXVECTOR2(normalAni->width / 2, normalAni->height / 2);

	this->SetPosition(App::WIDTH/2 - normalAni->width/2, App::HEIGHT - normalAni->height);
}


CPlayer::~CPlayer()
{
}

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
		this->scale.x = 1.f;
	}

	if (moving)
	{
		moveAni->Render();
	}
	else
	{
		normalAni->Render();
	}
	moving = false;
}

void CPlayer::Move(float dx)
{
	moving = true;
	if (dx < 0) left = true;
	else left = false;
	
	this->pos.x += dx;
}