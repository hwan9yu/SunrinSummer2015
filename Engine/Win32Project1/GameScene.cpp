#include "GameScene.h"
#include "App.h"
#include <stdio.h>

CGameScene::CGameScene()
{
	for (int i = 0; i < 1000; i++)
	{
		graphic[i] = new CAnimation(8.0f);
		graphic[i]->pushSprite("resource/player1.png");
		graphic[i]->pushSprite("resource/player2.png");
		graphic[i]->pushSprite("resource/player3.png");
		graphic[i]->pushSprite("resource/player4.png");
		graphic[i]->pushSprite("resource/player5.png");
		graphic[i]->pushSprite("resource/player4.png");
		graphic[i]->pushSprite("resource/player3.png");
		graphic[i]->pushSprite("resource/player2.png");

		PushScene(graphic[i]);
		graphic[i]->SetPosition(rand()%500, rand()%1000);
	}
}


CGameScene::~CGameScene()
{
}

void CGameScene::Input(float eTime)
{
	CInputManager *im = App::GetInstance()->g_pInputManager;
	if (im->keyState(VK_UP) > 0)
		pos.y -= 200 * eTime;
	if (im->keyState(VK_DOWN) > 0)
		pos.y += 200 * eTime;
	if (im->keyState(VK_LEFT) > 0)
		pos.x -= 200 * eTime;
	if (im->keyState(VK_RIGHT) > 0)
		pos.x += 200 * eTime;
}

void CGameScene::Update(float eTime)
{
	IScene::Update(eTime);
}

void CGameScene::Render()
{
	IScene::Render();
	for (int i = 0; i < 1000; i++)
		graphic[i]->Render();
}