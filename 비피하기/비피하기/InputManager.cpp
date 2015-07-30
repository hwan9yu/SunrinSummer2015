#include "InputManager.h"
#include <Windows.h>
bool CInputManager::lkey[256];
bool CInputManager::rkey[256];
CInputManager* CInputManager::instance = nullptr;

CInputManager::CInputManager()
{
	for (int i = 0; i < 256; i++)
	{
		lkey[i] = false;
		rkey[i] = false;
	}
}

CInputManager::~CInputManager()
{
}

void CInputManager::getKey()
{
	for (int i = 0; i < 256; i++)
	{
		lkey[i] = rkey[i];
		rkey[i] = (bool)(GetKeyState(i) & 0x8000);
	}
}

int CInputManager::keyState(int key)
{
	if (lkey[key] == true && rkey[key] == true) return 2;
	if (lkey[key] == false && rkey[key] == true) return 1;
	if (lkey[key] == true && rkey[key] == false) return -1;
	return 0;
}