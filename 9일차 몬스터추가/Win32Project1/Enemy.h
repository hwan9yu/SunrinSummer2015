#pragma once
#include "Animation.h"
#include "Font.h"
class IEnemy : public IScene
{
public:
	IEnemy(int hp);
	~IEnemy();

	CFontSceneNode *font;
	int hp;
	float width, height;
	void hit();
};

class CEnemy1 : public IEnemy
{
public:
	CEnemy1();
	~CEnemy1();

	virtual void Update(float eTime);
	virtual void Render();

	CAnimation *ani;
	float time, time2;
};

