#include <iostream>
#include <Windows.h>
#include "App.h"
using namespace std;
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#pragma comment(lib, "d3dx9")
#pragma comment(lib, "d3d9")

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	App::Initialize(hInstance, nCmdShow, "프로젝트 이름");
	App::DoLoop();
	App::Destroy();
	return 0;
}