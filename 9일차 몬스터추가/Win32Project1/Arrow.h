#pragma once
#include "Animation.h"
class CArrow : public IScene
{
public:
	CArrow();
	~CArrow();
	CAnimation *ani;
	float speed;
	virtual void Update(float eTime);
	virtual void Render();
};

