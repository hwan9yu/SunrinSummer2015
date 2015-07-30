#include "Director.h"
#include "InputManager.h"

CDirector::CDirector(IObject *scene)
	:game(true), m_pScene(nullptr)
{
	this->ChangeScene(scene);
}

CDirector::~CDirector()
{
	delete m_pScene;
	delete CInputManager::GetInstance();
}

void CDirector::Input()
{
	//CInputManager::getKey();				//이거를
	CInputManager::GetInstance()->getKey(); //이렇게
	m_pScene->Input();
}
void CDirector::Update()
{
	m_pScene->Update();
}
void CDirector::Render()
{
	m_pScene->Render();
}
void CDirector::Clear()
{
	m_pScene->Clear();
}
void CDirector::ChangeScene(IObject *p)
{
	if(m_pScene != nullptr)
		delete m_pScene;
	m_pScene = p;
	p->SetParent(this);
}