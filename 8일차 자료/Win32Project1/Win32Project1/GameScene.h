#pragma once
#include "Animation.h"
#include "Background.h"
#include "Player.h"
#include "Arrow.h"
#include "ParticleSystem.h"

#include <list>
using namespace std;

class CGameScene : public IScene
{
public:
	CGameScene();
	~CGameScene();

	CBackground *m_pBackground;
	CPlayer *m_pPlayer;

	float score;
	float delay;
	float time;

	virtual void Input(float eTime);
	virtual void Update(float eTime);
	virtual void Render();

	void PushArrow(float x, float y);
	void PushEffect(float x, float y);
};
