#pragma once
#include "IObject.h"
class CGameScene :
	public IObject
{
public:
	CGameScene();
	virtual ~CGameScene();

	virtual void Input();
	virtual void Update();
	virtual void Render();
	virtual void Clear();
};