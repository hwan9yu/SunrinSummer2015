#include "Func.h"
#include <Windows.h>
#include <iostream>
using namespace std;
void GotoXY(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void SetColor(int bgColor, int fontColor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), bgColor * 16 + fontColor);
}
void PrintFrame(int w, int h)
{
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (i==0 || j==0 || i==h-1 || j==w-1)
			{
				SetColor(15, 5);
				cout << "¢Æ";
			}
			else
			{
				SetColor(15, 15);
				cout << "  ";
			}
		}
		cout << endl;
	}
}