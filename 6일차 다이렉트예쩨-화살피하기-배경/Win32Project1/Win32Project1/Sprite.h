#pragma once
#include "IScene.h"
class CSprite :
	public IScene
{
public:
	CSprite(char *path);
	~CSprite();

	virtual void Update(float eTime);
	virtual void Render();

	LPDIRECT3DTEXTURE9 pTexture;
	RECT rect;
	DWORD color;
	float width, height;
	int RenderState;
};

