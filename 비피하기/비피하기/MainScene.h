#pragma once
#include "IObject.h"
class CMainScene :
	public IObject
{
private:
	int index; //
public:
	CMainScene();
	virtual ~CMainScene();

	virtual void Input();
	virtual void Update();
	virtual void Render();
	virtual void Clear();
};

