#include "MainScene.h"
#include "InputManager.h"
#include "Func.h"
#include "Director.h"
#include "GameScene.h"
#include <iostream>
#include <Windows.h>
using namespace std;

CMainScene::CMainScene()
	:index(0)
{
	system("cls");
	cout << "비 피하기"<<endl;
	PrintFrame(15, 10);

	GotoXY(6, 5); cout << "▶ 게임시작";
	GotoXY(6, 6); cout << "-- 게임종료";

}

CMainScene::~CMainScene()
{
}

void CMainScene::Input()
{
	if (CInputManager::GetInstance()->keyState(VK_UP) == 1)
	{
		index = 0;
		GotoXY(6, 5); cout << "▶";
		GotoXY(6, 6); cout << "--";
	}
	else if (CInputManager::GetInstance()->keyState(VK_DOWN) == 1)
	{
		index = 1;
		GotoXY(6, 5); cout << "--";
		GotoXY(6, 6); cout << "▶";
	}
	if (CInputManager::GetInstance()->keyState(VK_RETURN) == 1)
	{
		CDirector *dir = (CDirector*)this->GetParent();
		if (index == 0)
		{
			dir->ChangeScene(new CGameScene());
			return;
		}
		else
		{
			dir->game = false;
		}
	}
}
void CMainScene::Update()
{

}
void CMainScene::Render()
{

}
void CMainScene::Clear()
{

}