#include "Animation.h"

CAnimation::CAnimation(float speed)
{
	maxFrame=0;
	frameSpeed=speed;
	frame=0;
	color = D3DCOLOR_ARGB(255, 255, 255, 255);
}

CAnimation::~CAnimation()
{
	for(auto iter=animate.begin(); iter!=animate.end(); iter++)
	{
		delete(*iter);
	}
	animate.clear();
}

void CAnimation::pushSprite(char *path)
{
	CSprite *p=new CSprite(path);
	animate.push_back(p);
	this->width=p->width;
	this->height=p->height;
	p->parent=this;
	maxFrame++;
}

void CAnimation::Update(float eTime)
{
	IScene::Update(eTime);
	frame+=eTime*frameSpeed;

	if((int)frame>=maxFrame)
	{
		frame=0;
	}
}

void CAnimation::Render()
{
	if(maxFrame==0) return;
	IScene::Render();
	animate[(int)frame]->color=this->color;
	animate[(int)frame]->Render();
}