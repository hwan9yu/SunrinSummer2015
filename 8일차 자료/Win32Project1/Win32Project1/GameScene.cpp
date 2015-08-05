#include "GameScene.h"
#include "App.h"
CGameScene::CGameScene()
{
	m_pBackground = new CBackground();
	PushScene(m_pBackground);

	m_pPlayer = new CPlayer();
	PushScene(m_pPlayer);

	time = 0.0f;
	delay = 3.0f;
}

CGameScene::~CGameScene()
{

}

void CGameScene::Input(float eTime)
{
	IScene::Input(eTime);
	if (App::GetInstance()->g_pInputManager->keyState('A') > 0)
	{
		m_pPlayer->Move(-300 * eTime);
	}
	if (App::GetInstance()->g_pInputManager->keyState('D') > 0)
	{
		m_pPlayer->Move(+300 * eTime);
	}
}

void CGameScene::Update(float eTime)
{
	IScene::Update(eTime);
	time += eTime;

	if (time > delay)
	{
		time = 0.0f;
		delay = (float)(rand()%1000) / 3000.f;
		this->PushArrow(rand()%App::WIDTH, -150.0f);
	}
	
}

void CGameScene::Render()
{
	IScene::Render();
	m_pBackground->Render();

	for (auto iter = children.begin(); iter != children.end(); iter++)
	{
		if (*iter != m_pBackground)
			(*iter)->Render();
	}

}

void CGameScene::PushArrow(float x, float y)
{
	CArrow *p = new CArrow();
	p->SetPosition(x, y);
	this->PushScene(p);
}

void CGameScene::PushEffect(float x, float y)
{
	CParticleSystem *p = new CParticleSystem("resource/particle/particle.png");
	p->SetPosition(x, y);
	this->PushScene(p);
	p->start();
}
