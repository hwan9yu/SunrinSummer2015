
#pragma once
#include "IScene.h"


class CParticle : virtual public IScene
{
private:
	LPDIRECT3DTEXTURE9 texture;
public:

	D3DXVECTOR2 speed;
	float lifeTime;
	float nowLifeTime;
	float rotSpeed;
	int RenderState;

	int a, r, g, b;

	CParticle( char* path, D3DXVECTOR2 speed, float lifetime, float size, float rotSpeed, int a, int r, int g, int b, int RenderState );
	~CParticle();

	void Render();
	void Update( float eTime );
};