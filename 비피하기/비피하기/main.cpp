#include <iostream>
#include "Func.h"
#include "Director.h"
#include "MainScene.h"
#include <Windows.h>
using namespace std;

int main()
{
	CDirector *Director = new CDirector(new CMainScene());

	while (Director->game)
	{
		Director->Input();
		Director->Update();
		Director->Render();
		Sleep(33);
		Director->Clear();
	}

	delete Director;
	return 0;
}