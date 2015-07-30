#pragma once
#include "IObject.h"
class CDirector : public IObject
{
private:
	IObject *m_pScene;
public:
	CDirector(IObject *scene);
	virtual ~CDirector();

	virtual void Input();
	virtual void Update();
	virtual void Render();
	virtual void Clear();

	void ChangeScene(IObject *p);
	bool game;
};

