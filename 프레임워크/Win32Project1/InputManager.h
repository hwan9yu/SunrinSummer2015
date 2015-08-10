#pragma once
#include <d3dx9.h>

class CInputManager
{
public:
	CInputManager();
	~CInputManager();

	bool lkey[256], rkey[256];
public:
	
	void getKey();
	D3DXVECTOR2 getPoint();
	int keyState(int key);
	bool anyKey();
};