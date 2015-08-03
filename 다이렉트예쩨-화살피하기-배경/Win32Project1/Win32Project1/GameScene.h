#pragma once
#include "Animation.h"
#include "Background.h"

class CGameScene : public IScene
{
public:
	CGameScene();
	~CGameScene();

	CBackground *m_pBackground;

	virtual void Input(float eTime);
	virtual void Update(float eTime);
	virtual void Render();
};
