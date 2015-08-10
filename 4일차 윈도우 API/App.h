#pragma once
#include "windows.h"
#include "atlstr.h"
#include <d3dx9.h>

class App
{
private:
	static App *instance;
	static void InitWindow();					// 윈도우를 초기화
	static void FloatWindow(int nCmdShow);		// 윈도우를 띄움
	static void InitD3D();						// DX 장치설정
	static CString title;

	static const int WIDTH = 1600;
	static const int HEIGHT = 900;
public:
	App();
	~App();

	static HINSTANCE hInstance;
	static HWND hWnd;
	static LPDIRECT3D9 g_pD3D;					// 그래픽카드를 생성
	static LPDIRECT3DDEVICE9 g_pd3dDevice;		// 생성한 그래픽카드 정보를 받아서 사용할 수 있게 해주는 변수
	static LPD3DXSPRITE g_pSprite;				// 그래픽카드와 연결해서 2D이미지를 출력할 수 있게 해줌
	static D3DPRESENT_PARAMETERS d3dpp;			// 화면출력의 세부사항을 담고있음

	static int DoLoop();						// 메시지를 처리하며 무한루프
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam); // 메시지 처리 프로시저

	static void Initialize(HINSTANCE inst, int nCmdShow, CString str);
	static void Destroy();

	static App* GetInstance()
	{
		if (instance == nullptr)
			instance = new App();

		return instance;
	}
};

