#pragma once
#include "Animation.h"

class CGameScene : public IScene
{
public:
	CGameScene();
	~CGameScene();

	virtual void Input(float eTime);
	virtual void Update(float eTime);
	virtual void Render();

	CAnimation *graphic[1000];
};

