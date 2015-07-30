#include "GameScene.h"
#include <iostream>
#include <Windows.h>
using namespace std;

CGameScene::CGameScene()
{
	system("cls");
	cout << "°ÔÀÓ¾À";
}
CGameScene::~CGameScene()
{
}

void CGameScene::Input()
{
	cout << "°ÔÀÓ¾À ÀÎÇ²" << endl;
}
void CGameScene::Update()
{
	cout << "°ÔÀÓ¾À ¾÷µ«" << endl;
}
void CGameScene::Render()
{
	cout << "°ÔÀÓ¾À ·£´õ" << endl;
}
void CGameScene::Clear()
{
	cout << "°ÔÀÓ¾À Å¬·Á" << endl;
}