#pragma once
#include "Sprite.h"
class CBullet :
	public IScene
{
public:
	CBullet();
	~CBullet();

	CSprite *sprite;
	bool available;

	virtual void Update(float eTime);
	virtual void Render();

};

