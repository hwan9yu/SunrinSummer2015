#pragma once
#include "IScene.h"
class CSceneManager : public IScene
{
public:
	CSceneManager();
	~CSceneManager();

	IScene *nowScene;
	void ChangeScene(IScene *p);

	virtual void Input(float eTime);
	virtual void Update(float eTime);
	virtual void Render();
};
