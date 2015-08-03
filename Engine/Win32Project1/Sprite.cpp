#include "Sprite.h"
#include "App.h"
#include <atltypes.h>
CSprite::CSprite(char* path)
{
	
	color = D3DCOLOR_ARGB(255, 255, 255, 255);

	pTexture = App::GetInstance()->g_pResourceManager->LoadTexture(path);

	D3DSURFACE_DESC desc;
	pTexture->GetLevelDesc(0, &desc);
	width = (float)desc.Width;
	height = (float)desc.Height;

	rect = CRect(0, 0, (int)width, (int)height);

	RenderState = 0;
}

CSprite::~CSprite()
{
}

void CSprite::Render()
{
	IScene::Render();
	App::GetInstance()->g_pSprite->SetTransform(&mat);
	App::GetInstance()->g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	if (RenderState == 1)
	{
		App::g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		App::g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		App::g_pd3dDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	}

	App::GetInstance()->g_pSprite->Draw(pTexture, &rect, NULL, NULL, color);
	App::GetInstance()->g_pSprite->End();
}

void CSprite::Update(float eTime)
{
	IScene::Update(eTime);
}