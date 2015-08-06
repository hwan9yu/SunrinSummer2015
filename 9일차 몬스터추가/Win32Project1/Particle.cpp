#include "App.h"
#include "Particle.h"

CParticle::CParticle( char* path, D3DXVECTOR2 speed, float lifetime, float size, float rotSpeed, int a, int r, int g, int b, int RenderState )
{
	D3DSURFACE_DESC desc;
	texture = App::GetInstance()->g_pResourceManager->LoadTexture(path);
	texture->GetLevelDesc( 0, &desc );

	scalingCenter = rotatingCenter = D3DXVECTOR2(desc.Width / 2.f, desc.Height / 2.f);

	this->speed = speed;
	this->lifeTime = lifetime;
	this->a = a;
	this->r = r;
	this->g = g;
	this->b = b;
	this->RenderState = RenderState;
	this->rotSpeed = rotSpeed;
	
	scale = D3DXVECTOR2( size, size );
	nowLifeTime = 0.f;

	pos = -D3DXVECTOR2(desc.Width / 2.f, desc.Height / 2.f);
}
CParticle::~CParticle()
{
}

void CParticle::Render()
{
	if(parent==NULL) return;
	IScene::Render();

	App::GetInstance()->g_pSprite->Begin( D3DXSPRITE_ALPHABLEND );
	App::GetInstance()->g_pSprite->SetTransform(&mat);

	if( RenderState == 1 )
	{
		App::GetInstance()->g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		App::GetInstance()->g_pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );
		App::GetInstance()->g_pd3dDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
	}
	
	App::GetInstance()->g_pSprite->Draw(texture, NULL, NULL, NULL, D3DCOLOR_ARGB(a, r, g, b));
	App::GetInstance()->g_pSprite->End();
}
void CParticle::Update( float eTime )
{
	IScene::Update(eTime);
	pos += speed*eTime;
	nowLifeTime += eTime;
	rot += rotSpeed*eTime;
}