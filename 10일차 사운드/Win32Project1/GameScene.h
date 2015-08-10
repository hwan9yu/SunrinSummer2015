#pragma once
#include "Animation.h"
#include "Background.h"
#include "Player.h"
#include "ParticleSystem.h"

class CGameScene : public IScene
{
private:
	float time;
	float bulletTime;
	float delay;
public:
	CGameScene();
	~CGameScene();

	CBackground *m_pBackground;
	CPlayer *m_pPlayer;
	IScene *m_pArrowScene;
	IScene *m_pEffectScene;
	IScene *m_pEnemyScene;
	IScene *m_pBulletScene;

	virtual void Input(float eTime);
	virtual void Update(float eTime);
	virtual void Render();

	void PushArrow(float x, float y, float rot);
	CParticleSystem* PushEffect(float x, float y);
	void PushEnemy1(float x, float y);
	void PushBullet(float x, float y);
};
