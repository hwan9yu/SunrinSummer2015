#pragma once
#include <d3dx9.h>
#include <list>
using namespace std;

class IScene;
typedef list<IScene*> LIST;

class IScene
{
public:
	D3DXMATRIX mat;
	D3DXVECTOR2 pos;
	D3DXVECTOR2 scale;
	D3DXVECTOR2 scalingCenter;
	D3DXVECTOR2 rotatingCenter;
	float rot;

	LIST children;

	IScene* parent;
public:
	IScene();
	virtual ~IScene();

	virtual void Input(float eTime);
	virtual void Update(float eTime);
	virtual void Render();

public:
	void PushScene(IScene *p);
	void PopScene(IScene *p, bool isErase = true);
	void SetPosition(float x, float y)
	{
		pos = D3DXVECTOR2(x, y);
	}
	void SetScale(float x, float y)
	{
		scale = D3DXVECTOR2(x, y);
	}
};
