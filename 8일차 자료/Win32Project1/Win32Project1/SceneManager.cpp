#include "SceneManager.h"
#include <stdio.h>

CSceneManager::CSceneManager()
{
	nowScene = nullptr;
}


CSceneManager::~CSceneManager()
{
	if (nowScene != nullptr)
		delete nowScene;
}

void CSceneManager::Input(float eTime)
{
	if (nowScene != nullptr)
		nowScene->Input(eTime);
}

void CSceneManager::Update(float eTime)
{
	if (nowScene != nullptr)
		nowScene->Update(eTime);
}

void CSceneManager::Render()
{
	if (nowScene != nullptr)
		nowScene->Render();
}

void CSceneManager::ChangeScene(IScene *p)
{
	if (nowScene != nullptr)
		delete nowScene;

	nowScene = p;
	p->parent = this;
}