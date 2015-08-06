#include "Enemy.h"
#include "GameScene.h"
#include "App.h"

IEnemy::IEnemy(int hp)
{
	this->hp = hp;
	font = new CFontSceneNode(10, 50);
	PushScene(font);

	char str[3];
	sprintf_s(str, 3, "%d", hp);
	font->setString(str);
	font->color = D3DCOLOR_ARGB(255, 255, 255, 255);

	width = height = 0;
}

IEnemy::~IEnemy()
{

}

void IEnemy::hit()
{
	hp--;
	char str[3];
	sprintf_s(str, 3, "%d", hp);
	font->setString(str);
	pos.y -= 20;
}

CEnemy1::CEnemy1() : time(0.f), time2(0.f), IEnemy(3)
{
	ani = new CAnimation(4.0f);
	PushScene(ani);
	ani->pushSprite("resource/enemy/fish1.png");
	ani->pushSprite("resource/enemy/fish2.png");

	width = ani->width;
	height = ani->height;
}


CEnemy1::~CEnemy1()
{
}

void CEnemy1::Update(float eTime)
{
	IEnemy::Update(eTime);
	CGameScene *gs = (CGameScene*)this->parent->parent;
	
	if (hp <= 0)
	{
		CParticleSystem *p = gs->PushEffect(pos.x + ani->width/2, pos.y + ani->height/2 + 55.0f);
		p->setScalep(4.0f, 5.0f);
		p->direction = -90;
		p->spread = 30;
		p->setSpeed(400.0f, 700.0f);
		p->start();
		this->parent->PopScene(this);
		return;
	}

	time += eTime;
	time2 += eTime;
	if (pos.y < 50)
	{
		pos.y += 150 * eTime;
		if (pos.y > 50) pos.y = 50;
	}

	if (time > 3.0f)
	{
		gs->PushEffect(this->pos.x+20, this->pos.y + 140);
		gs->PushArrow(this->pos.x - 65, this->pos.y + 170, D3DX_PI / 2);
		gs->PushArrow(this->pos.x - 65, this->pos.y + 170, D3DX_PI / 2 - 0.4);
		gs->PushArrow(this->pos.x - 65, this->pos.y + 170, D3DX_PI / 2 + 0.4);
		time = 0.f;
	}

	if (time2 > 7.0f)
	{
		pos.y += 700 * eTime;
	}

	if (pos.y > App::HEIGHT)
	{
		this->parent->PopScene(this);
		return;
	}

}

void CEnemy1::Render()
{
	IEnemy::Render();
	ani->Render();
	font->Render();
}