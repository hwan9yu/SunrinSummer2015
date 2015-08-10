#include "InputManager.h"
#include "App.h"

CInputManager::CInputManager()
{
	memset(lkey,false,sizeof(lkey));
	memset(rkey,false,sizeof(rkey));
}

CInputManager::~CInputManager()
{

}

void CInputManager::getKey()
{
	for(int i=0; i<256; i++)
	{
		lkey[i]=rkey[i];
		rkey[i]=bool(GetKeyState(i)&0x8000);
	}
}

D3DXVECTOR2 CInputManager::getPoint()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(App::GetInstance()->hWnd,&pt);

	return D3DXVECTOR2(pt.x,pt.y);
}

int CInputManager::keyState(int key)
{
	if(lkey[key] && rkey[key]) return 2;
	if(!lkey[key] && rkey[key]) return 1;
	if(lkey[key] && !rkey[key]) return -1;
	return 0;
}

bool CInputManager::anyKey()
{
	bool aKey = false;
	for (int i = 0; i < 255; i++)
	{
		if (i == 12) continue;
		if (this->keyState(i) > 0)
		{
			aKey = true;
		}
	}

	return aKey;
}