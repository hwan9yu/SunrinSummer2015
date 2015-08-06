#include "Bullet.h"


CBullet::CBullet()
{
	sprite = new CSprite("resource/bullet/bullet.png");
	PushScene(sprite);

	available = true;
}

CBullet::~CBullet()
{
}

void CBullet::Update(float eTime)
{
	IScene::Update(eTime);

	if (available == false)
	{
		this->parent->PopScene(this);
		return;
	}

	pos.y -= 500 * eTime;
	if (pos.y < -200)
		this->parent->PopScene(this);
}

void CBullet::Render()
{
	IScene::Render();
	sprite->Render();
}