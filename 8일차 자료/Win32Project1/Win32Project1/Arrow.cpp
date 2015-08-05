#include "Arrow.h"
#include "App.h"
#include "GameScene.h"
CArrow::CArrow()
{
	ani = new CAnimation(10.0f);
	PushScene(ani);

	ani->pushSprite("Resource/arrow/1.png");
	ani->pushSprite("Resource/arrow/2.png");
	ani->pushSprite("Resource/arrow/3.png");
	ani->pushSprite("Resource/arrow/2.png");

	float degreeRand = (float)(rand() % 60 + 60);

	this->rot = degreeRand / 180.0f * D3DX_PI;
	this->rotatingCenter = D3DXVECTOR2(ani->width - 7, ani->height / 2);

	speed = rand() % 300 + 150;
}


CArrow::~CArrow()
{
}

void CArrow::Update(float eTime)
{
	IScene::Update(eTime);
	CGameScene * gs = (CGameScene*)this->parent;
	CPlayer *player = gs->m_pPlayer;

	//this->rot = atan2((player->pos.y + player->normalAni->height / 2) - (this->pos.y + this->rotatingCenter.y), (player->pos.x + player->normalAni->width / 2) - (this->pos.x + this->rotatingCenter.x));

	pos.x += cos(rot) * speed * eTime;
	pos.y += sin(rot) * speed * eTime;

	if (pos.y > App::HEIGHT + ani->width){
		this->parent->PopScene(this);
		return;
	}

	RECT arrowRect;
	arrowRect.left = pos.x + this->rotatingCenter.x - 1;
	arrowRect.right = pos.x + this->rotatingCenter.x + 1;
	arrowRect.top = pos.y + this->rotatingCenter.y - 1;
	arrowRect.bottom = pos.y + this->rotatingCenter.y + 1;

	RECT playerRect;
	playerRect.left = player->pos.x + 10;
	playerRect.top = player->pos.y + 10;
	playerRect.right = player->pos.x + player->normalAni->width - 10;
	playerRect.bottom = player->pos.y + player->normalAni->height - 10;

	RECT tmpRect;
	if (IntersectRect(&tmpRect, &arrowRect, &playerRect))
	{
		gs->PushEffect(pos.x + this->rotatingCenter.x, pos.y + this->rotatingCenter.y);
		this->parent->PopScene(this);
		return;
	}

}

void CArrow::Render()
{
	IScene::Render();
	ani->Render();
}