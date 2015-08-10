#include "GameScene.h"

CGameScene::CGameScene()
{
	m_pBackground = new CBackground();
	PushScene(m_pBackground);
}

CGameScene::~CGameScene()
{

}

void CGameScene::Input(float eTime)
{
	IScene::Input(eTime);
}

void CGameScene::Update(float eTime)
{
	IScene::Update(eTime);
}

void CGameScene::Render()
{
	IScene::Render();
	m_pBackground->Render();
}