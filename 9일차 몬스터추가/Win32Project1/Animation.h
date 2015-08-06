#pragma once
#include "Sprite.h"
#include <vector>
using namespace std;

class CAnimation : public IScene
{
public:
	CAnimation(float speed);
	~CAnimation();

	vector<CSprite*> animate;

	float frame, frameSpeed;
	int maxFrame;

	float width, height;
	DWORD color;

	void pushSprite(char *path);
public:
	virtual void Update(float eTime);
	virtual void Render();
};