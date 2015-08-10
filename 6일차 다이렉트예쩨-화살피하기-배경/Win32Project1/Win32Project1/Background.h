#pragma once
#include "Sprite.h"
class CBackground : public IScene
{
private:
	float time;
public:
	CBackground();
	virtual ~CBackground();

	virtual void Update(float eTime);
	virtual void Render();

	CSprite *bg;
	CSprite *star;
};