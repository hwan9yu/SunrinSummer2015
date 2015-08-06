#pragma once
#include "Animation.h"

class CPlayer : public IScene
{
private:
	bool moving, left;
public:
	CPlayer();
	~CPlayer();

	CAnimation *normalAni, *moveAni;
	// D3DXVECTOR2 colPos;

	virtual void Update(float eTime);
	virtual void Render();

	void Move(float dx);
};

