#include "Font.h"
#include "App.h"

CFontSceneNode::CFontSceneNode(int bufferSize, UINT size, char* fontname)
{
	string = new char[bufferSize];
	this->fontname = fontname;
	D3DXCreateFontA(App::GetInstance()->g_pd3dDevice, size, size / 2 - size / 10, FW_HEAVY, D3DX_DEFAULT, NULL, DEFAULT_CHARSET, OUT_TT_PRECIS, CLEARTYPE_QUALITY, NULL, fontname, &font);

	color=D3DCOLOR_ARGB(255,0,0,0);
}
CFontSceneNode::~CFontSceneNode()
{
	//delete( font );
	delete[] string;
}

void CFontSceneNode::Render()
{
	IScene::Render();
	App *app = App::GetInstance();
	app->g_pSprite->SetTransform(&mat);
	app->g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	font->DrawTextA(app->g_pSprite, string, len, NULL, DT_TOP | DT_LEFT | DT_NOCLIP, color);
	app->g_pSprite->End();
}
void CFontSceneNode::Update( float eTime )
{
	IScene::Update(eTime);
}

void CFontSceneNode::setString( char string[],bool autosize )
{
	strcpy_s(this->string,strlen(string)+1,string);
	if(autosize)
	{
		len=strlen(this->string);
	}
}
